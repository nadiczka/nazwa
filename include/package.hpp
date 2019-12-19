//
// Created by igach on 18.12.2019.
//

#ifndef PROJEKT_NIEGIT_PACKAGE_HPP
#define PROJEKT_NIEGIT_PACKAGE_HPP

#include <set>

using ElementID = int;

class Package {
public:
    Package();

    Package(Package &&other);

    ~Package();

    Package &operator=(Package &&other);

    ElementID get_id();

private:
    ElementID id;
    static std::set <ElementID> assigned_IDs;
    static std::set <ElementID> freed_IDs;
};

#endif //PROJEKT_NIEGIT_PACKAGE_HPP
