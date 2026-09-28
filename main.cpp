#include<iostream>
#include<queue>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include"FlightInfo.h"
#include<exception>
#include"BookRequests.h"

using namespace std;


struct CompareRequests
{
	bool operator()(const BookRequests& a, const BookRequests& b) // функтор, функціональний об'єкт. В початковій черзі там стоїть less і порівнюється за допомогою a < b 
	{
		if (a.getPriority() != b.getPriority()) 
		{
			return a.getPriority() < b.getPriority();
		}

		TimeRequests tA = a.getTime();
		TimeRequests tB = b.getTime();

		if (tA.month != tB.month)
		{
			return tA.month > tB.month;
		}
		if (tA.day != tB.day) 
		{
			return tA.day > tB.day;
		}
		if (tA.hours != tB.hours) 
		{
			return tA.hours > tB.hours;
		}
		if (tA.minutes != tB.minutes) 
		{
			return tA.minutes > tB.minutes;
		}
	}
};


void requestProcessing(priority_queue<BookRequests, vector<BookRequests>, CompareRequests> reqQueue, map<string, FlightInfo>& flights, vector<BookRequests>&confirmed, vector<BookRequests>&partConfirmed, vector<BookRequests>&rejected)
{
	while (!reqQueue.empty()) 
	{
		auto currentReq = reqQueue.top();
		int reqSeats = currentReq.getAmountOfSeat();
		bool flightFound = false;

		for (auto& f : flights)
		{
			auto dataDep = currentReq.getDay();
			if (f.second.sityFrom == currentReq.getSityFrom() && f.second.sityTo == currentReq.getSityTo() && f.second.departure.day==dataDep.day && f.second.departure.month == dataDep.month)
			{
				unsigned& seatsOnFlight = (currentReq.getseatType() == SeatType::bussiness) ? f.second.businessSeats : f.second.economySeats;

					if (reqSeats <= seatsOnFlight) 
					{
						seatsOnFlight -= reqSeats;
						confirmed.push_back(currentReq);
						cout << "Request " << currentReq.getName() << " added to vector confirmed!" << endl;
						flightFound = true;
						break;
					}
					else if (reqSeats > seatsOnFlight && seatsOnFlight != 0)
					{
						seatsOnFlight = 0;
						partConfirmed.push_back(currentReq);
						cout << "Request " << currentReq.getName() << " added to vector partially confiirmed!" << endl;
						flightFound = true;
						break;
					}
					else
					{
						rejected.push_back(currentReq);
						cout << "Request " << currentReq.getName() << " added to vector rejected" << endl;
					}

				flightFound = true;
			}
			
		}
		if (!flightFound)
		{
			rejected.push_back(currentReq);
			cout << "No suitable flight for " << currentReq.getName() << " found!" << endl;
		}

		reqQueue.pop();
	}
}

void printVector(vector<BookRequests> a, map<string, FlightInfo>& flights)
{
	if (a.empty())
	{
		cout << "There are no requests of this type" << endl;
	}
	else
	{
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\t\tRequests\n";
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\tNAME\t\t| DEP DAY |  TIME  | FLIGHT |\tFROM\t|\tTO\t|\tCLASS\t| SEATS  |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;


		for (const auto& req : a)
		{
			for (const auto& f : flights)
			{
				if (f.second.sityFrom == req.getSityFrom() && f.second.sityTo == req.getSityTo() && f.second.departure.day == req.getDay().day)
				{
					auto day = req.getDay();

					cout << "  " << req.getName() << "\t|  ";
					if (f.second.departure.day < 10) 
						cout << "0";
					cout << f.second.departure.day << ".";
					if (f.second.departure.month < 10)
						cout << "0";
					cout<< f.second.departure.month << "  | ";
					if (f.second.departure.hours < 10) 
						cout << "0";
					cout << f.second.departure.hours << ":";
					if (f.second.departure.minutes < 10) 
						cout << "0";
					cout << f.second.departure.minutes << "  | ";
					cout << f.first<<"  |\t";
					cout << f.second.sityFrom << "\t|\t";
					cout << f.second.sityTo << "\t|";

					SeatType typeS = req.getseatType();
					if(typeS==SeatType::bussiness) cout << "   bussiness   |";
					else
						cout << "    economy    |";
					cout << "   " << req.getAmountOfSeat() << "    |";
					cout << endl;
					cout << "------------------------------------------------------------------------------------------------------------------" << endl;
					break;
				}
			}
		}
	}
}

