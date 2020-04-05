#pragma once
#ifndef _MESSAGE_H
#define _MESSAGE_H
#include <string>
#include <set>
#include "Folder.h"

using namespace std;
//Exercise 13.34
class Message {
	friend class Folder;
public:
	explicit Message(const string& str = "") :contents(str) {}
	Message(const Message& m);
	Message& operator=(const Message& m);
	~Message();
	Message(Message&& m) noexcept;
	Message& operator=(Message&& m) noexcept;

	void save(Folder& f);
	void remove(Folder& f);
	void addFolder(Folder& f);//Exercise 13.37
	void remFolder(Folder& f);//Exercise 13.37
private:
	string contents;
	set<Folder*> folders;
	void add_to_Folders(const Message& m);
	void remove_from_Folders();
	void move_Folders(Message *m);

};


#endif // !_MESSAGE_H

