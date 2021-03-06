#include<iostream>
using namespace std;

struct Vertex{
	int name;
	char* color;
	int startTime;
	int finishTime;
};

struct Node{
	Vertex v;
	struct Node* next = NULL;
};

struct Node* head = NULL;
char *BLACK = "Black", *GREY = "Grey", *WHITE = "White";
int numVertices, numEdges, count=0;
Vertex* vertices;
int** graph;
int** graphTranspose;

void inputGraph(){
	cout<<"Enter number of Vertices: ";		cin>>numVertices;
	cout<<"Enter number of Edges: ";		cin>>numEdges;
	vertices = new Vertex[numVertices];
	graph = new int*[numVertices];
	int i, j, k;
	for(i=0; i<numVertices; i++){
		vertices[i].name = i;
		vertices[i].color = WHITE;
		vertices[i].finishTime = 0;
		vertices[i].startTime = 0;
	}	
	for(i=0; i<numVertices; i++){
		graph[i] = new int[numVertices];
		for(j=0; j<numVertices; j++){
			graph[i][j] = INT_MAX;
		}
	}
	for(i=0; i<numEdges; i++){
		cout<<i+1<<". Enter start vertex: ";		cin>>j;
		cout<<"Enter end vertex: ";					cin>>k;
		graph[j][k] = 1;
		graphTranspose[k][j] = 1;
	}
}

void DFS(Vertex s){
	if(s.color == WHITE){
		vertices[s.name].color = GREY;
		vertices[s.name].startTime = ++count;
		for(int i=0; i<numVertices; i++){	
			if(s.name != i && graph[s.name][i] != INT_MAX){
				DFS(vertices[i]);
			}
		}
		vertices[s.name].finishTime = ++count;
		vertices[s.name].color = BLACK;
		struct Node* node = new Node();
		node->v = vertices[s.name];
		node->next = head;
		head = node;
	}
}

void printSortedGraph(){
	struct Node* temp = head;
	while(temp != NULL){
		cout<<temp->v.name<<" -- ";
		temp = temp->next;
	}
}

void DFSGT(Vertex s){
	if(s.color == WHITE){
		vertices[s.name].color = GREY;
		for(int i=0; i<numVertices; i++){	
			if(s.name != i && graphTranspose[s.name][i] != INT_MAX){
				DFSGT(vertices[i]);
			}
		}
		vertices[s.name].color = BLACK;
		cout<<s.name<<" -- ";
	}
}

int main(){
	inputGraph();
	// 9 9 0 7 0 1 6 7 1 7 1 2 3 2 2 5 3 4 4 5
	for(int i=0; i<numVertices; i++){
		DFS(vertices[i]);
	}
	struct Node* temp = head;
	for(int i=0; i<numVertices; i++){
		vertices[i].color = WHITE;
	}
	while(temp != NULL){
		cout<<"\n";
		DFSGT(temp->v);
		temp = temp->next;
	}
//	printSortedGraph();
	return 0;
}
