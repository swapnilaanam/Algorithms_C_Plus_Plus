#include <bits/stdc++.h>
using namespace std;

// Declaring all the global variable

vector<int> adjacent_list[10000],dfs_traversed_path;
string color[10000];
int parent[10000],level[10000];
int current_level = 0;

// Function for initializing all the variable of all nodes to their default value

void dfs_initializer(int node_number) {
    for(int i=0;i<node_number;i++) {
        color[i] = "W";  // marked as white meaning not visited
        parent[i] = -1;
        level[i] = -1;
    }
}

// Function which will take two nodes and will add them to create adjacent list

void add_edge(int u,int v) {
    adjacent_list[u].push_back(v);
    adjacent_list[v].push_back(u);  // as our graph is bi-directional
}

// This is our main dfs traversal function, by this we take a node as parameter, then from that node we explore
// it's child using adjacency list, for every child we run the dfs function recursively and complete dfs traversal (current upto depth limit)

void dfs_traversal(int current_node,int current_depth_limit) {
    color[current_node] = "G";   // marked as we visited the node
    level[current_node] = current_level;
    dfs_traversed_path.push_back(current_node);  // adding the node to our dfs path

    int adjacent_list_size = adjacent_list[current_node].size();

    for(int i=0;i<adjacent_list_size;i++) {       // running a loop for getting all the child of our currently explored node

        if(current_level == current_depth_limit)  // Here we check if we already explored node of level/depth up to the current depth limit,
            break;                               //  if we did, we don't explore the child of that node and break out of loop

        int child_node = adjacent_list[current_node][i];

        if(color[child_node] == "W") {   // checking whether the child is previously visited or not
            current_level++;            //  as we are exploring child node from parent node we increase the level by 1
            parent[child_node] = current_node;
            dfs_traversal(child_node,current_depth_limit);   // we recursively call the dfs function again on the child node
        }
    }
    color[current_node] = "B";   // marked when all the child of one node is explored
    current_level--;            //  as after exploring a node completely we backtrack to its parent node so we decrease the level by 1
}

int main() {
    int node_number,edge_number,starting_node,u,v,i,j;
    int depth_limit = 9;

    cin>>node_number>>edge_number;

    dfs_initializer(node_number);  // Initializing all the variable of all nodes to their default value

    for(i=0;i<edge_number;i++) {
        cin>>u>>v;
        add_edge(u,v);
    }

    cin>>starting_node;

    // we run a loop to run dfs for 0 to highest depth limit 9 (every time we increase depth limit by 1 and run dfs)

    for(j=0;j<=depth_limit;j++) {
        dfs_traversal(starting_node,j);  // we will call our dfs function from starting node and will give current depth limit
        cout<<endl;
        cout<<"When depth limit: "<<j<<endl;
        cout<<endl;
        for(i=0;i<dfs_traversed_path.size();i++) {
            int current_path = dfs_traversed_path[i];
            cout<<"Explored "<<current_path<<" at depth "<<level[current_path]<<endl;
        }

        dfs_initializer(node_number);  // Initializing all the variable of all nodes to their default value
        dfs_traversed_path.clear();   //  clearing the dfs path vector
        current_level = 0;
    }
}


