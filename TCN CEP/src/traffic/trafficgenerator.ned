package selectiverepeatarq.traffic;

simple TrafficGenerator
{
    parameters:
        double packetRate @unit(pk/s);
        xml destAddresses;
        @display("i=block/source");
        
    gates:
        output out;
        
    @statistic[packetSent](
        title="Packets sent";
        source=count;
        record=vector,stats;
        interpolationmode=none;
    );
}