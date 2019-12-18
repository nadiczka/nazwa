//
// Created by igach on 18.12.2019.
//

#include "../include/package.hpp"

std::set<ElementID> Package::assigned_IDs;
std::set<ElementID> Package::freed_IDs;
Package::Package()
{
    if(!freed_IDs.empty()){
        id = *freed_IDs.begin();
    }
    else if(!assigned_IDs.empty()){
        id = *freed_IDs.end() + 1;
    }
    else
    {
        id = 1;
    }
assigned_IDs.insert(id);
}

Package::Package(Package &&other)
{
    id = other.id;
    other.id = -1;
}

Package::~Package()
{
    if(id<0)
    {
        assigned_IDs.erase(id);
        freed_IDs.insert(id);
    }
}

Package &Package::operator=(Package &&other)
{
    assigned_IDs.erase(id);
    freed_IDs.insert(id);
    id = other.id;
    other.id = -1;
    return *this;
}

ElementID Package::get_id()
{
    return id;
}