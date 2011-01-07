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

#define N 1000 //number of objects

int main()
{
	ofstream file;
	file.open("output.dat");

	int quanta = 5;
	int mat[ N ];
	srand( (unsigned) time( 0 ) );
	int cycle = 10000*N;

	//set all the object's energy to 5 quanta
	for(int i = 0; i < N; i++)
		mat[ i ] = quanta;

	for(int k = 0; k < cycle; k++)
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

			k -= 1; 
		}			
	}
	
	file << "Element" << setw( 13 ) << "Value" << endl;

	//output the final macrostate and verify the conservation of the total energy of the system:
	int total_energy = 0;
	for(int j = 0; j < N; j++)
	{
		file << setw( 7 ) << j + 1 << setw( 13 ) << mat[ j ] << endl;
		total_energy += mat [ j ];
	}
	cout << total_energy << endl;
		

	return 0;
}

		
