cmake_minimum_required(VERSION 3.22)
project(OS3)

set(CMAKE_CXX_STANDARD 14)

add_executable(OS3 main.cpp ConfigurationHandler.cpp ConfigurationHandler.h BoundedQueue.cpp UnboundedQueue.cpp Report.cpp Report.h ReporterHandler.h ReporterHandler.cpp mutex.cpp mutex.h mutex_scope.cpp mutex_scope.h)
