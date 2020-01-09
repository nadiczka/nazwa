//
// Created by Nadia on 09.01.2020.
//

#ifndef SIMNET_NODES_MOCKS1_HPP
#define SIMNET_NODES_MOCKS1_HPP

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "config.hpp"

#include "nodes.hpp"

class MockReceiver : public IPackageReceiver {
public:
    MOCK_METHOD1(receive_package, void(Package&&));

    MOCK_CONST_METHOD0(begin, IPackageStockpile::const_iterator());

    MOCK_CONST_METHOD0(cbegin, IPackageStockpile::const_iterator());

    MOCK_CONST_METHOD0(end, IPackageStockpile::const_iterator());

    MOCK_CONST_METHOD0(cend, IPackageStockpile::const_iterator());

#if (defined EXERCISE_ID && EXERCISE_ID != EXERCISE_ID_NODES)
    MOCK_CONST_METHOD0(get_receiver_type, ReceiverType());
#endif

    MOCK_CONST_METHOD0(get_id, ElementID());
};

#endif //SIMNET_NODES_MOCKS1_HPP
