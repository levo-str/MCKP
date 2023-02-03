#pragma once
#include<vector>
#include "sackcomposition.h"
#include "ResourceManagerBB.h"

/*
* Node class for the branch and bound algorithm
* [depth] depth of the node in the branch and bound tree
* [bound] bound of the node
* [currentValue] actual profit of the sack composition stored in the node
* [setsAlreadyPresent] unordered_set to remember which set of the problem are alrezady present in the node
*/
class Node
{
public:
	Node(float b, SackComposition sack, std::unordered_set<int> setsAlreadyPresent);
	Node(){};

private:
	float bound;
	int currentValue;
	int depth;
	SackComposition sackComposition;
	std::unordered_set<int> setsAlreadyPresent;
	friend class ResourceManagerBB;
};
