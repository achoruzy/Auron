// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace Auron {
    class Logger
    {
    public:
        static void Initialize();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return single_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetGameLogger() { return single_GameLogger; }
    private:
        static std::shared_ptr<spdlog::logger> single_CoreLogger;
        static std::shared_ptr<spdlog::logger> single_GameLogger;
    };
}

// Editor and game logs
#define LOG_INFO(...)          ::Auron::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...)       ::Auron::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::Auron::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::Auron::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// TODO: To remove these below and generalize logger solution for allowing creation of own loggers by client.
// Game only logs
#define LOG_GAME_INFO(...)     ::Auron::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_GAME_WARNING(...)  ::Auron::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_GAME_ERROR(...)    ::Auron::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_GAME_CRITICAL(...) ::Auron::Logger::GetCoreLogger()->critical(__VA_ARGS__)