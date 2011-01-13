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

#define maxCycle 100000

int main()
{
	//input data:
	double Temperature = 4; //has dimension of energy
	double initial_v = 0;
	double delta_v = 4;
	double Beta = 1000;

	double max_v = 10.*sqrt(Temperature);
	double interval_v = max_v/100;

	double v_new, v_change;
	double delta_E;

	srand( (unsigned) time(0) );

	//histogram vector
	double P[ maxCycle ];
	
	double mean_v = 0;
	double mean_energy = 0;
	double sqr_mean_energy = 0;
	int accept_step = 0;
	int accept_step_else = 0;
	double v_old = initial_v;
	for(int mcCycle = 0; mcCycle < maxCycle; mcCycle++)
	{
		v_change = ( 2 * double( rand() ) / RAND_MAX - 1 ) * delta_v;
		v_new = v_old + v_change;

		delta_E = 0.5*(v_new*v_new - v_old*v_old);
		//cout << delta_E << endl;
		
		if(delta_E <= 0)
		{
			accept_step++;
			v_old = v_new;
		}
		else if( (double(rand())/RAND_MAX) <= exp(-delta_E/Temperature) )
		{
			accept_step_else++;
			v_old = v_new;
		}
		
		//Store the new velocities
		P[ mcCycle ] = v_new;

		mean_v += v_new;
		mean_energy += 0.5*v_new*v_new;
		sqr_mean_energy += (0.5*v_new*v_new)*(0.5*v_new*v_new);

	}
	
	mean_v /= maxCycle;
	mean_energy /= maxCycle;
	sqr_mean_energy /= maxCycle;
	double variance = sqr_mean_energy - mean_energy*mean_energy;
	//double result = 0.5*v_new*v_new;
	cout << "mean_energy = " << mean_energy << endl;
	cout << "variance = " << variance << endl;
	cout << "mean_v = " << mean_v << endl;

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
		//cout << "numbers of velocities in the " << j + 1 << " interval: " << frequency << endl;
	}

			
	cout << accept_step << endl;
	cout << accept_step_else << endl;
	
	return 0;
}
		

