#include <omnetpp.h>
using namespace omnetpp;

class GatewayQueue : public cSimpleModule
{
  private:
    cQueue queue;
    cMessage *serviceTimer;
    bool busy = false;

    int droppedPackets = 0;
    int receivedPackets = 0;

  protected:
    virtual void initialize() override {
        serviceTimer = new cMessage("serviceComplete");
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == serviceTimer) {
            cPacket *pkt = (cPacket *)queue.pop();
            send(pkt, "out");

            if (!queue.isEmpty()) {
                simtime_t serviceTime = exponential(1.0 / (double)par("mu"));
                scheduleAt(simTime() + serviceTime, serviceTimer);
            }
            else {
                busy = false;
            }
        }
        else {
            receivedPackets++;

            if (queue.getLength() >= par("queueLimit").intValue()) {
                droppedPackets++;
                delete msg;
                return;
            }

            queue.insert(msg);

            if (!busy) {
                busy = true;
                simtime_t serviceTime = exponential(1.0 / (double)par("mu"));
                scheduleAt(simTime() + serviceTime, serviceTimer);
            }
        }
    }

    virtual void finish() override {
        recordScalar("receivedPackets", receivedPackets);
        recordScalar("droppedPackets", droppedPackets);
        recordScalar("finalQueueLength", queue.getLength());

        cancelAndDelete(serviceTimer);
    }
};

Define_Module(GatewayQueue);