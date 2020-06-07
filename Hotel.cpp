#include<vector>
#include<string>
#include<iostream>
#include <fstream>
#include"Rooms.h"
#include"Date.h"
#include"Reservation.h"
#include "Hotel.h"
#include <chrono>


const int MAX_CMD_LEN = 8;
const int MAX_IMP_LEN = 100;
const char* SAVE_FILE_NAME = "system.txt";

Hotel::Hotel()
{}

Hotel& Hotel::i()
{
	static Hotel instance;
	return instance;
}

Date Hotel::DateFrom(int day, int month, int year)
{
	dates.push_back({ day, month, year });
	std::cout << day << "-" << month << "-" << year <<" ";
	return dates.back();
}

Date Hotel::DateTo(int day, int month, int year)
{
	dates.push_back({ day, month, year });
	std::cout << day << "-" << month << "-" << year << " ";
	return dates.back();
}

void Hotel::Room(int room, const char* note)
{
	reservations.push_back({ room, note });
	std::cout << room << " " << note << std::endl;
}

void Hotel::CheckOut(int room_number)
{
	size_t index = -1;
	for (size_t i = 0; i < reservations.size(); i++)
	{
		if (reservations[i].GetRoom() == room_number)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		reservations.erase(reservations.begin() + index);
		std::cout << "Reservation was delet." << std::endl; 
	}
}


void Hotel::run()
{
	int room;
	char input[MAX_CMD_LEN];
	int day_from, month_from, year_from;
	int day_to, month_to, year_to;
	char note [MAX_IMP_LEN] ;
	do
	{
		std::cin >> input;
		if (strcmp(input, "checkin") == 0)
		{
			std::cout << "Enter date form: ";
			std::cin >> year_from >> month_from >> day_from;
			std::cout << "Enter date to: ";
			std::cin >> year_to >> month_to >> day_to;
			if (year_from > year_to || month_from > month_to)
			{
				std::cout << "Invalid date." << std::endl 
					      << "Make new reservation." << std::endl;
			}
			else
			{
				std::cout << "Enter room: ";
				std::cin >> room;
				std::cout << "Write note: ";
				std::cin.ignore(MAX_IMP_LEN, '\n');
				std::cin.getline(note, MAX_IMP_LEN);
				DateFrom(year_from, month_from, day_from);
				DateTo(year_to, month_to, day_to);
				Room(room, note);
				std::cout << "Room was succsefully reserved" << std::endl;
			}
		}
		else if(strcmp(input, "unaveilable") == 0)
		{
			std::cout << "Enter date form: ";
			std::cin >> year_from >> month_from >> day_from;
			std::cout << "Enter date to: ";
			std::cin >> year_to >> month_to >> day_to;
			if (year_from > year_to || month_from > month_to)
			{
				std::cout << "Invalid date." << std::endl;					
			}
			else
			{
				std::cout << "Enter room: ";
				std::cin >> room;
				std::cout << "Write note: ";
				std::cin.ignore(MAX_IMP_LEN, '\n');
				std::cin.getline(note, MAX_IMP_LEN);
				DateTo(year_to, month_to, day_to);
				DateFrom(year_from, month_from, day_from);
				Room(room, note);
			}
		}
		else if (strcmp(input, "checkout") == 0)
		{
			std::cout <<"Enter room number: "<<std::endl;
		    std::cin >> room;
			CheckOut(room);
		}
		else if (strcmp(input, "save") == 0)
		{
			serialize();
		}
		else if (strcmp(input, "open") == 0)
		{
			deserialize();
		}
		else if (strcmp(input, "help") == 0)
		{
			HelpPanel();
		}
		else if (strcmp(input, "exit") == 0) 
		{
			
				std::cout << "Did you want to Exit [y/n]? ";
				char option;
				std::cin.ignore(MAX_IMP_LEN, '\n');
				std::cin.get(option);
				if (option == 'n' || option == 'N')
					input[0] = '\n';	
		}
		else 
		{
			std::cout << "Unknown command! Type 'help' for available commands." << std::endl;
		}
	} 
	while (strcmp(input, "exit") != 0);
}

bool Hotel::serialize() const
{
	std::ofstream out(SAVE_FILE_NAME, std::ios::binary);

	if (!out) {
		std::cout << "Cannot open " << SAVE_FILE_NAME << " file for writing!" << std::endl;
		return false;
	}

	size_t len;
	len = reservations.size();
	out.write((const char*)&len, sizeof(len));
	for (size_t i = 0; i < len; i++)
		reservations[i].serialize(out);

	out.close();
	std::cout << "Successfully saved" << std::endl;
	return true;
}


bool Hotel::deserialize()
{
	std::ifstream in(SAVE_FILE_NAME, std::ios::binary);
	if (!in)
		return false;

	size_t len;

	in.read((char*)&len, sizeof(len));
	for (size_t i = 0; i < len; i++)
		reservations.push_back(Reservation(in));

	in.close();
	std::cout << "Successfully loaded" << std::endl;
	return true;
}

void Hotel::HelpPanel()
{
	std::cout << "checkin <from> <to> <room> <note> - create reservation" << std::endl
		<< "availability <date> - check for free rooms" << std::endl
		<< "checkout <room> - delete reservation" << std::endl
		<< "report <form> <to> - information for used rooms" << std::endl
		<< "find <beds> <from> <to> - finding of the right room" << std::endl
		<< "find! <beds> <from> <to> - urgent fiding ot the right room" << std::endl
		<< "unaveilable <room> <from> <to> <note> - declares room cant be used " << std::endl
		<< "open - load file" << std::endl
		<< "close - closes currently opened file" << std::endl
		<< "save - saves the currently open file" << std::endl
		<< "save as - prints this information" << std::endl
		<< "exit - exists the program" << std::endl;
}
