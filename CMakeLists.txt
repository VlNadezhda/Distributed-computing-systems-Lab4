cmake_minimum_required(VERSION 3.20)
project(4)

set(CMAKE_CXX_STANDARD 11)

#add_executable(4 4.cpp)
add_executable(tcp_server1 tcp_server1.cpp)
add_executable(tcp_client1 tcp_client1.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(tcp_server1 Threads::Threads)
target_link_libraries(tcp_client1 Threads::Threads)