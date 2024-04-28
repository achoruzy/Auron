// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <typeinfo>

namespace Auron {
    template <typename T, typename ... TP>
    class Event
    {
    private:
        std::vector<std::function<T(TP...)>> subscribers {};
    public:
        Event() {}

        ~Event()
        {
            UnbindAll();
        }

        void operator+=(const std::function<T(TP...)>& f)
        {
            Bind(f);
        }

        void operator-=(const std::function<T(TP...)>& f)
        {
            Unbind(f);
        }

        void Bind(const std::function<T(TP...)>& f)
        {
            subscribers.push_back(f);
        }

        void Unbind(const std::function<T(TP...)>& f)
        {
            subscribers.erase(
                std::remove_if(
                    subscribers.begin(), 
                    subscribers.end(),
                    [&f](const std::function<T(TP...)>& func) 
                    {
                        return IsSubsEqual(func, f);
                    }
                ),
                subscribers.end()
            );
        }

        void UnbindAll()
        {
            subscribers.clear();
        }
    public:
        void Invoke(const TP& ... args)
        {
            // TODO: make it async or to buffer
            for (auto s : subscribers)
            {
                s(args ...);
            }
        }
    private:
        static bool IsSubsEqual(const std::function<T(TP...)>& s1, const std::function<T(TP...)>& s2) 
        {
        if (s1 && s2) 
        {
            std::cout << &s1 << " - " << &s2 << "\n";
            // return f1.target_type() == f2.target_type() && 
            //     f1.target<T(TP...)>() == f2.target<T(TP...)>();
            return &s1 == &s2;
        }
        return false;
        }
    };
}

#define EVENT(r_type, ...) ::Auron::Event<r_type, __VA_ARGS__>()