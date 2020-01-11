#ifndef SIMNET_NODES_HPP
#define SIMNET_NODES_HPP


#include <map>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <random>
#include <memory>

#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"

enum class ReceiverType {
    WORKER, STORAGEHOUSE
};


class IPackageReceiver {
public:
    virtual ElementID get_id() const = 0;
    virtual void receive_package(Package&& p) = 0;

    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;
    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;
};


class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator random_function = probability_generator) {rand_func = random_function;}
    IPackageReceiver* choose_receiver();
    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
    inline preferences_t& get_preferences() { return preferences_;}

    inline const_iterator cbegin() const { return preferences_.cbegin(); }
    inline const_iterator cend() const { return preferences_.cend(); }
    inline const_iterator begin() const { return preferences_.cbegin(); }
    inline const_iterator end() const { return preferences_.cend(); }
private:
    std::map<IPackageReceiver*,double> preferences_;
    ProbabilityGenerator  rand_func;
};

class PackageSender {
public:
    inline PackageSender() {bufer = std::nullopt;}
    PackageSender(PackageSender&&)=default;
    void send_package();
    std::optional<Package>& get_sending_buffer();
    ReceiverPreferences receiver_preferences_;
protected:
    void push_package(Package&& package);
    std::optional<Package> bufer ;
};

class Ramp: public PackageSender {
public:

    Ramp(ElementID id_, TimeOffset di): PackageSender(), id(id_), delivery_interval(di) {}
    void deliver_goods(Time t);
    inline TimeOffset get_delivery_interval() { return delivery_interval; }
    inline ElementID get_id() const { return id; }
private:
    ElementID id;
    TimeOffset delivery_interval;
};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID ID): id(ID) {stockpile = std::make_unique<PackageQueue>();}
    Storehouse(ElementID ID, std::unique_ptr<PackageQueue> ptr = std::make_unique<PackageQueue>()) : id(ID), stockpile(std::move(ptr)) {}
    void receive_package(Package&& aPackage) override;
    inline ElementID get_id() const override { return id; };
    inline ReceiverType getReceiverType() const { return ReceiverType::STORAGEHOUSE; };

    inline IPackageStockpile::const_iterator cbegin() const override { return stockpile->cbegin();};
    inline IPackageStockpile::const_iterator cend() const override { return stockpile->cend();};
    inline IPackageStockpile::const_iterator begin() const override { return stockpile->cbegin();};
    inline IPackageStockpile::const_iterator end() const override { return stockpile->cend();};
private:
    ElementID id;
    std::unique_ptr<IPackageStockpile> stockpile;
};



class Worker: public PackageSender, public IPackageReceiver {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> ptr) : PackageSender(), processing_durationWorker(pd), idWorker(id), ptrWorker(std::move(ptr)) {bufor = std::nullopt;};
    void do_work(Time timePackage);
    TimeOffset get_processing_duration() const;
    Time get_package_processing_start_time() const;
    inline ElementID get_id() const override { return idWorker; };
    void receive_package(Package&& aPackage) override;

    inline ReceiverType getReceiverType() const { return ReceiverType::WORKER; };
    inline IPackageStockpile::const_iterator cbegin() const override { return ptrWorker->cbegin();};
    inline IPackageStockpile::const_iterator cend() const override { return ptrWorker->cend();};
    inline IPackageStockpile::const_iterator begin() const override { return ptrWorker->cbegin();};
    inline IPackageStockpile::const_iterator end() const override { return ptrWorker->cend();};

private:
    TimeOffset processing_durationWorker;
    ElementID idWorker;
    std::unique_ptr <PackageQueue> ptrWorker;
    std::optional <Package> bufor;
    Time timePackage = 0;
};
/*
class Factory: public Ramp, public Worker, public Storehouse {
public:
    // -----------------------dla Rampy----------------------------
    void add_ramp(Ramp&& nramp);
    void remove_ramp(ElementID id);
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const;
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const;
    NodeCollection<Ramp>::const_iterator ramp_cend() const;

    // -----------------------dla Workera----------------------------
    void add_worker(Worker&& nwork);
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id);
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const;
    NodeCollection<Worker>::const_iterator worker_cbegin() const;
    NodeCollection<Worker>::const_iterator worker_cend() const;

    // ----------------------dla Magazynu---------------------------
    void add_storehouse(Storehouse&& nstore);
    void remove_storehouse(ElementID id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id);
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const;
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const;
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const;

    // --------------------------ogolne-----------------------------
    void remove_receiver(NodeCollection<Node>& collection , ElementID id);
    bool is_consistent(void niewiemco);
    void do_deliveries(Time t);
    void do_package_passing(void tutezniewiem);
    void do_work(Time t);
private:
    std::list<Ramp> ramps;
    std::list<Worker> workers;
    std::list<Storehouse> storehouses;

};
*/

#endif //SIMNET_NODES_HPP
