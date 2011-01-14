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
	ofstream file;
	file.open("histogram.dat");

	const int N = 1000; //number of objects
	const int max_quanta = 35;
	int quanta = 5;
	int quanta_1 = 7;
	int quanta_2 = 3;

	int mat[ N ]; //vector which contains the energy of each object
	int maxCycle = 100*N; //maximum number of cycles

	srand( (unsigned) time( 0 ) );

	//set all the object's energy to 5 quanta
	//for(int i = 0; i < N; i++)
	//	mat[ i ] = quanta;

	//Another energy distribution initial condition
	for(int i = 0; i < N/2; i++)
		mat[ i ] = quanta_1;
	for(int i = N/2; i < N; i++)
		mat[ i ] = quanta_2;

	for(int k = 0; k < maxCycle; k++)
	{
		//pick up two objects randomly
		int object_1 = int( N*rand() )/RAND_MAX;
		int object_2 = int( N*rand() )/RAND_MAX;
		
		//exchange one quanta between them
		mat[ object_1 ] += 1;
		mat[ object_2 ] -= 1;
		
		//check if some object has negative quanta
		if( ( (mat[ object_1 ] < 0) || (mat[ object_2 ] < 0) ) || ( (mat[ object_2 ] < 0) && (mat[ object_1 ] < 0) ) )
		{
			mat[ object_1 ] -= 1;
			mat[ object_2 ] += 1;
			
			//Keep previous configuration
			k -= 1; 
		}
	}
	
	file << "Quanta" << setw( 13 ) << "Frequency" << endl;

	//output the final macrostate and verify the conservation of the total energy of the system:
	int total_energy = 0;
	for(int j = 0; j < N; j++)
		total_energy += mat [ j ];
	cout << total_energy << endl;

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
		density[ i ] = double(frequency)/N;
		file << i + 1 << setw(13) << frequency << endl;
		cout << "number of " << i + 1 << "'s : " << frequency << endl;	
	}
	
	return 0;
}

		
