all: fb td

td: MyADTTestDriver.o MyADT.o Profile.o
	g++ -Wall -o td MyADTTestDriver.o MyADT.o Profile.o

fb: FriendsBook.o MyADT.o Profile.o MyADTTestDriver.o
	g++ -Wall -o fb FriendsBook.o MyADT.o Profile.o

MyADTTestDriver.o: MyADTTestDriver.cpp MyADT.h Profile.h
	g++ -Wall -c MyADTTestDriver.cpp

FriendsBook.o: FriendsBook.cpp MyADT.h Profile.h
	g++ -Wall -c FriendsBook.cpp

MyADT.o: MyADT.h MyADT.cpp
	g++ -Wall -c MyADT.cpp

Profile.o: Profile.h Profile.cpp
	g++ -Wall -c Profile.cpp

clean:
	rm -f fb *.o