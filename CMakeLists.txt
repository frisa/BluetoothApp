cmake_minimum_required(VERSION 3.10)
project(BluetoothApp)

set(CMAKE_CXX_STANDARD 14)

# Add the directories containing dbus.h and dbus-arch-deps.h
include_directories(/usr/include/dbus-1.0)
include_directories(/usr/lib/x86_64-linux-gnu/dbus-1.0/include)

add_executable(BluetoothApp program.cpp)

# Link against the dbus-1 library
target_link_libraries(BluetoothApp dbus-1)
