void chain(TChain *ch){

	// List of run numbers for analysis. 37Na runs. 86 Total
	
	std::vector<int>filelist = {
		1281, 1282, 1283, 1284, 1285, 1286, 1287, 1288,
		1290, 1291, 1292, 1293, 1294, 1295, 1296, 1297, 
		1298, 1299, 1300, 1301, 1302, 1303, 1304, 1305, 
		1306, 1307, 1308, 1309, 1310, 1311, 1312, 1313, 
		1314, 1315, 1316, 1317, 1318, 1319, 1320, 1321, 
		1322, 1323, 1324, 1325,	1326, 1327, 1328, 1329, 
		1330, 1331, 1333, 1334, 1336, 1337, 1392, 1393, 
		1394, 1396, 1397, 1399, 1400, 1401, 1403, 1404, 
		1405, 1406, 1407, 1408, 1409, 1410, 1411, 1412, 
		1413, 1414, 1415, 1416, 1417, 1418, 1419, 1420, 
		1421, 1422, 1424, 1425, 1426, 1427, 1428, 1429, 
		1430, 1431, 1432, 1433};


	// Number of run files
	int totalfiles = filelist.size();

	cout << "Number of data files to be added: " << totalfiles << endl;

	// Loop over all run files and add to TChain
	for(int i=0; i<totalfiles; i++){
		stringstream filein;
		//filein << "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resorted37Na/run-";
		//filein << "/mnt/analysis/e21062/aad/e21062B/sortedNew/run-";
		filein << "/mnt/analysis/e21062/aad/e21062B/reverse/run-";
		//filein << "/mnt/analysis/e21062/aad/e21062B/sorted/run-";
		filein << filelist[i];
		filein << "-sorted.root";

		string tfile = filein.str();
	
		cout << "Adding file " << filein.str() << " to chain." << endl;

		ch->Add(filein.str().c_str());
	}

	cout << "Data files successfully added." << endl;
}
