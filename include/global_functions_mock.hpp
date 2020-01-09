//
// Created by Nadia on 09.01.2020.
//

#ifndef SIMNET_GLOBAL_FUNCTIONS_MOCK1_HPP
#define SIMNET_GLOBAL_FUNCTIONS_MOCK1_HPP

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "helpers.hpp"

// -------

class IGlobalFunctionsMock {
public:
    virtual double generate_canonical() = 0;

    virtual ~IGlobalFunctionsMock() = default;
};

class GlobalFunctionsMock : public IGlobalFunctionsMock {
public:
    MOCK_METHOD0(generate_canonical, double());
};


// ----

class GlobalFunctionsFixture : public ::testing::Test {
public:
    GlobalFunctionsFixture() {
#if !(defined EXERCISE_ID && EXERCISE_ID == EXERCISE_ID_NODES)
        probability_generator = [&]() { return global_functions_mock.generate_canonical(); };
#endif
    }

    ~GlobalFunctionsFixture() override {
#if (defined EXERCISE_ID && EXERCISE_ID == EXERCISE_ID_NODES)
        //        probability_generator = []() { return 0; };
#else
        probability_generator = default_probability_generator;
#endif
    }

protected:
    GlobalFunctionsMock global_functions_mock;
};

// ----

#endif //SIMNET_GLOBAL_FUNCTIONS_MOCK1_HPP
