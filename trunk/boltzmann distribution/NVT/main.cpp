/*
	Exercice proposed by Hjorth-Jensen in "simulation of the Boltzmann distribution"
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

#define maxCycle 1000

int main()
{
	//input data:
	double Temperature = 4; //has dimension of energy
	double initial_v = 0;
	double delta_v = 4;
	double Beta = 1000;

	double max_v = 10.*sqrt(Temperature);
	double interval_v = max_v/500;

	double v_new, v_change;
	double delta_E;

	srand( (unsigned) time(0) );

	//histogram vector
	double P[ maxCycle ];

	int accept_step = 0;
	int accept_step_else = 0;
	double v_old = initial_v;
	for(int mcCycle = 0; mcCycle < maxCycle; mcCycle++)
	{
		v_change = ( 2 * double( rand() ) / RAND_MAX - 1 ) * delta_v;
		v_new = v_old + v_change;

		delta_E = 0.5*(v_new*v_new - v_old*v_old);
		
		if(delta_E <= 0)
		{
			accept_step++;
			v_old = v_new;
		}
		else if( (double(rand())/RAND_MAX) <= 0.5 )
		{
			accept_step_else++;
			v_old = v_new;
		}
		
		//Store the new velocities
		P[ mcCycle ] = v_new;

	}

	//int Number[];
	
	//An attempt to make an histogram
	for(int j = 0; j < 5*max_v; j++)
	{	
		int frequency = 0;
		for(int i = 0; i < maxCycle; i++)
		{
			if( ( ( abs(P[ i ]) ) > j*interval_v ) && ( ( abs(P[ i ]) ) < (j + 1)*interval_v ) )
				++frequency;
		}
		cout << "numbers of velocities in the " << j + 1 << " interval: " << frequency << endl;
	}

			
	cout << accept_step << endl;
	cout << accept_step_else << endl;
	
	return 0;
}
		

