#include<iostream>
#include<iomanip> //for std:: setprecision
#include<cstdlib> //for malloc and free

using namespace std;

//define the structure for the capacitor
struct _capacitor{
	double* time;
	double* voltage;
	double* current;
	double C;
};

typedef struct _capacitor Capacitor;

//constants
const double delta_t=1e-10;//time step
const double final_time=5e-6;//final time(S)
const int num_timesteps=50000;//total number of timesteps
const double R=1000;//resistance(ohms)
const double C_val=100e-12;//capacitance(F)
const double I_const=1e-2;//constant current(A)
const double V0=10.0;//initial voltage

//function to allocate memory for arrays
void initializeCapacitor(Capacitor* cap)
{
	cap->C =C_val;
	cap->time=new double[num_timesteps];
	cap->voltage=new double[num_timesteps];
	cap->current=new double[num_timesteps];

	//initialize time array
	for(int i=0; i<num_timesteps; i++)
	{
		cap->time[i]=i*delta_t;
	}
}

//function to free memory
void freeCapacitor(Capacitor* cap)
{
	delete[] cap->time;
	delete[] cap->voltage;
	delete[] cap->current;
}

//constant current charging
void constantCurrentCharging(Capacitor* cap)
{
	cap->voltage[0]=0.0;
	cap->current[0]=I_const;

	for(int i=1; i<num_timesteps; i++)
	{
	cap->voltage[i]=cap->voltage[i-1]+(cap->current[i-1]* delta_t/cap->C);
	cap->current[i]=I_const; //throughout const

	//output every 200 timesteps
		if(i%200==0)
		{
			cout<<fixed <<setprecision(6);
			cout<<"[Const Voltage] Time: "<<cap->time[i]<<"s," << "Voltage:" <<cap->voltage[i]<<"V, "<<"Current:" <<cap->current[i]<<"A" <<endl;
		}
	}
}
//constant Voltage Charging
void constantVoltageCharging(Capacitor* cap)
{
	cap->voltage[0]=0.0;
	cap->current[0]=V0/R;

//time iteration loop 
	for(int i=1; i<num_timesteps; i++)
	{
 		cap->current[i]=cap->current[i-1]-(cap->current[i-1]* delta_t/(R* cap->C));
 		cap->voltage[i]=cap->voltage[i-1]+(cap->current[i-1]* delta_t/ cap->C);

 //output every 200 timesteps
  	if(i%200==0)
 		{	
 			cout<<fixed<<setprecision(6);
			cout<<"[const Voltage] Time: "<<cap->time[i]<<"s," <<"Voltage:" <<cap->voltage[i]<<"V, " <<"currnet:" <<cap->current[i]<<"A"<<endl;
		}
	}
}
//main function
int main()
{
	Capacitor cap_current;
	Capacitor cap_voltage;

	//Initialize and simulate const current charging
	initializeCapacitor(&cap_current);
	cout<<"\nsimulating constant current charging:\n";
	constantCurrentCharging(&cap_current);
	freeCapacitor(&cap_current);

	//initialize and simulate const voltage charging
	initializeCapacitor(&cap_voltage);
	cout<<"\nSimulating constant voltage charging:\n";
	constantVoltageCharging(&cap_voltage);
	freeCapacitor(&cap_voltage);

	return 0;
}
