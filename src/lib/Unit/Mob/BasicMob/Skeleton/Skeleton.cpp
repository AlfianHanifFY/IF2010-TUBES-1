#include "Unit/Mob/BasicMob/Skeleton/Skeleton.hpp"

Skeleton::Skeleton(int level) : BasicMob("Skeleton", level)
{
    
    

    Skill *boneShardSkill = new Skill("Bone Shard", 30, 0, getStat(1) * 1.5);
    boneShardSkill->addEffect(new BrittleEffect("Brittle Effect", "Menyebabkan effect 'Brittle' (Rapuh) dengan mengurangi defense.", 1, 1.0f, 0.3f));
    addSkill(boneShardSkill);

    setAssets("./Assets/Unit/Mob/Basic/Skeleton");
}

Skeleton::~Skeleton() {}

void Skeleton::act(Unit *target)
{
    if (!target)
        return;

    
    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (currentHealth < maxHealth * 0.5 && chance <= 0.05)
    {
        useSkill(getSkill("Heal"), this);
        return;
    }

    
    chance = static_cast<float>(rand()) / RAND_MAX;
    if (chance <= 0.25)
    {
        useSkill(getSkill("Bone Shard"), target);
        return;
    }

    attack(target);
}