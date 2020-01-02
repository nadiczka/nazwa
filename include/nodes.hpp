#ifndef SIMNET_NODES_HPP
#define SIMNET_NODES_HPP
#include <map>

enum class Nodes {
    RAMP, STOREHOUSE, WORKER
};

double ProbabilityGenerator();

class ReceiverPreferences {
public:
    ReceiverPreferences(std::function<double()> rand_function = ProbabilityGenerator());
    IPackageReceiver* choose_receiver();
    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
private:
    std::map<IPackageReceiver*,double> preferences_;
    double temporary_probability;
};

class IPackageReceiver {
public:
    IPackageReceiver(ReceiverPreferences receiver_preferences);
    void send_package();
    std::optional<Package> get_sending_buffer();
protected:
    void push_package(Package&& package);
private:
    ReceiverPreferences receiver_preferences_;
};

#endif //SIMNET_NODES_HPP
