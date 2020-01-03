#ifndef SIMNET_NODES_HPP
#define SIMNET_NODES_HPP
#include <map>
#include "types.hpp"
#include "package.hpp"


enum class Nodes {
    RAMP, STOREHOUSE, WORKER
};

double ProbabilityGenerator();

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
    void send_package();
    std::optional<Package> get_sending_buffer();
protected:
    void push_package(Package&& package);
private:
    ReceiverPreferences receiver_preferences_;
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

#endif //SIMNET_NODES_HPP
