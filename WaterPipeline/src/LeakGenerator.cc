#include <omnetpp.h>
using namespace omnetpp;

class LeakGenerator : public cSimpleModule
{
  private:
    cMessage *leakTimer;

  protected:
    virtual void initialize() override {
        leakTimer = new cMessage("leakEvent");
        scheduleNextLeak();
    }

    void scheduleNextLeak() {
        double lambda = par("lambda");
        simtime_t nextLeakTime = exponential(1.0 / lambda);
        scheduleAt(simTime() + nextLeakTime, leakTimer);
    }

    virtual void handleMessage(cMessage *msg) override {
        send(new cMessage("leakDetected"), "out");
        scheduleNextLeak();
    }

    virtual void finish() override {
        cancelAndDelete(leakTimer);
    }
};

Define_Module(LeakGenerator);