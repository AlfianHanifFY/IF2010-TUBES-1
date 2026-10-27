#include "SkillTree/SkillTree.hpp"
#include <algorithm>

SkillTree::SkillTree(string name) : name(name)
{
}

SkillTree::~SkillTree()
{
    activeSkills.clear();
    learnedSkills.clear();
}

string SkillTree::getName() const
{
    return name;
}
bool SkillTree::isLearned(Skill *skill)
{
    for (Skill *s : learnedSkills)
    {
        if (s == skill)
        {
            return true;
        }
    }
    return false;
}

bool SkillTree::CanMaster(Skill *skill)
{
    
    for (Skill *s : learnedSkills)
    {
        if (s == skill)
            return false;
    }

    
    string key = "";
    for (auto &entry : skills)
    {
        if (entry.second == skill)
        {
            key = entry.first;
            break;
        }
    }

    
    if (key == "")
        return false;

    
    if (key == "Base")
        return true;

    
    if (key == "A1" || key == "B1")
    {
        Skill *base = skills["Base"];
        return base && isLearned(base);
    }
    else if (key == "A2")
    {
        Skill *a1 = skills["A1"];
        return a1 && isLearned(a1);
    }
    else if (key == "B2")
    {
        Skill *b1 = skills["B1"];
        return b1 && isLearned(b1);
    }

    
    return false;
}

void SkillTree::addLearnedSkill(Skill *s)
{
    this->learnedSkills.push_back(s);
}

void SkillTree::update()
{
    activeSkills.clear();

    Skill *lastA = nullptr;
    Skill *lastB = nullptr;
    bool baseLearned = false;

    
    for (Skill *s : learnedSkills)
    {
        if (s == skills["A2"])
            lastA = s;
        else if (s == skills["A1"] && lastA == nullptr)
            lastA = s;

        if (s == skills["B2"])
            lastB = s;
        else if (s == skills["B1"] && lastB == nullptr)
            lastB = s;

        if (s == skills["Base"]) 
            baseLearned = true;
    }

    
    if (lastA && lastB)
    {
        activeSkills.push_back(lastA);
        activeSkills.push_back(lastB);
    }
    else if (lastA)
    {
        activeSkills.push_back(lastA);
        activeSkills.push_back(skills["Base"]);
    }
    else if (lastB)
    {
        activeSkills.push_back(lastB);
        activeSkills.push_back(skills["Base"]);
    }
    else
    {
        activeSkills.push_back(skills["Base"]);
    }
    if (baseLearned)
    {
        cout << "base" << endl;
    }
}

vector<Skill *> SkillTree::getActiveSkill()
{
    return activeSkills;
}

void SkillTree::addSkill(Skill *skill, string status)
{
    cout << "Menambahkan " << skill->getName() << " ke status " << status << endl;
    cout << "Pointer: " << skill << endl;

    this->skills[status] = skill;
}

map<string, Skill *> SkillTree::getSkills()
{
    return this->skills;
}