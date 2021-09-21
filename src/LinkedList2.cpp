#include "LinkedList2.h"

template <> void LinkedList<Room>::print(){
	Node<Room>* temp = this->head;
	int count = 0;
	while(temp != NULL) {
		std::cout << "RoomNode " << count << std::endl;
		std::cout << "Room number: " << temp->data->roomNumber << std::endl;
		std::cout << "Treasure: " << temp->data->treasure << std::endl;
		std::cout << "Searched: " << temp->data->searched << std::endl << std::endl;
		temp = temp->next;
		count++;
	}
}
 
template <> void LinkedList<SearchResults>::print(){
	Node<SearchResults>* temp = this->head;
	int count = 0;
	while(temp != NULL) {
		std::cout << "Search Result " << count << std::endl;
		std::cout << "Room number: " << temp->data->roomNumber << std::endl;
		std::cout << "Treasure: " << temp->data->treasure << std::endl << std::endl;
		temp = temp->next;
		count++;
	}
}

SearchResults* createResult(int roomNumber, float treasure) {
	SearchResults* newResult = new SearchResults;
	newResult->roomNumber=roomNumber;
	newResult->treasure=treasure;
	return newResult;
}

