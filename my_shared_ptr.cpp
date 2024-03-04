#include "my_shared_ptr.h"

#include <iostream>

int main()
{
    MySharedPtr<int> obj(5);
    std::cout << "USERS:" << obj.getCount() << std::endl;

    {
        MySharedPtr<int> newobj(obj);
        std::cout << "USERS:" << obj.getCount() << std::endl;
        std::cout << "USERS:" << newobj.getCount() << std::endl;

        MySharedPtr<int> newobjmoved(std::move(obj));
        std::cout << "USERS:" << newobj.getCount() << std::endl;
    }

    std::cout << "USERS:" << obj.getCount() << std::endl;
}