#include <iostream>
#include <list>

enum class PackageQueueType {
    FIFO, LIFO
};

using ElementID = int;

class PackageQueue {
public:
    PackageQueue(PackageQueueType queue): {
        switch (queue) {
            case PackageQueueType::FIFO:
                //tu nizej jakas instukcja
                std::cout << "stos" << std::endl;
                break;
            case PackageQueueType::LIFO:
                //tu tez
                std::cout << "kolejka" << std::endl;
                break;
        }
    }


    PackageQueue emplace_back() { return PackageQueue.emplace_back() } //daje element na koniec listy

private:
    std::list<ElementID> QueueType;
};

int main() {

    //przykladowy sposob uzycia:

    PackageQueueType queue = PackageQueueType::LIFO;

    switch (queue) {
        case PackageQueueType::FIFO:
            //tu nizej jakas instukcja
            std::cout << "stos" << std::endl;
            break;
        case PackageQueueType::LIFO:
            //tu tez
            std::cout << "kolejka" << std::endl;
            break;
    }
}