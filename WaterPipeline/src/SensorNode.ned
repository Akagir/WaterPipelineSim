package waterpipeline;

simple SensorNode
{
    parameters:
        double reportInterval @unit(s) = default(10s);
    gates:
        input leakIn;
        output out;
}