/*
This code simulates elastic energy changes for a group of at least 1000 objects.
It uses the Microcanonical Ensemble (NVE)
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	//Creat output file
	ofstream file, afile;
	file.open("histogram.dat");
	afile.open("convergence.dat");

	const int N = 1000; //number of objects
	const int max_quanta = 35;

	int mat[ N ]; //vector which contains the energy of each object
	int maxCycle = 100*N; //maximum number of cycles

	int nDistribution;

	cout << "Enter among the three distributions below:" << endl;
	cout << "1: 100% with 5 quanta;" << endl;
	cout << "2: 50% with 7 quanta and 50% with 3 quanta;" << endl;
	cout << "3: 50% with 4 quanta and 50% with 6 quanta." << endl;

	cin >> nDistribution;

	switch(nDistribution)
	{
	case 1:
		//int quanta = 5;
		for(int i = 0; i < N; i++)
		mat[ i ] = 5;
		break;
	case 2:
		for(int i = 0; i < N/2; i++)
			mat[ i ] = 7;
		for(int i = N/2; i < N; i++)
			mat[ i ] = 3;
		break;
	case 3:
		for(int i = 0; i < N/2; i++)
			mat[ i ] = 4;
		for(int i = N/2; i < N; i++)
			mat[ i ] = 6;
		break;
	default:
		cout << "That's not a valid distribution!" << endl;
	}
	
	//seed the rand() function
	srand( (unsigned) time( 0 ) );
	
	//acceptance index
	int accepted = 0;

	for(int k = 0; k < maxCycle; k++)
	{
		//pick up two objects randomly
		int object_1 = int( N*rand() )/RAND_MAX - 1;
		int object_2 = int( N*rand() )/RAND_MAX - 1;
		
		//exchange one quanta between them
		mat[ object_1 ] += 1;
		mat[ object_2 ] -= 1;
		
		//check if some object has negative quanta
		if( ( (mat[ object_1 ] < 0) || (mat[ object_2 ] < 0) ) )
		{
			accepted++;

			//Keep previous configuration
			mat[ object_1 ] -= 1;
			mat[ object_2 ] += 1;
			
			//discount in order to count only effective energies exchanges
			k -= 1; 
		}

		//Verify convergence of the ground state population
		int count = 0;
		for(int i = 0; i < N; i++)
		{
			if(mat[ i ] == 0)
				++count;
		}
		afile << k << setw(13) << count << endl;
	}
	
	//Verify the conservation of the total energy of the system:
	double total_energy = 0;
	for(int j = 0; j < N; j++) {
		total_energy += mat [ j ];
	}

	file << "Quanta" << setw( 13 ) << "Frequency" << endl;

	//compute the frequency in which each energy appears in the final macrostate till max_quanta
	double density[ max_quanta ];
	for(int i = 0; i < max_quanta; i++)
	{
		int frequency = 0;
		for(int j = 0; j < N; j++)
			{
				if(mat[ j ] == i)
					++frequency;
			}
		density[ i ] = double(frequency)/double(N);
		file << i + 1 << setw(13) << frequency << endl;
		cout << "number of " << i + 1 << " quantas's energy: " << frequency << endl;	
	}

	cout << "total energy is = " << total_energy << endl;
	cout << "total number of cycles used = " << maxCycle + accepted << endl;
	cout << "effective cycles used = " << maxCycle << endl;
	cout << "discounted steps (in porcentage) = " << 100*(double(accepted)/double(maxCycle + accepted)) << "%" << endl;
	
	return 0;
}

		
