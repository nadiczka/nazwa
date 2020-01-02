#include "nodes.hpp"

double ProbabilityGenerator() {
    return rand() % 1 + 0;
}

ReceiverPreferences::ReceiverPreferences(std::function<double()> rand_function = ProbabilityGenerator()){
    temporary_probability = rand_function;
}

ReceiverPreferences::add_receiver(IPackageReceiver* receiver){
    _preferences.insert(receiver, temporary_probability);
    temporary_probability = 0;
}

ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
    _preferences.erase(receiver);
}

ReceiverPreferences::choose_receiver() {
    maximum = 0;
    for (auto& i : _preferences.items()){
        if (i->second > maximum) {
            maximum = i->second
        }
    }
    for (auto& i : _preferences.items()){
        if (i->second = maximum) {
            return i->first;
        }
    }
}