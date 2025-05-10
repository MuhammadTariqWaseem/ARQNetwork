// src/protocols/ARQProtocol.h
#ifndef __ARQPROTOCOL_H__
#define __ARQPROTOCOL_H__

#include <omnetpp.h>
#include "src/protocol/messages/ARQFrame_m.h"
#include "src/protocol/messages/ControlMessage_m.h"

using namespace omnetpp;

class ARQProtocol : public cSimpleModule {
  private:
    // Window parameters
    int windowSize;
    int nextSeqNum;
    int lastAckReceived;

    // Buffers
    std::map<int, ARQFrame*> sentBuffer;
    std::set<int> nakReceived;

    // Timers
    std::map<int, cMessage*> timers;

    // Node identification
    int myAddress;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  private:
    void sendDataPacket();
    void processAck(ControlMessage *ack);
    void processNak(ControlMessage *nak);
    void timeoutHandler(cMessage *msg);
    void sendControlMessage(int kind, int seqNum, int dest);
};

#endif
