#include "BookRequests.h"


BookRequests::BookRequests(string name, Priority p, TimeRequests time, string sFrom, string sTo, DayOfDep _day, SeatType sType, unsigned c)
	:PIB(name), timeRequests(time), priority(p), sityFrom(sFrom), day(_day), sityTo(sTo), seatType(sType), countSeat(c)
{ }

string BookRequests::getName()const
{
	return PIB;
}

const TimeRequests& BookRequests::getTime()const
{
	return timeRequests;
}

Priority BookRequests::getPriority() const
{
	return priority;
}

string BookRequests::getSityFrom() const
{
	return sityFrom;
}

string BookRequests::getSityTo() const
{
	return sityTo;
}

DayOfDep BookRequests::getDay() const
{
	return day;
}

SeatType BookRequests::getseatType() const
{
	return seatType;
}

unsigned BookRequests::getAmountOfSeat()const
{
	return countSeat;
}