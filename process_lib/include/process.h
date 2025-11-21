#pragma once

#include <string>
#include <vector>

class Process {
public:
    Process(const std::string& path, const std::vector<std::string>& args = {});

    ~Process();

    void wait();

    int getExitCode();

private:
    Process(const Process&) = delete;
    Process& operator=(const Process&) = delete;

    int exit_code_ = -1;

#ifdef _WIN32
    void* process_handle_ = nullptr;
#else
    int pid_ = -1;
#endif
};
