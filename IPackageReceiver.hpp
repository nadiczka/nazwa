#ifndef NODE_IPACKAGERECEIVER_HPP
#define NODE_IPACKAGERECEIVER_HPP


#include "Package.hpp"
#define ElementID int


class IPackageReceiver {
public:
    virtual void receive_package(Package) = 0;

    virtual ElementID get_id()  = 0;

};



#endif //NODE_IPACKAGERECEIVER_HPP
