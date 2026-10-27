#ifndef OGRE_HPP
#define OGRE_HPP

#include <iostream>
using namespace std;

#include "../BossMob.hpp"

class Ogre : public BossMob
{
public:
    Ogre(int level);
    virtual ~Ogre();

    virtual void act(Unit *target) override;
};

#endif
