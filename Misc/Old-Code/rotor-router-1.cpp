//-----------------------------------------------//
//  RotorRouter-v1
//  Created by Julian M. Rice | July 2018
//-----------------------------------------------//

// LIBRARIES & NAMESPACE ------------------------//
#include <iostream>
#include <string>
using namespace std;

// CONSTANTS ------------------------//
const int EDGE_LIMIT = 10;
const int VERTEX_LIMIT = 10;

// STRUCTS ------------------------//
struct Vertex;

struct Edge {
    Vertex* pointA;
    Vertex* pointB;
};

struct Vertex {
    Vertex();
    void PrintStatus();
    
    int visitedCount = 0, currentIndex = 0, edgeCount = 0;
    string label;
    Edge connectedEdges[EDGE_LIMIT];
};

void testFunction() {
    Edge e1, e2, e3, e4, e5;
    Vertex A, B, C, D;
    Edge incidentToA[EDGE_LIMIT] = {e1, e2, e3};
    Edge incidentToB[EDGE_LIMIT] = {e1, e4, e5};
    Edge incidentToC[EDGE_LIMIT] = {e3, e5};
    Edge incidentToD[EDGE_LIMIT] = {e2, e4};
    e1.pointA =
}

void Vertex::PrintStatus() {
    cout << "----------------------------" << endl;
    cout << "-- VERTEX " << label << endl;
    cout << "-- Times Visited: " << visitedCount << endl;
    cout << "-- Pointing to: " << currentIndex << endl;
    cout << "----------------------------" << endl << endl;
}

struct Node {
    Node* next;
    Vertex v;
};

class LinkedList {
public:
    LinkedList() : head(NULL), size(0) {}
    ~LinkedList();
    void Print();
    void Insert(Vertex v);
    int Size();
private:
    int size;
    Node* head;
};

void LinkedList::Print() {
    Node* mover = head;
    while (mover->next != NULL) {
        mover->v.PrintStatus();
    }
    return;
}

void LinkedList::Insert(Vertex v) {
    if (head == NULL) {
        head = new Node();
        head->next = NULL;
        head->v = v;
        return;
    }
    else {
        Node* mover = head;
        while (mover->next != NULL) {
            mover = mover->next;
        }
        Node* newDude = new Node();
        mover->next = newDude;
        newDude->next = NULL;
        newDude->v = v;
    }
    return;
}

int LinkedList::Size() {
    int count = 1;
    if (head == NULL)
        return 0;
    if (head->next == NULL)
        return count;
    while (head->next != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

struct Graph {
    //Functions
    Graph(Vertex V[], Edge E[]);
    
    //Variables
    LinkedList V;
};

// FUNCTIONS PROTOTYPES ------------------------//
void initializeGraph();


int main(int argc, const char * argv[]) {
    
}

// FUNCTIONS ------------------------//
void initializeGraph () {
    
}