#include "graph.h"
#include <iostream>
#include <fstream>
#include <set>

int Graph::findVertIdx (std::string const& _name) {
    int i = verts.size()- 1;
    while (i >= 0) {
        if (verts[i].name == _name) {
            return i;
        }
        i--;
    }
    return -1; //ERROR
}

Graph::Graph(std::string const& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error ("Couldn't open file");
    }
    std::string line;
    std::getline(file,line,'\n');
    int pos = line.find( ' ' );
    size = std::stoi(line.substr(0,pos));
    int edges = std::stoi(line.substr(pos+1));
    std::string currElem;
    int fromIdx, toIdx;
    while (edges > 0) {
        line.clear();
        fromIdx = -1; toIdx = -1;
        std::getline(file,line);
        while ( ( ( pos = line.find( ' ' ) ) != std::string::npos  ) || (!line.empty())) {
            if (pos == -1) {
                currElem = line;
                line.erase();
            }
            else {
                currElem = line.substr(0,pos);
                line.erase(0,pos+1);
            }
            if (fromIdx == -1) {
                fromIdx = findVertIdx(currElem);
                if (fromIdx == -1) {
                    Vertex newVert = Vertex(); newVert.name = currElem;
                    verts.push_back(newVert);
                    fromIdx = verts.size() - 1;
                }
            }
            else if (toIdx == -1) {
                toIdx = findVertIdx(currElem);
                if (toIdx == -1) {
                    Vertex newVert = Vertex(); newVert.name = currElem;
                    verts.push_back(newVert);
                    toIdx = verts.size() - 1;
                }
            }
            else {
                addEdge(fromIdx,toIdx,std::stoi(currElem));
                addEdge(toIdx,fromIdx,std::stoi(currElem));
            }
        }
        edges--;
    }
    std::getline(file,currElem);
    timeToExplore = std::stoi(currElem);
    file.close();
}

// CREDIT TO SDP_2022_23/GROUP2/EXERCISES/GRAPHS
int Graph::shortestPath( int start, int end) {
	// Create a set to store vertices that are being processed 
	std::set< int > setds;

	// Create a vector for distances and initialize all 
	// distances as infinite (INF) 0
	std::vector<int> dist( size, INF );

	// Insert source itself in Set and initialize its 
	// distance as 0. 
	setds.insert( start );
	dist[ start ] = 0;

	/* Looping till all shortest distance are finalized
	then setds will become empty */
	while ( !setds.empty() )
	{
		// The first vertex in Set is the minimum distance 
		// vertex, extract it from set. 
		int u = *( setds.begin() );
		setds.erase( setds.begin() );

		// vertex label is stored in second of pair (it 
		// has to be done this way to keep the vertices 
		// sorted distance (distance must be first item 
		// in pair) 

		for ( const Edge& e : verts[u].adj )
		{
			// Get vertex label and weight of current adjacent 
			// of u. 
			int v = e.first;
			int weight = e.second;

			// If there is shorter path to v through u. 
			if ( dist[ v ] > dist[ u ] + weight )
			{
				/* If distance of v is not INF then it must be in
				our set, so removing it and inserting again
				with updated less distance.
				Note : We extract only those vertices from Set
				for which distance is finalized. So for them,
				we would never reach here. */
				if ( dist[ v ] != INF )
					setds.erase( v );

				// Updating distance of v 
				dist[ v ] = dist[ u ] + weight;
				setds.insert( v );
			}
		}
        
	}
    return dist[end];
}

void Graph::visitMost (bool goingBack, int const& startEnd, int currIdx,int timeLeft, int visitedPlaces, std::ostream& os) {
    if (size == 1) {
        os << verts[0].name << '\n';
        return;
    }
    os << verts[currIdx].name << ' ';
    verts[currIdx].visited = true;
    Edge fastest(MAX,MAX);
    bool over = false;
    while (!over) {
        // all places are visited
        if (visitedPlaces == size) 
            goingBack = true;
        // no time to visit other places
        if (goingBack && visitedPlaces == 1 && startEnd == currIdx) {
            os << '\n';
            break;
        }
        if (!goingBack) {
            fastest.second = MAX;
            for (Edge& edge : verts[currIdx].adj) {
                if (!verts[edge.first].visited && fastest.second > edge.second) {
                    fastest = edge;
                }
            }
            int shortestPathBack = shortestPath(fastest.first,startEnd);
            if (timeLeft - fastest.second - shortestPathBack > 0) {
                os << verts[fastest.first].name << ' ';
                verts[fastest.first].visited = true;
                currIdx = fastest.first;
                timeLeft -= fastest.second;
                ++visitedPlaces;
            }
            else if (timeLeft - fastest.second - shortestPathBack == 0) {
                goingBack = true;
                os << verts[fastest.first].name << ' ';
                currIdx = fastest.first;
                verts[fastest.first].visited = true;
                timeLeft -= fastest.second;
                ++visitedPlaces;
            }
            else {
                goingBack = true;
            }
        }
        else {
            fastest.second = MAX;
            for (Edge& edge : verts[currIdx].adj) {
                if (edge.first == startEnd && timeLeft - edge.second >= 0) {
                    os << verts[startEnd].name << '\n';
                    over = true;
                }
                if (verts[edge.first].visited && fastest.second > edge.second) {
                    fastest = edge;
                }
            }
            if (over) break;
            verts[fastest.first].visited = false;
            currIdx = fastest.first;
            timeLeft -= fastest.second;
            os << verts[fastest.first].name << ' ';
        }
    }
    for (Vertex& vert : verts) {
        vert.visited = false;
    }
}