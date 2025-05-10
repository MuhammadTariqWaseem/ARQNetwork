// ARQFrame.msg
packet ARQFrame {
    int srcAddress;
    int destAddress;
    int seqNum;
    bool isAck;
    bool isNak;
    bool lastPacket;
    char payload[1000];
}