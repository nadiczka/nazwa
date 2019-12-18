#ifndef SIMNET_IPACKAGESTOCKPILE_H
#define SIMNET_IPACKAGESTOCKPILE_H

#include "Typy.h"
#include "Package.hpp"

class IPackageStockpile {
public:
    virtual void push(Package &&elem) = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0 ;

private:

};

#endif //SIMNET_IPACKAGESTOCKPILE_H
