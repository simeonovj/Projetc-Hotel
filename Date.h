#pragma once
#include <ostream>
#include <fstream>

/**
*class Date
*/
class Date
{
public:
	/**
* Constructor
*/
	Date(int year, int month, int day);


	/**
* Get methds
*/
	inline double GetDay() const { return m_day; }
	inline double GetMonyh() const { return m_month; }
	inline double GetYear() const { return m_year; }

	/**
*  Serialize and deserialize methods
*/
	void serialize(std::ofstream& out) const;
	Date(std::ifstream& in);

	friend std::ostream& operator<<(std::ostream& out, const Date& obj)
	{
		return out << obj.m_year << " " << obj.m_month << " " << obj.m_day;
	}
	
private:
	int m_day;
	int m_month;
	int m_year;	
};

