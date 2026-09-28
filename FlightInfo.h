#pragma once
#include<string>

struct FlightTime {
	unsigned day, month, hours, minutes;
};

struct  FlightInfo
{
	std::string sityFrom;
	std::string sityTo;
	FlightTime departure;
	unsigned businessSeats;
	unsigned economySeats;
};