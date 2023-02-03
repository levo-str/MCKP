#include "ResourceManagerBB.h"
#include "Node.h"
#include <limits>
#include <queue>

float calculateRatio(JobConfiguration jobConfiguration) {
	if (jobConfiguration.getResources() == 0) {
		if (jobConfiguration.getProfit() > 0) {
			return std::numeric_limits<float>::max();
		}
		else {
			return -std::numeric_limits<float>::max();
		}
	}
	else {
		return (float)jobConfiguration.getProfit() / (float)jobConfiguration.getResources();
	}
}

bool compareByRatio(JobConfiguration a, JobConfiguration b) {
	return calculateRatio(a) > calculateRatio(b);
}


/**
* Default builder for ResourceManagerBB
*/
ResourceManagerBB::ResourceManagerBB() : ResourceManager() {
}

ResourceManagerBB::~ResourceManagerBB(){
}

/**
* ResourceManager builder
*/
ResourceManagerBB::ResourceManagerBB(int numberOfResources, std::unordered_map<int, JobConfiguration> mapItems) : ResourceManager(numberOfResources, mapItems) {
	this->numberItems = mapItems.size();
	unordered_set<int> encounteredSets;
	for (auto item : mapItems) {
		itemsSortedByRatio.push_back(item.second);
		if (encounteredSets.count(item.second.getTask()) == 0)
			numberOfSets++;
	}
	std::sort(itemsSortedByRatio.begin(), itemsSortedByRatio.end(), compareByRatio);
	//std::cout << "Initialisation complete" << endl;
}

/**
* Calculates the bound adding by order of ratio the items from sets that are still not in the node and items yet to be studied. When the remaining knapsack capacity is inferior to the item weight add, the fraction 
* what can still fit. It's the normal bound function for the 0/1 Knapsack but adapted to the set constraint.
*/
float ResourceManagerBB::calculateBound(int depth, SackComposition currentSackComposition, unordered_set<int> setsAlreadyPresent) {
	
	float bound = (float) currentSackComposition.calculateTotalProfit();

	if (currentSackComposition.getItemList().size() == numberOfSets || setsAlreadyPresent.size() == numberOfSets ) 
		return bound;
	int remainingWeightInKnapSack = this-> numberResources - currentSackComposition.calculateTotalWeight();
	
		for (int i = depth + 1; i < itemsSortedByRatio.size(); i++) {
			JobConfiguration item = itemsSortedByRatio[i];
			if (setsAlreadyPresent.count(item.getTask()) == 0) {
				if (item.getResources() <= remainingWeightInKnapSack) {
					bound += item.getProfit();
					remainingWeightInKnapSack -= item.getResources();
				}
				else {
					bound += remainingWeightInKnapSack * calculateRatio(item);
					remainingWeightInKnapSack = 0;
					break;
				}
			}
		}
	return bound;
}

SackComposition ResourceManagerBB::solveMckp() {
	std::queue<Node> nodesToExpand;
	//std::unordered_map<int, int > initialIndexMap = initializeMaxRatioItemIndexPerSet(itemsSortedByRatio);
	
	Node rootNode = Node(calculateBound(-1, SackComposition(vector<JobConfiguration>()), unordered_set<int>()), SackComposition(), unordered_set<int>());
	rootNode.depth = -1;
	nodesToExpand.push(rootNode);
	int bestValue = -std::numeric_limits<int>::max();
	SackComposition bestComposition = SackComposition(std::vector<JobConfiguration>());

	while (!nodesToExpand.empty()) {
		Node nodeConsidered = nodesToExpand.front();
		nodesToExpand.pop();
		//if it's a leaf node
		if (nodeConsidered.depth >= numberItems - 1) {
			if (nodeConsidered.currentValue >= bestValue) {
				bestValue = nodeConsidered.currentValue;
				bestComposition = nodeConsidered.sackComposition;
			}
		}

		else {
			if (nodeConsidered.bound > bestValue) {
				//else it's not worth studying
				if (nodeConsidered.currentValue > bestValue) {
					bestValue = nodeConsidered.currentValue;
					bestComposition = nodeConsidered.sackComposition;
				}

				JobConfiguration itemConsidered = itemsSortedByRatio[nodeConsidered.depth + 1];
				// include itemConsidered 
				if (nodeConsidered.setsAlreadyPresent.count(itemConsidered.getTask()) == 0 && (nodeConsidered.sackComposition.getTotalWeight() + itemConsidered.getResources()) <= numberResources) {
					
					std::vector<JobConfiguration> leftChildItemList = nodeConsidered.sackComposition.getItemList();
					leftChildItemList.push_back(itemsSortedByRatio[nodeConsidered.depth + 1]);
					
					std::unordered_set<int> newSetsAlreadyPresent = nodeConsidered.setsAlreadyPresent;
					newSetsAlreadyPresent.insert(itemConsidered.getTask());
					
					int leftChildBound = calculateBound(nodeConsidered.depth + 1, SackComposition(leftChildItemList), newSetsAlreadyPresent);
					Node leftChildNode = Node(leftChildBound, SackComposition(leftChildItemList), newSetsAlreadyPresent);
					leftChildNode.depth = nodeConsidered.depth + 1;
					
					if (leftChildNode.bound > (float)bestValue) {
						nodesToExpand.push(leftChildNode);
					}
				}
				//without including item considered
				Node rightChildNode = Node(calculateBound(nodeConsidered.depth + 1, nodeConsidered.sackComposition, nodeConsidered.setsAlreadyPresent), nodeConsidered.sackComposition, nodeConsidered.setsAlreadyPresent);
				rightChildNode.depth = nodeConsidered.depth + 1;
				
				if (rightChildNode.bound > (float) bestValue) {
					nodesToExpand.push(rightChildNode);
				}

			}
		}
	}
	return bestComposition;
}

SackComposition ResourceManagerBB::solveMckpConcurrently() {
	return SackComposition(vector<JobConfiguration>());
}
