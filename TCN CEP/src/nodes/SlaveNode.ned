package selectiverepeatarq.nodes;

import selectiverepeatarq.protocol.ARQProtocol;

module SlaveNode
{
    parameters:
        int address;  // Unique address for this slave
        @display("i=misc/node;b=40,40;bgb=100,104");  // Different icon from primary

    gates:
        input in;  // Single input gate
        output out;  // Single output gate

    submodules:
        arqProtocol: ARQProtocol {
            parameters:
                address = default(address);
                windowSize = default(1);  // Slaves typically need smaller windows
        }

    connections:
        in --> arqProtocol.in;
        arqProtocol.out --> out;
}
