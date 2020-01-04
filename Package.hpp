#ifndef NODE_PACKAGE_HPP
#define NODE_PACKAGE_HPP


#include "IPackageReceiver.hpp"

class Package {
public:
    Package();
    Package(Package&&)
    ElementID get_id();
};


#endif //NODE_PACKAGE_HPP
