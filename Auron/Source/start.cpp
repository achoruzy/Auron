// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Core/Auron.h"
#include "Core/Event/Event.h"
#include <iostream>

void test_func(int a)
{
    std::cout << "test " << a << "\n";
}
void test_func2(int a)
{
    std::cout << "test2 " << a << "\n";
}

int main(int argc, char** argv)
{
    auto auron = Auron::Auron();

    auron.Initialize();

    // just some testing here, cause why not
    auto ev = EVENT(int);
    ev.Bind(test_func, "test_func1");
    ev.Bind(test_func2, "test_func2");
    ev.Bind(test_func, "test_func1");
    ev.Invoke(77);
    std::cout << "====== \n";
    ev.Unbind(test_func, "test_func1");
    ev.Invoke(88);
    std::cout << "====== \n";
    ev.Unbind(test_func, "test_func1");
    ev.Invoke(99);
    std::cout << "====== \n";
    std::cout << "====== \n";
    auto ev2= new Auron::Event<int>();
    ev2->Bind(test_func, "test_func1");
    ev2->Bind(test_func2, "test_func2");
    ev2->Bind(test_func, "test_func1");
    ev2->Invoke(77);
    std::cout << "====== \n";
    ev2->Unbind(test_func, "test_func1");
    ev2->Invoke(88);
    std::cout << "====== \n";
    ev2->Unbind(test_func, "test_func1");
    ev2->Invoke(99);
    delete ev2;

    return 0;
}