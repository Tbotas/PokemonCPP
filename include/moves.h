#pragma once
#include <string>
#include <vector> 
#include <iostream>
#include "types.h"

class Move {
public:
    std::string m_name;
    Type m_type;
    
    uint8_t m_basePower;
    uint8_t m_accuracy;

    Move(std::string name, Type type, uint8_t basePower, uint8_t accuracy) {
        m_name = name;
        m_type = type;
        m_basePower = basePower;
        m_accuracy = accuracy;
    };
    
    Move() {}
};