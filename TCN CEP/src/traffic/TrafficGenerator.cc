#include <omnetpp.h>
#include "../protocol/messages/ARQFrame_m.h"

using namespace omnetpp;

class TrafficGenerator : public cSimpleModule
{
  private:
    cMessage *generatePacketEvent;
    simtime_t lastPacketTime;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void generateAndSendPacket();
};

Define_Module(TrafficGenerator);

void TrafficGenerator::initialize()
{
    generatePacketEvent = new cMessage("generatePacket");
    lastPacketTime = simTime();
    scheduleAt(simTime() + exponential(1.0/par("packetRate").doubleValue()),
              generatePacketEvent);
}

void TrafficGenerator::handleMessage(cMessage *msg)
{
    if (msg == generatePacketEvent) {
        generateAndSendPacket();
        scheduleAt(simTime() + exponential(1.0/par("packetRate").doubleValue()),
                  generatePacketEvent);
    }
    else {
        delete msg;  // Shouldn't receive other messages
    }
}

void TrafficGenerator::generateAndSendPacket()
{
    // Create new ARQ frame
    ARQFrame *frame = new ARQFrame();

    // Set destination (random from configured addresses)
    cValueArray *addresses = check_and_cast<cValueArray*>(par("destAddresses").objectValue());
    int destIndex = intuniform(0, addresses->size()-1);
    frame->setDestAddress(addresses->get(destIndex).intValue());

    // Set source (assuming 0 for primary)
    frame->setSrcAddress(0);

    // Set sequence number (not used by generator, set by ARQ protocol)
    frame->setSeqNum(-1);

    // Set payload
    char payload[1000];
    sprintf(payload, "Payload generated at %s", simTime().str().c_str());
    frame->setPayload(1000, *payload);  // Note the dereferencing of payload

    // Send the frame
    send(frame, "out");

    // Update statistics
    emit(registerSignal("packetSent"), 1);
    lastPacketTime = simTime();
}
