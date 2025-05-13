package selectiverepeatarq.traffic;

simple TrafficGenerator {
    parameters:
        double packetRate = default(exponential(5pk/s));  // Note: unit added
        string destAddresses = default("1,2,3");
        @display("i=block/source");
    
    gates:
        output out;
}
