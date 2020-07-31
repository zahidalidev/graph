#include<iostream>
#include<iomanip>
#include <string>
#include <fstream>
#include <stdio.h> 
#include <string.h> 
#include <typeinfo>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

class Graph{
	public:
		int inputEdges, inputVertix;
		
		void makeadjacencyMatrix(int **graph, int source, int destination){
			graph[source][destination] = 1; 
		}			
		
		void depthFirstSearch(int startingNodeIndex, vector<bool>& visited, int** graph, char verticesNames[]){ 			  
		    cout << verticesNames[startingNodeIndex] << ", ";  //print current node 
		    visited[startingNodeIndex] = true; //visited true			  
		    for (int i = 0; i < inputVertix; i++) { 
		        if (graph[startingNodeIndex][i] == 1 && (!visited[i])) { 
		            depthFirstSearch(i, visited, graph, verticesNames); 
		        } 
		    } 
		} 
};


int * stringToIntegerVerices(string line){
	static int array[2];
	int vertices = 0;
	int graphDirection = 0;
	string vert;
	int verLength = 0;
	
	for(int i = 0; i < line.length(); i++){
		
		if(line[i] == '_'){
			string s2(1, line[i+1]);
			stringstream toInt2(s2);
			toInt2 >> array[1]; 	//converting character to string
			break;	
		}else{
			string s(1, line[i]);	//converting character to string 
			vert = vert + s;		//concatinating string
			verLength++;
		}
	}	 
					
	stringstream toInt1(vert);	//converting strings to integer
    toInt1 >> vertices;           //storing integer
    
    array[0] = vertices;
	return array;   
}

int toIntger(string a){
	int edges = 0;
	
	stringstream toInt(a);
	toInt >> edges;
	
	return edges;
}



int main() {
	system("Color E5");
	
	Graph g;
	
	int isGraphDirected;
    char * verticesNames;
    verticesNames = new char [g.inputVertix];
	
	//files lines
	string line1, line2, line3, allEdges;
	
	
//*************************** Reading File ******************************

	string line;
	
	char * fileName; 
	fileName = new char[100];
	cout << "\n\n\t\t*********************** Enter The File Name With Extension: ";
	cin >> fileName;
	cout << "\n\n";
	
	int count = 0, edgCount = 0;
	ifstream mfile (fileName);
	if (mfile.is_open()){
		while ( getline (mfile,line) )	{
    	  	
    	  	//extracting details of first line
    	  	if(count == 0 ){
    	  		line1 = line;
		  	}
		  	
			if(count == 1){
				line2 = line;
			}
			
			if(count == 2){
		  		line3 = line;
			}
			
			if(count > 2){
				allEdges = allEdges + "_" + line;
				edgCount++;
				
			}	
					
    	  	count++;
    	}
		mfile.close();
	}
	else{
		cout << "\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!! Unable to open file !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
		return 0;	
	} 


//*************************** Extracting Data from File data ******************************

	//extracting data from line1
	int *array;
	array = stringToIntegerVerices(line1);
	for ( int i = 0; i < 2; i++ ) {
	  	if(i == 0){
	  		g.inputVertix = *(array + i);
		}else{
			isGraphDirected = *(array + i);
			
		}	  
	}
	
	//extracting data from line2
	int nameCount = 0;
	for(int i = 0; i < line2.length(); i++){
		if(line2[i] != ' '){
			verticesNames[nameCount] = line2[i];
			nameCount++;
		}
	}
	
	//extracting data from line3
	g.inputEdges = toIntger(line3);
	
	//extracting data from line4
	int edCount = 0;
	for(int i = 0; i < allEdges.length(); i++){
		
		if(allEdges[i] != '_' && allEdges[i] != ' '){
			allEdges[edCount] = allEdges[i];
			edCount++;
		}
	}	 

//*************************** Creating Matrix ******************************
	
   
   	//making matrix 
   	int** graph = new int* [g.inputVertix];
   	for(int i = 0; i < g.inputVertix; i++){
   		graph[i] = new int[g.inputVertix];
   	}
	
	//initilizing with 0
   	for(int i = 0; i < g.inputVertix; i++){   	
	  	for(int j = 0; j < g.inputVertix; j++){
      		graph[i][j] = 0;
	  	} 
   	}
   
//*************************** adding edges ******************************
	int source = 0;
	int destination = 0;
	int len = strlen(verticesNames);
	
	for(int i = 0, j = 1; i < g.inputEdges * 2; i = i + 2, j = j + 2){	
		
		for(int k = 0; k < len ; k++){	
			
			if(allEdges[i] == verticesNames[k]){
				source = k;
			}
			
			if(allEdges[j] == verticesNames[k]){
				destination = k;
			}
			
		}
		g.makeadjacencyMatrix(graph, source, destination);
		
		if(isGraphDirected == 0){
			g.makeadjacencyMatrix(graph, destination, source);
		}
	}
	
	char startingNode;
	cout << " \n\n\t\t************************ Enter the Starting Node eg. A: ";
	cin >> startingNode;
	startingNode = toupper(startingNode);
	
	int startingNodeIndex;
	for(int i = 0; i < len; i++){
		if(startingNode == verticesNames[i]){
			startingNodeIndex = i;
		}
	}
	
	vector<bool> visited(g.inputVertix, false); 
	cout << "\n\t\t\t\t Visited Nodes Are: ";
	g.depthFirstSearch(startingNodeIndex, visited, graph, verticesNames); 
	cout << "\n\n";
	
   
   return 0;
}

