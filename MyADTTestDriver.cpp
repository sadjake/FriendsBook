/*
  myADTTestDriver.cpp
  Description: Unit tests for MyADT class methods.
  Author: Jake Choi
 */

#include <iostream>
#include <string>
#include <cctype>
#include "MyADT.h"
#include "Profile.h"
using std::cout;
using std::endl;

bool testGetElementCount(MyADT &adt, unsigned int result) {
    return adt.getElementCount() == result;
}

// description: tests the insert() method of MyADT including checking for duplicates
bool testInsert(MyADT &adt, Profile &profile) {
    if (adt.insert(profile)) {
        // successfully inserted, now check for duplicates
        if (adt.insert(profile)) {
            // inserting a duplicate should fail
            std::cout << "FAILED: Duplicate profile insertion" << std::endl;
            return false;
        }
        std::cout << "PASSED: Insertion of profile" << std::endl;
        return true;
    }
    std::cout << "FAILED: Insertion failed" << std::endl;
    return false;
}

bool testSearch(MyADT &adt, Profile &profile) {
    return adt.search(profile) != nullptr;
}

bool testRemove(MyADT &adt, Profile &profile) {
    return adt.remove(profile);
}

bool testRemoveAll(MyADT &adt) {
    adt.removeAll();
    return adt.getElementCount() == 0;
}

bool testCopyConstructor(MyADT &adt, Profile profiles[], int arrSize) {
    MyADT destAdt = adt; 
    
    for (int i = 0; i < arrSize; i++) { 
        if (destAdt.search(profiles[i]) == nullptr) {
            return false;
        }
    }
    return true;
}

int main() {
    // initialize a new ADT
    MyADT *myAdt = new MyADT();

    // check if teh initialization was successful
    if (myAdt == nullptr) {
        cout << "Failed to initialize MyADT" << endl;
        return -1;
    }

    // test getElementCount: this should return 0
    // since elementcount sohulid be 0
    cout << "Testing get element count (Expected: 0)" << endl;
    if (testGetElementCount(*myAdt, 0)) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // array of profiles used for testing insertion, searching, and removal
    const int numProfiles = 6;
    Profile profilesToTest[numProfiles] = {
        Profile("Aang"), Profile("Bob"), Profile("Zuck"), 
        Profile("Anna"), Profile("Bill"), Profile("Benny")
    };

    // test insertion and find the inserted elements
    cout << "Testing insertion" << endl;
    for (int i = 0; i < numProfiles; i++) {
        if (testInsert(*myAdt, profilesToTest[i])) {
            cout << "PASSED " << i + 1 << endl;
        } else {
            cout << "FAILED " << i + 1 << endl;
        }
    }

    // test searching for elements just inserted
    cout << "Testing search" << endl;
    for (int i = 0; i < numProfiles; i++) {
        if (testSearch(*myAdt, profilesToTest[i])) {
            cout << "PASSED " << i + 1 << endl;
        } else {
            cout << "FAILED " << i + 1 << endl;
        }
    }

    // check element count again: should be 6
    cout << "Testing get element count (Expected: 6)" << endl;
    if (testGetElementCount(*myAdt, numProfiles)) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // test the removal of a profile
    cout << "Testing removal" << endl;
    for (int i = 0; i < 2; i++) {
        if (testRemove(*myAdt, profilesToTest[i])) {
            cout << "PASSED " << i + 1 << endl;
        } else {
            cout << "FAILED " << i + 1 << endl;
        }
    }

    // test Remove all
    cout << "Testing remove all" << endl;
    if (testRemoveAll(*myAdt)) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // test insert when full and removign non-existent profile
    const int numProfiles2 = 6;
    Profile profilesToTest2[numProfiles2] = {
        Profile("Anna"), Profile("Alicia"), Profile("Abba"), 
        Profile("Abbey"), Profile("Aang"), Profile("Axel")
    };
    
    cout << "Testing insertion for when full" << endl;
    cout << "Should say FAILED: Insertion failed when trying to insert more than 5"<<endl;
    for (int i = 0; i < numProfiles2 - 1; i++) {
        if (testInsert(*myAdt, profilesToTest2[i])) {
            cout << "PASSED " << i + 1 << endl;
        } else {
            cout << "FAILED " << i + 1 << endl;
        }
    } // should fail to insert for when full
    if (!testInsert(*myAdt, profilesToTest2[numProfiles2 - 1])) {
        cout << "PASSED " << numProfiles2 << endl;
    } else {
        cout << "FAILED " << numProfiles2 << endl;
    }
    cout << "Testing removal of non-existent profile" << endl;
    if (!testRemove(*myAdt, profilesToTest2[numProfiles2 - 1])) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // check element count again: should be 5
    cout << "Testing get element count (Expected: 5)" << endl;
    if (testGetElementCount(*myAdt, numProfiles2 - 1)) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // test copy constructor
    cout << "Testing copy constructor" << endl;
    if (testCopyConstructor(*myAdt, profilesToTest2, 5)) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // test remove all using remove()
    cout << "Testing remove all with single remove" << endl;
    for (int i = 0; i < numProfiles2 - 1; i++) {
        if (testRemove(*myAdt, profilesToTest2[i])) {
            cout << "PASSED " << i + 1 << endl;
        } else {
            cout << "FAILED " << i + 1 << endl;
        }
    }

    // check element count again: Should be 0
    cout << "Testing get element count (Expected: 0)" << endl;
    if (testGetElementCount(*myAdt, 0)) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // Delete myAdt
    delete myAdt;

    return 0;
}
// sept 29 2023