#include "Storehouse.hpp"

void Storehouse::receive_package(Package aPackage) {

}

ElementID Storehouse::get_id() {
    return this->id;
}

Storehouse::Storehouse(int id, std::unique_ptr<IPackageStockpile> d) {

}


