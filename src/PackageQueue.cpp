#include "PackageQueue.h"

PackageQueue::PackageQueue(PackageQueueType QueueType): _QueueType(QueueType) {
    switch (QueueType) {
        case PackageQueueType::FIFO:
            _pop = [this]() -> Package {
                Package result = _list.front();
                _list.pop_front();
                return result;
            };
            break;
        case PackageQueueType::LIFO:
            _pop = [this]() -> Package {
                Package result = _list.back();
                _list.pop_back();
                return result;
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
