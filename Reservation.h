#include "Rooms.h"
#include "Date.h"
#include <vector>
#include <ostream>
#include <fstream>
#pragma once

/**
* class Reservation
*/
class Reservation
{
public:	
	/**
* Big four
*/
	Reservation(int room, const char* note);
	Reservation(const Reservation& other);
	Reservation& operator=(const Reservation& other);
	~Reservation();

	/**
*  Serialize and deserialize methods
*/
	void serialize(std::ofstream& out) const;
	Reservation(std::ifstream& in);

	/**
* Get methds
*/
	inline int GetRoom() const { return m_room; }
	inline const char* GetNote() const { return note; }

private:
	void copy(const Reservation& other);
	void clear();

	int m_room;
	char* note;
};

