#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//A structure to represent an adjacency list node
struct AdjListNode {
int successor;
struct AdjListNode* next;
};

//A structure to represent an adjacency list 
struct AdjList {
int age;  //age associated with the particular vertex id
int VertexId;
int TeenCnt;
struct AdjListNode *head;
};


//A structure to represent a Graph
struct Graph {
int numVertex; // Number of Vertices in the graph
struct AdjList* array; 
}; 


//Function to create a new Node in adjacent list
struct AdjListNode* NewAdjListNode(int successor) {
struct AdjListNode* newnode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
newnode->successor = successor;
newnode->next = NULL;
return newnode;
}

//Function to create Graph
struct Graph* createGraph(int numVertex)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->numVertex = numVertex;
 
    // Create an array of adjacency lists.  Size of array will be numVertex
    graph->array = (struct AdjList*) malloc(numVertex * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL and age as 0
    int i;
    for (i = 0; i < numVertex; ++i)
        graph->array[i].head = NULL;
	graph->array[i].age = 0;
	graph->array[i].VertexId = 0;
	graph->array[i].TeenCnt = 0;
 
    return graph;
}

// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertex; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d age %d TeenCnt %d\n ", v,graph->array[v].age,graph->array[v].TeenCnt  );
        //printf("\n Adjacency list of vertex age %d\n ", graph->array[v].age);
        //printf("\n Adjacency list of vertex TeenCnt %d\n ", graph->array[v].TeenCnt);

//        while (pCrawl)
//        {
//            printf("-> %d", pCrawl->successor);
//            pCrawl = pCrawl->next;
//        }
        printf("\n");
    }
}

// A utility function to age associated with particular Vertex
int FindAge(struct Graph* graph, int vertex_id)
{
    int v;
    for (v = 0; v < graph->numVertex; ++v)
    {
	if(graph->array[v].VertexId == vertex_id) {
	return graph->array[v].age;
	}
    }
	return 0;

}


int main(int argc, char *argv[]) 
{
	char *inputFile   = "/no/such/file";
        char buffer[10000];
   	char *rd;
	char *parse;
	char *str;
	struct Graph* ATFGraph;
	struct AdjListNode* newnode;
	if(argc !=2) {
	    printf("%s requires input graph.txt file: <Name of the input file> \n", argv[0]);
	    return -1;
  	}
	
	inputFile = strdup(argv[1]);  //Input graph file
	printf("before file open\n");
        // open input file
        FILE *fp = fopen(inputFile, "r");
        if (fp == NULL) {
	 perror("open");
	 fprintf(stderr, "Cannot open input file\n");
	 exit(1);
        }
    

       //Read the file into an array of strcuture type rec_t
       int vertices = 0;
       while (1) {	
   	rd = fgets(buffer, 10000, fp);
   	if (rd == 0) {// 0 indicates EOF 
   	    break;
   	}
   	if (rd < 0) {
   	    perror("read");
   	    exit(1);
   	    }
   	vertices++;
       }
   
   
        //Close the input file 
        (void) fclose(fp);
///////////////////////////////////////////// Done calculating number of vertices //////////////////


   
//Create Graph with numVertex = vertices

        ATFGraph = createGraph(vertices);
	printf("graph created with %d vertices\n", vertices);


///////////////////////////////////////////Populate Graph///////////////////////////////////////////

	int number;
	int index = 0;

        // open input file
        fp = fopen(inputFile, "r");
        if (fp == NULL) {
	 perror("open");
	 fprintf(stderr, "Cannot open input file\n");
	 exit(1);
        }
    
//////////////////////////////////////////Read each line and populate graph array/////////////////////
       while (1) {	
   	rd = fgets(buffer, 10000, fp);
   	if (rd == 0) {// 0 indicates EOF 
   	    break;
   	}
   	if (rd < 0) {
   	    perror("read");
   	    exit(1);
   	    }
	
	//puts(buffer);

	ATFGraph->array[index].age = rand() % 50;
	parse = strtok(buffer, " ");
	str = parse;
	number = atoi(str);
	ATFGraph->array[index].VertexId = number;
	parse = strtok(NULL, " ");
//////////////////////////////////Populate adjacent list///////////////////////////////////////////

	while(parse !=NULL) {
  	  str = parse;
	  number = atoi(parse);
	  newnode = NewAdjListNode(number);
          newnode->next = ATFGraph->array[index].head;
          ATFGraph->array[index].head = newnode;
	  parse = strtok(NULL, " ");
	  }
	index++;	
	
       }
   
   
        //Close the input file 
        (void) fclose(fp);

//printGraph(ATFGraph);	
   
////////////////Calculate Number of teenage follower for each vertex (age between 13 and 19)/////////////////////


printf("before calculating number of teenagers\n");
	int successor_age;
	struct AdjListNode* listnode;
	for(index = 0; index <  ATFGraph->numVertex; ++index) 
	{
		printf("Checking Vertex number %d\n", index);
		listnode = ATFGraph->array[index].head;
	        while (listnode)
	        {
		    successor_age = FindAge(ATFGraph, listnode->successor);
		    if(successor_age >=13 && successor_age <=19)
			ATFGraph->array[index].TeenCnt++;	
	            listnode = listnode->next;
	        }
    	}

printf("after calculating number of teenagers\n");


//printGraph(ATFGraph);	
///////////////Average number of teenage followers of users over 20 years (K years)  old
	int TotalFollowers = 0;
	int TotalUsers = 0;
	for(index = 0; index <  ATFGraph->numVertex; ++index) 
	{
		if(ATFGraph->array[index].age > 20) {
		   TotalUsers++;
		   TotalFollowers = TotalFollowers + (ATFGraph->array[index].TeenCnt);
		}
	
    	}
	

	printf ("Followers %d Users %d\n",TotalFollowers, TotalUsers);
	printf ("Average number of Teenage followers %d\n",TotalFollowers/TotalUsers);
	//printGraph(ATFGraph);	





}
















 
// Adds an edge to an undirected graph
//void addEdge(struct Graph* graph, int src, int dest)
//{
//    // Add an edge from src to dest.  A new node is added to the adjacency
//    // list of src.  The node is added at the begining
//    struct AdjListNode* newNode = newAdjListNode(dest);
//    newNode->next = graph->array[src].head;
//    graph->array[src].head = newNode;
// 
//    // Since graph is undirected, add an edge from dest to src also
//    newNode = newAdjListNode(src);
//    newNode->next = graph->array[dest].head;
//    graph->array[dest].head = newNode;
//}
 

