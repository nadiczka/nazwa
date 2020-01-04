#include "nodes.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <random>
#include <map>

std::random_device rd;
std::mt19937 rng(rd());

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator pg) {
    temporary_probability = pg;
}

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver){
    preferences_.insert(receiver, temporary_probability);
    temporary_probability = 0;
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
    preferences_.erase(receiver);
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    int maximum = 0;
    for (auto& i : preferences_.items()){
        if (i->second > maximum) {
            maximum = i->second
        }
    }
    for (auto& i : preferences_.items()){
        if (i->second = maximum) {
            return i->first;
        }
    }
}

// Packagesender zle
void PackageSender::send_package()
{
    std::srand(std::time(nullptr));
    double random = rand() / RAND_MAX;
    auto receiver = receiver_preferences_(random);
    Package package = sending_buffer.back();
    sending_buffer.pop_back();

}

Package* PackageSender::get_sending_buffer()const
{

}

void push_package(Package&& package)
{

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