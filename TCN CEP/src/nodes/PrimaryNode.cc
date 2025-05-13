#include <omnetpp.h>
#include <map>
#include <string>
#include "../protocol/messages/ARQFrame_m.h"

using namespace omnetpp;

class PrimaryNode : public cSimpleModule  // Changed from SimpleModule to cSimpleModule
{
private:
    int windowSize;
    int nextSeqNum = 0;
    int base = 0;
    std::map<int, bool> acked;
    std::map<int, cMessage*> timers;
    std::map<int, int> destMap; // Maps seqNum to destination address

protected:
    virtual void initialize() override {
        windowSize = par("windowSize");
    }

    virtual void handleMessage(cMessage *msg) override {  // Changed message to cMessage
        // Handle incoming frames from TrafficGenerator
        if (msg->getArrivalGateId() == gate("inFromGen")->getId()) {
            ARQFrame *frame = check_and_cast<ARQFrame*>(msg);  // Changed Frame to ARQFrame
            processNewFrame(frame);
            return;
        }

        // Handle ACKs from slaves
        if (!msg->isSelfMessage()) {
            ARQFrame *ack = check_and_cast<ARQFrame*>(msg);  // Changed Frame to ARQFrame
            if (ack->isAck()) {
                processAck(ack);
            }
            delete msg;
            return;
        }

        // Handle timeout events
        if (msg->isSelfMessage() && strncmp(msg->getName(), "timeout-", 8) == 0) {
            handleTimeout(msg);
            return;
        }
    }

    void processNewFrame(ARQFrame *frame) {  // Changed Frame to ARQFrame
        if (nextSeqNum - base >= windowSize) {
            EV << "Window full, buffering frame\n";
            delete frame;
            return;
        }

        int seqNum = nextSeqNum++;
        frame->setSeqNo(seqNum);
        destMap[seqNum] = frame->getDestAddr();

        send(frame, "out", frame->getDestAddr());
        EV << "Sent frame with seq=" << seqNum << " to " << frame->getDestAddr() << "\n";

        cMessage *timer = new cMessage(("timeout-" + std::to_string(seqNum)).c_str());
        scheduleAt(simTime() + 1.0, timer);
        timers[seqNum] = timer;
    }

    void processAck(ARQFrame *ack) {  // Changed Frame to ARQFrame
        int seqNum = ack->getSeqNo();
        EV << "Received ACK for seq=" << seqNum << "\n";

        if (timers.find(seqNum) != timers.end()) {
            cancelAndDelete(timers[seqNum]);
            timers.erase(seqNum);
        }

        acked[seqNum] = true;

        while (acked.find(base) != acked.end()) {
            acked.erase(base);
            base++;
        }
    }

    void handleTimeout(cMessage *timer) {
        std::string name = timer->getName();
        int seqNum = std::stoi(name.substr(8));

        EV << "Timeout for seq=" << seqNum << ", retransmitting\n";

        if (destMap.find(seqNum) != destMap.end()) {
            ARQFrame *frame = new ARQFrame("frame");  // Changed Frame to ARQFrame
            frame->setSeqNo(seqNum);
            frame->setDestAddr(destMap[seqNum]);
            frame->setIsAck(false);
            send(frame, "out", frame->getDestAddr());

            scheduleAt(simTime() + 1.0, timer);
        } else {
            EV << "No destination found for seq=" << seqNum << "\n";
            delete timer;
        }
    }
};

Define_Module(PrimaryNode);
