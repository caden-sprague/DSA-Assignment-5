#include <iostream>
#include <cstdlib>
#include "llcpInt.h"
using namespace std;


// definition of BuildDistinctMirrorPairs of Assignment 5 Part 1
// ( ***** put at near top to facilitate printing and marking ***** )
// by (to help ID your code): <CADEN SPRAGUE>

void BuildDistinctMirrorPairs (Node*& head)
{
   if (head == 0) return;  // Empty list, nothing to do

   Node* current = head;
   Node* duplicates = 0;
   
   // Step 1: Remove duplicates
   while (current != 0) 
   {
      Node* runner = current;

      // Check all subsequent nodes for duplicates
      while (runner->link != 0) 
      {
         if (runner->link->data == current->data) 
         {
            // Duplicate found 
            Node* theDuplicate = runner->link;

            // remove it from head list 
            runner->link = runner->link->link;

            // checking if recycle bin containts theDuplicate->data
            Node* duplicatesIterator = duplicates;
            while(duplicatesIterator != 0)
            {
               if(duplicatesIterator->data == theDuplicate->data)
               {
                  break;
               }
               else
               {
                  duplicatesIterator = duplicatesIterator->link;
               }
            }

            if (duplicatesIterator != 0) 
            {
               // add to duplicates list
               theDuplicate->link = duplicates;
               duplicates = theDuplicate; 
            }
            else 
            {
               // or trash it
               delete theDuplicate;
            }

         } 
         else 
         {
            runner = runner->link;
         }
      }
      current = current->link;
   }

   // Step 2: Mirror Section
   int headLength = 1;
   Node* last = head;      

   while(last->link != 0)
   {
      headLength++;
      last = last->link;
   }

   // head length is the length of LL (without any mirror stuff)
   // last = the original last node of LL (without any mirror stuff)

   // iterate thru LL in reverse order
   for (int i = headLength-1; i >= 0; i--) 
   {
      Node* runner = head;
      
      // traverse LL
      for( int j = 0; j < i; j++)
      {
         runner = runner->link;
      }

      // runner = the node we are wanting to copy in mirror section

      // duplicates is basically a recycle bin now that we are checking 
      //    to see if we can steal from
      // if duplicates is empty or duplicates contain the data we are 
      //    looking for
      if(duplicates != 0 && duplicates->data == runner->data)
      {
         // set the last node of LL to duplicate
         // reset last = to duplicate
         last->link = duplicates;
         last = last -> link;

         // remove duplicate from "recycle bin"
         duplicates = duplicates->link;

         last->link = 0;
      }
      // if recycle bin does not contain runner->data
      else 
      {
         // make new node
         Node* newNode = new Node;
         newNode->data = runner->data;
         newNode->link = 0;

         // set last = newNode and increment last
         last->link = newNode;
         last = last->link;
      }
   }
}


//////////////////////////////////////////////////////////////////
// definitions for helper functions for use ONLY by Assign05P1.cpp)
// (be sure to NOT exclude these from you as-is-text file)
//////////////////////////////////////////////////////////////////

int FindListLength(Node* headPtr)
{
   int length = 0;

   while (headPtr != 0)
   {
      ++length;
      headPtr = headPtr->link;
   }

   return length;
}

bool IsSortedUp(Node* headPtr)
{
   if (headPtr == 0 || headPtr->link == 0) // empty or 1-node
      return true;
   while (headPtr->link != 0) // not at last node
   {
      if (headPtr->link->data < headPtr->data)
         return false;
      headPtr = headPtr->link;
   }
   return true;
}

void InsertAsHead(Node*& headPtr, int value)
{
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = headPtr;
   headPtr = newNodePtr;
}

void InsertAsTail(Node*& headPtr, int value)
{
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = 0;
   if (headPtr == 0)
      headPtr = newNodePtr;
   else
   {
      Node *cursor = headPtr;

      while (cursor->link != 0) // not at last node
         cursor = cursor->link;
      cursor->link = newNodePtr;
   }
}

