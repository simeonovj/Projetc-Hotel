#include <cstring>
#include <fstream>
#include "Reservation.h"
#include "Rooms.h"
#include <iostream>


Reservation::Reservation(std::ifstream& in)
{
	size_t len;
	in.read((char*)&len, sizeof(len));
	note = new char[len];
	in.read(note, len);
	in.read((char*)&m_room, sizeof(m_room));
}

Reservation::Reservation(int room, const char* note)
	: m_room(room)
	,note(new char[strlen(note)+1])
{
	strcpy(this->note, note);
}

Reservation::Reservation(const Reservation& other)
{
	copy(other);
}

Reservation& Reservation::operator=(const Reservation& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Reservation::~Reservation()
{
	clear();
}

void Reservation::serialize(std::ofstream& out) const
{
	size_t len;
	len = strlen(note) + 1;
	out.write((const char*)&len, sizeof(len));
	out.write((const char*)note, len);
	out.write((const char*)&m_room, sizeof(m_room));
}

void Reservation::copy(const Reservation& other)
{
	m_room = other.m_room;
	note = new char[strlen(other.note) + 1];
	strcpy(note, other.note);
}

void Reservation::clear()
{
	delete[] note;
	note = nullptr;
}
