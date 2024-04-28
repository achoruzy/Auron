// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <vector>
#include <functional>
#include <string>
#include "Subscriber.h"

namespace Auron {
    template <typename ... TP>
    class Event
    {
    private:
        std::vector<Subscriber<TP...>*> subscribers {};
    public:
        Event() {}

        ~Event()
        {
            UnbindAll();
        }

        void operator+=(const Subscriber<TP...>& s)
        {
            Bind(s);
        }

        void operator-=(const Subscriber<TP...>& s)
        {
            Unbind(s);
        }

        void Bind(const std::function<void(TP...)>& s, const std::string name)
        {
            Subscriber<TP...>* sub = new Subscriber<TP...>(s, name);
            subscribers.push_back(sub);
        }

        void Bind(const Subscriber<TP...>& s)
        {
            subscribers.push_back(&s);
        }

        void Unbind(const std::function<void(TP...)>& s, const std::string name)
        {
            Subscriber<TP...>* unsub = new Subscriber<TP...>(s, name);
            this->Unbind(*unsub);
        }

        void Unbind(const Subscriber<TP...>& unsub)
        {
            auto it = std::find_if(
                    subscribers.begin(),
                    subscribers.end(),
                    [unsub](const Subscriber<TP...>* sub)
                    {
                        return IsSubsEqual(sub, &unsub);
                    }
                );
            delete *it;
            subscribers.erase(it);
        }

        void UnbindAll()
        {
            for (auto s : subscribers) { delete s; }
            subscribers.clear();
        }

        void Invoke(const TP& ... args)
        {
            // TODO: send to event buffer and call in specific game loop stage
            for (auto s : subscribers)
            {
                s->Call(args...);
            }
        }

    private:
        static bool IsSubsEqual(const Subscriber<TP...>* s1, const Subscriber<TP...>* s2)
        {
            if (s1 && s2) { return *s1 == *s2; }
            return false;
        }
    };
}

#define EVENT(...) ::Auron::Event<__VA_ARGS__>()