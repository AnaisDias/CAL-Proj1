/*
 * Menu.cpp
 *
 *  Created on: 26 de Abr de 2014
 *      Author: Anaís
 */
#include <iostream>
#include <vector>
#include "Menu.h"
#include "Loading.h"

using namespace std;

Graph* graph = new Graph;
int mainMenu(){
	cout << endl;
	cout << "---------------------------------" << endl;
	cout << "      Optimal Team Formation     " << endl;
	cout << "---------------------------------" << endl;
	cout << endl;
	cout << "1. Visualize graph" << endl;
	cout << "2. Insert project and calculate team" << endl;
	cout << "3. Exit" << endl;
	cout << endl;

	int input;
	cout << "Choose an option:" << endl;
	cout << "> ";
	cin >> input;

	switch (input) {
	case 1:
		visualizeGraphMenu();
		break;
	case 2:
		calculationMenu(insertProjectMenu());
		break;
	case 3:
		return -1;
	default:
		cout << endl;
		cout << "Invalid input." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Press enter...";
		cin.get();
		mainMenu();
		break;
	}

	return 0;
}

void visualizeGraphMenu(){
	Graph* graph = new Graph;
	graph->loadGraph(pickGraphMenu());
	printGraph(*graph);
}

vector<string> insertProjectMenu(){
	vector<string> projectSkills;
	cout << endl;
	cout << "---------------------------------" << endl;
	cout << "         Insert Project          " << endl;
	cout << "---------------------------------" << endl;
	cout << endl;
	cout << "Please insert project skills" << endl;
	cout << "(insert 0 when done)" << endl;
	cout <<  endl;

	string input;
	cout << "> ";
	while(input!="0"){
		cin >> input;
		if(input != "0")
			projectSkills.push_back(input);
		cout << endl;
	}

	return projectSkills;
}

void calculationMenu(vector<string> skills){

	string str= pickGraphMenu();

	Graph prim;
	graph->loadGraph(str);
	(*graph).subsetSelection(skills);
	(*graph).primAlgorithm(prim, skills);
	printGraph(prim);
	graph->printSolution(prim);
	cout<<"fim do print\n";
	//printGraph(prim);
}


