#include "Message.h"
#include "Folder.h"
//Exercise 13.34
Message::Message(const Message& m):contents(m.contents), folders(m.folders) {
	add_to_Folders(m);
}

Message& Message::operator=(const Message& m) {
	remove_from_Folders();
	contents = m.contents;
	folders = m.folders;
	add_to_Folders(m);
	return *this;
}

Message::Message(Message&& m) noexcept :contents(std::move(m.contents)) {
	move_Folders(&m);
}

Message& Message::operator=(Message&& m) noexcept {
	if (this != &m) {
		remove_from_Folders();
		contents = std::move(m.contents);
		move_Folders(&m);
	}
	return *this;
}

void  Message::move_Folders(Message* m) {
	folders = std::move(m->folders);
	for (Folder* f : folders) {
		f->remMsg(m);
		f->addMsg(this);
	}
	m->folders.clear();
}

Message::~Message() {
	remove_from_Folders();
}

void Message::save(Folder& f) {
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder& f) {
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folders(const Message& m) {
	for (Folder* f : m.folders) {
		f->addMsg(this);
	}
}

void Message::remove_from_Folders() {
	for (Folder* f : folders) {
		f->remMsg(this);
	}
}

void Message::addFolder(Folder& f) {
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remFolder(Folder& f) {
	folders.erase(&f);
	f.remMsg(this);
}