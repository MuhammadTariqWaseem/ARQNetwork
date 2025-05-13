package selectiverepeatarq.protocol;

simple ARQProtocol {
    parameters:
        int address;
        int windowSize;
    gates:
        input inFromGen;  // Traffic generator input
        input in[3];      // From slaves (ACKs)
        output out[3];    // To slaves (data frames)

}