/*
public:
    PackageQueue(PackageQueueType queue): {
        switch (queue) {
            case PackageQueueType::FIFO:
                //tu ma sie zrobic kolejka
                break;
            case PackageQueueType::LIFO:
                //tu sie tworzy stos
                break;
        }
    }

    PackageQueue pop() { return PQueue.list::pop_back() } // usuwa ostatni element
    PackageQueue pop() { return PQueue.list::pop_front() } // usuwa pierwszy element
    PackageQueue emplace_back() { return PQueue.emplace_back() } //daje element na koniec listy

private:
    std::list<ElementID> PQueue;
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
 */