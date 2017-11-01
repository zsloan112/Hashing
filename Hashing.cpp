#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>

using namespace std;

const int TABLE_SIZE = 20;

class HashNode{
public: 
	int value;
	HashNode* next;

	HashNode(int value){
		this->value = value;
		this->next = NULL;
	}
};

class HashTable{
private:
	HashNode** hTable;
public: 
	HashTable(){
		hTable = new HashNode*[TABLE_SIZE];
		for(int i = 0; i < TABLE_SIZE; i++){
			hTable[i] = NULL;
		}
	}

	~HashTable(){
		for(int i = 0; i < TABLE_SIZE; i++){
			HashNode* entry = hTable[i];
			while(entry != NULL){
				HashNode *prev = entry;
				entry = entry->next;
				delete prev;
			}
		}
		delete[] hTable;
	}
	int h(int key){
	return key % 20;
}

void hashInsert(int key){
	int hashLoc = h(key);
	HashNode* prev = NULL;
	HashNode* entry = hTable[hashLoc];
	while(entry != NULL){
		prev = entry;
		entry = entry->next;
	}
	if(entry == NULL){
		entry = new HashNode(key);
		if(prev == NULL){
			hTable[hashLoc] = entry;
		}
		else{
			prev->next = entry;
		}
	}
	else{
		entry->value = key;
	}
}

void hashDelete(int key){
	int hashLoc = h(key);
	HashNode *entry = hTable[hashLoc];
	HashNode *prev = NULL;

	if(entry == NULL || entry->value != key){
		cout << "No element found at key" << endl;
		return;
	}

	while(entry->next != NULL){
		prev = entry;
		entry = entry->next;
	}
	if(prev != NULL){
		prev->next = entry->next;
	}
	delete entry;
	cout << "Entry Successfully Deleted" << endl;
	
}

int hashSearch(int key){
	bool flag = false;
	int hashLoc = h(key);
	HashNode *entry = hTable[hashLoc];
	while(entry != NULL){
		if(entry->value == key){
			return 1;
			flag = true;
		}
		entry = entry->next;
	}
	if(!flag)
		return -1;
}

void hashPrint(){
	for(int i = 0; i < TABLE_SIZE; i++){
		HashNode *entry = hTable[i];
		cout << "Slot #" << i << ": ";
		while(entry != NULL){
			cout << entry->value << " ";
			entry = entry->next;
		}
		cout << endl;
	}
}

};


int main(){
	HashTable hash;

	int key;
	int selection;

	while(selection != 5){
		cout << "----------------------------------------" << endl;
		cout << "| Operations for Hash Table            |" << endl;
		cout << "----------------------------------------" << endl;
		cout << "| 1. Insert element into the table     |" << endl;
		cout << "| 2. Delete element from the table     |" << endl;
		cout << "| 3. Search for an element in the table|" << endl;
		cout << "| 4. Print elements of Hash Table      |" << endl;
		cout << "| 5. Exit Program                      |" << endl;
		cout << "----------------------------------------" << endl;
		cout << "Selection: ";
		cin >> selection;

		switch(selection){
			case 1: 
				int newHashValue;
				cout << "Enter a value to insert into the table: ";
				cin >> newHashValue;
				if(hash.hashSearch(newHashValue) == -1){
					hash.hashInsert(newHashValue);
				}else{
					cout << "Value is already in the hash table" << endl;
				}
				break;
			case 2:
				int delHashValue;
				cout << "Enter a value to delete from the table: ";
				cin >> delHashValue;
				hash.hashDelete(delHashValue);
				break;
			case 3:
				int searchVal;
				cout << "Enter a value to search for: ";
				cin >> searchVal;
				if(hash.hashSearch(searchVal) == -1){
					cout << searchVal << " is not in the hash table" << endl;
				}else{
					cout << searchVal << " was foud in slot #" << hash.h(searchVal) << endl;
				}
				break;
			case 4:
				cout << endl;
				hash.hashPrint();
				cout << endl;
				break;
			default:
				break;
		}
	}
}




