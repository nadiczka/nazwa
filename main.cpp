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

    PackageQueue QL(PackageQueueType::FIFO);

    Worker W1(1, 2, std::make_unique<PackageQueue>(PackageQueueType::FIFO));


    return EXIT_SUCCESS;
}

