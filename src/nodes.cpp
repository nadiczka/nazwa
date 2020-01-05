#include "nodes.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <random>
#include <map>

std::random_device rd;
std::mt19937 rng(rd());

double pg() {
    return std::generate_canonical<double, 10>(rng);
}


ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator pg) {
    ProbabilityGenerator rand_func = pg;
}

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
    int maximum = 0;
    for (auto& [key, value]: preferences_) {
        if (value > maximum) {
            maximum = value;
        }
    }
    for (auto& [key, value]: preferences_) {
        if (value = maximum) {
            return key;
        }
    }
}

PackageSender::PackageSender(ReceiverPreferences receiver_preferences) {
    receiver_preferences_ = receiver_preferences;
    bufer = std::nullopt;
}

void PackageSender::push_package(Package&& package)
{
    bufer = package;
}

Package* PackageSender::get_sending_buffer()const
{

}

void PackageSender::send_package()
{
    if (bufer) {
        auto receiver = receiver_preferences_.choose_receiver();
        Package package = get_sending_buffer();
        receiver->receivePackage(package);
    }
}






Ramp::Ramp(ElementID id, TimeOffset di): id(id), delivery_interval(di)
{}

void Ramp::deliver_goods(Time t)
{
    if (t == delivery_interval)
    {
        Package package;
        sending_buffer.push_back(package);
    }
}

void Storehouse::receive_package(Package aPackage) {

}

int IPackageReceiver::get_type() {
    return this->type;
}

ElementID Storehouse::get_id() {
    return this->id;
}

Storehouse::Storehouse(int id, std::unique_ptr<IPackageStockpile> d) {
    this->type = 2;
}

void Worker::receive_package(Package aPackage) {

}

ElementID Worker::get_id() {
    return this->id;
}

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) {
    this->type = 1;
}

void Worker::do_work(Time t) {

}

TimeOffset Worker::get_processing_duration() {
    return 0;
}

Time Worker::get_package_processing_start_time() {
    return 0;
}