#include "Shop/ShopItem.hpp"

ShopItem::ShopItem(Item *item, int quantity)
    : item(item), quantity(quantity) {}

Item *ShopItem::getItem() const
{
    return item;
}

int ShopItem::getQuantity() const
{
    return quantity;
}

void ShopItem::increaseQuantity(int amount)
{
    quantity += amount;
}

bool ShopItem::decreaseQuantity(int amount)
{
    if (quantity >= amount)
    {
        quantity -= amount;
        return true;
    }
    return false;
}