cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(EXISTS "${location}")
    message(FATAL_ERROR "you forgot to run BuildLah_finaliseProject(), make sure to call it at the end of your CMakeLists.txt")
endif()
