#pragma once
#include<vector>
#include <ostream>
#include<iostream>
#include"Rooms.h"
#include"Date.h"
#include"Reservation.h"

/**
*  class Hotel
*/
class Hotel
{
private:
	Hotel();
public:
	/**
*  Singleton system
*/
	static Hotel& i();
	Hotel(const Hotel&) = delete;
	void operator=(const Hotel&) = delete;

	///Date function
	Date DateFrom(int day, int month, int year);
	///Date function
	Date DateTo(int day, int month, int year);
	///get Room function
	void Room(int room, const char* note);
	///Delete room function
	void CheckOut(int room_number);
	/// help functin
	void HelpPanel();

	/**
*  Serialize and deserialize methods
*/
	bool serialize() const;
	bool deserialize();

	/**
*  Run function
*/
	void run();
		
private:	
	/**
*  Vectors
*/
	std::vector<Reservation> reservations;
	std::vector<Date> dates;
	std::vector<Rooms> rooms;
};

