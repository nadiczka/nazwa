#ifndef NODE_WORKER_HPP
#define NODE_WORKER_HPP


#include <memory>
#include "IPackageQueue.hpp"
#include "IPackageReceiver.hpp"

#define TimeOffset int
#define Time int

class Worker: public IPackageQueue, public IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);
    void receive_package(Package aPackage) override;
    int get_id() override;
    void do_work(Time t);
    TimeOffset get_processing_duration();
    Time get_package_processing_start_time();

private:
    ElementID id;
    TimeOffset pd;
    std::unique_ptr<IPackageQueue> q;
};


#endif //NODE_WORKER_HPP
