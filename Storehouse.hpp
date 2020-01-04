#ifndef NODE_STOREHOUSE_HPP
#define NODE_STOREHOUSE_HPP


#include <bits/unique_ptr.h>
#include "IPackageReceiver.hpp"
#include "IPackageStockpile.hpp"

class Storehouse : public IPackageReceiver {
public:
    Storehouse(int id, std::unique_ptr<IPackageStockpile> d);
    void receive_package(Package aPackage) override;
    ElementID get_id() override;

private:
    ElementID id;
    std::unique_ptr<IPackageStockpile> d;
};


#endif //NODE_STOREHOUSE_HPP
