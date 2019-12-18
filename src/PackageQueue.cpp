#include "PackageQueue.h"

PackageQueue::PackageQueue(QueueType queuetype)
        :_queueType(queuetype)
{
    if (queuetype == QueueType::FIFO)
    {
        _popFunction = [this]()->Package
        {
            Package result = _deque.front();
            _deque.pop_front();
            return result;
        };
    }
    else if (queuetype == QueueType::LIFO)
    {
        _popFunction = [this]()->Package
        {
            Package result = _deque.back();
            _deque.pop_back();
            return result;
        };
    }
}

void PackageQueue::push(Package package)
{
    _deque.push_back(package);
}

Package PackageQueue::pop()
{
    return _popFunction();
}

Package* PackageQueue::view()const
{
    Package * result = new Package[_deque.size()];
    for (int i = 0; i < _deque.size(); i++)
    {
        result[i] = _deque[i];
    }
    return result;
}

bool PackageQueue::empty() const
{
    return _deque.empty();
}

int PackageQueue::size() const
{
    return _deque.size();
}