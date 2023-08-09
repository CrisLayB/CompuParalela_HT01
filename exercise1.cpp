#include <iostream>
#include <omp.h>
#include <unistd.h>

int main(int argc, char*argv[])
{
    int thread_num = strtol(argv[1], NULL, 10);

    #pragma omp parallel num_threads(thread_num)
    {
        std::cout << "Hello World\n" << std::endl;
    }    
    
    return 0;
}