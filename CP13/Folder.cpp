#include "Folder.h"
//Exercise 13.36
void Folder::addMsg(Message* m) {
	messages.insert(m);
}

void Folder::remMsg(Message* m){
	messages.erase(m);
}