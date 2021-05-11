// TravllingSalesman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

#include <iostream>

using namespace std;

class Graph {
private:
	// number of vertices
	int n;

	// adjacency matrix
	int g[100][100];

public:
	// constructor
	Graph(int x)
	{
		n = x;

		// initializing each element of the adjacency matrix to zero
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				g[i][j] = 0;
			}
		}
	}

	void writeToFile() {
		ofstream out("file.txt");
		out << "     ";
		for (int i = 0;i < n;i++) {
			out << "Node" << i + 1 << " ";
		}

		for (int i = 0; i <n; i++)
		{
			out << "\n";
			out << "Node" << i + 1;
			for (int j = 0; j < n; j++)
				out << "    " << g[i][j]; 
			out << "\n";
		}
		cout << "Graph is saved in file.txt\n";
	}
	void displayAdjacencyMatrix()
	{
		cout << "\n\n Adjacency Matrix:\n";

		// displaying the 2D array
		cout << "     ";
		for (int i = 0;i < n;i++) {
			cout << "Node" << i + 1 << " ";
		}
		for (int i = 0; i < n; ++i) {
			cout << "\n";
			cout << "Node" << i + 1;
			for (int j = 0; j < n; ++j) {

				cout << "    " << g[i][j];
			}
		}
	}

	void addEdge(int x, int y, int w)
	{

		// checks if the vertex exists in the graph
		if ((x >= n) || (y > n)) {
			cout << "Vertex does not exists!";
		}

		// checks if the vertex is connecting to itself
		if (x == y) {
			cout << "Same Vertex!";
		}
		else {
			// connecting the vertices
			g[y][x] = w;
			g[x][y] = w;
		}
	}

	void addVertex()
	{
		// increasing the number of vertices
		n++;
		int i;

		// initializing the new elements to 0
		for (i = 0; i < n; ++i) {
			g[i][n - 1] = 0;
			g[n - 1][i] = 0;
		}
	}

	void removeVertex(int x)
	{
		// checking if the vertex is present
		if (x > n) {
			cout << "\nVertex not present!";
			return;
		}
		else {
			int i;

			// removing the vertex
			while (x < n) {
				// shifting the rows to left side
				for (i = 0; i < n; ++i) {
					g[i][x] = g[i][x + 1];
				}

				// shifting the columns upwards
				for (i = 0; i < n; ++i) {
					g[x][i] = g[x + 1][i];
				}
				x++;
			}

			// decreasing the number of vertices
			n--;
		}
	}
	int travllingSalesmanProblem()
	{
		// store all vertex apart from source vertex
		int s = 0;
		vector<int> vertex;
		for (int i = 0; i < n; i++)
			if (i != s)
				vertex.push_back(i);

		// store minimum weight Hamiltonian Cycle.
		int min_path = INT_MAX;
		do {

			// store current Path weight(cost)
			int current_pathweight = 0;

			// compute current path weight
			int k = s;
			for (int i = 0; i < vertex.size(); i++) {
				current_pathweight += g[k][vertex[i]];
				k = vertex[i];
			}
			current_pathweight += g[k][s];

			// update minimum
			min_path = min(min_path, current_pathweight);

		} while (
			next_permutation(vertex.begin(), vertex.end()));

		return min_path;
	}
};


int main()
{
	// creating objects of class Graph
	int vertex = 4;
	Graph obj(vertex);

	// calling methods
	obj.addEdge(0, 1, 10);
	obj.addEdge(0, 2, 15);
	obj.addEdge(0, 3, 20);
	obj.addEdge(1, 2, 35);
	obj.addEdge(1, 3, 25);
	obj.addEdge(2, 3, 30);

	// the adjacency matrix created
	obj.displayAdjacencyMatrix();
	//calculate shortest path
	cout <<endl<<"The cost of travel is "<< obj.travllingSalesmanProblem()<<endl;

	while (1) {
		cout << "Select one option\n1.Add node\n2.Remove node\n3.Export to file\n4.Exit\n";
		int choice;
		cin >> choice;
		string addAgain = "y";
		switch (choice) {
			case 1:
				int node;
				int weight;
				vertex++;
				obj.addVertex();
				while(addAgain.compare("Y")==0 || addAgain.compare("y")==0)
				{
					cout << "Input the existing node to make a connection\n";
					cin >> node;
					if (node > vertex) {
						cout << "Please select a node from 0 to " << vertex-1<<endl;
						continue;
					}
					cout << "Input the weight between new node and " << node << endl;
					cin >> weight;
					obj.addEdge(node - 1, vertex - 1, weight);
					cout << "Do you want to add one more edge ? Y/N ";
					cin >> addAgain;
				}
				obj.displayAdjacencyMatrix();
				cout << endl << "The new cost of travel is " << obj.travllingSalesmanProblem() << endl;
				break;

			case 2:
				if ( vertex <= 2) {
					cout << "Cannot delete any further node\n";
					break;
				}
				obj.displayAdjacencyMatrix();
				cout << "\nPlease select a node to delete\n";
				int selected;
				for (int i = 0;i < vertex;i++) {
					cout << i + 1 << ". Node" << i + 1 << endl;
				}
				cin >> selected;
				obj.removeVertex(selected - 1);
				vertex--;
				cout << "The new graph representation is\n";
				obj.displayAdjacencyMatrix();
				cout << endl << "The new cost of travel is " << obj.travllingSalesmanProblem() << endl;
				break;
			case 3:
				//expor to file
				obj.writeToFile();
				break;

			case 4:
				return 0;
		}
			
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
