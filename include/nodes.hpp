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
    WORKER, STORAGEHOUSE
};


class IPackageReceiver {
public:
    virtual ElementID get_id() = 0;
    virtual void receive_package(Package) = 0;
};


class ReceiverPreferences {
public:
    ReceiverPreferences(ProbabilityGenerator random_function);
    IPackageReceiver* choose_receiver();
    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
    std::map<IPackageReceiver*,double>::const_iterator cbegin() const { return preferences_.cbegin(); }
    std::map<IPackageReceiver*,double>::const_iterator cend() const { return preferences_.cend(); }
    std::map<IPackageReceiver*,double>::iterator begin() { return preferences_.begin(); }
    std::map<IPackageReceiver*,double>::const_iterator begin() const { return preferences_.cbegin(); }
    std::map<IPackageReceiver*,double>::iterator end() { return preferences_.end(); }
    std::map<IPackageReceiver*,double>::const_iterator end() const { return preferences_.cend(); }
private:
    std::map<IPackageReceiver*,double> preferences_;
    ProbabilityGenerator  rand_func;
};

class PackageSender {
public:
    PackageSender(ProbabilityGenerator PGen);
    void send_package();
    std::optional<Package> get_sending_buffer();
    ReceiverPreferences receiver_preferences_;
protected:
    void push_package(Package&& package);
    std::optional<Package> bufer ;
};

class Ramp: public PackageSender {
public:
    Ramp(ElementID id_, TimeOffset di, ProbabilityGenerator PGen);
    void deliver_goods(Time t);
    inline TimeOffset get_delivery_interval() { return delivery_interval; }
    inline ElementID get_id() const { return id; }
private:
    ElementID id;
    TimeOffset delivery_interval;
};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID );
    void receive_package(Package aPackage) override;
    inline ElementID get_id() override { return id; }
private:
    ElementID id;
    std::unique_ptr<IPackageStockpile> stockpile;
};



class Worker: public PackageSender, public IPackageReceiver {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> ptr, ProbabilityGenerator PGen);
    void do_work(Time timeWorker);
    TimeOffset get_processing_duration() const;
    Time get_package_processing_start_time() const;
    ElementID get_id() override;
    void receive_package(Package aPackage) override;
private:
    TimeOffset processing_durationWorker;
    ElementID idWorker;
    std::unique_ptr <PackageQueue> ptrWorker;
    std::optional <Package> bufor;
    Time timeWorker;
};

#endif //SIMNET_NODES_HPP
