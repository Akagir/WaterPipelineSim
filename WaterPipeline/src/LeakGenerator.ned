package waterpipeline;

simple LeakGenerator
{
    parameters:
        double lambda = default(0.02); // leak arrival rate
    gates:
        output out;
}