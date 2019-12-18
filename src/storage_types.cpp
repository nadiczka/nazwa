#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType QueueType): _QueueType(QueueType) {
    switch (QueueType) {
        case PackageQueueType::FIFO:
            _pop = [this]() -> package {
                package first_elem = std::move(_list.front());
                _list.pop_front();
                return first_elem;
            };
            break;
        case PackageQueueType::LIFO:
            _pop = [this]() -> package {
                package last_elem = std::move(_list.back());
                _list.pop_back();
                return last_elem;
            };
            break;
    }
}

void PackageQueue::push(package &&elem) {
    _list.push_back(elem);
}

bool PackageQueue::empty() const {
    return _list.empty();
}

size_t PackageQueue::size() const {
    return _list.size();
}

package PackageQueue::pop() {
    return _pop();
}
