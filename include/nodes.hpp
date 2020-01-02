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
    std::map<IPackageReceiver*,double> _preferences;
    double temporary_probability;
};

#endif //SIMNET_NODES_HPP
