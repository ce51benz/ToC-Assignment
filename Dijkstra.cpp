#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

int stringToInteger(string str);
void main(){
	int y=-1,z;
	int graph[12][12];
	ifstream infile;
	string str,input;
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
		}
		y++;
	}
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