void printRejected(const vector<BookRequests>& rejected)
{
	if (rejected.empty())
	{
		cout << "No rejected requests." << endl;
		return;
	}

	cout << "\n----------------------------------------------------------------" << endl;
	cout << "                     REJECTED REQUESTS LIST" << endl;
	cout << "----------------------------------------------------------------" << endl;

	int i = 1;
	for (const auto& req : rejected)
	{
		cout << "Request " << i << ": " << endl;
		cout << "    Name: " << req.getName() << endl;
		auto t = req.getTime();
		cout << "    Time when the request was made: " << t.day << ".";
		if (t.month < 10)
		{
			cout << "0";
		}
		cout << t.month << " at " << t.hours << ":";
		if (t.minutes < 10)
		{
			cout << "0";
		}
		cout << t.minutes << endl;
		auto p = req.getPriority();
		cout << "    Priority: ";
		if (p == Priority::Low)
		{
			cout << "Low" << endl;
		}
		else if (p == Priority::Medium)
		{
			cout << "Medium" << endl;
		}
		else if (p == Priority::High)
		{
			cout << "High" << endl;
		}

		auto d = req.getDay();
		cout << "    Day of departure: ";
		if (d.day < 10)
		{
			cout << "0";
		}
		cout << d.day << ".";
		if (d.month < 10)
		{
			cout << "0";
		}
		cout << d.month << endl;
		cout << "    From: " << req.getSityFrom() << endl;
		cout << "    To: " << req.getSityTo() << endl;
		cout << "    Type of seat: ";
		if (req.getseatType() == SeatType::bussiness)
		{
			cout << "business class" << endl;
		}
		else if (req.getseatType() == SeatType::economy)
		{
			cout << "economy class" << endl;
		}
		cout << "    Amount of seats: " << req.getAmountOfSeat() << endl;

		i++;
		cout << endl;
	}
}


