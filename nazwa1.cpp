
enum class PackageQueueType {
    FIFO, LIFO
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