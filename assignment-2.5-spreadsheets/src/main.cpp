#include <memory>
#include "datahandler.hpp"

int
main(int argc, char **argv)
{
    std::unique_ptr<DataHandler> dh = std::make_unique<DataHandler>();
    dh->import_data<Course>("res/courses.csv");
    dh->import_data<Student>("res/students.csv");
    dh->import_data<equivalencies>("res/equivalencies.csv");
    dh->load_grades();
    dh->make_report();
    dh->summary();

    return 0;
}
