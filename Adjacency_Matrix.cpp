#include<iostream>
#include<iomanip>
using namespace std;

class Graph{
	
	private:
		int source, destination;
	public:
		int inputEdges, inputVertix;
		
			void makeadjacencyMatrix(int **graph){
				for(int i = 0; i < inputEdges; i++) {
				    cout << "\nEnter the vertex pair for edge "<<i+1;
				    cout << "\nV(1): ";
				    cin >> source;
				    cout << "V(2): ";
				    cin >> destination;
				      
				    graph[source - 1][destination - 1] = 1;
  				 }
			}
			
			void printAdjacencyMatrix(int** graph){
				int i, j;
			//   printing matrix
				cout<<"\n\n    ";
				
			   	for(i = 0; i < inputVertix; i++){
			   		cout<<"   ("<<i+1<<")";	
				}
			      
				cout<<"\n\n";
			   
			   	for(i = 0; i < inputVertix; i++){
				    cout<<"   ("<<i+1<<")";
				     
					for(j = 0; j < inputVertix; j++){
				        cout<<"    "<<graph[i][j];
				    }
				    cout<<"\n\n";
			   	}
			}
};


int main() {
	
	Graph g;
	
   	int i, j;
   
   	cout << "Enter the number of vertexes of the graph: ";
   	cin >> g.inputVertix;
   
   	cout << "\nEnter the number of edges of the graph: ";
   	cin >> g.inputEdges;
   
   	int** graph = new int* [g.inputVertix];
   	
   	for(int i = 0; i < g.inputVertix; i++){
   		graph[i] = new int[g.inputVertix];
   	}

   	for(i = 0; i < g.inputVertix; i++){   	
	  	for(j = 0; j < g.inputVertix; j++){
      		graph[i][j] = 0;
	  	} 
   	}
   
   	g.makeadjacencyMatrix(graph);
	g.printAdjacencyMatrix(graph);
   
}

