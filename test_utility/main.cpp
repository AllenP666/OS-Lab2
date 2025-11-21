#include <iostream>
#include "process.h"

int main() {
    std::string dummy_path = DUMMY_APP_PATH;

    std::cout << "[Test Utility] Launching dummy app: " << dummy_path << std::endl;

    try {
        Process dummy_process(dummy_path);

        std::cout << "[Test Utility] Waiting for dummy app to finish..." << std::endl;
        dummy_process.wait();

        int exit_code = dummy_process.getExitCode();
        std::cout << "[Test Utility] Dummy app finished with exit code: " << exit_code << std::endl;

        if (exit_code == 42) {
            std::cout << "[Test Utility] TEST PASSED!" << std::endl;
            return 0;
        } else {
            std::cout << "[Test Utility] TEST FAILED! Expected 42, got " << exit_code << std::endl;
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "[Test Utility] An error occurred: " << e.what() << std::endl;
        return 1;
    }
}
