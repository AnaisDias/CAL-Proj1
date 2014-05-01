/*
 * Graph.h
 *
 *  Created on: 29 de Mar de 2014
 *      Author: Anaís
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Specialist.h"

using namespace std;

class Edge;
class Graph;

//Vertex
class Vertex
{
public:
    Vertex(Specialist info);
    ~Vertex();
    Specialist getInfo() const;
    vector<Edge> getEdges();
    friend class Graph;

private:
    vector<Edge > edges;
    Specialist info;
    void addEdge(Vertex *dest, int weight);
    int removeEdgeTo(Vertex *d);
};

class Edge {
	Vertex * dest;
	int weight;
public:
	Edge(Vertex *d, int weight);
	Vertex * getDest();
	int getWeight();
	friend class Graph;
	friend class Vertex;
	bool operator<(const Edge& e1) const;
};


class Graph {
	vector<Vertex *> vertexSet;
	int totalweight;

public:
	Graph();
	~Graph();
	int getTotalWeight();
	void setTotalWeight(int w);
	bool addVertex(const Specialist &info);
	bool addEdge(const Specialist &source, const Specialist &dest, int w);
	bool removeVertex(const Specialist &in);
	bool removeEdge(const Specialist &source, const Specialist &dest);
//	void setSubsetGraph(Graph sub);
	void primAlgorithm(Graph &prim, vector<string> projskills);
	void subsetSelection(vector<string> skills);
	vector<Vertex * > getVertexSet() const;
	int getNumVertex() const;
	Specialist getInfoByID(int id);
	bool projectNeedsMet(vector<string> &skills, Specialist spe);
	void printSolution(Graph primsolution);
	void loadGraph(string str);

};


#endif /* GRAPH_H_ */
