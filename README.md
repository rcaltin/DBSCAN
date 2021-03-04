# DBSCAN
Minimalistic header only DBSCAN clustering algorithm implementation in C++

# Example
	std::vector<DBScanClusterItem> items;
	
	//TODO: fill the items vector
	
	DBScan dbs(&items, 2, 5);
	dbs.run();
