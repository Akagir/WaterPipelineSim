package waterpipeline;

simple GatewayQueue
{
    parameters:
        double mu = default(1.0); // service rate
        int queueLimit = default(20);
    gates:
        input in[];
        output out;
}