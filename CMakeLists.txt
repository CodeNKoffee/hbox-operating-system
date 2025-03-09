cmake_minimum_required(VERSION 3.10)
project(OS_Milestone_01 C)

set(CMAKE_C_STANDARD 11)

# Find pthread package
find_package(Threads REQUIRED)

# Add source files
set(SOURCES
    src/main.c
    src/threads.c
    src/metrics.c
    src/scheduler.c
)

# Add executable
add_executable(scheduler ${SOURCES})

# Link pthread library
target_link_libraries(scheduler PRIVATE Threads::Threads)

# Add include directories
target_include_directories(scheduler PRIVATE src)