#ifndef SIMNET_NODES_HPP
#define SIMNET_NODES_HPP
#include <map>
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include <bits/unique_ptr.h>
#include <memory>
#include <map>
#include <functional>


enum class Nodes {
    RAMP, WORKER
};

class IPackageReceiver {
public:
    virtual void receive_package(Package) = 0;

    virtual ElementID get_id()  = 0;
};


class Storehouse : public IPackageReceiver {
public:
    Storehouse(int id, std::unique_ptr<IPackageStockpile> d);
    void receive_package(Package aPackage) override;
    ElementID get_id() override;

private:
    ElementID id;
    std::unique_ptr<IPackageStockpile> d;
};


class ReceiverPreferences {
public:
    ReceiverPreferences(ProbabilityGenerator pg);
    IPackageReceiver* choose_receiver();
    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
private:
    std::map<IPackageReceiver*,double> preferences_;
    ProbabilityGenerator temporary_probability;
};

class PackageSender {
public:
    void send_package();
    std::optional<Package> get_sending_buffer();
    ReceiverPreferences receiver_preferences_;
protected:
    void push_package(Package&& package);
    std::vector<Package> sending_buffer;
};


class Ramp: public PackageSender {
public:
    Ramp(ElementID id, TimeOffset di);
    void deliver_goods(Time t);
    inline TimeOffset get_delivery_interval() { return delivery_interval; }
    inline ElementID get_id() const { return id; }
private:
    ElementID id;
    TimeOffset delivery_interval;
};


class Worker: public IPackageQueue, public IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);
    void receive_package(Package aPackage) override;
    int get_id() override;
    void do_work(Time t);
    TimeOffset get_processing_duration();
    Time get_package_processing_start_time();

private:
    ElementID id;
    TimeOffset pd;
    std::unique_ptr<IPackageQueue> q;
};

#endif //SIMNET_NODES_HPP
