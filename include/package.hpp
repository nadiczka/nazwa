#ifndef PROJEKT_NIEGIT_PACKAGE_HPP
#define PROJEKT_NIEGIT_PACKAGE_HPP

#include <set>

using ElementID = int;

class package {
public:
    package();

    package(package &&other);

    ~package();
    package &operator=(package &&other);
    ElementID get_id();
private:
    ElementID id;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif //PROJEKT_NIEGIT_PACKAGE_HPP
