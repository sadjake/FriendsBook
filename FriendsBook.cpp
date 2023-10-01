/*
 * FriendsBook.cpp - Assignment 1
 * 
 * Class Description: Social network application (partial implementation).
 *
 * In this version, we use our MyADT.
 *
 * ***You cannot remove/change the code provided in this file.***
 *
 * Author: AL
 * Modified on: Sept. 14, 2023
 */

#include <iostream>
#include <string>
#include <cctype>
#include "Profile.h"
#include "MyADT.h"

using std::cout;
using std::ws;
using std::cin;
using std::endl;

void join(MyADT & theMembers) {
   // initialize the strings for the profile info
   string userName;
   string name;
   string email;
   string birthday;

   // prompt user to create their profile
   cout << "Create a profile." << endl;

   // get user input for profile details
   cout << "Enter a username (starting with a letter, no symbols): ";
   cin >> userName;

   // get name
   cout << "Enter your name: ";
   // clear any remaining newline characters in input stream
   // by using cin.ignore
   cin.ignore();
   //use getline to read text and store it in name 
   getline(cin, name);

   // get email
   cout << "Enter your email: ";
   cin >> email;

   // get email
   cout << "Enter your birthday (Month/DD/YYYY): ";
   cin >> birthday;

   // create a new profile with user's input
   Profile newProfile(userName, name, email, birthday);

   // insert new profile into theMembers
   if (theMembers.insert(newProfile)) {
      cout << "Profile created and joined FriendsBook successfully" << endl;
   } else {
      // else, failed to join friendsbook
      cout << "Failed to join FriendsBook. The username might already be taken." << endl;
   }
}

void leave(MyADT & theMembers) {
   // ask the user for their username to verify so that they can leave freidnsbook
   cout << "Enter your username to leave FriendsBook: ";
   string username;
   cin >> username;

   // create a profile object with the entered username
   Profile targetProfile(username);

   // remove the user's profile
   if (theMembers.remove(targetProfile)) {
      cout << "You have left FriendsBook. Goodbye!" << endl;
   } 
   else {
      // if can't remove the user's profile, still part of friendsbook
      cout << "Profile not found. You are still part of FriendsBook." << endl;
   }
}

void search(MyADT & theMembers) {
   // initialize a string variable specifically just for
   // searching up a user's name
   string searchUser;

   // prompt user to search for the username 
   cout << "Enter the username you want to search for: ";
   // clear any remaining newline characters in input stream
   cin.ignore();
   //use getline to read text and store it in name
   getline(cin, searchUser);

   // create a Profile object with the search username for comparison
   Profile searchProfile(searchUser);

   Profile* foundProfile = theMembers.search(searchProfile);

   if (foundProfile != nullptr) {
      // profile found
      cout << "Profile found:" << endl;
      cout << *foundProfile;
   } else {
      // when profile isnt found
      cout << "Profile not found." << endl;
   }
}

void modify(MyADT& theMembers) {
   // modify everything except username
   // ask the user for username to be able
   // to modify other parts of their info

   // initialize string variable for the username
   string username;

   // enter username to modify profile
   cout << "Enter your username to modify your profile: ";
   cin >> username;

   // Create a profile object with the entered username
   Profile targetProfile(username);

   // Search for the user's profile
   Profile* foundProfile = theMembers.search(targetProfile);

   if (foundProfile != nullptr) {
      // declare the strings
      string newName;
      string newEmail;
      string newBirthday;

      //prompt to update name
      cout << "Enter new name: ";
      cin.ignore();
      getline(cin, newName);

      // prompt to update email
      cout << "Enter new email: ";
      getline(cin, newEmail);

      // prompt to update birthday
      cout << "Enter new birthday: ";
      getline(cin, newBirthday);

      // update the profile information
      foundProfile->setName(newName);
      foundProfile->setEmail(newEmail);
      foundProfile->setBirthday(newBirthday);

      // message declaring profile has been updated
      cout << "Profile updated successfully!" << endl;
      } 

      // cant find profile
      else {
         cout << "Profile not found. Unable to modify." << endl;
   }
}

void print(MyADT & theMembers) {
   // personal note: refer to SamplePrintResult.txt
   // print order should be: username, name, email, birthday
   cout << "List of all members on FriendsBook:" << endl;

   // print all members
   theMembers.print();
}

int main() {

    // Variables declaration
    MyADT members = MyADT();  // Object MyADT on the stack, its arrays on the heap
    bool done = false;
    char input = 0;
        
    // Keep going until the user exits
    while (not done) {
        // Print menu to stdout
        cout << "\n----Welcome to FriendsBook!" << endl << endl;
        cout << endl << "Enter ..." << endl;
        cout << "j -> to join FriendsBook by creating a profile." << endl;
        cout << "l -> to leave FriendsBook." << endl;
        cout << "s -> to search for a friend on FriendsBook." << endl;
        cout << "m -> to modify your profile on FriendsBook." << endl;
        cout << "p -> to print all members on FriendsBook." << endl;
        cout << "x -> to exit FriendsBook." << endl << endl;


        cout << "Your choice: ";
        cin >> input;
        cout << endl;
        input = tolower(input);
        switch(input) {
            case 'j': join(members); break;
            case 'l': leave(members); break;
            case 's': search(members); break;
            case 'm': modify(members); break;
            case 'p': print(members); break;
            case 'x': cout << "\n----Bye!\n" << endl; 
                      done = true; break;
            default: cout << "Not sure what you mean! Please, try again!" << endl;
        }
    }

    return 0;
}
// sept 29 2023