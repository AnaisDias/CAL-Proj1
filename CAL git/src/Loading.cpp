/*
 * Loading.cpp
 *
 *  Created on: 28 de Abr de 2014
 *      Author: Anaís
 */

#include "Loading.h"
#include "graphviewer.h"

using namespace std;



vector<string> graphFilenames;

void loadGraphs()
{
	graphFilenames.clear();

	ifstream fin;
	fin.open("graphs.txt");
	if (!fin) {
		cerr << "Unable to open file containing graph filenames." << endl;
		exit(1);
	}

	int nGraphs;
	string filename;
	fin >> nGraphs;
	for (int i = 0; i < nGraphs; i++) {
		fin >> filename;
		graphFilenames.push_back(filename);
	}
}

string pickGraphMenu(){
	bool done;
	unsigned int input;

	do {
		done = false;

		cout << endl;
		cout << "Existing graphs: " << endl;
		for (unsigned int i = 0; i < graphFilenames.size(); i++)
			cout << i + 1 << ". " << graphFilenames[i] << endl;

		cout << endl;

		cout << "Choose a graph: ";
		cin >> input;
		if (1 <= input && input <= graphFilenames.size())
			done = true;
		else {
			cin.clear();
			cin.ignore(10000, '\n');

			cout << endl;
			cout << "Invalid input. Press enter. " << endl;
			cin.get();
		}
	} while (!done);

	return graphFilenames[input-1];
}



void printGraph(Graph gr){
	int incares = 0;

	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);

	vector<Vertex *> verSet= gr.getVertexSet();
	for (int i = 0; i < (gr.getVertexSet().size()/2); i++) {
		int id= verSet[i]->getInfo().getID();
		gv->addNode(id, 50, 120 + 120 * i);
		gv->setVertexLabel(id,verSet[i]->getInfo().getName());
		gv->setVertexColor(id,"blue");


	}

	for (int i = (gr.getVertexSet().size()/2); i <(gr.getVertexSet().size()); i++) {
		int id= verSet[i]->getInfo().getID();
		gv->addNode(id, 350, 120 + 120 * (i-(gr.getVertexSet().size()/2)));
		gv->setVertexLabel(id,verSet[i]->getInfo().getName());
		gv->setVertexColor(id,"blue");
	}



	for (int i = 0; i < verSet.size(); i++) {
		vector<Edge> ed = verSet[i]->getEdges();
		for (int j = 0; j < ed.size(); j++) {
			int l = ed[j].getDest()->getInfo().getID();
			int orig= verSet[i]->getInfo().getID();
			gv->addEdge(incares, orig, l, EdgeType::UNDIRECTED);

			int s = ed[j].getWeight();

			gv->setEdgeWeight(incares, s);

			if (ed[j].getWeight()>=5) {
				gv->setEdgeThickness(incares,1);
				gv->setEdgeColor(incares,"blue");
			} else{
				gv->setEdgeThickness(incares,2);
				gv->setEdgeColor(incares,"green");
			}

			incares++;
		}
	}
	gv->rearrange();
	system("pause");
}



