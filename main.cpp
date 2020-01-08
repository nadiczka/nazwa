//
// Created by Nadia on 04.01.2020.
//
#include <iostream>
#include "helpers.hpp"
#include "nodes.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"

int main() {

    ProbabilityGenerator f1 = []() { return 3.14; };

    PackageQueue QL(PackageQueueType::FIFO);

    std::unique_ptr<PackageQueue> wsk(&QL);


    Worker W1(1, 2, std::make_unique<PackageQueue>(PackageQueueType::FIFO), f1);


    return EXIT_SUCCESS;
}

