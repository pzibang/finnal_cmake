#include "./libsub/include/mysub.h"
#include "./libadd/include/myadd.h"
#include "myplus.h"

int main(void)
{
    std::cout<<_add(5, 10)<<std::endl;
    std::cout<<_sub(5, 10)<<std::endl;
    std::cout<<_plus(5, 10)<<std::endl;
    return 0;
}