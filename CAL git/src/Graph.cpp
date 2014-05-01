/*
 * Graph.cpp
 *
 *  Created on: 29 de Mar de 2014
 *      Author: Anaís
 */

#include "Graph.h"
#include "Specialist.h"

Vertex::Vertex(Specialist info) {
	this->info = info;
}

Vertex::~Vertex() {

}

Specialist Vertex::getInfo() const {
	return info;
}

vector<Edge> Vertex::getEdges(){
	return edges;
}

void Vertex::addEdge(Vertex *dest, int weight) {
	Edge newEdge(dest, weight);
	edges.push_back(newEdge);
}

int Vertex::removeEdgeTo(Vertex *d) {
	typename vector<Edge>::iterator it = edges.begin();
	//typename vector<Edge<T> >::iterator it2 = edges.end();

	while (it != edges.end()) {
		if (it->dest == d) {
			edges.erase(it);

			return it->weight;
		} else
			it++;
	}

	return 0;
}

Edge::Edge(Vertex *d, int weight) {
	this->dest = d;
	this->weight = weight;
}

Vertex * Edge::getDest(){
	return dest;
}
int Edge::getWeight(){
	return weight;
}

Graph::Graph() {
	totalweight = 0;
}

Graph::~Graph() {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		delete (vertexSet[i]);
}

int Graph::getTotalWeight() {
	return totalweight;
}

void Graph::setTotalWeight(int w) {
	totalweight = w;
}

bool Graph::addVertex(const Specialist &info) {
	typename vector<Vertex*>::iterator it = vertexSet.begin();
	//typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();

	for (; it != vertexSet.end(); it++)
		if ((*it)->info == info)
			return false;

	Vertex *v = new Vertex(info);
	vertexSet.push_back(v);

	return false;
}

bool Graph::addEdge(const Specialist &source, const Specialist &dest, int w) {
	typename vector<Vertex*>::iterator it = vertexSet.begin();
	//typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();

	int found = 0;
	Vertex *vS, *vD;
	while (found != 2 && it != vertexSet.end()) {
		if ((*it)->info == source) {
			vS = *it;
			found++;
		}

		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}

		it++;
	}

	if (found != 2)
		return false;

	vS->addEdge(vD, w);
	int currentweight = this->getTotalWeight();
	int newweight = currentweight + w;
	this->setTotalWeight(newweight);

	return true;
}

bool Graph::removeVertex(const Specialist &in) {
	typename vector<Vertex*>::iterator it = vertexSet.begin();
	typename vector<Vertex*>::iterator ite = vertexSet.end();

	for (; it != ite; it++) {
		// if found
		if ((*it)->info == in) {
			// temporarily save
			Vertex * v = *it;

			// delete
			vertexSet.erase(it);

			typename std::vector<Vertex*>::iterator it1 = vertexSet.begin();
			typename std::vector<Vertex*>::iterator it1e = vertexSet.end();

			for (; it1 != it1e; it1++)
				(*it1)->removeEdgeTo(v);

			delete v;
			return true;
		}
	}

	return false;
}

bool Graph::removeEdge(const Specialist &source, const Specialist &dest) {
	typename vector<Vertex*>::iterator it = vertexSet.begin();
	typename vector<Vertex*>::iterator ite = vertexSet.end();

	int found = 0;
	Vertex *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == source) {
			vS = *it;
			found++;
		}

		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}

		it++;
	}

	if (found != 2)
		return false;

	int weight = vS->removeEdgeTo(vD);
	int currentweight = this->getTotalWeight();
	int newweight = currentweight + weight;
	this->setTotalWeight(newweight);
	return (weight == 0);
}

vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

int Graph::getNumVertex() const {
	return getVertexSet().size();
}

void Graph::subsetSelection(vector<string> skills) {

	vector<Vertex *> set;
	set = this->getVertexSet();
	typename vector<Vertex*>::iterator it = set.begin();
	typename vector<Vertex*>::iterator ite = set.end();

	while (it != ite) {

		if (!((*it)->getInfo().hasProjectSkills(skills))) {
			Specialist spec = (*it)->getInfo();
			this->removeVertex(spec);
		}
		it++;
	}

}

