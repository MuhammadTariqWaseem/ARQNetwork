package selectiverepeatarq.protocol;

simple ARQProtocol {
    parameters:
        int address;
        int windowSize;
    gates:
        input in;
        output out;
}