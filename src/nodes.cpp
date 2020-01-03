#include "nodes.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>

std::random_device rd;
std::mt19937 rng(rd());

double probability_generator() {
    return std::generate_canonical<double, 10>(rng);
}

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator() = probability_generator()){
    temporary_probability = ProbabilityGenerator();
}

ReceiverPreferences::add_receiver(IPackageReceiver* receiver){
    preferences_.insert(receiver, temporary_probability);
    temporary_probability = 0;
}

ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
    preferences_.erase(receiver);
}

ReceiverPreferences::choose_receiver() {
    maximum = 0;
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