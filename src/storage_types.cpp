#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType QueueType): _QueueType(QueueType) {}

void PackageQueue::push(Package &&elem) {
    _list.push_back(elem);
}

bool PackageQueue::empty() const {
    return _list.empty();
}

size_t PackageQueue::size() const {
    return _list.size();
}

Package PackageQueue::pop() {
    switch (get_queue_type()) {
        case PackageQueueType::FIFO:
            return std::move(_list.front());
            break;
        case PackageQueueType::LIFO:
            return std::move(_list.back());
            break;
    }
}
