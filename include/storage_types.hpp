#ifndef SIMNET_STORAGE_TYPES_HPP
#define SIMNET_STORAGE_TYPES_HPP


#include <iostream>
#include <list>
#include <deque>
#include <functional>

#include "types.hpp"
#include "package.hpp"


enum class PackageQueueType {
    FIFO, LIFO
};


class IPackageStockpile {
public:
    virtual void push(Package &&elem) = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0 ;

private:

};


class IPackageQueue : public IPackageStockpile {

public:
    virtual PackageQueueType get_queue_type() const = 0;
    virtual Package pop() = 0;
private:

};


class PackageQueue : public IPackageQueue {

public:
    PackageQueue(PackageQueueType);
    PackageQueue() = default;
    void push(Package &&elem) override;
    bool empty() const override;
    size_t size() const override;
    Package pop() override;
    inline PackageQueueType get_queue_type() const override { return _QueueType; };

private:
    PackageQueueType _QueueType;
    std::list<Package> _list;

};


#endif //SIMNET_STORAGE_TYPES_HPP
