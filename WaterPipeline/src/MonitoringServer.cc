#include <omnetpp.h>
using namespace omnetpp;

class MonitoringServer : public cSimpleModule
{
  private:
    int receivedPackets = 0;
    simtime_t totalDelay = 0;

  protected:
    virtual void handleMessage(cMessage *msg) override {
        cPacket *pkt = check_and_cast<cPacket *>(msg);

        simtime_t delay = simTime() - pkt->getTimestamp();
        totalDelay += delay;
        receivedPackets++;

        EV << "Received: " << pkt->getName()
           << " delay=" << delay << endl;

        delete pkt;
    }

    virtual void finish() override {
        recordScalar("receivedPackets", receivedPackets);

        if (receivedPackets > 0)
            recordScalar("averageDelay", totalDelay / receivedPackets);
    }
};

Define_Module(MonitoringServer);