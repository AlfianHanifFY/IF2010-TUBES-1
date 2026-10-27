#include "Skill/Skill.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Skill::Skill(string name, int manaCost, int masteryCost, int damage)
{
    this->name = name;
    this->manaCost = manaCost;
    this->masteryCost = masteryCost;
    this->damage = damage;
}

Skill::~Skill()
{
    for (size_t i = 0; i < effects.size(); i++)
    {
        delete effects[i];
    }
    effects.clear();
}


string Skill::getName() const { return this->name; }
int Skill::getManaCost() const { return this->manaCost; }
int Skill::getMasteryCost() const { return this->masteryCost; }
int Skill::getDamage() const { return this->damage; }
const vector<Effect *> &Skill::getEffects() const { return this->effects; }
const vector<string> &Skill::getPrerequisites() const { return this->prerequisites; }

void Skill::setName(const string &name) { this->name = name; }
void Skill::setManaCost(int manaCost) { this->manaCost = manaCost; }
void Skill::setMasteryCost(int masteryCost) { this->masteryCost = masteryCost; }
void Skill::setDamage(int damage) { this->damage = damage; }

void Skill::addEffect(Effect *effect) { this->effects.push_back(effect); }
void Skill::removeEffect(Effect *effect)
{
    auto it = find(effects.begin(), effects.end(), effect);
    if (it != effects.end())
    {
        delete *it;
        effects.erase(it);
    }
}

void Skill::addPrerequisite(const string &prerequisiteSkillName)
{
    if (find(prerequisites.begin(), prerequisites.end(), prerequisiteSkillName) == prerequisites.end())
    {
        prerequisites.push_back(prerequisiteSkillName);
    }
}

bool Skill::use(Unit *target)
{
    if (damage > 0)
    {
        target->takeDamage(damage);
    }

    for (size_t i = 0; i < effects.size(); i++)
    {
        float chance = static_cast<float>(rand()) / RAND_MAX;
        if (chance <= effects[i]->getEffectChance())
        {
            HealthDrainEffect *drainEffect = dynamic_cast<HealthDrainEffect *>(effects[i]->clone());
            if (drainEffect != nullptr)
            {
                drainEffect->setDrainAmount(damage * 0.3);
                target->addEffect(drainEffect);
            }
            else
            {
                target->addEffect(effects[i]->clone());
            }
        }
    }

    return true;
}

bool Skill::operator==(const Skill &other) const
{
    return name == other.name && manaCost == other.manaCost && masteryCost == other.masteryCost && damage == other.damage;
}