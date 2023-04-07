#include "LocalDateTimeTest.h"
#include "UUIDTest.h"
#include "XmlTest.h"

int main(int argc, char *argv[])
{
    std::cout<< "-------------LocalDateTimeTest-------------- "<<std::endl;
    LocalDateTimeTest();
    std::cout<< "-------------UUIDTest-------------- "<<std::endl;
    UUIDTest();
    std::cout<< "-------------XmlTest-------------- "<<std::endl;
    XmlTest();
    return 0;
}
