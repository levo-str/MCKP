#pragma once
#include <atomic> //std::atomic_uint32_t
#include <iostream>
#include <fstream>
using namespace std;

/**
* @brief Class representing the affectation of resources on a task. 
*/
class Item
{
	
public:
	static atomic_uint32_t current_id; // added
	Item();
	Item(int r, int p, int t);
	int getResources();
	int getProfit();
	int getTask();
	int getId();

private :
	uint32_t id;
	
	int resources; //equivalent to weight in knapsack problem
	int profit;
	int task;

};


