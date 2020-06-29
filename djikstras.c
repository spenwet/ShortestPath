#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

//finds the shortest path from the currently discovered graph
int getNext(bool reached[], int dist[], int n){
    //set current min to INTMAX
    int c_min= INT_MAX;
    int min_i;
    for(int i=0;i<n;i++){
        //find the shortest path to any currently unvisited node
        if (!reached[i]&&dist[i]<c_min){
                c_min=dist[i];
                min_i=i;
        }
    }
    return min_i;
}


//Problem clearly calls for Dijkstra's shortest path algorithm
//take adjacency matrix and num vertices as input
int dijkstra(int graph[100][100], int n){
    //initialize array of shortest current possible distance to a node 
    //Initialize all but source to INTMAX so that source is read first
    int dist[n];
    dist[0]=0;
    for (int i=1;i<n;i++ ){
        dist[i]=INT_MAX;
    }
    //reached set, set of nodes that have been discovered
    //if set has been reached, true; otherwise false
    bool reached[n];
    //initialize values
    for (int i =0;i<n;i++ ){
        reached[i]=false;
    }

    //Loops until all vertices have been added
    for (int i=0; i<n; i++){
        //find the vertex shortest distance from the discovered map
        //will start with the capital, since it's the only 0
        int c_vert = getNext(reached, dist, n);
        reached[c_vert]=true;

        //if there is an edge incident on j, j has not been discovered, and the new path to j
        //would be shorter than the current path to j
        for (int j=0; j<n; j++){
            if (!reached[j] && graph[c_vert][j] && dist[c_vert] + graph[c_vert][j]< dist[j]){
                //make that the new shortest possible distance to j
                dist[j]=dist[c_vert]+graph[c_vert][j];
            }
        }
    }

    //find the longest length  and return it
    int c_max=0;
    for (int i=0; i<n; i++){
        if (dist[i]>c_max){
            c_max=dist[i];
        }
    }
    return c_max;
}

int main()
{
    //we know n is in the range [1,100], so make it the biggest possible
    int graph[100][100];
    //char for getchar
    int ch;
    //line gets what current line we are on
    int line=0;
    //n is number of vertices, c_num is for getting the number going in the
    //graph, and c_index gets the current index of the line
    int n=0, c_num=0, c_index=0;
    while ( ( ch=getchar() ) != EOF ) {
        if (line==0){
            if(ch=='\n'){
                //initialize diagonal to zero
                for (int i=0;i<n;i++){
                    graph[i][i]=0;
                }
                line++;
            }else{
                //get the number of vertices
                if (ch-48<=9&&ch-48>=0){
                    n*=10;
                    n+=ch-48;
                }else{
                    //exits if number of vertices is not a number
                    printf("Invalid input for number of vertices. Exiting program");
                    return 1;
                }
            }
        }else{
            if (ch-48<=9&&ch-48>=0){
                //get number for input
                c_num*=10;
                c_num+=(ch-48);
            }else if (ch=='x'){
                //make sure an x stands alone
                if (c_num!=0){
                    printf("Invalid input for adjacency matrix. Exiting program");
                    return 1;
                }
            }else if (ch==' '){
                //make sure they aren't putting in too many numbers
                if (c_index>=line){
                    printf("Invalid input for adjacency matrix. Exiting program");
                    return 1;
                }
                //add number to adjacency matrix
                graph[line][c_index]=c_num;
                graph[c_index][line]=c_num;
                //increase index and wipe number
                c_index++;
                c_num=0;
            }else if (ch=='\n'){
                //make sure they aren't putting in too many numbers
                if (c_index>=line){
                    printf("Invalid input for adjacency matrix. Exiting program");
                    return 1;
                }
                //same as a space, but also wipes index and increases line
                graph[line][c_index]=c_num;
                graph[c_index][line]=c_num;
                c_num=0;
                c_index=0;
                line++;
            }else{
                //makes sure there are no illegal inputs 
                printf("Invalid input for adjacency matrix. Exiting program");
                return 1;
            }
            if (line>=n){
                //ends when lines of adjacency matrix are filled
                break;
            }
        }
    
    }

    // call dijkstra and print value
    int ret = dijkstra(graph, n);
    printf("%d", ret);

    return 0;
}
