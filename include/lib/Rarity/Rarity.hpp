#ifndef RARITY_HPP
#define RARITY_HPP

#include <iostream>
using namespace std;

class Rarity
{
private:
    char type;

public:
    Rarity(char type);
    ~Rarity();
    
    char getType() const;

    
    float getMultiplier() const;
    std::string getRarityName() const;
    int getMaxEffectCount() const;
};

#endif
