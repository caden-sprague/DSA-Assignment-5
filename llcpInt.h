#ifndef LLCP_INT_H
#define LLCP_INT_H

#include <iostream>

struct Node
{
   int data;
   Node *link;
};


// prototype for BuildDistinctMirrorPairs of Assignment 5 Part 1
// (see assignment description for the function's specification)


////////////////////////////////////////////////////////////////////
// prototypes for 11 functions (for use by Assign05P1.cpp ONLY)
// (NOT for use by BuildDistinctMirrorPairs of Assignment 5 Part 1)
int    FindListLength(Node* headPtr);
bool   IsSortedUp(Node* headPtr);
void   InsertAsHead(Node*& headPtr, int value);
void   InsertAsTail(Node*& headPtr, int value);
void   InsertSortedUp(Node*& headPtr, int value);
bool   DelFirstTargetNode(Node*& headPtr, int target);
bool   DelNodeBefore1stMatch(Node*& headPtr, int target);
void   ShowAll(std::ostream& outs, Node* headPtr);
void   FindMinMax(Node* headPtr, int& minValue, int& maxValue);
double FindAverage(Node* headPtr);
void   ListClear(Node*& headPtr, int noMsg = 0);
////////////////////////////////////////////////////////////////////

#endif

