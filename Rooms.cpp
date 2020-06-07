#include "Rooms.h"

Rooms::Rooms(int RoomNumber, int Beds)
	:room_number(RoomNumber)
	,m_beds(Beds)
{
}

void Rooms::serialize(std::ofstream& out) const
{
	out.write((const char*)&room_number, sizeof(room_number));
	out.write((const char*)&m_beds, sizeof(m_beds));
}

Rooms::Rooms(std::ifstream& in)
{
	in.read((char*)&room_number, sizeof(room_number));
	in.read((char*)&m_beds, sizeof(m_beds));
}

