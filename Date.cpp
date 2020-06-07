#include "Date.h"

Date::Date(int year, int month, int day)
	:m_day(day)
	,m_month(month)
	,m_year(year)
{}

void Date::serialize(std::ofstream & out) const
{
	out.write((const char*)&m_year, sizeof(m_year));
	out.write((const char*)&m_month, sizeof(m_month));
	out.write((const char*)&m_day, sizeof(m_day));
}

Date::Date(std::ifstream& in)
{
	in.read((char*)&m_year, sizeof(m_year));
	in.read((char*)&m_month, sizeof(m_month));
	in.read((char*)&m_day, sizeof(m_day));
}
