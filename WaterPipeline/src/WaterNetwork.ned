package waterpipeline;

network WaterNetwork
{
    parameters:
        int numSensors = default(5);

    submodules:
        sensor[numSensors]: SensorNode;
        leakGen: LeakGenerator;
        gateway: GatewayQueue;
        server: MonitoringServer;

    connections allowunconnected:
        for i=0..numSensors-1 {
            sensor[i].out --> gateway.in++;
        }

        leakGen.out --> sensor[0].leakIn;
        gateway.out --> server.in;
}