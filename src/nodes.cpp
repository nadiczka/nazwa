#include "nodes.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <random>
#include <map>

std::random_device rd;
std::mt19937 rng(rd());
/*
ProbabilityGenerator pg {
    return std::generate_canonical<double, 10>(rng);
}

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator pg){
    temporary_probability = pg;
}
 */ // <------------------ to jest zle mocno

/*
void ReceiverPreferences::add_receiver(IPackageReceiver* receiver){
    preferences_.insert(receiver, temporary_probability);
    temporary_probability = 0;
}*/  // <-------------------- a tu mu cos w insercie nie pasuje ale nie mam pojecia co

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

//nizej Nadii
void PackageSender::sendPackage()
{

}


// to nizej nie wiem czy ok
Package* PackageSender::get_sending_buffer()const
{
    Package* result = new Package[push_package.size()];
    for (int i = 0; i < push_package.size(); i++)
    {
        result[i] = push_package[i];
    }
    return result;
}

Ramp::Ramp(ElementID id, TimeOffset di): id(id), delivery_interval(di)
{}

void Ramp::deliver_goods(Time t)
{
    if (t == delivery_interval)
    {
        Package package;
        sendingBuffer.push_back(package);
    }
}

void Storehouse::receive_package(Package aPackage) {

}

ElementID Storehouse::get_id() {
    return this->id;
}

Storehouse::Storehouse(int id, std::unique_ptr<IPackageStockpile> d) {

}

void Worker::receive_package(Package aPackage) {

}

int Worker::get_id() {
    return 0;
}

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) {

}

void Worker::do_work(Time t) {

}

TimeOffset Worker::get_processing_duration() {
    return 0;
}

Time Worker::get_package_processing_start_time() {
    return 0;
}