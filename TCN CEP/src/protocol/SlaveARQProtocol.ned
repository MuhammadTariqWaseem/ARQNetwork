package selectiverepeatarq.protocol;

simple SlaveARQProtocol {
    parameters:
        int address;
        int windowSize;
    gates:
        input in;    // Single input
        output out;   // Single output
}