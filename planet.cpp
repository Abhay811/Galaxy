//planet.cpp file for HW1
//Purpose: This file contains the class implementation for the planet class and its derivatives rocky and gas.
//         
#include "planet.h"
#include <iostream>
using namespace std;

//Constructs an empty planet setting all data members to a zero value.
planet::planet() : planet_name(NULL), atmosphere(NULL), next_p(NULL), prev_p(NULL), distance_from_sun(0), temperature(0), planet_mass(0), rings(0), moons(0) {}

//Eecursive planet destructor deallocates any dynamically allocated variables and also the next planet.
planet::~planet()
{
	if (planet_name) delete[]planet_name;
	if (atmosphere) delete[]atmosphere;
	if (next_p) delete next_p;
}

//Copy constructor assigns all variables to source's value and sets previous and next planet to NULL
planet::planet(const planet& source)
{
	planet_name = new char[strlen(source.planet_name) + 1]; strcpy(planet_name, source.planet_name);
	atmosphere = new char[strlen(source.atmosphere) + 1]; strcpy(atmosphere, source.atmosphere);
	next_p = prev_p = NULL;
	type = source.type;
	distance_from_sun = source.distance_from_sun;
	temperature = source.temperature;
	planet_mass = source.planet_mass;
	moons = source.moons;
	rings = source.rings;
}

//Returns an integer value denoting the type of the planet (Rocky or Gas).
int planet::get_type()
{
	return type;
}

//Returns by reference a pointer to the next planet attached in the DLL
planet*& planet::next()
{
	return next_p;
}

//Returns by reference a pointer to the previous planet attached in the DLL
planet*& planet::prev()
{
	return prev_p;
}

//Outputs all information regarding the planet and also calculates for possibility of life.
//Returns true if life is found
bool planet::declare_life()
{
	bool check = 0;
	if (type == -1) return 0;
	cout << "   Executing life detection algorithm.\n   Here are the planet details:\n";
	cout << "   Planet Name: " << planet_name << endl;
	cout << "   Planet Type: "; if (type) cout << "Rocky\n"; else cout << "Gassy\n";
	cout << "   Planet Mass: " << planet_mass << " Earths (1E = 5.972*10^24 kg)" << endl;
	cout << "   Temperature: " << temperature << " Celsius (C)" << endl;
	cout << "   Atmosphere: " << atmosphere << endl;
	cout << "   Distance from the sun: " << distance_from_sun << " million km" << endl;
	cout << "   Presence of rings: "; if (rings) cout << "Yes\n"; else cout << "No\n";
	cout << "   Number of Moons: " << moons << endl;
	//the strstr() function returns true if 'unlikely' is contained within "atmosphere". 
	if (!strstr(atmosphere, "unlikely") && temperature > -30 && temperature < 70 && distance_from_sun>70 && distance_from_sun < 170) {
		cout << "   PLANET SUPPORTS LIFE\n\n";
		check = 1;
	}
	else cout << "   PLANET DOES NOT SUPPORT LIFE\n\n";
	return check;
}

//Constructor calls the default version of planet() automaticalls
rocky::rocky() {}

//Calls the copy constructor of planet passing in the source 'rocky planet'
rocky::rocky(const rocky& source) : planet(source) {}

//Calls the default constructor of planet and sets the planet's distance from the sun to the passed in value.
//For a rocky planet, the atmospheres are unique, the temperatures are more constrained and the planet mass is lesser.
//All the variables set are not unique to rocky or gas, and therefore can be called within planet itself
rocky::rocky(double sun_distance) : planet()
{
	distance_from_sun = sun_distance;
	char* temp = new char[TEMP];
	strcpy(temp, "planet");
	get_random(temp);
	planet_name = new char[strlen(temp) + 1];
	strcpy(planet_name, temp);
	delete[]temp;
	temp = new char[TEMP];
	strcpy(temp, "rocky");
	get_random(temp);
	atmosphere = new char[strlen(temp) + 1];
	strcpy(atmosphere, temp);
	delete[]temp;
	type = 1;
	temperature = rand() % 350 - 50; //temperatures between -50 and 300 degrees
	planet_mass = double(rand() % 250) / 100 + 0.1;
	moons_and_rings(); //calls another function to set values for the moons and rings
}

//Sets the moons and rings values appropriately
void rocky::moons_and_rings()
{
	int dice_roll = rand() % 8 + 1;
	if (dice_roll == 8) rings = 1; //Chances of a rocky planet with rings are 1/8
	dice_roll = rand() % 8 + 1;
	if (dice_roll == 8) moons = rand() % 4 + 1; //Chances of having a moon is equally low and the number of them is limited between 1-5.
}

//Calls the default planet constructor first
gas::gas() {}

//Calls the planet copy constructor passing source
gas::gas(const gas& source) : planet(source) {}

//Calls the default constructor of planet and sets the planet's distance from the sun to the passed in value.
//For a gas planet, the atmospheres are unique, the temperatures are less constrained and the planet mass is higher.
gas::gas(double sun_distance) : planet()
{
	distance_from_sun = sun_distance;
	char* temp = new char[TEMP];
	strcpy(temp, "planet");
	get_random(temp);
	planet_name = new char[strlen(temp) + 1];
	strcpy(planet_name, temp);
	delete[]temp;
	temp = new char[TEMP];
	strcpy(temp, "gas");
	get_random(temp);
	atmosphere = new char[strlen(temp) + 1];
	strcpy(atmosphere, temp);
	delete[]temp;
	type = 0;
	temperature = rand() % 600 - 150; //Temperatures between -150 and 450 degrees celsius
	planet_mass = double(rand() % 1000) / 100 + 0.1; //Planet mass in number of earths (E)
	moons_and_rings();
}

//Sets the moons and rings values appropriately
void gas::moons_and_rings()
{
	int dice_roll = rand() % 2 + 1;
	if (dice_roll == 2) rings = 1; //chances of having rings and moons are higher
	dice_roll = rand() % 2 + 1;
	if (dice_roll == 2) moons = rand() % 10 + 5; //number of moons possible are also higher
}
