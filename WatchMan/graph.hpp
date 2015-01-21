#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>

enum BFS_COLOR { WHITE, GRAY, BLACK };
constexpr int BFS_INFINITY = 2147483646;

template <typename T>
struct Vertex {
	Vertex(T v)
		: value(v), color(WHITE), d(BFS_INFINITY), dtopred(BFS_INFINITY), pred(nullptr) { }

	Vertex(const Vertex<T>& v)
		: value(v.value), color(v.color), d(v.d), dtopred(v.dtopred), pred(v.pred) { }

	Vertex() { }
	~Vertex() { }
	
	T value;

	//fields necessary for BFS
	BFS_COLOR color;
	int d; //number of edges to get there
	Vertex<T>* pred;
	int dtopred; //distance to pred

	bool operator==(const Vertex<T> &other) const {
		return this->value == other.value;
  	}

  	bool operator!=(const Vertex<T> &other) const {
  		return not(this->value == other.value);
  	}

  	//required for inheriting from map
  	bool operator<(const Vertex<T> &other) const {
		return this->value < other.value;
  	}
};

template <typename T>
struct VertexFactory : std::vector< Vertex<T>* > {

	~VertexFactory() { this->clear(); }

	Vertex<T>* make_vertex(T value) {
		for(auto v : *this) {
			if(v->value == value)
				return v;
		}
		Vertex<T>* v = new Vertex<T>(value);
		this->push_back(v);
		return v;
	}
};

template <typename T>
struct Edge {
	Edge(Vertex<T>* src, Vertex<T>* dest, int w) 
		: src(src), dest(dest), weight(w) { }


	Vertex<T>* dest; //the destination vertex
	Vertex<T>* src;

	int weight;
	int capacity() { return weight; }

	bool operator==(const Edge<T> &other) const {
		return (*dest == *other.dest) && (*src == *other.src) && (weight == other.weight);
  	}

  	bool operator!=(const Vertex<T> &other) const {
  		return not(*this == other);
  	}
};

template <typename T>
struct EdgeFactory : std::vector< Edge<T>* > {

	~EdgeFactory() { this->clear(); }

	Edge<T>* make_edge(Vertex<T>* src, Vertex<T>* dest, int w) {
		for(auto edge : *this) {
			if(*(edge->src) == *src && *(edge->dest) == *dest && edge->weight == w)
				return edge;
		}
		Edge<T>* e = new Edge<T>(src, dest, w);
		this->push_back(e);
		return e;
	}
};


template <typename T>
struct AdjacencyList : std::list< Edge<T>* > {

	bool contains(Edge<T>* e) {
		for(auto edge : *this) {
			if(*e == *edge) {
				return true;
			}
		}
		return false;
	}
};

template <typename T>
struct Graph : std::map< Vertex<T>, AdjacencyList<T> > {
	//You can assume all the basic functions from map

	EdgeFactory<T>* ef = new EdgeFactory<T>();

	void add_vertex(Vertex<T>* v) {
		if(this->find(*v) == this->end()) {
			AdjacencyList<T> al;
			this->emplace(*v, al);
		}
	}

	//function to add an edge
	void add_edge(Vertex<T>* src, Vertex<T>* dest, int capacity) {
		//check that the source and destination arent the same
		if(src == dest)
			return;

		// check that the destination is in the graph
		// if not we need to add it
		if(this->find(*dest) == this->end()) {
			AdjacencyList<T> al;
			this->emplace(*dest, al);
		}

		//check that the vertex isnt already in the graph
		//if its not
		if(this->find(*src) == this->end()) {
			//add it to the graph
			//add the dest to its adjacency list
			Edge<T>* e = ef->make_edge(src, dest, capacity);
			AdjacencyList<T> al;
			al.push_back(e);
			this->emplace(*src, al);
		}
		//if it is already in the graph then add the dest to its adjacency list
		else {
			//get the pair
			auto vertex = this->find(*src);
			//add the edge to the adjacency list
			Edge<T>* e = ef->make_edge(src, dest, capacity);
			//checks to see if the edge is already in the adjacency list
			if(!vertex->second.contains(e))
				vertex->second.push_back(e);
		}
	}

	//returns the nodes adjacent to the node v
	AdjacencyList<T> get_adjacent_list(Vertex<T> v) {
		auto search = this->find(v);
		if(search != this->end()) {
			return search->second; 
		}
		else {
			//return empty adj list
			AdjacencyList<T> empty;
			return empty;
		}

	}

	void print() {
		for(auto v : *this) {
			std::cout << '|' << v.first.value << "| -> ";
			for(auto e : v.second) {
				std::cout << e->dest->value << '(' << e->capacity() << ") ->";
			}
			std::cout << '\n';
		}
	};

	void adv_print() {
		for(auto v : *this) {
			std::cout << '|' << v.first.value <<  '(' << v.first.color << ',' << v.first.d << ')' << "| -> ";
			for(auto e : v.second) {
				std::cout << e->dest->value << '(' << e->dest->color << ',' << e->dest->d << ") ->";
			}
			std::cout << '\n';
		}
	};
};

#endif