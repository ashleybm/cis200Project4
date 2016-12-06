/*
Egil Shijaku
program 4 CIS 200
*/

#include<iostream>
#include<stack>
#include<queue>
using namespace std;

const int LOADTIME = 2;
class Train {
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
	void load()
	{

	}

};
class Plane {
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
	void load() 
	{

	}

};

class Dock {
	stack<int> tempStack;
	stack<int> stackOf5;
	queue<int> assemblyLine;
public:
	Dock(stack<int> s, queue<int> q)
	{
		while (!s.empty())
		{
			tempStack.push(s.top());
			s.pop();
		}
		while (!q.empty())
		{
			assemblyLine.push(q.front());
			q.pop();
		}
	}

};

int main()
{
	int nrTrains;
	int nrPlanes;
	int trainTotalPackages;
	int planeTotalPackages;
	int nrPackage;
	Train ** trains;
	Plane ** planes;
	cin >> nrTrains >> nrPlanes >> trainTotalPackages >> planeTotalPackages;

	trains = new Train *[nrTrains];
	planes = new Plane *[nrPlanes];
	for (int i = 1; i <= nrTrains; i++)
	{
		cin >> nrPackage;
		trains[i] = new Train(i, nrPackage);
	}
	for (int i = 1; i <= nrPlanes; i++)
	{
		cin >> nrPackage;
		planes[i] = new Plane(i, nrPackage);
		
	}
	stack<int> stack;
	queue<int> queue;
	for (int i = 0; i < trainTotalPackages; i++)
	{
		cin >> nrPackage;
		stack.push(nrPackage);
	}
	for (int i = 0; i < planeTotalPackages; i++)
	{
		cin >> nrPackage;
		queue.push(nrPackage);
	}

	Dock dock(stack, queue);
	
	return 0;
}

