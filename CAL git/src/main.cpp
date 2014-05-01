/*
 * Files.cpp
 *
 *  Created on: 30 de Mar de 2014
 *      Author: Anaís
 */
//#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

#include "Menu.h"
#include "Graph.h"
#include "Specialist.h"
#include "Loading.h"

using namespace std;



int main()
{
	loadGraphs();
	mainMenu();
	return 0;


}



