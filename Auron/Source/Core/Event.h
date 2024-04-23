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
        std::vector<std::function<T>> subscribers {};
    public:
        Event() {}

        ~Event()
        {
            UnbindAll();
        }

        void operator+=(std::function<T> f)
        {
            Bind(f);
        }

        void operator-=(std::function<T> f)
        {
            Unbind(f);
        }

        void Bind(std::function<T> f)
        {
            subscribers.push_back(f);
        }

        void Unbind(std::function<T> f)
        {
            // TODO:
        }

        void UnbindAll()
        {
            subscribers.clear();
        }
    public:
        template <typename ... TP>
        void Invoke(TP ... args)
        {
            // TODO: make it async
            for (auto f : subscribers)
            {
                f(args ...);
            }
        }
    };
}

#define EVENT(r_type, ...) ::Auron::Event<r_type(__VA_ARGS__)>()