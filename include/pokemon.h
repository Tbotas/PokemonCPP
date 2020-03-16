#pragma once
#include <string>
#include <vector> 
#include <iostream>
#include "types.h"
#include "moves.h"

class Pokemon {
public:
    std::string m_name;
    Type m_type1, m_type2;
    uint8_t m_level;
    uint8_t m_attack;
    uint8_t m_defense;
    int8_t m_hp;
    int8_t m_maxhp;
    Move m_move;

    Pokemon(std::string name, Type type1, Type type2, uint8_t level, uint8_t hp, uint8_t attack, uint8_t defense, Move move) {
        m_name = name;
        m_type1 = type1;
        m_type2 = type2;
        m_level = level;
        m_hp = hp;
        m_maxhp = hp;
        m_attack = attack;
        m_defense = defense;
        m_move = move;
    };
private:
};