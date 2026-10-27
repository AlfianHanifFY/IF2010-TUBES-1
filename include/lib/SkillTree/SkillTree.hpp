#ifndef SKILLTREE_HPP
#define SKILLTREE_HPP

#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "../Skill/Skill.hpp"

class SkillTree
{
private:
    string name;
    vector<Skill *> learnedSkills;
    vector<Skill *> activeSkills;
    bool isLearned(Skill *skill);
    map<string, Skill *> skills;

    

public:
    SkillTree(string name);
    virtual ~SkillTree();

    string getName() const;
    map<string, Skill *> getSkills();

    void update();
    bool CanMaster(Skill *skill);

    void addSkill(Skill *, string);
    void addLearnedSkill(Skill *);
    vector<Skill *> getActiveSkill();
};

#endif