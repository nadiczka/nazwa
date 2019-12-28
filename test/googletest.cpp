/*#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"

using ::testing::Return;

TEST(PackageQueueTest, PackageQueueTest_Sequence) {
    std::list<int> l = {7, 5, 16, 8};
    PackageQueue fifo_queue(PackageQueueType FIFO);
    PackageQueue lifo_queue(PackageQueueType LIFO);
    fifo_queue.push(1)
    lifo_queue.push(1)
    EXPECT_EQ(7, fifo_queue.pop());
    EXPECT_EQ(8, lifo_queue.pop());
}*/
