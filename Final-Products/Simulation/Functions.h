//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  Functions.h    ------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#ifndef Functions_h
#define Functions_h

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <utility>
#include <cstdlib>

class Vertex;
class Edge;
class Graph;
class StatList;

using namespace std;

int randomInteger(int min, int max);
int instructions();
int testInstructions();
int quasiWalk(int steps, Graph g, Vertex* s, double resultsV[],
              double resultsE[], StatList stats, string& temp);
int mobileAgent(Graph graph, Vertex* start, int iterations, string& temp);
int findEulerCycle(Graph graph, string& temp);

#endif
