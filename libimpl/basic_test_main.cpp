#include "basic_sys.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::string filename_linux = "/opt/aiyo/profile.md";
    std::string filename_win32 = "C:\\Users\\aiyo\\Document\\profile.txt";
    std::cout << "-- dirname(" << filename_linux << ", linux): " << dirname(filename_linux) << std::endl;
    std::cout << "-- dirname(" << filename_win32 << ", win32): " << dirname(filename_win32) << std::endl;
    std::cout << "-- basename(" << filename_linux << ", linux): " << basename(filename_linux) << std::endl;
    std::cout << "-- basename(" << filename_win32 << ", win32): " << basename(filename_win32) << std::endl;
    std::cout << "-- read_file(main.cpp): " << read_file("main.cpp") << std::endl;
    return 0;
}