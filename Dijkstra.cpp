#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<cmath>

//Things to do
//1.Tell path of sub path before reach destination
//2.Detect error from read file
//3.Multi weight read value

using namespace std;
//Convert string to integer by use inputstream to convert.
int stringToInteger(string str);
void reverseString(string &str);
class Vertex{
public:
	char vname;
	Vertex(char ch){
		vname = ch;
	}
	Vertex(){
		vname = ' ';
	}

	vector<Vertex> adjacent;

	bool operator!=(Vertex v){
		return this->vname != v.vname;
	}
	bool operator==(Vertex v){
		return this->vname == v.vname;
	}

	void operator=(Vertex v){
		vname = v.vname;
		adjacent.clear();
		for (Vertex newvt : v.adjacent)
			adjacent.push_back(newvt);
	}

	bool operator<(Vertex v)const{
		return vname < v.vname;
	}
};

class Edge{
public:
	Vertex source;
	Vertex dest;
	int dist;
};

class Graph{
public:
	vector<Vertex> vertex;
	vector<Edge> edge;
	Vertex find(char vertexname){
		for (Vertex x : vertex){
			if (x.vname == vertexname)
				return x;
		}
		return NULL;
	}

	int length(Vertex u, Vertex v){
		for (Edge e : edge){
			if (e.source == u && e.dest == v)
				return e.dist;
		}
		return NULL;
	}

};
void displayPath(map<Vertex, Vertex>&prev, Vertex source, Vertex v, string &path, bool includeFinal);
void Dijkstra(Graph g, Vertex source,Vertex dest){
	string path;
	map<Vertex, float> dist;
	map<Vertex, Vertex> prev;
	Vertex u;
	vector<Vertex> Q;
	float alt;
	dist[source] = 0;

	for (Vertex v : g.vertex){
		if (v != source){
			dist[v] = INFINITY;
			prev[v] = NULL;
		}
		Q.push_back(v);
	}

	//Display initialized value
	cout << "[Initialized]" << endl;
	for (Vertex v : Q)
		cout << "Dist[" << v.vname << "] = " << dist[v] << endl;
	cout << endl;
	cout << "[Evaluate]" << endl;
	while (!Q.empty()){
		float min = dist[Q.front()];
		u = Q.front();
		for (Vertex v : Q){
			if (dist[v] < min){
				u = v;
				min = dist[v];
			}
		}

		//Remove vertex from Q
		for (vector<Vertex>::iterator it = Q.begin(); it != Q.end(); it++){
			if (!((*it) != u)){
				Q.erase(it);
				break;
			}
		}
		//Display evalutate path in each visit.
		cout << "Visit:" << u.vname <<" ,Dist["<<u.vname<<"] = "<<dist[u]<< endl;
		for (Vertex neighbor : u.adjacent){
			alt = dist[u] + g.length(u, neighbor);
			if (alt < dist[neighbor]){
				dist[neighbor] = alt;
				prev[neighbor] = u;
			}	
		}
		if (!Q.empty())
			cout << "Evaluate distance of remain unvisited vertexes." << endl;
		else
			cout << "No more vertex to evaluate."<<endl;
		for (Vertex v : Q){
			cout << "Dist[" << v.vname << "] = " << dist[v];
			if (dist[v] != INFINITY)
				cout << "\t";
			cout << "\t";
			cout << "path is:";
			displayPath(prev, source, v, path,false);
		}
		cout << "========================"<<endl;
	}

	//Display shortest path result.
	cout <<"[Finished]" << endl;
	cout << "Shortest path is:";
	displayPath(prev, source, dest, path, true);
	cout << "Distance from " << source.vname << " to " << dest.vname << " = " << dist[dest] << endl;


}


void main(){
	int row=-1,col,weight;
	ifstream infile;
	string str,input;
	char s,d;
	Graph graph;
	infile.open("graphTOC.csv");
	if (infile.fail())
		cerr << "Fail to open file.";

	//Read file and initialize graph.
	while (!infile.eof()){
		col = 0;
		infile >> str;
		for (int i = 0; i < str.length(); i++){
			if (!isalpha(str[i]) && !ispunct(str[i])){
				input = "";
				input = input + str[i];
				weight = stringToInteger(input);
				//If weight is not zero create edge and add it to graph.
				//Also add adjacent vertex to source vertex.
				if (weight > 0){
					Edge e;
					e.source = graph.vertex[row];
					e.dest = graph.vertex[col];
					e.dist = weight;
					graph.edge.push_back(e);
					graph.vertex[row].adjacent.push_back(graph.vertex[col]);
				}
				col++;
			}

			//If alphabet is read,create Vertex and add it to graph.
			else if (isalpha(str[i])){
				Vertex r(str[i]);
				graph.vertex.push_back(r);
			}
		}
			row++;
	}
	/*for (vector<Vertex>::iterator it = graph.vertex.begin(); it != graph.vertex.end(); it++)
		cout << (*it).vname << ' ';
	cout << endl;

	for (Vertex v : graph.vertex){
		cout << "Adjacent of " << v.vname << " is ";
		for (Vertex u : v.adjacent)
			cout << u.vname << " ";
		cout << endl<<endl;
	}

	for (Edge path : graph.edge){
		cout << "Source:" << path.source.vname << endl;
		cout << "Dest:" << path.dest.vname << endl;
		cout << "Weight:" << path.dist << endl;
		cout << "==========================" << endl;
	}*/
	cout << "KMITL TOC1/2557 Assignment 1 Dijkstra's Algorithm" << endl;
	cout << "[Member]" << endl;
	cout << "1.Maturose Kappako\t55010977" << endl;
	cout << "2.Suratchanan Kraidech\t55011362" << endl<<endl;
	while (true)
	{
		cout << "Enter source vertex:";
		cin >> s;
		cout << "Enter destination vertex:";
		cin >> d;
		if (graph.find(s) == NULL || graph.find(d) == NULL)
			cerr << "Input vertex incorrect,please try again.";
		else
			break;
	}
	cout << endl;
	Dijkstra(graph, graph.find(s), graph.find(d));

	infile.close();
}

//This function use for display path from source to destination.
//Destination display depend on includeFinal.
void displayPath(map<Vertex, Vertex>&prev, Vertex source, Vertex v, string &path, bool includeFinal){
	path = "";
	if (prev[v] != NULL){
		if (includeFinal)
			path = path + v.vname + " ";
		while (prev[v] != source){
			path = path + prev[v].vname + " ";
			v = prev[v];
		}
		path = path + prev[v].vname;
		reverseString(path);
	}
	else
		path = "Undefined";
	cout << path << endl;
}


int stringToInteger(string str){
	istringstream stream(str);
	int value;
	stream >> value;
	if (stream.fail() || !stream.eof()){
		cout << "error!!!" << endl;
		return NULL;
	}
	return value;
}

void reverseString(string &str){
	string reverse = "";
	if (str != ""){
		for (int i = str.length() - 1; i >= 0; i--)
			reverse = reverse + str[i];
	}
	str = reverse;
}