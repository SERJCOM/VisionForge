#pragma once
#include <iostream>
#include <chrono>
#include <string>

class Timer{
public:
    void Start(){
        time_now = std::chrono::high_resolution_clock::now();
    }

    void PrintTime(){
        std::cout << std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1> >>(std::chrono::high_resolution_clock::now() - time_now).count() << std::endl;
        time_now = std::chrono::high_resolution_clock::now();
    }

    void PrintTime(std::string comment){
        std::cout << comment.c_str() << " " << std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1> >>(std::chrono::high_resolution_clock::now() - time_now).count() << std::endl;
        time_now = std::chrono::high_resolution_clock::now();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> time_now;
};
