#include <iostream>
#include "MyADT.h"
#include "Profile.h"

using std::cout;
using std::endl;

int main(){
    MyADT myMembers; // creating an instance of myADT class

    //create profiles
    Profile profile1("Xiao Wong", "abcreally", "jxw123@coldmail.com", "August 2 2003");
    Profile profile2("Louis Pace", "ihatethis", "lous@nowhere.com", "May 25 2001");
    Profile profile3("Marie Lower", "marieLower", "marie@somewhere.ca", "Jule 21 1999");
    Profile profile4("Arwinder Singh", "mrcropdgsn", "meow@telthem.com", "December 17 1998");

    // insert profiles in myADT
    myMembers.insert(profile1);
    myMembers.insert(profile2);
    myMembers.insert(profile3);
    myMembers.insert(profile4);

    // print myADT elements
    myMembers.print();

    //search for a profile
    Profile target("ihatethis");
    Profile* find = myMembers.search(target);

    if (find != nullptr){
        cout << "Profile found: " << *find << endl;
    }else{
        cout << "Profile not found" << endl;
    }

    //remove profile
    Profile to_remove("marieLower");
    bool removed = myMembers.remove(to_remove);

    if (removed){
        cout << "They removed now" << endl;
    }else{
        cout << "Whoopsies, looks like they either do not exist or they don't wanna be removed!"<< endl;
    }

    // print updated elements 
    myMembers.print();

    //remove all elements
    myMembers.removeAll();

    //print elements after removing all
    myMembers.print();

    return 0;
}
