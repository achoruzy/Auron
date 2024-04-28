// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <functional>
#include <string>

namespace Auron {
    template <typename ... TP>
    class Subscriber
    {
    private:
        std::function<void(TP...)> func;
        std::string name;

    public:
        Subscriber(const std::function<void(TP...)>& sub, const std::string subName)
        {
            func = sub;
            name = subName;
        }
        ~Subscriber() {}
        const bool operator==(const Subscriber<TP...>& other) const { return this->GetName() == other.GetName(); }
        void operator()(TP... args) { Call(args...); }
        void Call(TP... args) { func(args...); }
        const std::string GetName() const { return name; }
    };
}