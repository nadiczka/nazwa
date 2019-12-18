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

    void push(Package &&other) override;
    bool empty() const override;
    size_t size() const override;
    Package pop() override;
    inline ackageQueueType get_queue_type() const override { return QueueType; };

private:
    PackageQueueType QueueType; // = _queueType
    std::deque<Package> _deque;  //po co
    std::function<Package()> _popFunction;  // po co

};

#endif //SIMNET_PACKAGEQUEUE_H
