#include "nodes.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <random>
#include <map>


//--------------------------------------------ReceiverPreferences------------------------------------------------------

std::random_device rd;
std::mt19937 rng(rd());

double pg() {
    return std::generate_canonical<double, 10>(rng);
}


ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator random_function) {
    rand_func = random_function;
}

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver){
    if (preferences_.empty()){
        preferences_.insert(std::make_pair(receiver, 1));
    }
    preferences_.insert(std::make_pair(receiver, rand_func));
    double sum_probabilities = 1 + rand_func;
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
    for (auto& [key, value]: preferences_) {
        sum_probabilities += value;
        if (sum_probabilities >= distributio) {
            return key;
        }
    }
}

//--------------------------------------------PackageSender------------------------------------------------------


PackageSender::PackageSender(ProbabilityGenerator PGen) {
    receiver_preferences_(PGen);
    bufer = std::nullopt;
}

void PackageSender::push_package(Package&& package)
{
    bufer.emplace(std::move(package));
}
std::optional<Package> PackageSender::get_sending_buffer()
{
    return std::move(bufer);
}

void PackageSender::send_package()
{
    if (bufer) {
        auto receiver = receiver_preferences_.choose_receiver();
        Package package = std::move(*bufer);
        receiver->receive_package(package);
    }
}


//--------------------------------------------Ramp------------------------------------------------------


Ramp::Ramp(ElementID id_, TimeOffset di, ProbabilityGenerator PGen)
{
    PackageSender(PGen);
    id = id_;
    delivery_interval = di;
}

void Ramp::deliver_goods(Time t)
{
    if (t == delivery_interval)
    {
        Package package;
        push_package(package);
    }
}


//--------------------------------------------Worker------------------------------------------------------

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> ptr, ProbabilityGenerator PGen){
    PackageSender(PGen);
    idWorker = id;
    processing_durationWorker = pd;
    ptrWorker = std::move(ptr);
}


void Worker::do_work(Time t){
    if (t == 0)
    {
        if(bufor)
        {
            push_package(std::move(*bufor));
            bufor.reset();
        }
        bufor.emplace(ptrWorker->pop());
    }
}

TimeOffset Worker::get_processing_duration() const {
    return processing_durationWorker;
}

Time Worker::get_package_processing_start_time() const {
    return timeWorker;
}

ElementID Worker::get_id() {
    return idWorker;
}

void Worker::receive_package(Package aPackage) {
    ptrWorker->push(aPackage);
}


//--------------------------------------------Storehouse------------------------------------------------------
Storehouse::Storehouse(ElementID ID) : id(ID)
{
    stockpile = std::make_unique<PackageQueue>();
}

void Storehouse::receive_package(Package aPackage) {
    stockpile->push(aPackage);
}

