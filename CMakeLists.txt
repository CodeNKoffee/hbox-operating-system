cmake_minimum_required(VERSION 3.10)
project(OS_Milestone_01 C)

set(CMAKE_C_STANDARD 11)

# Find pthread package
find_package(Threads REQUIRED)

# Add executable
add_executable(scheduler src/main.c)

# Link pthread library
target_link_libraries(scheduler PRIVATE Threads::Threads)