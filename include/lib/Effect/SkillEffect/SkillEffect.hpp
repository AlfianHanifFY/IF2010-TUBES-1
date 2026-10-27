#ifndef SKILLEFFECT_HPP
#define SKILLEFFECT_HPP

#include <iostream>
using namespace std;

#include "../Effect.hpp"
class Unit;

class SkillEffect : public Effect
{
public:
    SkillEffect(string name, string description, int duration, float effectChance);
    virtual ~SkillEffect();

    
    SkillEffect(const SkillEffect &other);
    virtual string getType() const;
};

#endif
