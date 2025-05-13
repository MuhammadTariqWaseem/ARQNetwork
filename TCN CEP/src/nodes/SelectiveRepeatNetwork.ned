package selectiverepeatarq.nodes;
import selectiverepeatarq.traffic.TrafficGenerator;
network SelectiveRepeatNetwork
{
    types:
        channel WiredLine extends ned.DatarateChannel {
            delay = 10ms;
            datarate = 1Mbps;
        }
    submodules:
        trafficGen: TrafficGenerator {
            parameters:
                packetRate = exponential(5);  // Removed unit here
//                destAddresses = [1, 2, 3];
            @display("p=300,50");  // Position at top center
        }
        primary: PrimaryNode {
            parameters:
                address = 0;
            @display("p=300,150");  // Center
        }
        slave1: SlaveNode { 
            address = 1; 
            @display("p=150,250");  // Left
        }
        slave2: SlaveNode { 
            address = 2; 
            @display("p=300,250");  // Middle
        }
        
        slave3: SlaveNode { 
            address = 3; 
            @display("p=450,250");  // Middle
        }

    connections allowunconnected:
        // TrafficGen → Primary (MUST match PrimaryNode's input gate)
        trafficGen.out --> WiredLine --> primary.inFromGen;  // or primary.in[0] if no inFromGen

        // Primary → Slaves (downlink)
        primary.out[0] --> WiredLine --> slave1.in[0];
        primary.out[1] --> WiredLine --> slave2.in[1];
        primary.out[2] --> WiredLine --> slave3.in[2];

        // Slaves → Primary (uplink)
        slave1.out[0] --> WiredLine --> primary.in[0];
        slave2.out[1] --> WiredLine --> primary.in[1];
        slave3.out[2] --> WiredLine --> primary.in[2];
}
