#pragma once

#include <string>
#include <vector>
#include <functional>
#include <imgui.h>

namespace Auron {

class CommandConsole {
public:
    CommandConsole();
    ~CommandConsole();

    void Draw();
    void AddCommand(const std::string& name, std::function<void(const std::vector<std::string>&)> callback);
    void ClearLog();
    void AddLog(const char* fmt, ...);
    void ExecuteCommand(const std::string& command);
    int TextEditCallback(ImGuiInputTextCallbackData* data);

private:
    bool m_showConsole;
    char m_inputBuffer[256];
    std::vector<std::string> m_history;
    int m_historyPos;
    std::vector<std::string> m_log;
    std::vector<std::pair<std::string, std::function<void(const std::vector<std::string>&)>>> m_commands;
    
    void DrawConsoleButton();
    void DrawConsoleWindow();
    void ProcessCommand(const std::string& command);
    void ScrollToBottom();
};

} // namespace Auron 