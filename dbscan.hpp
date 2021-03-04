/////////////////////////////////////////////////////////////
//
// dbscan.hpp
//
// Minimalistic header only DBSCAN clustering algorithm implementation in C++
//
// Created By: Recep ALTIN @rcaltin
//
// https://github.com/rcaltin/DBSCAN
//
/////////////////////////////////////////////////////////////

#ifndef DBSCAN_H
#define DBSCAN_H

#include <vector>

constexpr int DBSCAN_UNCLASSIFIED = -1;
constexpr int DBSCAN_NOISE = -2;

typedef struct DBScanClusterItem
{
	DBScanClusterItem(double value = 0, void* userDataHandle = nullptr)
		: Value(value),
		UserDataHandle(userDataHandle),
		Cluster(DBSCAN_UNCLASSIFIED)
	{ }

	double Value;
	int Cluster;
	void* UserDataHandle;
} DBScanClusterItem;

class DBScan {
public:
	DBScan(std::vector<DBScanClusterItem>* items, unsigned int minClusterSize, float epsilon)
		: mItems(items),
		mMinClusterSize(minClusterSize),
		mEpsilon(epsilon)
	{ }

	~DBScan() {}

	bool run()
	{
		if (!mItems)
			return false;

		int cluster = -1;
		for (auto it = mItems->begin(); it != mItems->end(); ++it)
			if (it->Cluster == DBSCAN_UNCLASSIFIED) expand(*it, ++cluster);

		return true;
	}

private:
	void expand(DBScanClusterItem& item, int cluster)
	{
		std::vector<DBScanClusterItem*>& clusterItems = findClusterItems(item);

		bool noise = clusterItems.size() < mMinClusterSize;

		for (auto it = clusterItems.begin(); it != clusterItems.end(); ++it)
		{
			DBScanClusterItem* i = (*it);

			if (noise)
				i->Cluster = DBSCAN_NOISE;
			else if (i->Cluster == DBSCAN_UNCLASSIFIED)
			{
				i->Cluster = cluster;

				if (i->Value != item.Value)
					expand(*i, cluster);
			}
		}
	}

	std::vector<DBScanClusterItem*> findClusterItems(const DBScanClusterItem& item)
	{
		std::vector<DBScanClusterItem*> cluster;
		for (auto it = mItems->begin(); it != mItems->end(); ++it)
		{
			if (std::abs(item.Value - it->Value) <= mEpsilon)
				cluster.push_back(&(*it));
		}

		return cluster;
	}

	std::vector<DBScanClusterItem>* mItems;
	unsigned int mMinClusterSize;
	double mEpsilon;
};

#endif // DBSCAN_H