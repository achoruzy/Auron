#include "CommandConsole.h"
#include <algorithm>
#include <cstdarg>
#include <sstream>

namespace Auron {

CommandConsole::CommandConsole() 
    : m_showConsole(false)
    , m_historyPos(-1)
{
    m_inputBuffer[0] = 0;
    AddCommand("clear", [this](const std::vector<std::string>&) { ClearLog(); });
    AddCommand("help", [this](const std::vector<std::string>&) {
        AddLog("Available commands:");
        for (const auto& cmd : m_commands) {
            AddLog("- %s", cmd.first.c_str());
        }
    });
}

CommandConsole::~CommandConsole() {}

void CommandConsole::Draw() {
    DrawConsoleButton();
    if (m_showConsole) {
        DrawConsoleWindow();
    }
}

void CommandConsole::DrawConsoleButton() {
    ImGui::SetNextWindowPos(ImVec2(10, ImGui::GetIO().DisplaySize.y - 30));
    ImGui::SetNextWindowSize(ImVec2(100, 20));
    ImGui::Begin("Console Button", nullptr, 
        ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button(m_showConsole ? "Hide Console" : "Show Console")) {
        m_showConsole = !m_showConsole;
    }

    ImGui::End();
}

void CommandConsole::DrawConsoleWindow() {
    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y - 200));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 200));
    
    ImGui::Begin("Command Console", &m_showConsole, 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoCollapse);

    // Log display
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
    for (const auto& log : m_log) {
        ImGui::TextUnformatted(log.c_str());
    }
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();

    // Command input
    ImGui::Separator();
    bool reclaim_focus = false;
    if (ImGui::InputText("Input", m_inputBuffer, IM_ARRAYSIZE(m_inputBuffer),
        ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory,
        [](ImGuiInputTextCallbackData* data) -> int {
            CommandConsole* console = (CommandConsole*)data->UserData;
            return console->TextEditCallback(data);
        }, (void*)this)) {
        char* input_end = m_inputBuffer + strlen(m_inputBuffer);
        while (input_end > m_inputBuffer && input_end[-1] == ' ') input_end--;
        *input_end = 0;
        if (m_inputBuffer[0]) {
            ExecuteCommand(m_inputBuffer);
        }
        strcpy(m_inputBuffer, "");
        reclaim_focus = true;
    }

    ImGui::SetItemDefaultFocus();
    if (reclaim_focus) {
        ImGui::SetKeyboardFocusHere(-1);
    }

    ImGui::End();
}

void CommandConsole::AddCommand(const std::string& name, std::function<void(const std::vector<std::string>&)> callback) {
    m_commands.push_back({name, callback});
}

void CommandConsole::ClearLog() {
    m_log.clear();
}

void CommandConsole::AddLog(const char* fmt, ...) {
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf)-1] = 0;
    va_end(args);
    m_log.push_back(buf);
}

void CommandConsole::ExecuteCommand(const std::string& command) {
    AddLog("> %s", command.c_str());
    m_history.push_back(command);
    m_historyPos = -1;

    std::istringstream iss(command);
    std::vector<std::string> args{std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}};
    
    if (args.empty()) return;

    std::string cmd = args[0];
    args.erase(args.begin());

    auto it = std::find_if(m_commands.begin(), m_commands.end(),
        [&cmd](const auto& pair) { return pair.first == cmd; });

    if (it != m_commands.end()) {
        it->second(args);
    } else {
        AddLog("Unknown command: %s", cmd.c_str());
    }
}

void CommandConsole::ProcessCommand(const std::string& command) {
    ExecuteCommand(command);
}

void CommandConsole::ScrollToBottom() {
    ImGui::SetScrollHereY(1.0f);
}

int CommandConsole::TextEditCallback(ImGuiInputTextCallbackData* data) {
    switch (data->EventFlag) {
        case ImGuiInputTextFlags_CallbackHistory: {
            const int prev_history_pos = m_historyPos;
            if (data->EventKey == ImGuiKey_UpArrow) {
                if (m_historyPos == -1) {
                    m_historyPos = static_cast<int>(m_history.size()) - 1;
                } else if (m_historyPos > 0) {
                    m_historyPos--;
                }
            } else if (data->EventKey == ImGuiKey_DownArrow) {
                if (m_historyPos != -1) {
                    if (++m_historyPos >= static_cast<int>(m_history.size())) {
                        m_historyPos = -1;
                    }
                }
            }

            if (prev_history_pos != m_historyPos) {
                const char* history_str = (m_historyPos >= 0) ? m_history[m_historyPos].c_str() : "";
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, history_str);
            }
            break;
        }
        case ImGuiInputTextFlags_CallbackCompletion: {
            // Find matches
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while (word_start > data->Buf) {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';') break;
                word_start--;
            }

            // Build a list of candidates
            std::vector<std::string> candidates;
            for (const auto& cmd : m_commands) {
                if (strnicmp(cmd.first.c_str(), word_start, (int)(word_end - word_start)) == 0) {
                    candidates.push_back(cmd.first);
                }
            }

            if (candidates.empty()) {
                // No match
                AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            } else if (candidates.size() == 1) {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0].c_str());
                data->InsertChars(data->CursorPos, " ");
            } else {
                // Multiple matches. Complete as much as we can
                int match_len = (int)(word_end - word_start);
                for (;;) {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.size() && all_candidates_matches; i++) {
                        if (i == 0) {
                            c = toupper(candidates[i][match_len]);
                        } else if (c == 0 || c != toupper(candidates[i][match_len])) {
                            all_candidates_matches = false;
                        }
                    }
                    if (!all_candidates_matches) break;
                    match_len++;
                }

                if (match_len > 0) {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0].c_str(), candidates[0].c_str() + match_len);
                }

                // List matches
                AddLog("Possible matches:\n");
                for (int i = 0; i < candidates.size(); i++) {
                    AddLog("- %s\n", candidates[i].c_str());
                }
            }
            break;
        }
    }
    return 0;
}

} // namespace Auron 