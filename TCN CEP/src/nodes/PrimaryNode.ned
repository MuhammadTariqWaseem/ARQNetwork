package selectiverepeatarq.nodes;

import selectiverepeatarq.traffic.TrafficGenerator;
import selectiverepeatarq.protocol.ARQProtocol;

module PrimaryNode
{
    parameters:
        int address;
        @display("i=block/routing;b=60,60");

    gates:
        input inFromGen;  // Traffic generator input
        input in[3];      // From slaves (ACKs)
        output out[3];    // To slaves (data frames)

    submodules:
        arqProtocol: ARQProtocol {
            parameters:
                address = default(0);
                windowSize = default(4);
        }

    connections:
        // Traffic generator connection
        inFromGen --> arqProtocol.inFromGen;
        
        // Slave connections (indexed to avoid ambiguity)
        in[0] --> arqProtocol.in[0];
        in[1] --> arqProtocol.in[1];
        in[2] --> arqProtocol.in[2];
        
        arqProtocol.out[0] --> out[0];
        arqProtocol.out[1] --> out[1];
        arqProtocol.out[2] --> out[2];
}