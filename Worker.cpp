#include "Worker.hpp"

void Worker::receive_package(Package aPackage) {

}

int Worker::get_id() {
    return 0;
}

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) {

}

void Worker::do_work(Time t) {

}

TimeOffset Worker::get_processing_duration() {
    return 0;
}

Time Worker::get_package_processing_start_time() {
    return 0;
}
