/*
 * edgetype.h
 *
 *  Created on: 27 de Abr de 2014
 *      Author: Anaís
 */


#ifndef _EDGETYPE_
#define _EDGETYPE_

/**
 * Classe que enumera os tipos de arestas. Usar EdgeType.UNDIRECTED para uma aresta sem direcção, ou
 * EdgeType.DIRECTED para uma aresta dirigida.
 */
class EdgeType {
 public:
  const static int UNDIRECTED = 0;
  const static int DIRECTED = 1;
};


#endif /* EDGETYPE_H_ */
