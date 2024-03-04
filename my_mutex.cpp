#include "my_mutex.h"

#include <iostream>
#include <vector>
#include <thread>
#include <stdlib.h>

#define NUM_THREADS 10

using namespace std::chrono_literals;

Mutex mtx;

void foo(int id)
{
    int val = rand();
    std::cout << "foo_" << id << "() sleeping for " << val << "ms" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(val % 100));

    mtx.lock();
    std::cout << "Have lock in foo_" << id << "()..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(val % 50));
    mtx.unlock();
    
    std::cout << "Released lock in foo_" << id << "()..." << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    mtx.lock();
    std::cout << "Have lock in main()..." << std::endl;

    for (size_t i = 1; i <= NUM_THREADS; i++)
    {
        threads.emplace_back(foo, i);
    }

    std::this_thread::sleep_for(3s);
    mtx.unlock();
    std::cout << "Released lock in main()..." << std::endl;

    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        threads[i].join();
    }
}