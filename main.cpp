#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <random>

#include "jobconfiguration.h"
#include "SackComposition.h"
#include "resourceManager.h"

auto get_time() {
	return std::chrono::high_resolution_clock::now();
}


int main() {
	
	/**
	// TODO put this part in test file
	Item testItem = Item(1, 1, 1);
	Item secondTestItem = Item(1, 1, 1);
	cout << "Testing if ID auto-incrementation works and if object creation is possible" << endl;
	cout << testItem.getId() << endl;
	cout << secondTestItem.getId();
	*/

	// Creating the tables to solve the multiple choice knapsack problem :
	// first one classic knapsack problem
	// second one composition of the knapsack in each case
	// third one (optional) just the list ordered by increasing id of the Items
	// apply normal dynamic knapsack resolution algorithm but also test out for configurations and test out where there is already an 
	// item on the same task 

	// first sketch without creating class or anything
		//int numberItems, numberResources;
		//unordered_map<int, JobConfiguration> mapItems;
		//cout << "number of Items = number of Job configurations = ";
		//cin >> numberItems;
		//cout << endl << "number of resources we have = ";
		//cin >> numberResources;
		//cout << endl;
		//int** profitArray = new int* [numberItems + 1];

		//int r, p, t;

		//for (int i = 0; i < numberItems+1; i++) {
		//	if (i != numberItems) {
		//		cout << "Item number  " << i + 1 << " please" << endl;
		//		cout << "resources = ";
		//		cin >> r;
		//		cout << endl;
		//		//p = pow(r,i+1);
		//		cout << "profit = ";
		//		cin >> p;
		//		cout << endl;
		//		//cout << "task number = ";
		//		//cin >> t;
		//		t = 0;
		//		cout << endl;

		//		JobConfiguration item = JobConfiguration(r, p, t);
		//		cout << "item number : " << item.getId() << endl;
		//		mapItems[item.getId()] = item;
		//	}
		//	profitArray[i] = new int[numberResources + 1];
		//}


	std::vector<int> v(3);

	// Set up our random number generator
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<int> dist1(1, 10000);
	std::uniform_int_distribution<int> dist2(1, 10000);
	std::uniform_int_distribution<int> dist3(1, 100);
	//specify the number of nodes
	//specify the number of jobs running 
	//calculate memory consumption
	//calculate speedup of the algorithm
	//look into other parallelization methods

	long long totalTimeForSerialResolution = 0;
	long long totalTimeForParallelResolution = 0;

	for (int testNumber = 0; testNumber < 10; testNumber++) {
		
		int numberOfSet = dist3(rng);
		int weight = dist2(rng);

		unordered_map<int, JobConfiguration> mapItems;
		
		for (int itemNumber = 0; itemNumber < dist1(rng); itemNumber++) {
			std::generate(begin(v), end(v), [&]() { return dist2(rng); });
			mapItems[itemNumber + 1] = JobConfiguration(v[0], v[1], v[2] % numberOfSet);
		}

		auto start = get_time();
		ResourceManagerDP problemSolver = ResourceManagerDP(weight, mapItems);
		SackComposition solution = problemSolver.solveMckp();
		auto finish = get_time();
		auto duration =
		std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
		totalTimeForSerialResolution += duration.count();
		
		
		auto parallelStart = get_time();

		ResourceManagerDP parallelProblemSolver = ResourceManagerDP(weight, mapItems);
		SackComposition parallelSolution = parallelProblemSolver.solveMckpConcurrently();
		
		auto parallelFinish = get_time();
		
		auto parallelDuration =
			std::chrono::duration_cast<std::chrono::milliseconds>(parallelFinish - parallelStart);
		totalTimeForParallelResolution += parallelDuration.count();

		if (solution.calculateTotalProfit() != parallelSolution.calculateTotalProfit()) {
			std::cout << "There is a problem" << std::endl;
		}
	}

	/*
	unordered_map<int, JobConfiguration> mapItems;
	mapItems[1] = JobConfiguration(4, 4, 1);
	mapItems[2] = JobConfiguration(5, 3, 1);
	mapItems[3] = JobConfiguration(7, 4, 1);
	mapItems[4] = JobConfiguration(3, 9, 1);
	mapItems[5] = JobConfiguration(3, 9, 2);
	mapItems[6] = JobConfiguration(7, 12, 2);
	mapItems[7] = JobConfiguration(6, 8, 3);
	mapItems[8] = JobConfiguration(8, 4, 3);
	mapItems[9] = JobConfiguration(3, 3, 4);
	mapItems[10] = JobConfiguration(8, 4, 4);
	mapItems[11] = JobConfiguration(6, 8, 4);
	mapItems[12] = JobConfiguration(10, 12, 4);
	auto start = get_time();
	ResourceManagerDP problemSolver = ResourceManagerDP(50, mapItems);
	SackComposition solution = problemSolver.solveMckp();
	int** profitArray = problemSolver.getProfitArray();
	auto finish = get_time(); 
	cout << endl << "Sack composition is : " << endl;
	for (auto item : solution.getItemList()) {
		cout << item.second.getId() << ",";
	}
	auto duration =
		std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << "Elapsed time = " << duration.count() << " ms\n";
	*/

	cout << "for serial execution : " << totalTimeForSerialResolution << "ms" << endl;
	cout << "for parallel execution : " << totalTimeForParallelResolution << "ms" << endl;
	
	return 0;
}
