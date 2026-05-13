#include <omnetpp.h>
using namespace omnetpp;

class SensorNode : public cSimpleModule
{
  private:
    cMessage *reportTimer;

  protected:
    virtual void initialize() override {
        reportTimer = new cMessage("periodicReport");
        scheduleAt(simTime() + par("reportInterval"), reportTimer);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == reportTimer) {
            cPacket *pkt = new cPacket("pressureReport");
            pkt->setTimestamp(simTime());
            send(pkt, "out");

            scheduleAt(simTime() + par("reportInterval"), reportTimer);
        }
        else {
            // leak alarm received from LeakGenerator
            cPacket *alarm = new cPacket("leakAlarm");
            alarm->setTimestamp(simTime());
            send(alarm, "out");

            delete msg;
        }
    }

    virtual void finish() override {
        cancelAndDelete(reportTimer);
    }
};

Define_Module(SensorNode);