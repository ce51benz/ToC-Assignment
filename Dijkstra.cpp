#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<cmath>
using namespace std;

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
public :
	vector<Vertex> vertex;
	vector<Edge> edge;
	Vertex find(char vertexname){
		for (Vertex x : vertex){
			if (x.vname == vertexname)
				return x;
		}
		return 0;
	}

	int length(Vertex u, Vertex v){
		for (Edge e : edge){
			if (e.source == u && e.dest == v)
				return e.dist;
		}
		return NULL;
	}

};

void Dijkstra(Graph g, Vertex source){
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

	while (!Q.empty()){
		float min = dist[Q.front()];
		for (Vertex v : Q){
			if (dist[v] < min){
				u = v;
				min = dist[v];
			}
		}
		for (vector<Vertex>::iterator it = Q.begin(); it != Q.end(); it++){
			if (!((*it) != u)){
				Q.erase(it);
				break;
			}
		}

		for (Vertex neighbor : u.adjacent){
			alt = dist[u] + g.length(u, neighbor);
			if (alt < dist[u]){
				dist[neighbor] = alt;
				prev[neighbor] = u;
			}
		}
	}
	//Show result

}
int stringToInteger(string str);
void main(){
	int row=-1,col,weight;
	int graph[12][12];
	ifstream infile;
	string str,input;
	Graph g;
	infile.open("graphTOC.csv");
	if (infile.fail())
		cerr << "Fail to open file.";
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
					e.source = g.vertex[row];
					e.dest = g.vertex[col];
					e.dist = weight;
					g.edge.push_back(e);
					g.vertex[row].adjacent.push_back(g.vertex[col]);
				}
				col++;
			}

			//If alphabet is read,create Vertex and add it to graph.
			else if (isalpha(str[i])){
				Vertex r(str[i]);
				g.vertex.push_back(r);
			}
		}
			row++;
	}
	for (vector<Vertex>::iterator it = g.vertex.begin(); it != g.vertex.end(); it++)
		cout << (*it).vname << ' ';
	cout << endl;

	for (Vertex v : g.vertex){
		cout << "Adjacent of " << v.vname << " is ";
		for (Vertex u : v.adjacent)
			cout << u.vname << " ";
		cout << endl<<endl;
	}

	for (Edge path : g.edge){
		cout << "Source:" << path.source.vname << endl;
		cout << "Dest:" << path.dest.vname << endl;
		cout << "Weight:" << path.dist << endl;
		cout << "==========================" << endl;

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