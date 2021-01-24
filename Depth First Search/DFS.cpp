#include <bits/stdc++.h>
using namespace std;

// Declaring all the global variable

vector<int> adjacent_list[10000], dfs_traversed_path;
string color[10000];
int parent[10000],level[10000];
int maximum_depth = 0, current_level = 0;

// Function which will take two nodes and will add them to create adjacent list

void add_edge(int u,int v) {
    adjacent_list[u].push_back(v);
    adjacent_list[v].push_back(u);   // as our graph is bi-directional
}

// This is our main dfs traversal function, by this we take a node as parameter, then from that node we explore
// it's child using adjacency list, for every child we run the dfs function recursively and complete dfs traversal

void dfs_traversal(int current_node) {
    color[current_node] = "G";  // marked as we visited the node
    level[current_node] = current_level;
    dfs_traversed_path.push_back(current_node);  // adding the node to our dfs path

    if (current_level > maximum_depth) {  // by this we are keeping track of maximum depth traversed
        maximum_depth = current_level;
    }

    int adjacent_list_size = adjacent_list[current_node].size();

    for(int i=0;i<adjacent_list_size;i++) {  // running a loop for getting all the child of our currently explored node

        int child_node = adjacent_list[current_node][i];

        if(color[child_node] == "W") {    // checking whether the child is previously visited or not
            current_level++;             //  as we are exploring child node from parent node we increase the level by 1
            parent[child_node] = current_node;
            dfs_traversal(child_node);    // we recursively call the dfs function again on the child node
        }
    }
    color[current_node] = "B";   // marked when all the child of one node is explored ( fully explored)
    current_level--;            //  as after exploring a node completely we backtrack to its parent node so we decrease the level by 1
}

int main() {
    int node_number,edge_number,starting_node,u,v,i;

    cin>>node_number>>edge_number;

    // Initializing the variable of all nodes to their default value

    for(i=0;i<node_number;i++) {
        color[i] = "W";
        parent[i] = -1;
        level[i] = -1;
    }

    for(i=0;i<edge_number;i++) {
        cin>>u>>v;
        add_edge(u,v);
    }

    cin>>starting_node;

    dfs_traversal(starting_node);  // we will call our dfs function from starting node

    cout<<endl;

    // print the dfs traversed path and it's corresponding depth

    for(i=0;i<dfs_traversed_path.size();i++) {
        int current_path = dfs_traversed_path[i];
        cout<<"Explored "<<current_path<<" at depth "<<level[current_path]<<endl;
    }

    cout<<endl;
    cout<<"Maximum Depth reached: "<<maximum_depth<<endl;  //printing the maximum depth dfs traversed
}
