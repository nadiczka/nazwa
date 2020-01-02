#include "nodes.hpp"

double ProbabilityGenerator() {
    return rand() % 1 + 0;
}

ReceiverPreferences::ReceiverPreferences(std::function<double()> rand_function = ProbabilityGenerator()){
    temporary_probability = rand_function;
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

IPackageReceiver::IPackageReceiver(ReceiverPreferences receiver_preferences){
    receiver_preferences_ = receiver_preferences;
}

IPackageReceiver::send_package{
    //I DONT KNOW... YET
};