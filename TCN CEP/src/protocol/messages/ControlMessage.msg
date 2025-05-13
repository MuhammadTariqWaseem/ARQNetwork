// ControlMessage.msg
message ControlMessage {
    int kind; // 0=ACK, 1=NAK, 2=Timeout
    int seqNum;
    int senderAddress;
}