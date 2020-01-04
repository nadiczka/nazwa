#ifndef NODE_IPACKAGESTOCKPILE_HPP
#define NODE_IPACKAGESTOCKPILE_HPP


#include "IPackageQueue.hpp"

class IPackageStockpile : public IPackageQueue {
    virtual void push(Package&&) = 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;
};


#endif //NODE_IPACKAGESTOCKPILE_HPP
