#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h> 
#include <string.h> 
#include <typeinfo>
#include <sstream>

using namespace std;

class Node{
	
	public:
	    char data;			//data variable for values
	    Node *next;			//next pointer
	    
		Node* newAdjListNode(char value){
		    Node *node = new Node;	//new node
		    node -> data = value;	//saving data into the ndoe
		    node -> next = NULL;	//the next pointer of node is null
		    return node;
		}
};

// List class
class List{
	
	public:
	    Node *head;  //head pointer
};

//Graph Class

class Graph{
	
	public:
	    int vertex;
	    List *arr;		//array of list
		
		Graph* createGraph(int vertex){
		    Graph *graph = new Graph;
		    graph -> vertex = vertex;
		    
		    graph -> arr = new List[vertex];  //creating array of list
		
		    for(int i = 0; i < vertex; i++){
		        graph -> arr[i].head = NULL;  //head of every list is null at the begining
		    }
		    return graph;
		}
		
		void addEdge(Graph *graph, int src, char dest){
			Node n;	//n is object of Node class
		    
			//addning edge from source to destination
		    Node *nptr = n.newAdjListNode(dest);
		    nptr -> next = graph -> arr[src].head;
		    graph -> arr[src].head = nptr;
		    
		}
		
		//function to print the graph
		void printGraph(Graph* graph, char verticesNames[]){

			cout << "\n\tAdjacency List\n\n";
		    for(int i = 0; i < graph -> vertex; i++){	//printing all adjacency lists of graph 
		    	
		        Node *root = graph -> arr[i].head;

		        cout << "\t"<< verticesNames[i];
		        while(root != NULL){	//printing one list
		            cout << " --> " << root -> data;
		            root = root -> next;
		        }
		        cout << endl;
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

int main(){
	
	Graph *graph;
    Graph g;
    
    int vertices, isGraphDirected, edges;
    char verticesNames[vertices];
	
	//files lines
	string line1, line2, line3, allEdges;
	
	
//*************************** Reading File ******************************

	string line;
	
	int count = 0, edgCount = 0;
	ifstream mfile ("graphData.txt");
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
		cout << "Unable to open file";	
	} 


//*************************** Extracting Data from File data ******************************

	//creating graph extracting data from line1
	int *array;
	array = stringToIntegerVerices(line1);
	for ( int i = 0; i < 2; i++ ) {
	  	if(i == 0){
	  		vertices = *(array + i);
		}else{
			isGraphDirected = *(array + i);
			
		}	  
	}
	graph = g.createGraph(vertices);  //creating graph
	
	//extracting data from line2
	int nameCount = 0;
	for(int i = 0; i < line2.length(); i++){
		if(line2[i] != ' '){
			verticesNames[nameCount] = line2[i];
			nameCount++;
		}
	}
	
	//extracting data from line3
	edges = toIntger(line3);
//	cout << edges;
	
	//extracting data from line4
	int edCount = 0;
	for(int i = 0; i < allEdges.length(); i++){
		
		if(allEdges[i] != '_' && allEdges[i] != ' '){
			allEdges[edCount] = allEdges[i];
			edCount++;
		}
	}	 
	
	
//***************************** making adjacency list ****************************** 

	int src = 0;
	int len = strlen(verticesNames);
	for(int i = 0, j = 1; i < edges * 2; i = i + 2, j = j + 2){	
		
		for(int k = 0; k < len ; k++){	
			if(allEdges[i] == verticesNames[k]){
				src = k;
			}
		}
		//calling addEdge method from the graph class
		g.addEdge(graph, src, allEdges[j]);
		
		//if graph is undirected (0 for undirected)		
		if(isGraphDirected == 0){
			for(int l = 0; l < len ; l++){
				if(allEdges[j] == verticesNames[l]){
					src = l;
				}
			}
			//calling addEdge method from the graph class
			g.addEdge(graph, src, allEdges[i]);
		}
	
	}
	
	
//***************************** printing adjacency list ******************************

    g.printGraph(graph, verticesNames);
    
    return 0;
}
