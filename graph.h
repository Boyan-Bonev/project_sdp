#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <set>
#include <string>
#include <vector>
#include <iostream>

using Edge = std::pair<int,int>; // to, value
struct Vertex {
    std::string name;
    std::vector<Edge> adj;
    bool visited = false;
    bool operator== (Vertex const& other) { return name == other.name; }
};

static const size_t INF = 100000;
class Graph {
    size_t size;
    std::vector<Vertex> verts;
public:
    int timeToExplore;
    Graph(int vertsAmount) : size (vertsAmount) { verts.reserve(size); }
    Graph(std::string const& fileName);
    int getSize () const { return size; }
    int getTime () const { return timeToExplore; }
    int findVertIdx (std::string const& _name);
    void addEdge(int fromIdx, int toIdx, int value) {
        verts[fromIdx].adj.push_back(Edge(toIdx,value));
    }
    int shortestPath(int start, int end);
    void visitMost (bool goingBack, int const& startEnd, int currIdx,int timeLeft, int visitedPlaces, std::ostream& os = std::cout);
    void bestTravel (std::string startingName, std::ostream& os = std::cout) {
        int startingIdx = findVertIdx(startingName);
        if (startingIdx == -1) {
            throw std::runtime_error ("Element doesn't exist in this graph!");
        }
        visitMost(false,startingIdx,startingIdx,timeToExplore,1,os);
    }
};

#include "graph.cpp"

#endif 