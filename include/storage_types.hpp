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
    virtual void push(package &&elem) = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0 ;

private:

};


class IPackageQueue : public IPackageStockpile {

public:
    virtual PackageQueueType get_queue_type() const = 0;
    virtual package pop() = 0;
private:

};


class PackageQueue : public IPackageQueue {

public:
    PackageQueue(PackageQueueType);

    void push(package &&elem) override;
    bool empty() const override;
    size_t size() const override;
    package pop() override;
    inline PackageQueueType get_queue_type() const override { return _QueueType; };

private:
    PackageQueueType _QueueType;
    std::list<package> _list;  //po co
    std::function<package()> _pop;  // po co

};


#endif //SIMNET_STORAGE_TYPES_HPP
