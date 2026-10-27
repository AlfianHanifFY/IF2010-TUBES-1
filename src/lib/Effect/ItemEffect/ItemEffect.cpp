#include "Effect/ItemEffect/ItemEffect.hpp"

ItemEffect::ItemEffect(const string &name, const string &description, int duration, float effectChance)
    : Effect(name, description, duration, effectChance) {}

ItemEffect::~ItemEffect() {}

ItemEffect::ItemEffect(const ItemEffect &other) : Effect(other) {}
