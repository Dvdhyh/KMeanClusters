#include "HeaderMaster.h"

ClusterGroups::ClusterGroups(int _k) {
	if (_k < 2)
		_k = 2;

	k = _k;

	for (int i = 0; i < _k; i++) {
		holdClusters.emplace_back(a);
	}
}

void ClusterGroups::setK(int _k) {
	k = _k;
}

int ClusterGroups::getK() {
	return k;
}

void ClusterGroups::setWindowSize(RECT _rect) {
	windowWidth = _rect.right - _rect.left;
	windowHeight = _rect.bottom - _rect.top;
}

void ClusterGroups::GenerateData() {
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < dataNumber; i++) {
		x = rand() % (windowWidth - 1) + 1;
		y = rand() % (windowHeight - 1) + 1;
		holdData.emplace_back(std::make_pair(x, y));
	}

	//Create Random KPoints
	for (int i = 0; i < k; i++) {
		x = rand() % (windowWidth - 1) + 1;
		y = rand() % (windowHeight - 1) + 1;
		KPoint.emplace_back(std::make_pair(x, y));
	}
}

void ClusterGroups::GenerateData(int maxNum) {

	dataNumber = maxNum;

	GenerateData();
}

void ClusterGroups::setKPoints() {
	KPoint.clear();

	double kX, kY;
	for (int i = 0; i < k; i++) {
		kX = 0, kY = 0;

		int clusterSize = holdClusters[i].size();
		for (int j = 0; j < clusterSize; j++) {
			kX += holdClusters[i][j].first;
			kY += holdClusters[i][j].second;
		}
		KPoint.emplace_back(std::make_pair(kX / clusterSize, kY / clusterSize));
	}
}

bool ClusterGroups::checkPreviousKPoints() {
	if (PrevKPoint.size() == 0)
		return false;

	for (int i = 0; i < k; i++) {
		if (!(PrevKPoint[i].first == KPoint[i].first))
			return false;
		if (!(PrevKPoint[i].second == KPoint[i].second))
			return false;
	}
	return true;
}

void ClusterGroups::setPoints(int whichCluster, int x, int y) {
	holdClusters[whichCluster].emplace_back(std::make_pair(x, y));
}

double ClusterGroups::getDistance(int x1, int y1, int x2, int y2) {
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

//Returns the index of the smallest number 
int sortVec(std::vector<double> a) {
	int smallNum = 0;
	for (int i = 0; i < a.size() - 1; i++) {
		if (a[smallNum] > a[i + 1]) {
			smallNum = i + 1;
		}
	}
	return smallNum;
}

void ClusterGroups::SortIntoClusters() {
	PrevKPoint = KPoint;

	for(auto&a : holdClusters)
		a.clear();

	std::vector<double> order;

	for (auto&a : holdData) {
		for (int i = 0; i < k; i++) {
			order.emplace_back(getDistance(KPoint[i].first, KPoint[i].second, a.first, a.second));
		}

		setPoints(sortVec(order), a.first, a.second);
		order.clear();
	}
}

void ClusterGroups::clearAll() {
	holdData.clear();
	
	for(auto& a : holdClusters)
		a.clear();

	KPoint.clear();

	PrevKPoint.clear();
}