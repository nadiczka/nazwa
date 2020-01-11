#include "nodes.hpp"


//--------------------------------------------ReceiverPreferences------------------------------------------------------

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver){
    if (preferences_.empty()){
        preferences_.insert(std::make_pair(receiver, 1));
    }
    double new_probability = rand_func();
    preferences_.insert(std::make_pair(receiver, new_probability));
    double sum_probabilities = 1 + new_probability;
    for (auto& [key, value]: preferences_) {
        value = value/sum_probabilities;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
    preferences_.erase(receiver);
    double sum_probabilities = 0;
    for (auto& [key, value]: preferences_) {
        sum_probabilities += value;
    }
    for (auto& [key, value]: preferences_) {
        value = value/sum_probabilities;
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double distributio = rand_func();
    double sum_probabilities = 0;
    for (auto&[key, value]: preferences_) {
        sum_probabilities += value;
        if (sum_probabilities >= distributio) {
            return key;
        }
    }

    return preferences_.begin()->first;
}

//--------------------------------------------PackageSender------------------------------------------------------


void PackageSender::push_package(Package&& package)
{
    bufer.emplace(std::move(package));
}

std::optional<Package>& PackageSender::get_sending_buffer()
{
    return bufer;
}

void PackageSender::send_package()
{
    if (bufer) {
        auto receiver = receiver_preferences_.choose_receiver();
        Package package = std::move(*bufer);
        receiver->receive_package(std::move(package));
        bufer.reset();
    }
}


//--------------------------------------------Ramp------------------------------------------------------


void Ramp::deliver_goods(Time t)
{
    if(!bufer) {
        Package package;
        push_package(std::move(package));
    }

    if (t%delivery_interval == 0)
    {
        send_package();
    }
}


//--------------------------------------------Worker------------------------------------------------------

void Worker::do_work(Time t){
    if (!(ptrWorker -> empty()) && !bufor) {
        bufor = ptrWorker -> pop();
        timePackage = t;
    }
    if(t-timePackage == processing_durationWorker-1 && bufor) {
        push_package(std::move(*bufor));
        bufor.reset();
    }

}

TimeOffset Worker::get_processing_duration() const {
    return processing_durationWorker;
}

Time Worker::get_package_processing_start_time() const {
    return timePackage;
}

void Worker::receive_package(Package&& aPackage) {
    ptrWorker->push(std::move(aPackage));
}


//--------------------------------------------Storehouse------------------------------------------------------

void Storehouse::receive_package(Package&& aPackage) {
    stockpile->push(std::move(aPackage));
}
// 39 numer
/*

//----------------------------------------------Factory------------------------------------------------------

// -----------------------dla Rampy----------------------------
void Factory::add_ramp(Ramp&& nramp) {
    ramps.push_back(nramp);
}
void Factory::remove_ramp(ElementID id);
NodeCollection<Ramp>::iterator Factory::find_ramp_by_id(ElementID id);
NodeCollection<Ramp>::const_iterator Factory::find_ramp_by_id(ElementID id) const;
NodeCollection<Ramp>::const_iterator Factory::ramp_cbegin() const;
NodeCollection<Ramp>::const_iterator Factory::ramp_cend() const;

// -----------------------dla Workera----------------------------
void Factory::add_worker(Worker&& nwork) {
    workers.push_back(nwork);
}
void Factory::remove_worker(ElementID id);
NodeCollection<Worker>::iterator Factory::find_worker_by_id(ElementID id);
NodeCollection<Worker>::const_iterator Factory::find_worker_by_id(ElementID id) const;
NodeCollection<Worker>::const_iterator Factory::worker_cbegin() const;
NodeCollection<Worker>::const_iterator Factory::worker_cend() const;

// ----------------------dla Magazynu---------------------------
void Factory::add_storehouse(Storehouse&& nstore) {
    storehouses.push_back(nstore);
}
void Factory::remove_storehouse(ElementID id);
NodeCollection<Storehouse>::iterator Factory::find_storehouse_by_id(ElementID id);
NodeCollection<Storehouse>::const_iterator Factory::find_storehouse_by_id(ElementID id) const;
NodeCollection<Storehouse>::const_iterator Factory::storehouse_cbegin() const;
NodeCollection<Storehouse>::const_iterator Factory::storehouse_cend() const;

// --------------------------ogolne-----------------------------
void Factory::remove_receiver(NodeCollection<Node>& collection , ElementID id);
bool Factory::is_consistent(void niewiemco);
void Factory::do_deliveries(Time t);
void Factory::do_package_passing(void tutezniewiem);
void Factory::do_work(Time t);

 */