#include "Item.h"
#include <atomic> //std::atomic_uint32_t
#include <iostream>
#include <fstream>


atomic_uint32_t Item::current_id = 0; // added

Item::Item() : id(current_id++) {

}

Item::Item(int r, int p, int t) : id(current_id++) {
	resources = r;
	profit = p;
	task = t;
}

int Item::getId() {
	return id;
}

int Item:: getResources() {
	return resources;
}

int Item::getProfit() {
	return profit;
}

int Item::getTask() {
	return task;
}
