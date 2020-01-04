#ifndef SIMNET_NODES_HPP
#define SIMNET_NODES_HPP
#include <map>
#include "types.hpp"
#include "package.hpp"
#include <bits/unique_ptr.h>
#include <memory>


enum class Nodes {
    RAMP, STOREHOUSE, WORKER
};

double probability_generator();

class ReceiverPreferences {
public:
    ReceiverPreferences(std::function<double()> rand_function = ProbabilityGenerator());
    IPackageReceiver* choose_receiver();
    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
private:
    std::map<IPackageReceiver*,double> preferences_;
    double temporary_probability;
};

class PackageSender {
public:
//IPackageReceiver(ReceiverPreferences receiver_preferences);       <-- o co cho?
//no to miał byc konstruktor, zeby uzupelnic pole receiver_preferences tylko zla nazwa klasy
//wstawiam nowy:
    PackageSender(ReceiverPreferences receiver_preferences);
    void send_package();
    std::optional<Package> get_sending_buffer();
protected:
    void push_package(Package&& package);
private:
    ReceiverPreferences receiver_preferences_;
};

class IPackageReceiver {
public:
    virtual void receive_package(Package) = 0;

    virtual ElementID get_id()  = 0;
};

class Ramp: public PackageSender {
public:
    void Ramp(ElementID id, TimeOffset di);
    void deliver_goods(Time t);
    inline TimeOffset get_delivery_interval() { return delivery_interval; }
    inline ElementID get_id() const { return id; }
private:
    ElementID id;
    TimeOffset delivery_interval;
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
