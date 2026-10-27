#include "Inventory/Slot.hpp"


Slot::Slot() : item(nullptr), quantity(0) {}


Slot::Slot(Item* newItem, int qty) : item(newItem), quantity(qty) {}


Item* Slot::getItem() const {
    return item;
}


int Slot::getQuantity() const {
    return quantity;
}


void Slot::setItem(Item* newItem) {
    item = newItem;
}


void Slot::setQuantity(int newQuantity) {
    quantity = newQuantity;
}


void Slot::increaseQuantity(int amount) {
    quantity += amount;
}


void Slot::decreaseQuantity(int amount) {
    quantity -= amount;
}


bool Slot::isEmpty() const {
    return item == nullptr;
}
