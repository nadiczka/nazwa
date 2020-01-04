#ifndef NODE_IPACKAGEQUEUE_HPP
#define NODE_IPACKAGEQUEUE_HPP

enum PackageQueueType
{
    LIFO,
    FIFO
};

#include "IPackageStockpile.hpp"
#include "Package.hpp"

class IPackageQueue {
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
};


#endif //NODE_IPACKAGEQUEUE_HPP
