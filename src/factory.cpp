//
// Created by Nadia on 17.01.2020.
//

#include "factory.hpp"
#include "types.hpp"


bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED)
        return true;
    node_colors[sender] = NodeColor::VISITED;

    if(sender->receiver_preferences_.get_preferences().empty())
        return false;

    bool has_receiver_flag = false;
    bool has_storehouse_reachable = false;
    int bad_nodes = 0;
    for(auto receiver : sender->receiver_preferences_.get_preferences()) {
        if (receiver.first->get_receiver_type() == ReceiverType::STOREHOUSE){
            has_receiver_flag = true;
            has_storehouse_reachable = true;
        }
        else{
            auto worker_ptr = dynamic_cast<Worker*>(receiver.first);
            if(worker_ptr == sender)
                continue;
            has_receiver_flag = true;
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if(node_colors[sendrecv_ptr] == NodeColor::UNVISITED)
                has_storehouse_reachable = has_reachable_storehouse(sendrecv_ptr, node_colors);
        }
        if(!has_storehouse_reachable || !has_receiver_flag)bad_nodes++;
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if(has_storehouse_reachable && has_receiver_flag && bad_nodes == 0)
        return true;
    else return false;
}


bool Factory::is_consistent() const {
    std::map<const PackageSender*, NodeColor> node_colors;
    node_colors.clear();
    for(auto& rampy: ramps) {
        Ramp *rptr = const_cast<Ramp *>(&rampy);
        node_colors.insert({dynamic_cast<PackageSender *>(rptr), NodeColor::UNVISITED});
    }
    for(auto& workerzy: workers) {
        Worker *worker_ptr = const_cast<Worker *>(&workerzy);
        node_colors.insert({dynamic_cast<PackageSender *>(worker_ptr), NodeColor::UNVISITED});
    }

    for(auto& rampy: ramps) {
        try {

            if(!has_reachable_storehouse(&rampy,node_colors))
                return false;
        } catch (std::logic_error())
        { return false; }
    }
    return true;
}

void Factory::do_deliveries(Time t) {
    for(auto& rampy: ramps)
    {
        rampy.deliver_goods(t);
    }
}

void Factory::do_package_passing() {
    for(auto& rampy: ramps)
    {
        if(rampy.get_sending_buffer().has_value())
        {
            rampy.send_package();
        }
    }
    for(auto& workerzy: workers)
    {
        if(workerzy.get_sending_buffer().has_value())
        {
            workerzy.send_package();
        }
    }
}

void Factory::do_work(Time t) {
    for(auto& workerzy: workers)
    {
        workerzy.do_work(t);
    }
}