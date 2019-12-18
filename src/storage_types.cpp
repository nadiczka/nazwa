#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType QueueType): _QueueType(QueueType) {}

void PackageQueue::push(Package &&elem) {
    _list.emplace_back(std::move(elem));
}

bool PackageQueue::empty() const {
    return _list.empty();
}

size_t PackageQueue::size() const {
    return _list.size();
}

Package PackageQueue::pop(){
    switch(_QueueType){
        case PackageQueueType::FIFO:
            return std::move(_list.front());
        case PackageQueueType::LIFO:
            return std::move(_list.back());
        }
    return Package();
}

