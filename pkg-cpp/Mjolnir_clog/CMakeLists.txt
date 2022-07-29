cmake_minimum_required(VERSION 3.20)
project(Mjolnir_clog)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable( Mjolnir_clog
        test.cpp
        Buffer.cpp
        Buffer.h
        Mjolnir_clog.cpp
        Mjolnir_clog.h
        Mjolnir_clog_header.h
        UTC_Timer.h)
