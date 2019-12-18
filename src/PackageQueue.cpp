#include "PackageQueue.h"

PackageQueue::PackageQueue(PackageQueueType QueueType): _QueueType(QueueType) {
    switch (QueueType) {
        case PackageQueueType::FIFO:
            _pop = [this]() -> Package {
                Package first_elem = std::move(_list.front());
                _list.pop_front();
                return first_elem;
            };
            break;
        case PackageQueueType::LIFO:
            _pop = [this]() -> Package {
                Package last_elem = std::move(_list.back());
                _list.pop_back();
                return last_elem;
            };
            break;
    }
}

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
    return _pop();
}
