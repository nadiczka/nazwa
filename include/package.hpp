#ifndef PROJEKT_NIEGIT_PACKAGE_HPP
#define PROJEKT_NIEGIT_PACKAGE_HPP

#include <set>
#include "types.hpp"

class Package {
public:
    Package();

    Package(Package &&other);

    ~Package();
    Package &operator=(Package &&other);
    ElementID get_id();
private:
    ElementID id;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif //PROJEKT_NIEGIT_PACKAGE_HPP
