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

int main()
{
	//input data:
	const int experiments = 100; //Number of experiments
	const int maxCycle = 100000; //Maximum Monte Carlo Cycle
	
	double Temperature = 4; //Has dimension of energy
	double initial_v = 0;
	double delta_v = 4;

	double v_new, v_change;
	double delta_E;

	srand( (unsigned) time(0) );


	//Define bath temperature and velocity interval
	double max_v = 10.*sqrt(Temperature);
	double interval_v = max_v/100;

	//Histogram vector
	double P[ maxCycle ];
	
	//Initialize values and their respective vectors
	double mean_v = 0;
	double Mean_v[experiments];
	double mean_energy = 0;
	double Mean_energy[experiments];
	double sqr_mean_energy = 0;
	double Sqr_mean_energy[experiments];
	double sqr_mean_v = 0;
	double Sqr_mean_v[experiments];
	
	//Acceptance-step variables
	int accept_step;
	int accept_step_else;
	int not_accept;

	for(int i = 0; i < experiments; i++)
	{
		double v_old = initial_v;
		accept_step = 0;
		accept_step_else = 0;
		not_accept = 0;
		mean_v = 0;
		mean_energy = 0;
		v_new = 0;

		for(int mcCycle = 0; mcCycle < maxCycle; mcCycle++)
		{
			//Sort a velocity in the range (-delta_v, +delta_v)
			v_change = ( 2 * double( rand() ) / RAND_MAX - 1 ) * delta_v;
			v_new = v_old + v_change;

			//Compute energy change
			delta_E = 0.5*(v_new*v_new - v_old*v_old);
		
			//Metropolis acceptance conditions
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
			//keep the old configuration
			else 
			{
				v_new = v_old; 
				not_accept++;
			}
			
			//Store the new velocities
			P[ mcCycle ] = v_new;
	
			//Accumulate mean velocity and mean energy
			mean_v += v_new;
			sqr_mean_v += v_new*v_new;
			mean_energy += 0.5*v_new*v_new;
			sqr_mean_energy += (0.5*v_new*v_new)*(0.5*v_new*v_new);
	
		}
		//Get the mean value for the i experiment
		mean_v /= maxCycle;
		sqr_mean_v /= maxCycle;
		mean_energy /= maxCycle;
		sqr_mean_energy /= maxCycle;
		
		//Store the mean in its vector
		Mean_v[ i ] = mean_v;
		Sqr_mean_v[ i ] = sqr_mean_v;
		Mean_energy[ i ] = mean_energy;
		Sqr_mean_energy[ i ] = sqr_mean_energy;
	}
	
	//Calculate the mean through the experiments
	for(int i = 0; i < experiments; i++)
	{
		mean_v += Mean_v[ i ];
		sqr_mean_v += Sqr_mean_v[ i ];
		mean_energy += Mean_energy[ i ];
		sqr_mean_energy += Sqr_mean_energy[ i ];
	}
	mean_v /= experiments;
	sqr_mean_v /= experiments;
	mean_energy /= experiments;
	sqr_mean_energy /= experiments;

	//Compute variances and print relevant values	
	double energy_variance = sqr_mean_energy - mean_energy*mean_energy;
	double mean_v_variance = sqr_mean_v - mean_v*mean_v;
	cout << "Temperature = " << Temperature << endl;
	cout << "mean_energy = " << mean_energy << endl;
	cout << "energy variance = " << energy_variance << endl;
	cout << "mean_v = " << mean_v << endl;
	cout << "velocity variance = " << mean_v_variance << endl;
	cout << "---------------------------------------------------" << endl;

	//Generate histogram till n*max_v
	//Later, allocate memory to create a density vector
	int i, j;
	int n = 2;
	for(j = 0; j < n*max_v; j++)
	{	
		int frequency = 0;
		for(i = 0; i < maxCycle; i++)
		{
			if( ( ( abs(P[ i ]) ) > j*interval_v ) && ( ( abs(P[ i ]) ) < (j + 1)*interval_v ) )
				++frequency;
		}
		cout << "numbers of velocities in the " << j + 1 << " interval: " << frequency << endl;
	}
	
	//Print accepted and not accepted steps in metropolis scheme
	cout << "\nAccepted 'if' step = " << accept_step << endl;
	cout << "Accepted 'if else' step = " << accept_step_else << endl;
	cout << "Total accepted step = " << accept_step + accept_step_else << endl;
	cout << "Not accepted-step = " << not_accept << endl;

	return 0;
}
		

