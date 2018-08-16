//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  main.cpp    ---------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

// LIBRARIES & NAMESPACE ----------------------------------------------------
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"
#include "StatList.h"
#include "Functions.h"
using namespace std;

// INT MAIN -----------------------------------------------------------------
int main(int argc, const char * argv[]) {
    Graph g;
    StatList stats;
    
    Vertex A = Vertex("A",0,0,0); Vertex B = Vertex("B",0,0,0); Vertex C = Vertex("C",0,0,0);
    Vertex D = Vertex("D",0,0,0); Vertex E = Vertex("E",0,0,0); Vertex F = Vertex("F",0,0,0);
    Vertex G = Vertex("G",0,0,0); Vertex H = Vertex("H",0,0,0); Vertex I = Vertex("I",0,0,0);
    
    Vertex *Ap = &A; Vertex *Bp = &B; Vertex *Cp = &C; Vertex *Dp = &D; Vertex *Ep = &E;
    Vertex *Fp = &F; Vertex *Gp = &G; Vertex *Hp = &H; Vertex *Ip = &I;
    
    Edge e1a(Ap, Bp, 0, "AB"); Edge e1b(Bp, Ap, 0, "BA");
    Edge e2a(Ap, Cp, 1, "AC"); Edge e2b(Cp, Ap, 1, "CA");
    Edge e3a(Bp, Cp, 2, "BC"); Edge e3b(Cp, Bp, 2, "CB");
    Edge e4a(Bp, Gp, 3, "BG"); Edge e4b(Gp, Bp, 3, "GB");
    Edge e5a(Cp, Dp, 4, "CD"); Edge e5b(Dp, Cp, 4, "DC");
    Edge e6a(Cp, Ep, 5, "CE"); Edge e6b(Ep, Cp, 5, "EC");
    Edge e7a(Cp, Fp, 6, "CF"); Edge e7b(Fp, Cp, 6, "FC");
    Edge e8a(Cp, Gp, 7, "CG"); Edge e8b(Gp, Cp, 7, "GC");
    Edge e9a(Cp, Hp, 8, "CH"); Edge e9b(Hp, Cp, 8, "HC");
    Edge e10a(Dp, Ip, 9, "DI"); Edge e10b(Ip, Dp, 9, "ID");
    Edge e11a(Ep, Fp, 10, "EF"); Edge e11b(Fp, Ep, 10, "FE");
    Edge e12a(Ep, Gp, 11, "EG"); Edge e12b(Gp, Ep, 11, "GE");
    
    Edge* e1aP = &e1a; Edge* e1bP = &e1b;
    Edge* e2aP = &e2a; Edge* e2bP = &e2b;
    Edge* e3aP = &e3a; Edge* e3bP = &e3b;
    Edge* e4aP = &e4a; Edge* e4bP = &e4b;
    Edge* e5aP = &e5a; Edge* e5bP = &e5b;
    Edge* e6aP = &e6a; Edge* e6bP = &e6b;
    Edge* e7aP = &e7a; Edge* e7bP = &e7b;
    Edge* e8aP = &e8a; Edge* e8bP = &e8b;
    Edge* e9aP = &e9a; Edge* e9bP = &e9b;
    Edge* e10aP = &e10a; Edge* e10bP = &e10b;
    Edge* e11aP = &e11a; Edge* e11bP = &e11b;
    Edge* e12aP = &e12a; Edge* e12bP = &e12b;
    
    A.addEdge(e1aP); A.addEdge(e2aP);
    B.addEdge(e1bP); B.addEdge(e3aP); B.addEdge(e4aP);
    C.addEdge(e2bP); C.addEdge(e3bP); C.addEdge(e5aP);
    C.addEdge(e6aP); C.addEdge(e7aP); C.addEdge(e8aP); C.addEdge(e9aP);
    D.addEdge(e5bP); D.addEdge(e10aP);
    E.addEdge(e6bP); E.addEdge(e11aP); E.addEdge(e12aP);
    F.addEdge(e7bP); F.addEdge(e11bP);
    G.addEdge(e4bP); G.addEdge(e8bP); G.addEdge(e12bP);
    H.addEdge(e9bP);
    I.addEdge(e10bP);
    
    g.insertVertex(Ap); g.insertVertex(Bp); g.insertVertex(Cp);
    g.insertVertex(Dp); g.insertVertex(Ep); g.insertVertex(Fp);
    g.insertVertex(Gp); g.insertVertex(Hp); g.insertVertex(Ip);
    g.insertEdge(e1aP); g.insertEdge(e1bP);
    g.insertEdge(e2aP); g.insertEdge(e2bP);
    g.insertEdge(e3aP); g.insertEdge(e3bP);
    g.insertEdge(e4aP); g.insertEdge(e4bP);
    g.insertEdge(e5aP); g.insertEdge(e5bP);
    g.insertEdge(e6aP); g.insertEdge(e6bP);
    g.insertEdge(e7aP); g.insertEdge(e7bP);
    g.insertEdge(e8aP); g.insertEdge(e8bP); 
    g.insertEdge(e9aP); g.insertEdge(e9bP); 
    g.insertEdge(e10aP); g.insertEdge(e10bP); 
    g.insertEdge(e11aP); g.insertEdge(e11bP); 
    g.insertEdge(e12aP); g.insertEdge(e12bP);
    
    //Extra variables (arrays) used to calculate average visit values
    double arrayOfResults[10] = { 0,0,0,0,0,0,0,0,0,0 };       //Vertices
    double arrayOfEdgeResults[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; //Edges
    
    //This is for accessing the name when looking at average edge visit frequency
    Edge* edgeList[12] = { e1aP, e2aP, e3aP, e4aP, e5aP,
                           e6aP, e7aP, e8aP, e9aP, e10aP, e11aP, e12aP };
    
    int graphSize = g.getVertexCount(); //Number of vertices in graph
    int stabPeriod = 0;                 //Stabilization period (all tests combined)
    int temp = 0;                       //Stabilization period (for one test)
    int input = instructions();         //Find the number of steps (traversal)
    int tests = testInstructions();     //Find the number of tests (accuracy)
    int maximumLockInTime = g.getEdgeCount()*3*2; //Diameter is 3 in this case
    double bonusResults[maximumLockInTime+1];     //Distribution array for s. period
    string tempCycle;                   //Holds Euler cycle for one test
    vector<string> allEulerCycles;      //Holds every Euler cycle (all tests)
    
    //Initialize all possible stabilization to 0.
    for (int i = 0; i < maximumLockInTime+1; i++) {
        bonusResults[i] = 0;
    }
    
    //Start the rotor-router algorithm/mechanism!
    for (int i = 0; i < tests; i++) {
        //Start at a random vector
        Vertex* randomStart = g.randomVertex();
        
        //Returns the stabilization period, and furthermore contains the
        //mobile agent function (rotor-router algorithm).
        temp = quasiWalk(input, g, randomStart, arrayOfResults,
                         arrayOfEdgeResults, stats, tempCycle);
        
        //Add the Euler cycle for this specific test into the vector,
        //then reset the temporary string.
        allEulerCycles.push_back(tempCycle);
        tempCycle = "";
        
        //Add 1 to the stabilization period distribution array
        bonusResults[temp]++;
        stabPeriod += temp;
        
        //Find the (potentially new) max and min after this test is done
        if (temp > stats.getMax())
            stats.setMax(temp);
        if (temp < stats.getMin())
            stats.setMin(temp);
    }
    
    //Overall Results
    cout << "-RESULTS--------------------------" << endl;
    cout << "-Number of STEPS per TEST: " << input << endl;
    cout << "-Number of TESTS: " << tests << endl;
    
    //Vertex Average Visit Frequency
    cout << "  Average Visited Count for Vertices" << endl;
    for (int i = 0; i < graphSize; i++) {
        arrayOfResults[i] /= tests;
        cout << "    " << g.returnVertex(i)->getName() << ": "
             << arrayOfResults[i] << endl;
    }
    
    //Edge Average Visit Frequency
    cout << "  Average Visited Count for Edges" << endl;
    for (int i = 0; i < g.getEdgeCount() / 2; i++) {
        arrayOfEdgeResults[i] /= tests;
        cout << "    " << edgeList[i]->getName() << ": "
             << arrayOfEdgeResults[i] << endl;
    }
    
    //Every Euler Cycle (lock-in, all tests)
    cout << "  All Euler Cycles" << endl;
    for (int i = 0; i < allEulerCycles.size(); i++) {
        cout << "    Cycle " << i+1 << ": "
             << allEulerCycles[i] << endl;
    }
    
    //Stabilization Period Data
    cout << "  Stabilization Period Data" << endl;
    stats.setSum(stabPeriod);
    stats.setAvg(stats.getSum(), tests);
    cout << "    Worst Case: " << stats.getMax() << endl;
    cout << "    Average Case: " << stats.getAvg() << endl;
    cout << "    Best Case: " << stats.getMin() << endl;
    cout << "----------------------------------" << endl;
    
    //Stabilization Period Distribution
    for (int i = 0; i < maximumLockInTime+1; i++) {
        cout << i << ": " << bonusResults[i] << endl;
    }
    
    cout << "-END------------------------------" << endl << endl;
    return 0;
}
