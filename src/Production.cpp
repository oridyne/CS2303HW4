/*
 * Production.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Production.h"
#include <fstream>
#include <iostream>
#include <stdbool.h>
#include <string>
#include "AdjMat.h"
#include "Room.h"
#include "LinkedList2.h"

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[])
{
	printf("Starting Production\n");
	bool answer = false;

	if(argc <=1) //no interesting information
	{
		puts("Didn't find any arguments.");
		fflush(stdout);
		answer = false;
	}
	else //there is interesting information
	{
		printf("Found %d interesting arguments.\n", argc-1);
		fflush(stdout);
		std::string filename;
		int maxRooms = 0;
		float maxTreasure = 0;
		double maxTreas = 0.0;
		//don't want to read argv[0]
		////argv[i] is a string
		for(int i = 1; i<argc; i++) {
			switch(i) {
				case 1:
					//this is filename
					printf("The length of the filename is %d.\n",(int)strlen(argv[i]));
					printf("The proposed filename is %s.\n", argv[i]);
					if(strlen(argv[i])>=FILENAMELENGTHALLOWANCE) {
						puts("Filename is too long.");
						fflush(stdout);
						answer = false;
					}
					else {
						filename = argv[i];
						std::cout << "Filename is " << filename << "\n";
						fflush(stdout);
					}
					break;
				case 2:
					//this is maximum number of rooms
					maxRooms = std::stoi(argv[i]);
					printf("Number of rooms is %d\n",maxRooms);fflush(stdout);
					break;
				case 3:
					//this is maximum amount of treasure
					maxTreas = std::atof(argv[i]);
					printf("Amount of  treasure is %f\n",maxTreas);fflush(stdout);
					maxTreasure = (float) maxTreas;
					break;

				default:
					puts("Unexpected argument count."); fflush(stdout);
					answer = false;
					break;
			}//end of switch
		}//end of for loop on argument count
		puts("after reading arguments"); fflush(stdout);
		if (argc != 4) {
			while (maxRooms <= 0) {
				std::cout << "Input Max Rooms: \n";
				std::cin >> maxRooms;
				std::cout << "Number of rooms is " << maxRooms << "\n";
			}
			while ( maxTreasure <= 0 ) {
				std::cout << "Input Max Treasure: \n";
				std::cin >> maxTreasure;
				std::cout << "Amount of treasure is " << maxTreasure << "\n";
			}
		}
		//we'll want to read the file
		int nrooms = -1;
		AdjMat* adjMP = new AdjMat;
		//cannot, do not know nrooms init(adjMP);
		//puts("Back from init Adj Mat"); fflush(stdout);
		Room* theRoomPs[10];//addresses for 10 rooms

		puts("Before read file"); fflush(stdout);
		answer = readFile(filename, &nrooms, adjMP, theRoomPs); //read the file
		puts("Back from read file"); fflush(stdout);
		
		if(answer) {
			LinkedList<Room> *searchQ = new LinkedList<Room>;
			LinkedList<SearchResults> *historyP = new LinkedList<SearchResults>;
			std::cout << "starting search\n";
			bool done = false;
			int searchedRooms = 0;
			float foundTreasure = 0;
			Room* roomBeingSearched = theRoomPs[0];
			roomBeingSearched->searched = true;

			if((roomBeingSearched->treasure <= maxTreas) && (maxRooms > 0)) {
				historyP->addEnd(createResult(0, roomBeingSearched->treasure));
				std::cout << "Enqueuing room 0\n";
				foundTreasure = roomBeingSearched->treasure;
				searchedRooms = 1;
			}
			while (!done) {
				for(int col = 0; (col < nrooms) && !done; col++) {
					std::cout << "checking rooms " << roomBeingSearched->roomNumber << " and " << col << ".\n";
					if(adjMP->getEdge(roomBeingSearched->roomNumber, col) == 1) {
						std::cout << "found an edge\n";
						if(!(theRoomPs[col]->searched)) {
							std::cout << "Room " << col << " hasn't already been searched.\n";
							theRoomPs[col]->searched=true;
							if((foundTreasure + theRoomPs[col]->treasure <= maxTreasure) && (searchedRooms < maxRooms)) {
								foundTreasure += theRoomPs[col]->treasure;
								searchedRooms++;
								std::cout << "found treasure updated to " << foundTreasure << ".\n";
								std::cout << "Enqueuing room " << col << ".\n";
								std::cout << "Before enqueuing room empty reports " << searchQ->isEmpty() << "\n";
								searchQ->addEnd(theRoomPs[col]);
								historyP->addEnd(createResult(theRoomPs[col]->roomNumber, theRoomPs[col]->treasure));

								std::cout << "After enqueuing room empty reports " << searchQ->isEmpty() << "\n";
							}
						}
					}
					if(foundTreasure >= maxTreasure) {
						done = true;
						std::cout << "Done by treasure\n";
					}
					if(searchedRooms >= maxRooms) {
						done = true;
						std::cout << "Done by rooms\n";
					}
				}
				if(!done) {
					std::cout << "Invoking dequeue\n";
					roomBeingSearched = searchQ->dequeueLIFO();
				}
				if(searchQ->isEmpty()) {
					done = true;
					std::cout << "Done by queue empty\n";
				}
			}
			historyP->print();
			delete historyP;
			for(int i = 0; i < nrooms; i++) {
                 Room* currRoom = theRoomPs[i];
                 bool isInLL = searchQ->findNode(currRoom) != NULL;
                 if(!isInLL) {
					 delete theRoomPs[i];
                     theRoomPs[i] = NULL;
                 }
             }	
			delete searchQ;
		}
		delete adjMP;
	}
	return answer;
}

bool Production::readFile(std::string filename, int* nrooms, AdjMat* adjMP, Room** theRoomPs) {
	bool ok = false;
	//the file tells how many rooms there are
	/* FILE* fp = fopen(filename, "r"); //read the file */
	std::ifstream iFstream;
	iFstream.open(filename);
	if (!iFstream.is_open() || iFstream.eof()) {
		puts("Error! opening file");
	} else {
		/* fscanf(fp,"%d", nrooms); */
		iFstream >> *nrooms;	
		int howManyRooms = *nrooms;
		printf("Found %d rooms.\n", howManyRooms);
		adjMP->setN(howManyRooms);
		puts("Before init Adj Mat"); fflush(stdout);
		adjMP->init();
		puts("After init Adj Mat"); fflush(stdout);
		int temp = -1;
		for(int roomr = 1; roomr<*nrooms; roomr++)
		{
			printf("on row %d\n", roomr);fflush(stdout);
			for(int roomc = 0; roomc < roomr; roomc++)
			{
				/* fscanf(fp,"%d", &temp); */
				iFstream >> temp;
				printf("in column %d, read %d\n", roomc, temp);fflush(stdout);
				//now set the value in the adjacency matrix
				if(temp == 1) {
					adjMP->setEdge(roomr, roomc);
				}
			}
		}

		float tempTreas = 2.9;
		for(int roomr = 0; roomr<*nrooms; roomr++)
		{
			/* fscanf(fp,"%f", &tempTreas); */
			iFstream >> tempTreas;
			//make a room and set its treasure
			Room** aRoomP = theRoomPs;
			aRoomP = aRoomP + roomr;
			*aRoomP = createRoom(roomr, tempTreas, false);
			//now set the treasures
			printf("The treasure in room %d is %f\n", roomr, (*aRoomP)->treasure);
		}
		ok = true;
		iFstream.close();
	}
	return ok;
}

bool Production::getYesNo(char* query)
{
   bool answer = true; //so far
   char said = 'x';
   do
   {
	 printf("%s (y/n):",query);
     fflush(stdout);
     fflush(stdin);
     scanf("%c",&said);
   }while((said!= 'y')&&(said!='n'));
   if(said=='n')
   {
	   answer=false;
   }


   return answer;
}

