#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

class Vertex{
public:
	char vname;
	Vertex(char ch){
		vname = ch;
	}
};

map<Vertex, int> dist;
map<Vertex, Vertex> prev;


class Edge{
public:
	Vertex source;
	Vertex dest;
	int dist;
};

class Graph{
public :
	vector<Vertex> vertex;
	Vertex find(char vertexname){
		for (Vertex x : vertex){
			if (x.vname == vertexname)
				return x;
		}
		return 0;
	}
};


int stringToInteger(string str);
void main(){
	int y=-1,z;
	int graph[12][12];
	ifstream infile;
	string str,input;
	Graph g;
	infile.open("graphTOC.csv");
	if (infile.fail())
		cerr << "Fail to open file.";
	while (!infile.eof()){
		z = 0;
		infile >> str;
		for (int i = 0; i < str.length(); i++){
			if (!isalpha(str[i]) && !ispunct(str[i])){
				input = "";
				input = input + str[i];
				graph[y][z++] = stringToInteger(input);
			}
			else if (isalpha(str[i])){
				Vertex r(str[i]);
				g.vertex.push_back(r);
			}
		}
		y++;
	}
	for (vector<Vertex>::iterator it = g.vertex.begin(); it != g.vertex.end(); it++)
		cout << (*it).vname << ' ';
	cout << endl;
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 12; j++)
			cout << graph[i][j] << " ";
		cout << endl;
	}
	infile.close();
}


int stringToInteger(string str){
	istringstream stream(str);
	int value;
	stream >> value;
	if (stream.fail() || !stream.eof())
		cout << "error!!!" << endl;
	return value;
}