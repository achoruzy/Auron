// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Logger.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Auron {

    std::shared_ptr<spdlog::logger> Logger::single_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::single_GameLogger;

    void Logger::Initialize()
    {
        // TODO: pattern per level - critical and error needs more system info
        std::vector<spdlog::sink_ptr> editor_sinks;
        editor_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        editor_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", false));

        editor_sinks[0]->set_pattern("%^[%D %T] %n | %l: %v%$");
        editor_sinks[1]->set_pattern("%^[%D %T] %n | %l: %v%$");

        single_CoreLogger = std::make_shared<spdlog::logger>("AURON", begin(editor_sinks), end(editor_sinks));
        single_GameLogger = std::make_shared<spdlog::logger>("GAME", begin(editor_sinks), end(editor_sinks));

        spdlog::register_logger(single_CoreLogger);
        spdlog::register_logger(single_GameLogger);

        single_CoreLogger->set_level(spdlog::level::trace);
		single_CoreLogger->flush_on(spdlog::level::trace);
        single_GameLogger->set_level(spdlog::level::trace);
		single_GameLogger->flush_on(spdlog::level::trace);
    }
}
