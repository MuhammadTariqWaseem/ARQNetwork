package selectiverepeatarq.nodes;
import selectiverepeatarq.traffic.TrafficGenerator;

network SelectiveRepeatNetwork 

{
    parameters:
        @display("bgb=600,400"); // Set network canvas size
        
    submodules:
        primary: PrimaryNode {
            address = 0;
            @display("p=300,100"); // Position primary node
        }
        
        slave1: SlaveNode {
            address = 1;
            @display("p=150,250");
        }
        
        slave2: SlaveNode {
            address = 2;
            @display("p=300,250");
        }
        
        slave3: SlaveNode {
            address = 3;
            @display("p=450,250");
        }
        
        trafficGen: TrafficGenerator {
            packetRate = exponential(10);
            destAddresses = [1,2,3];
            @display("p=300,20");
        }
    
    connections:
        // Traffic Generator to Primary
        trafficGen.out --> primary.in++ { @display("ls=black,2"); };
        
        // Primary to Slaves
        primary.out++ --> slave1.in { @display("ls=blue,2"); };
        primary.out++ --> slave2.in { @display("ls=green,2"); };
        primary.out++ --> slave3.in { @display("ls=red,2"); };
        
        // Slaves back to Primary
        slave1.out --> primary.in++ { @display("ls=blue,1,dashed"); };
        slave2.out --> primary.in++ { @display("ls=green,1,dashed"); };
        slave3.out --> primary.in++ { @display("ls=red,1,dashed"); };
}