// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <vector>
#include <functional>

namespace Auron {
    template <typename T>
    class Event
    {
    private:
        std::vector<std::function<T>> subscribers;
    public:
        Event();
        ~Event();
        void operator+=(std::function<T> f);
        void operator-=(std::function<T> f);
        void Bind(std::function<T> f);
        void Unbind(std::function<T> f);
        void UnbindAll();
    private:
        void Invoke();
    };
}

#define EVENT(r_type, ...) ::Auron::Event(r_type(__VA_ARGS__))