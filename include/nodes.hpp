#ifndef SIMNET_NODES_HPP
#define SIMNET_NODES_HPP
#include <map>

enum class Nodes {
    RAMP, STOREHOUSE, WORKER
};

union Receiver {Worker worker; Storehouse storehouse;};

double ProbabilityGenerator();

class ReceiverPreferences {
public:
    ReceiverPreferences(std::function<double()> rand_function = ProbabilityGenerator());
    IPackageReceiver* choose_receiver();
private:
    std::map<Receiver*,double> _preferences;
};

#endif //SIMNET_NODES_HPP
