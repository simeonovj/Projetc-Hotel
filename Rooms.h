#pragma once
#include <fstream>

/**
*class Rooms
*/
class Rooms
{
public:
	/**
* Constructor
*/
	Rooms(int RoomNumber, int Beds);

	/**
*  Serialize and deserialize methods
*/
	void serialize(std::ofstream& out) const;
	Rooms(std::ifstream& in);

	/**
* Get methds
*/
	inline int GetRoomNumber() const { return room_number; }
	inline int GetBeds() const { return m_beds; }

private:
	int room_number;
	int m_beds;
};

