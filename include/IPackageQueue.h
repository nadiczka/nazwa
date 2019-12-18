#ifndef SIMNET_IPACKAGEQUEUE_H
#define SIMNET_IPACKAGEQUEUE_H

#include "IPackageStockpile.h"

class IPackageQueue : public IPackageStockpile {

public:
    virtual PackageQueueType get_queue_type() const = 0;
    virtual Package pop() = 0;
private:

};


#endif //SIMNET_IPACKAGEQUEUE_H
