/*
Project 4: Planes and Trains
Class : CIS 200

	Developers :
	Egil Shijaku
	Omari Chatman
	Ashley Baker

	Created : 12 / 6 / 2016
	Modified : 12 / 8 / 2016
	Github Repository : https://github.com/ashleybm/cis200Project4

*/

#include<iostream>
#include<string>
#include<stack>
#include<queue>
using namespace std;

const int TRAIN_LOAD_TIME = 2;
const int PLANE_LOAD_TIME = 10;


class Train
{
	int trainNr;
	int maxNrPackages;
	int currNrPackages;
	int time = 0;
public:
	Train(int nr, int nrPack)
	{
		trainNr = nr;
		maxNrPackages = nrPack;
	}
	void load(int docTime)
	{
		/*
		Precondition: The load is called for train
		Poscondition: Sets time to half that for the train number because_
		it is only half the way there, there is still the return trip.
		*/
		time = docTime + ((trainNr * TRAIN_LOAD_TIME) / 2); 

	}
	int getTime()
	{
		return time;
	}
};
class Plane
{
	int planeNr;
	int maxNrPackages;
	int currNrPackages;
	int time = 0;
public:
	Plane(int nr, int nrPack)
	{
		planeNr = nr;
		maxNrPackages = nrPack;
	}

	void load(int docTime)
	{
		/*
		Precondition: The load is called for plane.
		Poscondition: Assigns half the time to time because it is only half
		the way there. There is still the return trip.
		*/
		time = docTime + ((planeNr * PLANE_LOAD_TIME) / 2);

	}
	int getTime()
	{
		return time;
	}
};

class excededTotalNubmerOfPackages
{
	/*Accounts for exceeding the total number of packages initialized.*/
	string message;
public:
	excededTotalNubmerOfPackages(int maxPack, string type) {
		message = " Exceded maximum number of packages for " + type + ".\n" +
			+" Maximum number is: " + to_string(maxPack) + "\n";
	}
	void error()
	{
		cout << message;
	}
};
class noSuchIdException
{
	/*No such object is in dock exception.*/
	string message;
public:
	noSuchIdException(string type, int pckId)
	{
		message = type + " number " + to_string(pckId) + " is not in dock\n";
	}
	void error()
	{
		cout << message;
	}
};
int main()
{
	int nrTrains;
	int nrPlanes;
	int trainTotalPackages;
	int planeTotalPackages;
	int nrPackage;
	int packageId;
	Train ** trains;
	Plane ** planes;

	//Pulls in the first line of data.
	cin >> nrTrains >> nrPlanes >> trainTotalPackages >> planeTotalPackages;


	//Based on the first line, initialzes classes with metrics
	trains = new Train *[nrTrains];
	planes = new Plane *[nrPlanes];
	int tempNrOfPackages = 0;

	//Fills Trains data
	if (nrTrains > 0 && nrTrains < 100) 
	{
		for (int i = 1; i < nrTrains + 1; i++)
		{
			cin >> nrPackage;
			tempNrOfPackages = tempNrOfPackages + nrPackage;
			/*try
			{
			if (tempNrOfPackages > trainTotalPackages)
			throw excededTotalNubmerOfPackages(trainTotalPackages, "trains");
			}
			catch(excededTotalNubmerOfPackages e)
			{
			e.error();
			cin >> nrPackage;
			tempNrOfPackages = tempNrOfPackages + nrPackage;
			}*/
			trains[i] = new Train(i, nrPackage);
		}
	}
	tempNrOfPackages = 0;

	//Fills Planes Data
	if (nrPlanes > 0 && nrPlanes < 10) 
	{
		for (int i = 1; i < nrPlanes + 1; i++)
		{

			cin >> nrPackage;
			tempNrOfPackages = tempNrOfPackages + nrPackage;
			/*try
			{
			if (tempNrOfPackages > planeTotalPackages)
			throw excededTotalNubmerOfPackages(planeTotalPackages, "planes");
			}
			catch (excededTotalNubmerOfPackages e)
			{
			e.error();
			}*/
			planes[i] = new Plane(i, nrPackage);

		}
	}


	queue<int> tempTrainQueue;
	queue<int> convBelt;
	stack<int> stackOf5;

	//Train Queue 
	if (trainTotalPackages > 0 && nrTrains > 0 && nrTrains < 100) 
	{
		for (int i = 0; i < trainTotalPackages; i++)
		{
			cin >> packageId;
			/*try {
			if (packageId > nrTrains || packageId <= 0)
			throw noSuchIdException("Train", packageId);
			}
			catch (noSuchIdException e) {
			e.error();
			}*/

			tempTrainQueue.push(packageId);
		}
	}


	//Plane Queue
	if (planeTotalPackages > 0 && nrPlanes > 0 && nrPlanes < 10) 
	{
		for (int i = 0; i < planeTotalPackages; i++)
		{
			cin >> packageId;
			/*try {
			if (packageId > nrPlanes || packageId <= 0)
			throw noSuchIdException("Plane", packageId);
			}
			catch (noSuchIdException e) {
			e.error();
			}*/
			convBelt.push(packageId);
		}
	}
	int dockTrainTime = 0;

	//Handles Train Queue
	while (!tempTrainQueue.empty())
	{
		//Adds to stack of five.
		for (int i = 0; i < 5; i++)
		{
			if (!tempTrainQueue.empty()) {
				stackOf5.push(tempTrainQueue.front());
				tempTrainQueue.pop();
			}
		}
		//Handles stack of 5
		while (!stackOf5.empty())
		{
			//calculates time for trains
			trains[stackOf5.top()]->load(dockTrainTime);
			dockTrainTime = dockTrainTime + (stackOf5.top() * TRAIN_LOAD_TIME);
			stackOf5.pop();
		}
	}

	int dockPlaneTime = 0;

	//Handles Plane Queue
	if (trainTotalPackages > 0 && nrTrains > 0 && nrTrains < 100) 
	{

		for (int i = 1; i <= nrTrains; i++)
		{
			// prints out the calulated time of trains
			cout << trains[i]->getTime() << " ";
		}
		cout << endl;
	}

	//Empties the convBelt 
	while (!convBelt.empty())
	{
		//calculates time for trains
		planes[convBelt.front()]->load(dockPlaneTime);
		dockPlaneTime = dockPlaneTime + (convBelt.front() * PLANE_LOAD_TIME);
		convBelt.pop();
	}
	if (planeTotalPackages > 0 && nrPlanes > 0 && nrPlanes < 10) 
	{
		for (int i = 1; i <= nrPlanes; i++)
		{
			// prints out the calulated time of planes
			cout << planes[i]->getTime() << " ";
		}
		cout << endl;
	}

	return 0;
}