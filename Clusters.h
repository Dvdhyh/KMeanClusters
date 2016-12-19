#pragma once

class ClusterGroups {
public:
	int windowWidth = 0, windowHeight = 0, dataNumber = 10;

	//Empty Container
	std::vector<std::pair<int, int>>a;

	//Hold the k mean points
	std::vector<std::pair<double, double>>KPoint;

	//Hold the previous k mean points
	std::vector<std::pair<double, double>>PrevKPoint;

	//The number of Clusters
	int k;

	//Hold all x,y
	std::vector<std::pair<int, int>>holdData;

	//Separates all data into clusters groups
	std::vector<std::vector<std::pair<int, int>>>holdClusters;


	//Call constructor
	ClusterGroups(int _k);

	//Set the number of clusters
	void setK(int k);

	//Get the number of clusters
	int getK();

	//Set Window size
	void setWindowSize(RECT _rect);

	//Generate Random Points 
	void GenerateData();
	void GenerateData(int maxNum);

	//Set the k mean Points 
	void setKPoints();

	//Compare if K points are the same as last round
	bool checkPreviousKPoints();

	//Set all data points
	void setPoints(int whichCluster, int x, int y);

	//Find the distance
	double getDistance(int x1, int y1, int x2, int y2);

	//Sort data in their clusters
	void ClusterGroups::SortIntoClusters();

	//Blank all data 
	void clearAll();
};