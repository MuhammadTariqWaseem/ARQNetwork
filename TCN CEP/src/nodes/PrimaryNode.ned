
package selectiverepeatarq.nodes;

import selectiverepeatarq.traffic.TrafficGenerator;
import selectiverepeatarq.protocol.ARQProtocol;

module PrimaryNode
{
    parameters:
        int address;
        double packetRate @unit(pk/s); // Only if traffic gen is internal
        @display("i=block/routing;b=60,60");

    gates:
        input in[];  // Input gate array (for multiple slaves)
        output out[]; // Output gate array

    submodules:
        // ARQ Protocol implementation
        arqProtocol: ARQProtocol {
            parameters:
                address = default(address);
                windowSize = default(4);
                @display("p=91,52");
        }

        // Optional: Internal traffic generator
        // trafficGen: TrafficGenerator {
        //    parameters:
        //        packetRate = default(5pk/s);
        //        destAddresses = default([1,2,3]);
        // }

    connections:
        // Internal connections
        // If using internal traffic generator:
        // trafficGen.out --> arqProtocol.in;

        // External connections
        in++ --> arqProtocol.in;
        arqProtocol.out --> out++;
}
