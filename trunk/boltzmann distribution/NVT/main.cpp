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
	double Temperature = 4; //has dimension of energy
	int maxCycle = 1000;
	double initial_v = 3;
	double delta_v = 4;
	double large = pow(10.,-23.);
	double Beta = 1 / ( (1.38065)*large*Temperature );

	double max_v = 10.*sqrt(Temperature);
	double interval_v = max_v/500;

	double v_new, v_change;
	double delta_E;

	srand( (unsigned) time(0) );

	int accept_step = 0;
	double v_old = initial_v;
	for(int mcCycle = 0; mcCycle < maxCycle; mcCycle++)
	{
		v_change = ( 2 * double( rand() ) / RAND_MAX - 1 ) * delta_v;
		v_new = v_old + v_change;

		delta_E = 0.5*(v_new*v_new - v_old*v_old);
		cout << v_change << endl;
		
		if(delta_E <= 0)
		{
			accept_step++;
			v_old = v_new;
		}
		else if( (double(rand())/RAND_MAX) <= exp(-Beta*delta_E) )
		{
			accept_step++;
			v_old = v_new;
		}
	}
	cout << accept_step << endl;
	
	return 0;
}
		

