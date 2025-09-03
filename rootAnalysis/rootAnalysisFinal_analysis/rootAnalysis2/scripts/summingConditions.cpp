// Takes a list of gammas and tells you if any 2 of them add up to a 3rd 

void summingConditions(){

	int tol = 2;

	// list should be sorted from lowest to highest
	int list[] = {55, 62, 71, 90, 244, 250, 443, 595, 637, 646, 666, 788, 
			863, 885, 902, 946, 984, 1039, 1255, 1263, 1273, 1366, 
			1435, 1461, 1473, 1482, 1582, 1612, 1625, 2062, 2081, 
			2234, 2387, 3087, 3100, 3289, 3316, 3496};

	int size = end(list) - begin(list);
	
	for (int i = 0; i < size; i++){
		for (int j = i+1; j < size; j++){
			for (int val = list[i] + list[j] - tol; val <= list[i] + list[j] + tol; val++){
				for (int k = j+1; k < size; k++){				
					if(val == list[k]){
						cout << list[i] << " + " << list[j] << " = " << list[i] + list[j] << endl;		
					} 			
				}
			}
		}
	}

}
