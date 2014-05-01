/*
 * Loading.h
 *
 *  Created on: 28 de Abr de 2014
 *      Author: Anaís
 */

#ifndef LOADING_H_
#define LOADING_H_


#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

#include "Menu.h"
#include "Graph.h"
#include "Specialist.h"

using namespace std;

void loadGraphs();
string pickGraphMenu();
Graph* loadGraph(string filename);
void printGraph(Graph gr);


#endif /* LOADING_H_ */