int main()
{
	try
	{
		ifstream flightsFile("flights.txt");

		map<string, FlightInfo> flights;

		if (!flightsFile.is_open())
		{
			throw runtime_error("File is not open!");
		}

		string flightName;
		string sFrom, sTo;
		unsigned d, m, h, minutes, bus, econ;

		while (flightsFile >> flightName >> sFrom >> sTo >> d >> m >> h >> minutes >> bus >> econ)
		{
			flights[flightName] = { sFrom, sTo, {d, m, h, minutes}, bus, econ };
		}

		for (auto const& item : flights)
		{
			const auto& t = item.second.departure;
			cout << "Name of flight: " << item.first;
			cout << "\n  -Flight from: " << item.second.sityFrom << "\n  -Flight to:   " << item.second.sityTo;
			cout<<"\n  -Leaves:   "<< t.day << ".";
			if (t.month < 10)
			{
				cout << "0";
			}
			cout << t.month << " at " << t.hours << ":";
			if (t.minutes < 10)
			{
				cout << "0";
			}
			cout << t.minutes << endl;
			
			cout  << "  -Bussiness seats: " << item.second.businessSeats << "\n  -Economy seats:   " << item.second.economySeats << endl;
			cout << endl;
		}

		flightsFile.close();


		ifstream Data("requests.txt");

		vector<BookRequests> allRequests;

		if (!Data.is_open()) 
		{
			throw runtime_error("File is not open!");
		}

		string pib, sF, sT;
		unsigned day, mon, hour, min;
		unsigned depDay, depMon;
		int prio, sType, countSeat;

		while (Data >> pib >> prio >> day >> mon >> hour >> min >> sF >> sT >> depDay >> depMon >> sType >> countSeat)
		{
			TimeRequests Time = { day, mon, hour, min };

			DayOfDep DepartureDay = { depDay, depMon };

			BookRequests temp(pib, static_cast<Priority>(prio), Time, sF, sT, DepartureDay, static_cast<SeatType>(sType), countSeat);

			allRequests.push_back(temp);
		}

		Data.close();

		cout << endl;
		int i = 1;
		for (const auto& req : allRequests)
		{
			cout << "Request " << i << ": " << endl;
			cout << "    Name: " << req.getName() << endl;
			auto t = req.getTime();
			cout << "    Time when the request was made: " << t.day << ".";
			if (t.month < 10) 
			{
				cout << "0";
			}
			cout << t.month << " at " << t.hours << ":";
			if (t.minutes < 10)
			{
				cout << "0";
			}
			cout << t.minutes << endl;
			auto p = req.getPriority();
			cout << "    Priority: ";
			if (p == Priority::Low) 
			{
				cout << "Low" << endl;
			}
			else if (p == Priority::Medium) 
			{
				cout << "Medium" << endl;
			}
			else if (p == Priority::High)
			{
				cout << "High" << endl;
			}
			else 
			{ 
				cout << "Unknown"<< endl;
			}

			auto d = req.getDay();
			cout << "    Day of departure: ";
			if (d.day < 10)
			{
				cout << "0";
			}
			cout << d.day << ".";
			if (d.month < 10)
			{
				cout << "0";
			}
			cout << d.month << endl;
			cout << "    From: " << req.getSityFrom() << endl;
			cout << "    To: " << req.getSityTo() << endl;
			cout << "    Type of seat: ";
			if (req.getseatType() == SeatType::bussiness)
			{
				cout << "business class" << endl;
			}
			else if (req.getseatType() == SeatType::economy) 
			{
				cout << "economy class" << endl;
			}
			cout << "    Amount of seats: " << req.getAmountOfSeat() << endl;

			i++;
			cout << endl;
		}

		priority_queue<BookRequests, vector<BookRequests>, CompareRequests> reqQueue;

		for (const auto& req : allRequests)
		{
			reqQueue.push(req);
		}

		auto tempQueue = reqQueue;
		cout << "---------------------------------------------------------------" << endl;
		cout << "       \t \t\t   Priority Queue" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "       \t    \tNAME                |         PPIORITY     " << endl;
		cout << "---------------------------------------------------------------" << endl;
		while (!tempQueue.empty())
		{
			BookRequests topReq = tempQueue.top();
			Priority p = topReq.getPriority();
			cout <<"   " << topReq.getName() << "\t    |         ";
			if (p == Priority::Low)
			{
				cout << "Low" << endl;
			}
			else if (p == Priority::Medium)
			{
				cout << "Medium" << endl;
			}
			else if (p == Priority::High)
			{
				cout << "High" << endl;
			}
			cout << "---------------------------------------------------------------" << endl;
			tempQueue.pop();
		}

		vector<BookRequests> confirmed;
		vector<BookRequests> partConfirmed;
		vector<BookRequests> rejected;
		requestProcessing(reqQueue, flights, confirmed, partConfirmed, rejected);

		cout << "\n\n Confirmed requests:\n";
		printVector(confirmed, flights);

		cout << "\n\n Partially confirmed requests:\n";
		printVector(partConfirmed, flights);

		printRejected(rejected);


		cout << "-----------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\tflight occupancy analysis" << endl;
		cout << "-----------------------------------------------------------------------------------------" << endl;
		for (const auto& element : flights)
		{
			cout << "Name of flight: " << element.first << endl;
			cout << "    -Bussuness seats left: " << element.second.businessSeats << endl;
			cout << "    -Econome seats left: " << element.second.economySeats << endl;
			
			if (element.second.businessSeats == 0)
			{
				cout << "Bussiness class fully booked";
			}
			else if (element.second.economySeats == 0) 
			{
				cout << "Economy class fully booked";
			}
			else if (element.second.businessSeats == 0 || element.second.economySeats == 0)
			{
				cout << "Flight fully booked";
			}
			else
			{
				cout << "Flight still avaliable";
			}
			cout << endl << endl;
		}
	}
	catch (const exception& e)
	{
		cout << "Error:" << e.what() << endl;
	}
	

	return 0;
}