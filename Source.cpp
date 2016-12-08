/*
Egil Shijaku
program 4 CIS 200
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
	int time;
public:
	Train(int nr, int nrPack)
	{
		trainNr = nr;
		maxNrPackages = nrPack;
	}
	void load(int docTime)
	{
		time = docTime + ((trainNr * TRAIN_LOAD_TIME) / 2);//divided by 2 because this is only half way.
														//There is still the trip back to the dock.
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
	int time;
public:
	Plane(int nr, int nrPack)
	{
		planeNr = nr;
		maxNrPackages = nrPack;
	}

	void load(int docTime) 
	{
		time = docTime + ((planeNr * PLANE_LOAD_TIME) / 2);//divided by 2 because this is only half way.
														//There is still the trip back to the dock.
	}
	int getTime()
	{
		return time;
	}
};

class excededTotalNubmerOfPackages
{
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
	cin >> nrTrains >> nrPlanes >> trainTotalPackages >> planeTotalPackages;

	trains = new Train *[nrTrains];
	planes = new Plane *[nrPlanes];
	int tempNrOfPackages = 0;
	for (int i = 1; i <= nrTrains; i++)
	{
		cin >> nrPackage;
		tempNrOfPackages = tempNrOfPackages + nrPackage;
		try
		{
			if (tempNrOfPackages > trainTotalPackages)
				throw excededTotalNubmerOfPackages(trainTotalPackages, "trains");
		}
		catch(excededTotalNubmerOfPackages e)
		{
			e.error();
			cin >> nrPackage;
			tempNrOfPackages = tempNrOfPackages + nrPackage;
		}
		trains[i] = new Train(i, nrPackage);
	}
	tempNrOfPackages = 0;
	for (int i = 1; i <= nrPlanes; i++)
	{

		cin >> nrPackage;
		tempNrOfPackages = tempNrOfPackages + nrPackage;
		try
		{
			if (tempNrOfPackages > planeTotalPackages)
				throw excededTotalNubmerOfPackages(planeTotalPackages, "planes");
		}
		catch (excededTotalNubmerOfPackages e)
		{
			e.error();
		}
		planes[i] = new Plane(i, nrPackage);
		
	}
	queue<int> tempTrainQueue;
	queue<int> convBelt;
	stack<int> stackOf5;
	for (int i = 0; i < trainTotalPackages; i++)
	{
		cin >> packageId; 
		try {
			if (packageId > nrTrains || packageId <= 0)
				throw noSuchIdException("Train", packageId);
		}
		catch (noSuchIdException e) {
			e.error();
		}

		tempTrainQueue.push(packageId);
	}

	for (int i = 0; i < planeTotalPackages; i++)
	{
		cin >> packageId;
		try {
			if (packageId > nrPlanes || packageId <= 0)
				throw noSuchIdException("Plane", packageId);
		}
		catch (noSuchIdException e) {
			e.error();
		}
		convBelt.push(packageId);
	}
	int dockTrainTime = 0;

	while (!tempTrainQueue.empty())
	{
		for (int i = 0; i < 5; i++)
		{
			stackOf5.push(tempTrainQueue.front());
			tempTrainQueue.pop();
		}
		while (!stackOf5.empty())
		{
			trains[stackOf5.top()]->load(dockTrainTime);
			dockTrainTime = dockTrainTime + (stackOf5.top() * TRAIN_LOAD_TIME);
			stackOf5.pop();
		}
	}
	int dockPlaneTime = 0;
	for (int i = 1; i <= nrTrains; i++)
	{
		cout << trains[i]->getTime() << " ";
	}
	cout << endl;

	while (!convBelt.empty())
	{
		planes[convBelt.front()]->load(dockPlaneTime);
		dockPlaneTime = dockPlaneTime + (convBelt.front() * PLANE_LOAD_TIME);
		convBelt.pop();
	}
	for (int i = 1; i <= nrPlanes; i++)
	{
		cout << planes[i]->getTime() << " ";
	}
	cout << endl;
	return 0;
}

