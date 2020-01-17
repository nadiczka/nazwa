//
// Created by Nadia on 17.01.2020.
//

#ifndef SIMNET_FACTORY_HPP
#define SIMNET_FACTORY_HPP

#include <iostream>
#include <vector>
#include "types.hpp"
#include "nodes.hpp"

#include <iostream>

enum class NodeColor{
    UNVISITED, VISITED, VERIFIED
};

template <typename Node>
class NodeCollection{
public:
    //aliasy
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    //gettery
    NodeCollection<Node>::iterator find_by_id(ElementID id_) { return std::find_if(fContainer_.begin(), fContainer_.end(), [id_](const Node& x){ return id_ == elem.get_id();});}
    NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const { return std::find_if(fContainer_.cbegin(), fContainer_.cend(), [id_](const Node& x){ return id_ == elem.get_id();}); }

    NodeCollection<Node>::iterator begin(){ return fContainer_.begin(); }
    NodeCollection<Node>::iterator end(){ return fContainer_.end(); }
    NodeCollection<Node>::const_iterator begin() const{ return fContainer_.cbegin(); }
    NodeCollection<Node>::const_iterator cbegin() const{ return fContainer_.cbegin(); }
    NodeCollection<Node>::const_iterator end() const{ return fContainer_.cend(); }
    NodeCollection<Node>::const_iterator cend() const{ return fContainer_.cend(); }
    //settery
    void add(Node& node) { fContainer_.emplace_back(std::move(node));}
    void remove_by_id(ElementID id_)
    {
        auto it = find_by_id(id_);
        if(it != fContainer_.end())
            fContainer_.erase(it,++it);
    }
private:
    container_t fContainer_;
};

class Factory{
public:

    // -----------------------dla Rampy----------------------------
    void add_ramp(Ramp&& nramp) {ramps.add(nramp);}
    void remove_ramp(ElementID id){ramps.remove_by_id(id);}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramps.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return ramps.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin()const {return ramps.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend()const {return ramps.cend();}


    // -----------------------dla Workera----------------------------
    void add_worker(Worker&& nworker) {workers.add(nworker);}
    void remove_worker(ElementID id) {this -> remove_receiver(workers,id);}
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return workers.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return workers.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin()const {return workers.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend()const {return workers.cend();}


    // ----------------------dla Magazynu---------------------------
    void add_storehouse(Storehouse&& nstore) {stores.add(nstore);}
    void remove_storehouse(ElementID id) {this -> remove_receiver(stores,id);}
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {return stores.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return stores.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin()const {return stores.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend()const {return stores.cend();}

    //----------------------------ogolne----------------------------
    bool is_consistent() const;
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);
private:
    template <typename Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id){
        ReceiverType rtype = collection.begin()->get_receiver_type();
        collection.remove_by_id(id);
        if(rtype == ReceiverType::WORKER) {
            for (auto &ramp: ramps) {
                for (auto &preference: ramp.receiver_preferences_) {
                    if (preference.first->get_id() == id) {
                        ramp.receiver_preferences_.remove_receiver(preference.first);
                        break;
                    }
                }
            }
        }
        else {
            for (auto &worker: workers) {
                for (auto &preference: worker.receiver_preferences_) {
                    if (preference.first->get_id() == id) {
                        worker.receiver_preferences_.remove_receiver(preference.first);
                        break;
                    }
                }
            }
        }
    }

    NodeCollection<Ramp> ramps;
    NodeCollection<Worker> workers;
    NodeCollection<Storehouse> stores;
};

#endif //SIMNET_FACTORY_HPP
