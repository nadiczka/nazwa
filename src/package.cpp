#include "package.hpp"

std::set<ElementID> package::assigned_IDs;
std::set<ElementID> package::freed_IDs;
package::package()
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

package::package(package &&other)
{
    id = other.id;
    other.id = -1;
}

package::~package()
{
    if(id<0)
    {
        assigned_IDs.erase(id);
        freed_IDs.insert(id);
    }
}

package &package::operator=(package &&other)
{
    assigned_IDs.erase(id);
    freed_IDs.insert(id);
    id = other.id;
    other.id = -1;
    return *this;
}

ElementID package::get_id()
{
    return id;
}