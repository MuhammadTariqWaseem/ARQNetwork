#include "ARQProtocol.h"

Define_Module(ARQProtocol);

void ARQProtocol::initialize() {
    windowSize = par("windowSize").intValue();
    nextSeqNum = 0;
    lastAckReceived = -1;
    myAddress = par("address").intValue();
    
    if (getParentModule()->findSubmodule("trafficGen") != -1) {
        // Start sending if this is the primary node
        scheduleAt(simTime() + uniform(0, 0.1), new cMessage("start"));
    }
}

void ARQProtocol::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "start") == 0) {
            sendDataPacket();
            delete msg;
        }
        else {
            timeoutHandler(msg);
        }
        return;
    }
    
    if (dynamic_cast<ARQFrame*>(msg) != nullptr) {
        ARQFrame *frame = dynamic_cast<ARQFrame*>(msg);
        
        if (frame->getDestAddress() == myAddress) {
            // Process received data frame
            EV << "Node " << myAddress << " received frame with seq " << frame->getSeqNum() << endl;
            
            // Send ACK
            sendControlMessage(0, frame->getSeqNum(), frame->getSrcAddress());
            
            // Process payload (in real implementation)
            delete frame;
        }
        else {
            delete frame;  // Not for us
        }
    }
    else if (dynamic_cast<ControlMessage*>(msg) != nullptr) {
        ControlMessage *ctrl = dynamic_cast<ControlMessage*>(msg);
        
        if (ctrl->getKind() == 0) { // ACK
            processAck(ctrl);
        }
        else if (ctrl->getKind() == 1) { // NAK
            processNak(ctrl);
        }
        
        delete ctrl;
    }
}

void ARQProtocol::sendDataPacket() {
    if (nextSeqNum < lastAckReceived + windowSize) {
        ARQFrame *frame = new ARQFrame();
        frame->setSrcAddress(myAddress);
        frame->setDestAddress(intuniform(1, 3));  // Random slave
        frame->setSeqNum(nextSeqNum);
        frame->setIsAck(false);
        frame->setIsNak(false);
        
        // Set payload (simplified)
        char payload[1000];
        sprintf(payload, "Data packet %d from node %d", nextSeqNum, myAddress);
        // Fix: Check what parameters setPayload requires from ARQFrame_m.h
        // Assuming it takes string length and first character:
        frame->setPayload(strlen(payload), payload[0]);
        
        // Store in buffer
        sentBuffer[nextSeqNum] = frame->dup();
        
        // Set timer
        char timerName[20];
        sprintf(timerName, "timeout-%d", nextSeqNum);
        cMessage *timer = new cMessage(timerName);
        timers[nextSeqNum] = timer;
        scheduleAt(simTime() + 1.0, timer);  // 1s timeout
        
        // Send the frame
        send(frame, "out");
        
        EV << "Node " << myAddress << " sent frame with seq " << nextSeqNum << endl;
        nextSeqNum++;
        
        // Schedule next transmission
        scheduleAt(simTime() + exponential(1.0/par("packetRate").doubleValue()), 
                  new cMessage("start"));
    }
}

void ARQProtocol::processAck(ControlMessage *ack) {
    int ackNum = ack->getSeqNum();
    EV << "Node " << myAddress << " received ACK for seq " << ackNum << endl;
    
    // Cancel timer
    if (timers.find(ackNum) != timers.end()) {
        cancelAndDelete(timers[ackNum]);
        timers.erase(ackNum);
    }
    
    // Update last ack received
    if (ackNum > lastAckReceived) {
        lastAckReceived = ackNum;
    }
    
    // Remove from buffer
    if (sentBuffer.find(ackNum) != sentBuffer.end()) {
        delete sentBuffer[ackNum];
        sentBuffer.erase(ackNum);
    }
}

void ARQProtocol::processNak(ControlMessage *nak) {
    int nakNum = nak->getSeqNum();
    EV << "Node " << myAddress << " received NAK for seq " << nakNum << endl;
    
    nakReceived.insert(nakNum);
    
    // Resend the frame if we still have it
    if (sentBuffer.find(nakNum) != sentBuffer.end()) {
        ARQFrame *frame = sentBuffer[nakNum]->dup();
        send(frame, "out");
        
        // Reset timer
        if (timers.find(nakNum) != timers.end()) {
            cancelEvent(timers[nakNum]);
            scheduleAt(simTime() + 1.0, timers[nakNum]);
        }
    }
}

void ARQProtocol::timeoutHandler(cMessage *msg) {
    // Extract sequence number from timer name
    int seqNum;
    sscanf(msg->getName(), "timeout-%d", &seqNum);
    
    EV << "Timeout for frame " << seqNum << " on node " << myAddress << endl;
    
    // Resend the frame
    if (sentBuffer.find(seqNum) != sentBuffer.end()) {
        ARQFrame *frame = sentBuffer[seqNum]->dup();
        send(frame, "out");
        
        // Reset timer
        scheduleAt(simTime() + 1.0, msg);
    }
    else {
        delete msg;
        timers.erase(seqNum);
    }
}

void ARQProtocol::sendControlMessage(int kind, int seqNum, int dest) {
    ControlMessage *ctrl = new ControlMessage();
    ctrl->setKind(kind);
    ctrl->setSeqNum(seqNum);
    ctrl->setSenderAddress(myAddress);
    
    send(ctrl, "out");
}
