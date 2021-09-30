/*
 * Tests.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Tests.h"
#include "LinkedList2.h"
#include "Room.h"
#include <stdbool.h>

Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::tests()
{
	bool answer = true;

	bool ok1 = testReadFile();
	bool ok2 = testGotAdjacencyMatrix();
	bool ok3 = testMakeLList();
	bool ok4 = testEnqueue();
	//pedagogical bool ok5 = testRemoveFromList();
	bool ok6 = testPrintHistory();
	answer = ok1 && ok2 && ok3 && ok4  && ok6;
	return answer;
}

bool Tests::testReadFile()
{
	puts("starting testReadFile"); fflush(stdout);
	bool ok = false;
	//the file tells how many rooms there are
	int answer = -1;
	int rightAnswer = 8;


	AdjMat* adjMP = new AdjMat();
	Room* theRoomPs[10];//addresses for 10 rooms

	Production* pP = new Production();

	ok = pP->readFile("houseGraph.txt", &answer, adjMP, theRoomPs); //read the file
	if(ok)
	{
		if(answer!=rightAnswer) {
			puts("test failed on number of rooms");
		}
		puts("The adjacency matrix");
		for(int i = 0; i<answer; i++) {
			for(int j = 0; j<answer; j++) {
				printf("%d",adjMP->getEdge(i, j));

			}
			printf("\n");
		}
		puts("The treasure values");
		for(int i = 0; i<answer; i++) {
			printf("%f\n", theRoomPs[i]->treasure);
		} 
		for(int i = 0; i < rightAnswer; i++) {
			delete theRoomPs[i];
		}
	}	
	if(ok) {
		puts("testReadfile did pass");
	}
	else {
		puts("testReadfile did not pass.");
	}
	delete adjMP;
	delete pP;
	return ok;
}
bool Tests::testEnqueue()
{
	bool ok = true;
	if(ok)
	{
		puts("testEnqueue did pass");
	}
	else
	{
		puts("testEnqueue did not pass.");
	}
	return ok;
}
bool Tests::testGotAdjacencyMatrix()
{
	bool ok = true;
	if(ok)
	{
		puts("testGotAdjacencyMatrix did pass");
	}
	else
	{
		puts("testGotAdjacencyMatrix did not pass.");
	}
	return ok;
}

bool Tests::testMakeLList()
{
	bool ok = true;
	puts("starting testMakeLList");
	LinkedList<Room> *roomList = new LinkedList<Room>;
	float treasureL[3] = { 0.0f, 2.4f, 4.5f };
	for(int i = 0; i < 3; i++) {
		roomList->addEnd(createRoom(i, treasureL[i], false));
	}
	roomList->print();

	delete roomList;

	LinkedList<SearchResults> *resultList = new LinkedList<SearchResults>;
	for(int i = 0; i < 3; i++) {
		resultList->addEnd(createResult(i, treasureL[i]));
	}
	resultList->print();
	delete resultList;

	if(ok) {
		puts("testMakeLList did pass");
	} else {
		puts("testMakeLList did not pass.");
	}
	return ok;
}

bool Tests::testPrintHistory()
{
	bool ok = true;
	if(ok)
	{
		puts("testPrintHistory did pass");
	}
	else
	{
		puts("testPrintHistory did not pass.");
	}
	return ok;
}



