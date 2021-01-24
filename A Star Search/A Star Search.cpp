#include <bits/stdc++.h>
using namespace std;

// Declaring global source and target variable

pair<int,int> source;
pair<int,int> target;

// creating a structure cell to store cell information

struct cell {
    int parent_i,parent_j;
    int f,g,h;
};

cell cell_details[1000][1000]; // creating a cell_detials variable to store cell information

// This function checks whether our current move to a cell is valid or not

bool is_valid(int current_row, int current_col, int rows,int columns) {
    if(current_row >= 0 && current_col >=0 && current_row < rows && current_col < columns)
        return true;
    else
        return false;
}

// This function checks whether our current move to a cell is blocked(#) or not

bool is_unblocked(vector<vector<char>> &input_grid, int i, int j) {
    if(input_grid[i][j] != '#')
        return true;
    else
        return false;
}

// This function checks whether our current cell is the goal/ target cell or not

bool is_destination(int current_row, int current_column) {
    if(current_row == target.first && current_column == target.second)
        return true;
    else
        return false;
}

// This function gives us the heuristic value of current cell from target cell

int calculate_heuristic_value(int current_row,int current_col) {
    int manhathan_distance = abs(target.first - current_row) + abs(target.second - current_col); //calculating Manhattan distance of a cell from target cell
    return manhathan_distance;
}

// This function helps us to print the path from source to target using parent and backtract

void find_path() {
    int row = target.first;
    int column = target.second;

    pair<int,int> current_path;

    stack<pair<int,int>> path;  // declarig a stack for storing path

    while(!(cell_details[row][column].parent_i == row && cell_details[row][column].parent_j == column)) {
        path.push(make_pair(row,column));
        int temp_row = cell_details[row][column].parent_i;
        int temp_column = cell_details[row][column].parent_j;
        row = temp_row;
        column = temp_column;
    }

    cout<<endl;
    cout<<row<<","<<column<<" (Source)"<<endl;

    while(!path.empty()) {  // running until the path variable is not empty
        current_path = path.top();
        path.pop();

        if(current_path.first == target.first && current_path.second == target.second)
            cout<<current_path.first<<","<<current_path.second<<" (Target)"<<endl;
        else
            cout<<current_path.first<<","<<current_path.second<<endl;
    }
}

// This is our main a_star_search funtion, it takes source node and then traverse the grid/maze
// using heuristic cost + g cost( current cost from souce node)

