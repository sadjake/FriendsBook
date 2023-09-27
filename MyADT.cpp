/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - This is a value-oriented data collection: the elements are kept in 
 *                     ascending sort order of search key. 
 *                   - Its data structure is not expandable, i.e., resizable. 
 *
 * Author: AL
 * Last modified on: Sept. 2023
 */

#include <iostream>
#include <cctype>
#include "MyADT.h"  // Header file
#include "Profile.h"

using std::cout;
using std::endl;
    
// Default constructor.
MyADT::MyADT() {
   // personal note: use unsigned int i not just int i
   for (unsigned int i = 0; i < MAX_ALPHA; i++) {
         elements[i] = nullptr;
         elementCount[i] = 0;
   }
}  // end default constructor

// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
   // initialize element count to 0 and set elements to 0
   // if profile array is empty
   for (unsigned int i = 0; i < MAX_ALPHA; i++) {
      if (rhs.elements[i] == nullptr) {
         elements[i] = nullptr;
         elementCount[i] = 0;
      } 
      
      else {
         elements[i] = new Profile[MAX_ELEMENTS];
         // copy element count
         elementCount[i] = rhs.elementCount[i];

         for (unsigned int j = 0; j < rhs.elementCount[i]; j++) {
            elements[i][j] = Profile(
               rhs.elements[i][j].getUserName(), rhs.elements[i][j].getName(),
               rhs.elements[i][j].getEmail(), rhs.elements[i][j].getBirthday()
            );
         }
      }
   }
} // end copy constructor 

// Destructor
// Description: Destruct this object, releasing heap-allocated memory.
MyADT::~MyADT() {
   removeAll();
} // end destructor

// Description: Returns the total element count of elements currently stored in MyADT.
unsigned int MyADT::getElementCount() const {

   unsigned int element_count = 0;

   for (unsigned int i = 0; i < MAX_ALPHA; i++) {
         element_count += elementCount[i];
   }
   return element_count;
}  // end getElementCount

// Description: Inserts an element.
// Precondition: newElement must not already be in data collection.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
bool MyADT::insert(const Profile& newElement) {
   // get  index for the profile array 
   int arrayIndex = newElement.getFirstLetter() - 'A';

   // check if the target array is full; if so, return false.
   if (elementCount[arrayIndex] == MAX_ELEMENTS) {
      return false;
   }

   // if the array is empty, create a new profile array.
   if (elementCount[arrayIndex] == 0) {
      elements[arrayIndex] = new Profile[MAX_ELEMENTS];
      // check if memory allocation failed and return false
      // if it did fail
      if (elements[arrayIndex] == nullptr) {
         return false;
      }
   }

   // checkign for duplicate profiles in array
   for (unsigned int i = 0; i < elementCount[arrayIndex]; i++) {
      if (elements[arrayIndex][i] == newElement) {
         // return false assuming profile exists already
         return false;
      }
   }

   // insert new element
   for (unsigned int i = 0; i < elementCount[arrayIndex]; i++) {
      if (elements[arrayIndex][i] > newElement) {
         // shift all the elements to the right 
         for (unsigned int j = elementCount[arrayIndex]; j > i; j--) {
            elements[arrayIndex][j] = elements[arrayIndex][j - 1];
         }
         // insert the new element
         elements[arrayIndex][i] = newElement;
         elementCount[arrayIndex]++;
         // return true if the profile was inserted
         return true;
      }
   }
   // insert the new element at the last position
   elements[arrayIndex][elementCount[arrayIndex]] = newElement;
   elementCount[arrayIndex]++;
   
   return true;
} // end insert

// Description: Search for target element. 
//              Returns a pointer to the element if found,
//              otherwise, returns nullptr.
Profile* MyADT::search(const Profile& target) {
   int index = target.getFirstLetter() - 'A';
   for (unsigned int i = 0; i < elementCount[index]; i++) {
      if (elements[index][i] == target) {
         return &elements[index][i];
      }
   }
   return nullptr;
} // end of search

// Description: Remove an element. 
// Postcondition: toBeRemoved is removed and the appropriate elementCount has been decremented.
bool MyADT::remove(const Profile& toBeRemoved) {
   // get the element index for the profile array to be removed
   int arrayIndex = toBeRemoved.getFirstLetter() - 'A';

   // check if the array is empty
   if (elementCount[arrayIndex] == 0) {
      return false;
   }

   // find the profile that should be removed
   for (unsigned int i = 0; i < elementCount[arrayIndex]; i++) {
      // after finding profile remove it
      if (elements[arrayIndex][i] == toBeRemoved) {

         // shift all the elements to the left to 
         // overwrite the removed profile
         for (unsigned int j = i; j < elementCount[arrayIndex] - 1; j++) {
            elements[arrayIndex][j] = elements[arrayIndex][j + 1];
         }

         // decrement the element count for the array
         // (since a profile has been removed)
         elementCount[arrayIndex]--;

         // return true for profile has been removed
         return true;
      }
   }
   // return false if the profile wasn't found
   return false;
} // end remove

// get the element index for the profile arraay I wanna remove
// then cehck if its empty
// then check if elementCount is 1, then set elements index to nullptr 
// but not the index in the profile array, the index, 
// then do search
// once found, go thru loop to shift elements to left to overwirte what I have
// also want to delete the memory

// Description: Remove all elements.
void MyADT::removeAll() {
   // remove profiles, arrays should still be present 
   for (unsigned int i = 0; i < MAX_ALPHA; i++) {
      if (elementCount[i] != 0) {
         delete[] elements[i];
      }
   }
}  // end removeAll

void MyADT::print() {
   for (unsigned int i = 0; i < MAX_ALPHA; i++) {
      if (elements[i] != 0) {
         for (unsigned int j = 0; j < elementCount[i]; j++) {
            // print the users profile in the array
            cout << elements[i][j];
         }
      }
   }
} // end of print 

//  End of implementation file
