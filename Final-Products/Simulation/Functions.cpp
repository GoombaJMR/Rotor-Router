//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  Functions.cpp    ----------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#include "Functions.h"
#include "Edge.h"
#include "Vertex.h"
#include "StatList.h"
#include "Graph.h"
using namespace std;

int randomInteger(int min, int max) {
    //This function computes a random integer between min and max
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

int instructions() {
    //This function asks for the step count (S)
    int trips;
    cout << "[Console] Please input the number of times the mobile agent moves: ";
    cin >> trips;
    return trips;
}

int testInstructions() {
    //This function asks for the test count (T)
    int testCount;
    cout << "[Console] Please input the number of times the test will be run: ";
    cin >> testCount;
    return testCount;
}

int mobileAgent(Graph graph, Vertex* start, int iterations, string& temp) {
    //This function is the full implementation of the rotor-router mechanism
    Vertex* destination = NULL;
    for (int i = 0; i < iterations; i++) {
        //Access the next exit value of the current vertex
        int currentIndex = start->getIndex();
        
        //Increase the visit count for the edge that will be crossed by one
        start->edgeToCross(start, currentIndex)->incrementVisitCount();
        
        //Set the edge to traverse to be the index in the fixed cyclic order
        Edge* cross = start->edgeToCross(start, currentIndex);
        destination = cross->getEndVertex();
        
        //Output the mobile agent movement
        cout << "[Step " << i+1 << "] Agent crosses the EDGE "
        << cross->getStartVertex()->getName() << cross->getEndVertex()->getName()
        << " and is now at VERTEX " << cross->getEndVertex()->getName() << endl;
        
        //Add this traversed edge to the traversal history vector
        graph.insertEdgeToOverall(cross); //New
        
        //Increase the visit count of the vertex that the agent has arrived at
        destination->incrementVisited();
        
        //Change the index (update order) of the previous vertex
        start->changeIndex();
        
        //Change the starting point to where the mobile agent is at now
        start = destination;
    }
    //Return the stabilization period and set cycle to string temp
    int stabP = findEulerCycle(graph, temp);
    cout << "  Stabilization Period: " << stabP << endl;
    return stabP;
}

int findEulerCycle(Graph graph, string& temp) {
    //This function finds the lock-in Euler cycle for a single test
    int i = 0, currentCheck = 0, newCounter = 0, stabilizationPeriod = 0;
    Edge* startingEdge = NULL;
    int startingIndex = 0;
    int edgesTraversed = 0;
    while (true) {
        //Check if the edge has been visited before (in this function)
        currentCheck = graph.returnEdgeFromOverall(i)->getCheck();
        
        //Increase the number of edges traversed by one
        edgesTraversed++;
        
        //If the edge has been visited once and we are at the graph edge count...
        if (currentCheck == 1 && edgesTraversed == graph.getEdgeCount()+1) {
            //At this point, the agent has crossed every edge once
            //We can break out of the loop and record the Euler cycle
            break;
        }
        //An edge from earlier has been met again; we started midway through
        //a cycle and need to restart our search
        else if (currentCheck == 1 && edgesTraversed != graph.getEdgeCount()+1) {
            //Reset all visit counts for each edge (in this function) to 0
            for (int j = 0; j < graph.getOverallCount(); j++) {
                graph.returnEdgeFromOverall(j)->resetCycleCountCheck();
            }
            //Increase the point where we start counting from
            startingIndex++;
            i = startingIndex-1;
            edgesTraversed = 0;
        }
        //If the edge hasn't been visited, increment to 1 to mark it visited
        else if (currentCheck == 0) {
            graph.returnEdgeFromOverall(i)->incrementCheck();
        }
        i++;
    }
    //Get the edge from the overall history and set it to startingEdge
    startingEdge = graph.returnEdgeFromOverall(startingIndex);
    
    //The stabilization period is how many steps away from 0 the
    //Euler cycle's starting edge is.
    stabilizationPeriod = startingIndex;
    while (newCounter != graph.getEdgeCount()) { //m edges long
        //From the startingIndex, add each edge to the euler cycle vector
        graph.insertEdgeToCycle(startingEdge);
        startingIndex++;
        startingEdge = graph.returnEdgeFromOverall(startingIndex);
        newCounter++;
    }
    
    for (int k = 0; k < graph.getEdgeCount(); k++) {
        //Add the edge name to the temp, then an arrow to indicate movement
        temp += graph.returnEdgeFromCycle(k)->getName();
        temp += "->";
    }
    cout << endl;
    return stabilizationPeriod;
}

int quasiWalk(int steps, Graph g, Vertex* s, double resultsV[], double resultsE[], StatList stats, string& temp) {
    int graphVertexCount = g.getVertexCount();
    int currentEdgeID = 0;  //The ID of an edge (for undirected edges)
    int stabilization = 0;  //The result from mobileAgent gets placed in this variable
    Edge* currentEdge = NULL;
    
    //Calculate the stabilization period
    stabilization = mobileAgent(g, s, steps, temp);
    
    //Obtain data on visit counts (edge/vertex)
    //and clear all visit counts for the next iteration to occur
    for (int i = 0; i < graphVertexCount; i++) {
        resultsV[i] += g.returnVertex(i)->getVisited();
        for (int j = 0; j < g.returnVertex(i)->getEdgeCount(); j++) {
            currentEdge = g.returnVertex(i)->returnEdge(j);
            currentEdgeID = currentEdge->getID();
            resultsE[currentEdgeID] += currentEdge->getVisitCount();
            currentEdge->resetVisitCountEdge();
            currentEdge->resetCycleCountCheck();
        }
        g.returnVertex(i)->setVisitToZero();
        g.returnVertex(i)->resetAllEdgeVisits();
    }
    return stabilization;
}
