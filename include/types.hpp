#ifndef SIMNET_TYPES_HPP
#define SIMNET_TYPES_HPP
#include <functional>
#include "storage_types.hpp"

using ElementID = int;

using TimeOffset = int;

using Time = int;

using ProbabilityGenerator = std::function<double()>;

/*
using container_t = typename std_container_t<Node>;

using iterator = container_t::iterator;

using const_iterator = container_t::const_iterator;
*/
#endif //SIMNET_TYPES_HPP
