#pragma once
#ifndef _FOLDER_H
#define _FOLDER_H
#include <string>
#include "Message.h"

using namespace std;
//Exercise 13.36
class Folder {
	friend class Message;
public:
	explicit Folder(const string& str = "") :name(str) {}

	void addMsg(Message* m);
	void remMsg(Message* m);
private:
	string name;
	set<Message*> messages;

};

#endif // !_FOLDER_H

