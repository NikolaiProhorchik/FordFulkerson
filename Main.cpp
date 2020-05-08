#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int dfs(int v, int& counter, int** adjacency, int** potAdjacency, int* marks, bool* visited, int numofpoints, int drain, int maxFlow)
{
	if(v == drain)
	{
		return maxFlow;
	}
	
	visited[v] = true;
	marks[v] = counter;
	counter++;

	int currFlow;

	for (int i = 0; i < numofpoints; i++)
	{
		if (potAdjacency[v][i] != 0 && visited[i] == false && (currFlow = dfs(i, counter, adjacency, potAdjacency, marks, visited, numofpoints, drain, min(maxFlow, potAdjacency[v][i]))) > 0)
		{
			potAdjacency[v][i] -= currFlow;
			potAdjacency[i][v] += currFlow;
			return currFlow;
		}
	}

	return 0;
}

int main()
{
	int numofpoints;
	string str;
	int source;
	int drain;
	int maxFlow = 0;
	int currFlow = 0;

	ifstream in("input.txt");

	if (!in)
	{
		return 1;
	}

	stringstream strstr;
	string tx;

	getline(in, str);
	numofpoints = stoi(str);

	getline(in, str);
	strstr << str;
	strstr >> tx;
	source = stoi(tx);
	strstr >> tx;
	drain = stoi(tx);
	strstr.clear();

	int* marks = new int[numofpoints];
	bool* visited = new bool[numofpoints];

	int** adjacency		= new int*[numofpoints];
	int** potAdjacency	= new int*[numofpoints];

	for (int j = 0; j < numofpoints; j++)
	{
		adjacency[j]	= new int[numofpoints];
		potAdjacency[j] = new int[numofpoints];
	}

	for (int i = 0; i < numofpoints; i++)
	{
		getline(in, str);
		strstr << str;

		for (int j = 0; j < numofpoints; j++)
		{
			strstr >> tx;
			adjacency[i][j]	   = stoi(tx);
			potAdjacency[i][j] = stoi(tx);
		}

		strstr.clear();
		visited[i] = false;
	}
	
	in.close();

	int counter = 1;

	for (int i = 0; i < numofpoints; i++)
	{
		if(potAdjacency[source][i] != 0 && visited[i] == false)
		{
			while((currFlow = dfs(i, counter, adjacency, potAdjacency, marks, visited, numofpoints, drain, potAdjacency[source][i])) > 0)
			{
				maxFlow += currFlow;
			
				potAdjacency[source][i] -= currFlow;
				potAdjacency[i][source] += currFlow;
			
				for (int j = 0; j < numofpoints; j++)
				{
					visited[j] = false;
				}

				if(potAdjacency[source][i] == 0)
				{
					break;
				}
			}
		}
	}

	ofstream out("output.txt");

	int temp;

	for (int i = 0; i < numofpoints; i++)
	{
		for (int j = 0; j < numofpoints; j++)
		{
			temp = adjacency[i][j] - potAdjacency[i][j];

			if(temp >= 0)
			{
				out << temp  << " ";
			}
			else
			{
				out << 0  << " ";
			}
		}
		out << "\n";
	}

	out << maxFlow;

	out.close();

	return 0;
}