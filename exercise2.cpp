#include <iostream>
#include <omp.h>
#include <unistd.h>

int main(int argc, char*argv[])
{
    int thread_num = strtol(argv[1], NULL, 10);

    #pragma omp parallel num_threads(thread_num)
    {
        int getThreadNum =  omp_get_thread_num();

        std::string message = (getThreadNum % 2 == 0) 
            ? "Saludos del hilo: " + std::to_string(getThreadNum)
            : "Feliz cumpleaños numero: " + std::to_string(omp_get_num_threads());

        std::cout << message << std::endl; 
    }
    
    return 0;
}