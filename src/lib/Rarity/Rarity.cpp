#include "Rarity/Rarity.hpp"

Rarity::Rarity(char type) {}
Rarity::~Rarity() {}

char Rarity::getType() const
{
    return this->type;
}
float Rarity::getMultiplier() const
{
    if (type == 'E')
        return 1.0f; 
    else if (type == 'D')
        return 1.2f; 
    else if (type == 'C')
        return 1.5f; 
    else if (type == 'B')
        return 2.0f; 
    else if (type == 'A')
        return 3.0f; 
    else if (type == 'S')
        return 6.0f; 
    return 1.0f;     
}
std::string Rarity::getRarityName() const
{
    if (type == 'E')
        return "Common";
    else if (type == 'D')
        return "Uncommon";
    else if (type == 'C')
        return "Rare";
    else if (type == 'B')
        return "Epic";
    else if (type == 'A')
        return "Legendary";
    else if (type == 'S')
        return "Mythic";
    return "Common";
}

int Rarity::getMaxEffectCount() const
{
    switch (type)
    {
    case 'E':
        return 0; 
    case 'D':
        return 1; 
    case 'C':
        return 1; 
    case 'B':
        return 2; 
    case 'A':
        return 2; 
    case 'S':
        return 3; 
    default:
        return 0;
    }
}
