package selectiverepeatarq.nodes;

import selectiverepeatarq.protocol.ARQProtocol;

module SlaveNode
{
    parameters:
        int address;  // Unique address for this slave
        @display("i=misc/node;b=40,40;bgb=100,104");  // Different icon from primary

    gates:
        input in[3];  // Single input gate
        output out[3];  // Single output gate
        input inForm;

    submodules:
        arqProtocol: ARQProtocol {
            parameters:
                address = default(0);
                windowSize = default(1);  // Slaves typically need smaller windows
        }

    connections:
        inForm --> arqProtocol.inFromGen;
        in[address] --> arqProtocol.in[address];
        arqProtocol.out[address] --> out[address];
}
