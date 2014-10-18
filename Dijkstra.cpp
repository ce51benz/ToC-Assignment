#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<stack>
#include<map>
#include<cmath>
//Things to do
//1.String as node name.

using namespace std;
//Convert string to integer by use inputstream to convert.
int stringToInteger(string str);
class Vertex{
public:
	string vname;
	Vertex(string str){
		vname = str;
	}

	//Use for trigger NULL instantiation.
	Vertex(char* str){
		vname = "";
	}
	Vertex(){
		vname = "";
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
private:
	vector<Edge> edge;
public:
	vector<Vertex> vertex;
	Vertex find(string vertexname){
		for (Vertex x : vertex){
			if (x.vname == vertexname)
				return x;
		}
		return NULL;
	}

	int length(Vertex u, Vertex v){
		for (Edge e : edge){
			if ((e.source == u && e.dest == v) || (e.source == v && e.dest == u))
				return e.dist;
		}
		return NULL;
	}
	bool addEdge(Edge edgeToAdd){
		for (Edge e : edge){
			if ((e.source == edgeToAdd.source && e.dest == edgeToAdd.dest) ||
				(e.source == edgeToAdd.dest && e.dest == edgeToAdd.source)){
				if (e.dist != edgeToAdd.dist){
					cerr << "Edge check error!!!" <<endl << "The adjacency matrix's weight of edge is not match."<<endl;
					return false;
				}
				else
					return true;
			}
		}
		edge.push_back(edgeToAdd);
		return true;
	}
};
bool initialized(string &filename,Graph &graph);
bool isValidGraph(Graph &graph);
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


int main(){
	string str1,str2,filename;
	Graph graph;
	cout << "KMITL TOC1/2557 Assignment 1 Dijkstra's Algorithm" << endl;
	cout << "[Member]" << endl;
	cout << "1.Maturose Kappako\t55010977" << endl;
	cout << "2.Suratchanan Kraidech\t55011362" << endl << endl;
	cout << "input .csv file path(or only filename if stay at same location of program";
	cout << endl <<"that contain graph adjacency matrix representation:" << endl;
	getline(cin, filename);
	//Initialized graph from adjacency matrix file.
	//If initialized is false program will terminate here.
	if (!initialized(filename,graph)){
		return 0;
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
	if (!isValidGraph(graph)){
		cout << "This graph is invaild,please use proper adjacency matrix to represent!!!" << endl;
	}
	else{
		while (true)
		{
			cout << "Enter source vertex:";
			cin >> str1;
			cout << "Enter destination vertex:";
			cin >> str2;
			if (graph.find(str1) == NULL || graph.find(str2) == NULL)
				cerr << "Input vertex incorrect,please try again."<<endl;
			else
				break;
		}
		cout << endl;
		Dijkstra(graph, graph.find(str1), graph.find(str2));
	}
	return 0;
}

//This function use for display path from source to destination.
//Destination display depend on includeFinal.
void displayPath(map<Vertex, Vertex>&prev, Vertex source, Vertex v, string &path, bool includeFinal){
	stack<string> st;
	path = "";
	if (prev[v] != NULL){
		if (includeFinal)
			st.push(v.vname);
		while (v != source){
			st.push(prev[v].vname);
			v = prev[v];
		}
		while (!st.empty()){
			path = path + st.top() + ' ';
			st.pop();
		}
	}
	else
		path = "Undefined";
	cout << path << endl;
}

//This function use to check whether perferred graph is proper graph or not.
bool isValidGraph(Graph &graph){
	int oddVertexCount = 0;
	for (Vertex v : graph.vertex){
		if (v.adjacent.size() % 2 != 0)
			oddVertexCount++;
	}
	return oddVertexCount % 2 == 0 && graph.vertex.size() != 0;
}

//Initialized graph from adjacency matrix file.
bool initialized(string &filename,Graph &graph){
	int row = 0, col, weight;
	ifstream infile;
	string str, input;
	int shift;
	infile.close();
	infile.open(filename);
	if (infile.fail()){
		cerr << "Fail to open file."<<endl;
		return false;
	}

	//Read first line to create vertex and add it to graph.
	if (!infile.eof()){
		infile >> str;
		int i = 0;
		while (i < str.length()){
			shift = 1;
			if (!ispunct(str[i])){
				int j = i + 1;
				while (j < str.length()){
					if (!ispunct(str[j])){
						shift++; j++;
					}
					else
						break;
				}
				Vertex r(str.substr(i,shift));
				graph.vertex.push_back(r);
			}
			i += shift;
		}
	}
	//Read file and initialize graph.
	while (!infile.eof()){
		col = 0;
		infile >> str;
		if (infile.eof())break;
		int i = 0;
		while (i < str.length()){
			input = "";
			shift = 1;
			if (!ispunct(str[i])){
				int j = i + 1;
				while (j < str.length()){
					if (!ispunct(str[j])){
						shift++; j++;
					}
					else
						break;
				}
				input = input + str.substr(i, shift);
				try{
					weight = stringToInteger(input);
				}
				catch (exception ex){
					return false;
				}
				//If weight is not zero create edge and add it to graph.
				//Also add adjacent vertex to source vertex.
				if (weight > 0){
					Edge e;
					e.source = graph.vertex[row];
					e.dest = graph.vertex[col];
					e.dist = weight;
					if (!graph.addEdge(e))
						return false;
					graph.vertex[row].adjacent.push_back(graph.vertex[col]);
				}
				col++;
			}
			i += shift;
		}
		row++;
	}
	return true;
}

int stringToInteger(string str){
	istringstream stream(str);
	int value;
	stream >> value;
	if (stream.fail() || !stream.eof()){
		cout << "Input string error!!!" << endl;
		throw exception();
	}
	return value;
}