void Graph::primAlgorithm(Graph &prim, vector<string> projskills) {
	vector<string> skills = projskills;
	int vectorlength = 10;
	int comp=20;
	vector<int> comps;
	vector<Vertex *> nextvertex;

	nextvertex.clear();
	for (int i = 0; i < vectorlength; i++) {
		comps.push_back(comp);
	}
	vector<Vertex *> v = this->getVertexSet();
	Vertex firstv = *v[0];


	Specialist firstspec = firstv.getInfo();


	bool done = false;
	int d = 0;
	vector<Vertex *> F;
	F.clear();
	prim.addVertex(firstspec);
	prim.projectNeedsMet(skills, firstspec);

	while ((!done) && (F.size() < vectorlength)) {
		Specialist spec1 = v[d]->getInfo();
		vector<Edge> ed = v[d]->getEdges();

		for (int i = 0; i < ed.size(); i++) {
			if (ed[i].getWeight() < comps[d]) {

				comps[d] = ed[i].getWeight();
				nextvertex.push_back(ed[i].getDest());
			}
		}

		Specialist spec2 = nextvertex[d]->getInfo();
		prim.addVertex(spec2);

		prim.addEdge(spec1, spec2, comps[d]);
		F.push_back(nextvertex[d]);


		if (prim.projectNeedsMet(skills, spec2)) {
			done = true;
		}

		d++;

	}

}

Specialist Graph::getInfoByID(int id) {
	typename vector<Vertex*>::iterator it = vertexSet.begin();
	typename vector<Vertex*>::iterator ite = vertexSet.end();

	Specialist spec;

	while (it != ite) {
		if ((*it)->getInfo().getID() == id) {
			spec = (*it)->getInfo();
			return spec;
		}

		it++;
	}
	return spec;
}

bool Graph::projectNeedsMet(vector<string> &skills, Specialist spe) {
	if (skills.empty())
		return true;
	vector<string> specialistsk = spe.getSkills();

	for (int i = 0; i < skills.size(); i++) {
		for (int j = 0; j < specialistsk.size(); j++) {
			if (skills[i] == specialistsk[j]) {
				skills.erase(skills.begin()+i);
				if (skills.empty()) return true;
			}
		}
	}
	return false;
}

void Graph::printSolution(Graph primsolution) {

	vector<string> specNames;
	int cost = 0;
	vector<Vertex *> specs;
	string name;
	cost = primsolution.getTotalWeight();
	specs = primsolution.getVertexSet();

	for (int i = 0; i < specs.size(); i++) {
		name = (*specs[i]).getInfo().getName();
		specNames.push_back(name);
	}

	cout << endl;
	cout << "Ideal team: " << endl;
	cout << "{";
	for (int j = 0; j < specNames.size(); j++) {
		cout << specNames[j];
		if (j != specNames.size() - 1)
			cout << ", ";

	}


	cout << "}" << endl;
	cout << "Communication cost: " << cost << endl << endl;

	exit(1);

}

void Graph::loadGraph(string str) {


	ifstream fin;
	fin.open(str.c_str());
	if (!fin) {
		cerr << "Unable to open selected graph file." << endl;
		exit(1);
	}

	int nVertexes;
	int id;
	string name;
	int nSkills;
	string sk;
	vector<string> skills;
	vector<int> comps;
	fin >> nVertexes;
	for(int i=0; i<nVertexes; i++)
	{
		fin >> id >> name >> nSkills;

		for (int j=0; j<nSkills; j++)
		{
			fin >> sk;

			skills.push_back(sk);
		}
		Specialist spec(id,name);
		spec.setSkills(skills);
		this->addVertex(spec);
	}

	int nEdges=0;
	int idsource, iddest, compat;
	fin >> nEdges;
	for (int i = 0; i < nEdges; i++) {
			fin >> idsource >> iddest >> compat;
			Specialist spec1, spec2;

			spec1 = this->getInfoByID(idsource);
			spec2 = this->getInfoByID(iddest);
			this->addEdge(spec1, spec2, compat);
		}

}
