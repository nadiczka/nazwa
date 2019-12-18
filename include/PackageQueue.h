#ifndef SIMNET_PACKAGEQUEUE_H
#define SIMNET_PACKAGEQUEUE_H

#include <iostream>
#include <list>
#include <deque>
#include <functional>

#include "IPackageQueue.h"
#include "Typy.h"
#include "Package.hpp"

class PackageQueue : public IPackageQueue {

public:
    PackageQueue(PackageQueueType);

    void push(Package &&elem) override;
    bool empty() const override;
    size_t size() const override;
    Package pop() override;
    inline PackageQueueType get_queue_type() const override { return _QueueType; };

private:
    PackageQueueType _QueueType;
    std::list<Package> _list;  //po co
    std::function<Package()> _pop;  // po co

};

#endif //SIMNET_PACKAGEQUEUE_H
