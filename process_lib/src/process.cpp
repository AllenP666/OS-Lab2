#include "process.h"
#include <iostream>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

#ifdef _WIN32

Process::Process(const std::string& path, const std::vector<std::string>& args) {
    std::string command = "\"" + path + "\"";
    for (const auto& arg : args) {
        command += " " + arg;
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(NULL, &command[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        throw std::runtime_error("Failed to create process. Error code: " + std::to_string(GetLastError()));
    }

    this->process_handle_ = pi.hProcess;
    CloseHandle(pi.hThread);
}

Process::~Process() {
    if (this->process_handle_) {
        CloseHandle(this->process_handle_);
    }
}

void Process::wait() {
    if (this->process_handle_) {
        WaitForSingleObject(this->process_handle_, INFINITE);

        DWORD exit_code_dw;
        if (GetExitCodeProcess(this->process_handle_, &exit_code_dw)) {
            this->exit_code_ = static_cast<int>(exit_code_dw);
        }
    }
}

#else

Process::Process(const std::string& path, const std::vector<std::string>& args) {
    pid_t pid = fork();

    if (pid < 0) {
        throw std::runtime_error("fork() failed");
    }

    if (pid == 0) {
        std::vector<char*> argv;
        argv.push_back(const_cast<char*>(path.c_str()));
        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);

        execvp(argv[0], argv.data());

        perror("execvp failed");
        exit(127);
    } else {
        this->pid_ = pid;
    }
}

Process::~Process() {}

void Process::wait() {
    if (this->pid_ > 0) {
        int status;
        waitpid(this->pid_, &status, 0);

        if (WIFEXITED(status)) {
            this->exit_code_ = WEXITSTATUS(status);
        }
    }
}

#endif

int Process::getExitCode() {
    return this->exit_code_;
}