void a_star_search(vector<vector<char>> &input_grid, int rows,int columns) {

    int i,j,g_value,h_value,f_value;

    set<pair<int,pair<int,int>>> open_list;  // declaring a set, it will keep the cell with lower cost in front, sorted
    pair<int, pair<int,int>> current_cell;

    cell_details[rows][columns];  // variable to store cell information

    bool closed_list[rows][columns]; // for keeping track of visited cell
    bool found_target = false;

    memset(closed_list, false, sizeof(closed_list));  // initializing all value to false

    if(is_valid(source.first, source.second, rows, columns) == false)
        return;

    if(is_valid(target.first, target.second, rows, columns) == false)
        return;

    if((is_unblocked(input_grid,source.first,source.second) == false) || (is_unblocked(input_grid,target.first,target.second) == false))
        return;

    if(is_destination(source.first, source.second) == true)
        return;

    // Initializing all the cell information of all cell to default value

    for(i=0;i<rows;i++) {
        for(j=0;j<columns;j++) {
            cell_details[i][j].f = INT_MAX;
            cell_details[i][j].g = INT_MAX;
            cell_details[i][j].h = INT_MAX;
            cell_details[i][j].parent_i = -1;
            cell_details[i][j].parent_j = -1;
        }
    }

    i = source.first;
    j = source.second;

    cell_details[i][j].f = 0;
    cell_details[i][j].g = 0;
    cell_details[i][j].h = 0;
    cell_details[i][j].parent_i = i;
    cell_details[i][j].parent_j = j;

    open_list.insert(make_pair(0, make_pair(i,j)));

    // Running a loop until our set is not empty

    while(!open_list.empty()) {
        current_cell = *open_list.begin();
        open_list.erase(open_list.begin());

        i = current_cell.second.first;
        j = current_cell.second.second;

        closed_list[i][j] = true;  // marked as visited


        // Up move from current cell

        if(is_valid(i-1,j,rows,columns) == true) {   // checking if the move to a cell is valid/ cell is withing the grid/maze

            if(is_destination(i-1,j) == true) {    // checking if our current move to the cell is our goal/target or not
                cell_details[i-1][j].parent_i = i;
                cell_details[i-1][j].parent_j = j;
                find_path();
                found_target = true;
                return;
            }

            else if(closed_list[i-1][j] == false && is_unblocked(input_grid,i-1,j) == true) {  // checking if our move to a cell is unvisited
                g_value = cell_details[i][j].g + 1;                                            // and the cell is unblocked or not
                h_value = calculate_heuristic_value(i-1,j); // calculating heuristic value using Manhattan distance
                f_value = g_value + h_value;  // adding g cost and h cost

                if(cell_details[i-1][j].f == INT_MAX || cell_details[i-1][j].f > f_value) {  // check if our move to a cell, that is
                    open_list.insert(make_pair(f_value, make_pair(i-1,j)));                  // or that cell has better/ less cost or not

                    cell_details[i-1][j].f = f_value;
                    cell_details[i-1][j].g = g_value;
                    cell_details[i-1][j].h = h_value;
                    cell_details[i-1][j].parent_i = i;
                    cell_details[i-1][j].parent_j = j;
                }
            }
        }

        // Down Move from current cell

        if(is_valid(i+1,j,rows,columns) == true) {

            if(is_destination(i+1,j) == true) {
                cell_details[i+1][j].parent_i = i;
                cell_details[i+1][j].parent_j = j;
                find_path();
                found_target = true;
                return;
            }

            else if(closed_list[i+1][j] == false && is_unblocked(input_grid,i+1,j) == true) {
                g_value = cell_details[i][j].g + 1;
                h_value = calculate_heuristic_value(i+1,j);
                f_value = g_value + h_value;

                if(cell_details[i+1][j].f == INT_MAX || cell_details[i+1][j].f > f_value) {
                    open_list.insert(make_pair(f_value, make_pair(i+1,j)));

                    cell_details[i+1][j].f = f_value;
                    cell_details[i+1][j].g = g_value;
                    cell_details[i+1][j].h = h_value;
                    cell_details[i+1][j].parent_i = i;
                    cell_details[i+1][j].parent_j = j;
                }
            }
        }

        // Left Move from current cell

        if(is_valid(i,j-1,rows,columns) == true) {

            if(is_destination(i,j-1) == true) {
                cell_details[i][j-1].parent_i = i;
                cell_details[i][j-1].parent_j = j;
                find_path();
                found_target = true;
                return;
            }

            else if(closed_list[i][j-1] == false && is_unblocked(input_grid,i,j-1) == true) {
                g_value = cell_details[i][j].g + 1;
                h_value = calculate_heuristic_value(i,j-1);
                f_value = g_value + h_value;

                if(cell_details[i][j-1].f == INT_MAX || cell_details[i][j-1].f > f_value) {
                    open_list.insert(make_pair(f_value, make_pair(i,j-1)));

                    cell_details[i][j-1].f = f_value;
                    cell_details[i][j-1].g = g_value;
                    cell_details[i][j-1].h = h_value;
                    cell_details[i][j-1].parent_i = i;
                    cell_details[i][j-1].parent_j = j;
                }
            }
        }

        // Right Move

        if(is_valid(i,j+1,rows,columns) == true) {

            if(is_destination(i,j+1) == true) {
                cell_details[i][j+1].parent_i = i;
                cell_details[i][j+1].parent_j = j;
                find_path();
                found_target = true;
                return;
            }

            else if(closed_list[i][j+1] == false && is_unblocked(input_grid,i,j+1) == true) {
                g_value = cell_details[i][j].g + 1;
                h_value = calculate_heuristic_value(i,j+1);
                f_value = g_value + h_value;

                if(cell_details[i][j+1].f == INT_MAX || cell_details[i][j+1].f > f_value) {
                    open_list.insert(make_pair(f_value, make_pair(i,j+1)));

                    cell_details[i][j+1].f = f_value;
                    cell_details[i][j+1].g = g_value;
                    cell_details[i][j+1].h = h_value;
                    cell_details[i][j+1].parent_i = i;
                    cell_details[i][j+1].parent_j = j;
                }
            }
        }
    }
}

// Main function

int main() {
    int rows,columns,i,j;

    // Inputting row and column number

    cout<<"Enter row and column number (with a space between them): ";
    cin>>rows>>columns;

    // Declaring a 2D char vector to store the string input

    vector<vector<char>> input_grid(rows,vector<char>(columns));

    // Taking the string input in a 2D char vector

    for(i=0;i<rows;i++) {
        for(j=0;j<columns;j++) {
            cin>>input_grid[i][j];

            if (input_grid[i][j] == 's' || input_grid[i][j] == 'S') {  // if the current char is s we are storing the cell(coordinate) as source
                source.first = i;
                source.second = j;
            }
            if (input_grid[i][j] == 't' || input_grid[i][j] == 'T') { // if the current char is t we are storing the cell(coordinate) as target
                target.first = i;
                target.second = j;
            }
        }
    }

    a_star_search(input_grid,rows,columns);  // calling our main a_star_search function with inputted grid string and row,column number
}
