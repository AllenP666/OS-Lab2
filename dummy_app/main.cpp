#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "[Dummy App] Starting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "[Dummy App] Work done. Exiting with code 42." << std::endl;
    return 42;
}