void InsertSortedUp(Node*& headPtr, int value)
{
   Node *precursor = 0,
        *cursor = headPtr;

   while (cursor != 0 && cursor->data < value)
   {
      precursor = cursor;
      cursor = cursor->link;
   }

   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = cursor;
   if (cursor == headPtr)
      headPtr = newNodePtr;
   else
      precursor->link = newNodePtr;

   ///////////////////////////////////////////////////////////
   /* using-only-cursor (no precursor) version
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   //newNodePtr->link = 0;
   //if (headPtr == 0)
   //   headPtr = newNodePtr;
   //else if (headPtr->data >= value)
   //{
   //   newNodePtr->link = headPtr;
   //   headPtr = newNodePtr;
   //}
   if (headPtr == 0 || headPtr->data >= value)
   {
      newNodePtr->link = headPtr;
      headPtr = newNodePtr;
   }
   //else if (headPtr->link == 0)
   //   head->link = newNodePtr;
   else
   {
      Node *cursor = headPtr;
      while (cursor->link != 0 && cursor->link->data < value)
         cursor = cursor->link;
      //if (cursor->link != 0)
      //   newNodePtr->link = cursor->link;
      newNodePtr->link = cursor->link;
      cursor->link = newNodePtr;
   }

   ////////////////// commented lines removed //////////////////

   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   if (headPtr == 0 || headPtr->data >= value)
   {
      newNodePtr->link = headPtr;
      headPtr = newNodePtr;
   }
   else
   {
      Node *cursor = headPtr;
      while (cursor->link != 0 && cursor->link->data < value)
         cursor = cursor->link;
      newNodePtr->link = cursor->link;
      cursor->link = newNodePtr;
   }
   */
   ///////////////////////////////////////////////////////////
}

bool DelFirstTargetNode(Node*& headPtr, int target)
{
   Node *precursor = 0,
        *cursor = headPtr;

   while (cursor != 0 && cursor->data != target)
   {
      precursor = cursor;
      cursor = cursor->link;
   }
   if (cursor == 0)
   {
      cout << target << " not found." << endl;
      return false;
   }
   if (cursor == headPtr) //OR precursor == 0
      headPtr = headPtr->link;
   else
      precursor->link = cursor->link;
   delete cursor;
   return true;
}

bool DelNodeBefore1stMatch(Node*& headPtr, int target)
{
   if (headPtr == 0 || headPtr->link == 0 || headPtr->data == target) return false;
   Node *cur = headPtr->link, *pre = headPtr, *prepre = 0;
   while (cur != 0 && cur->data != target)
   {
      prepre = pre;
      pre = cur;
      cur = cur->link;
   }
   if (cur == 0) return false;
   if (cur == headPtr->link)
   {
      headPtr = cur;
      delete pre;
   }
   else
   {
      prepre->link = cur;
      delete pre;
   }
   return true;
}

void ShowAll(ostream& outs, Node* headPtr)
{
   while (headPtr != 0)
   {
      outs << headPtr->data << "  ";
      headPtr = headPtr->link;
   }
   outs << endl;
}

void FindMinMax(Node* headPtr, int& minValue, int& maxValue)
{
   if (headPtr == 0)
   {
      cerr << "FindMinMax() attempted on empty list" << endl;
      cerr << "Minimum and maximum values not set" << endl;
   }
   else
   {
      minValue = maxValue = headPtr->data;
      while (headPtr->link != 0)
      {
         headPtr = headPtr->link;
         if (headPtr->data < minValue)
            minValue = headPtr->data;
         else if (headPtr->data > maxValue)
            maxValue = headPtr->data;
      }
   }
}

double FindAverage(Node* headPtr)
{
   if (headPtr == 0)
   {
      cerr << "FindAverage() attempted on empty list" << endl;
      cerr << "An arbitrary zero value is returned" << endl;
      return 0.0;
   }
   else
   {
      int sum = 0,
          count = 0;

      while (headPtr != 0)
      {
         ++count;
         sum += headPtr->data;
         headPtr = headPtr->link;
      }

      return double(sum) / count;
   }
}

void ListClear(Node*& headPtr, int noMsg)
{
   int count = 0;

   Node *cursor = headPtr;
   while (headPtr != 0)
   {
      headPtr = headPtr->link;
      delete cursor;
      cursor = headPtr;
      ++count;
   }
   if (noMsg) return;
   clog << "Dynamic memory for " << count << " nodes freed"
        << endl;
}
//////////////////////////////////////////////////////////////////

