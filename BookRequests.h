#pragma once
#include<string>
#include<iostream>

using namespace std;

enum Priority
{
	Low = 1,
	Medium = 2,
	High = 3
};

enum SeatType 
{
	bussiness,
	economy
};

struct TimeRequests
{
	unsigned day;
	unsigned month;
	unsigned hours;
	unsigned minutes;
};

struct DayOfDep
{
	unsigned day;
	unsigned month;
};

class BookRequests{
private:
	string PIB;
	TimeRequests timeRequests;
	Priority priority;
	string sityFrom;
	string sityTo;
	DayOfDep day;
	SeatType seatType;
	unsigned countSeat;

public:
	BookRequests(string name, Priority p, TimeRequests time, string sFrom, string sTo, DayOfDep _day, SeatType sType, unsigned c);

	string getName()const;
	const TimeRequests& getTime()const;
	Priority getPriority() const;
	string getSityFrom()const;
	string getSityTo()const;
	DayOfDep getDay()const;
	SeatType getseatType()const;
	unsigned getAmountOfSeat()const;

};