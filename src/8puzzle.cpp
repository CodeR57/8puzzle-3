#include <iostream>
#include <vector>
#include<queue>
#include <math.h>
#include <algorithm>

using namespace std;

//Matrix that holds a problem, goal state, g(n) and h(n)
struct Matrix{
    vector < vector <int> > problem;
    vector < vector <int> > goal;
    int gn;
    int hn;
};

//sorts things in the right order for the priority queue
class Compare_Values    {
    public: 
        bool operator()(Matrix& M1, Matrix& M2){
            return(M1.hn + M1.gn > M2.hn + M2.gn);
        }
};

//keeps track of how many nodes are expanded 
int total_nodes = 0;

//A* Mattahatan Search Function
//calculates the hn value
void mat(Matrix& M){
    M.hn = 0;
    for(int i = 0; i < 3; i++){
        for(int j=0; j<3; j++){
            int val = M.problem[i][j];
            if(val != 0){
                int goal_row = (val - 1) / 3;
                int goal_column = (val - 1) % 3;
                M.hn = M.hn + abs(i - goal_row) + abs(j - goal_column);
            }
        }
    }
}


//A* Misplaced Tile function
//calculates the misplaced tile hn value
void misplaced_tile(Matrix& M){
    M.hn = 0;
    if(M.problem[0][0] != 1) M.hn++;
    if(M.problem[0][1] != 2) M.hn++;
    if(M.problem[0][2] != 3) M.hn++;
    if(M.problem[1][0] != 4) M.hn++;
    if(M.problem[1][1] != 5) M.hn++;
    if(M.problem[1][2] != 6) M.hn++;
    if(M.problem[2][0] != 7) M.hn++;
    if(M.problem[2][1] != 8) M.hn++;
    if(M.problem[2][2] != 0) M.hn++;
}

//OPERATORS: i and j are row and column values you want to move blank to
//moves blank up
Matrix UP(Matrix& M, int i, int j, int choice){
    swap(M.problem[i][j], M.problem[i+1][j]);
    //increment g(n)
    M.gn= M.gn + 1;
    //find h(n)
    if(choice == 1)
        M.hn = 0;
    if(choice == 2)
        misplaced_tile(M);
    if(choice == 3)
        mat(M);
    total_nodes++;
    return M;
}

//moves blank down
Matrix DN(Matrix& M, int i, int j, int choice){
    swap(M.problem[i][j],M.problem[i-1][j]);
    M.gn = M.gn+1;
    if(choice == 1)
        M.hn = 0;
    if(choice == 2)
        misplaced_tile(M);
    if(choice == 3)
        mat(M);
    total_nodes++;
    return M;
}

//moves blank right
Matrix RT(Matrix& M, int i, int j, int choice){
    swap(M.problem[i][j], M.problem[i][j-1]);
    M.gn = M.gn+1;
    if(choice == 1)
        M.hn = 0;
    if(choice == 2)
        misplaced_tile(M);
    if(choice == 3)
        mat(M);
    total_nodes++;
    return M;
}

//moves blank left
Matrix LF(Matrix& M, int i, int j, int choice){
    swap(M.problem[i][j], M.problem[i][j+1]);
    M.gn = M.gn+1;
    if(choice == 1)
        M.hn = 0;
    if(choice == 2)
        misplaced_tile(M);
    if(choice == 3)
        mat(M);
    total_nodes++;
    return M;
}

//function to expand nodes with operators (current node, operators)
//returns queue of matricies (all possible ways to move the blank)
void expand(Matrix M, priority_queue<Matrix, vector<Matrix>, Compare_Values> &nodes, int choice){

    Matrix M1; 
    M1.problem.push_back(std::vector<int>(3, 1));
    M1.problem.push_back(std::vector<int>(3, 2));
    M1.problem.push_back(std::vector<int>(3, 3));

    Matrix M2;
    M2.problem.push_back(std::vector<int>(3, 1));
    M2.problem.push_back(std::vector<int>(3, 2));
    M2.problem.push_back(std::vector<int>(3, 3));

    Matrix M3;
    M3.problem.push_back(std::vector<int>(3, 1));
    M3.problem.push_back(std::vector<int>(3, 2));
    M3.problem.push_back(std::vector<int>(3, 3));

    Matrix M4;
    M4.problem.push_back(std::vector<int>(3, 1));
    M4.problem.push_back(std::vector<int>(3, 2));
    M4.problem.push_back(std::vector<int>(3, 3));


    //make 4 copies of matrix M that we can store in the queue
    M1 = M;

    M2 = M;

    M3 = M;

    M4 = M; 

    //find which indicies the blank is at
    int row,column;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(M.problem[i][j] == 0){
                row = i;
                column = j;
                break;
            }
        }
    }

    //for each indicie that the blank is at, swap with the values it can swap with
    //blank in right top corner
    if(column == 2 && row == 0){
        nodes.push(LF(M1,row, column-1, choice));
        nodes.push(DN(M2,row+1,column, choice));
    }
    //blank in right middle
    else if(column == 2 && row == 1){
        nodes.push(UP(M1,row-1,column, choice));
        nodes.push(LF(M2, row, column-1, choice));
        nodes.push(DN(M3, row+1, column, choice));
    }
    //blank in right bottom corner
    else if(column ==2 && row ==2){
        nodes.push(UP(M1, row-1, column, choice));
        nodes.push(LF(M2, row, column -1,choice));
    }
    //blank in top left corner
    else if(column == 0 && row == 0){
        nodes.push(RT(M1,row, column+1,choice));
        nodes.push(DN(M2,row+1,column, choice));
    }
    //blank in left middle
    else if(column == 0 && row == 1){
        nodes.push(UP(M1,row-1,column,choice));
        nodes.push(RT(M2, row, column+1, choice));
        nodes.push(DN(M3, row+1, column, choice));
    }
    //blank in left bottom corner
    else if(column ==0 && row ==2){
        nodes.push(UP(M1, row-1, column, choice));
        nodes.push(RT(M2, row, column+1, choice));
    }
    //blank in middle top
    else if(column == 1 && row == 0){
        nodes.push(LF(M1,row, column-1, choice));
        nodes.push(DN(M2,row+1,column, choice));
        nodes.push(RT(M3, row, column+1, choice));
    }
    //blank in center of board
    else if(column == 1 && row == 1){
        nodes.push(UP(M1,row-1,column, choice));
        nodes.push(LF(M2, row, column-1, choice));
        nodes.push(DN(M3, row+1, column, choice));
        nodes.push(RT(M4, row, column+1, choice));
    }
    //blank in center bottom
    else if(column ==1 && row ==2){
        nodes.push(UP(M1, row-1, column, choice));
        nodes.push(LF(M2, row, column -1, choice));
        nodes.push(RT(M3, row, column + 1, choice));
    }

} 

//function to check if the matrix matches the goal state
bool checkIfGoal(vector < vector<int> >  M);

//general search function to use with search algorithms
void generalSearch(Matrix M, int choice){
    //find out which algorithm they will use and calculate h(n)
    if(choice == 1)
        M.hn = 0;
    else if(choice == 2)
        misplaced_tile(M);
    else if(choice == 3)
        mat(M);

    //create a priortiy queue of matrices
    priority_queue <Matrix, vector<Matrix>, Compare_Values> nodes;
    //push our problem into the queue
    nodes.push(M);

    cout << "Expanding state: " << endl;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j)
            cout << nodes.top().problem[i][j] << "\t" ;
        cout<<endl;
    }
    cout << endl;



    //to calculate the maximum nodes in the queue
    int max_queue=0;
    //if the queue isn't empty when we find the goal state, this exits the loop
    int notEmpty = 0; 
    do{    
        //check if the problem is unsolveable
        if(nodes.empty()){
            cout <<  "Failure. There is no solution to this problem." << endl;
            break;
        }

        //create a node to check with the value of our problem
        Matrix node;
        node.problem.push_back(std::vector<int>(3, 1));
        node.problem.push_back(std::vector<int>(3, 2));
        node.problem.push_back(std::vector<int>(3, 3));

        node.goal.push_back(std::vector<int>(3, 1));
        node.goal.push_back(std::vector<int>(3, 2));
        node.goal.push_back(std::vector<int>(3, 3));

        //make node become the best value in the queue
        node = nodes.top();
        //pop our node out of the queue
        nodes.pop();

        //check if our goal was found
        if(checkIfGoal(node.problem)){
            cout << "Goal node reached!" << endl;
            cout << endl << endl;
            cout << "To solve this problem, the algorithm expanded a total of " << total_nodes << "  nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time was " << max_queue << "." << endl;
            cout << "Depth of goal node was " << node.gn << "." << endl;
            //set not empty to one in case our queue isnt empty
            notEmpty = 1;
            return;
        }

        //expand the node's children and push them in the queue with expand
        expand(node,nodes,choice);
        //find the current size of the queue
        int curr_queue = nodes.size();
        //update maximum
        max_queue = max(max_queue, curr_queue);
        //expand the state that is in the top of the queue
        cout << "The best state to expand with a g(n)=" << nodes.top().gn << " and h(n)=" << nodes.top().hn << " is..." << endl;
        for(int f = 0; f < 3; ++f){
            for(int e = 0; e < 3; ++e)
                cout << nodes.top().problem[f][e] << "\t" ;
            cout<<endl;
        }
        cout << endl;



    }while(!nodes.empty() && !notEmpty);
    return;

}

int main(){

    Matrix M;
    //make goal matrix to visualize
    M.goal.push_back(std::vector<int>(3, 1));
    M.goal.push_back(std::vector<int>(3, 2));
    M.goal.push_back(std::vector<int>(3, 3));

    //create M's goal state
    M.goal[0][0]=1;
    M.goal[0][1]=2;
    M.goal[0][2]=3;
    M.goal[1][0]=4;
    M.goal[1][1]=5;
    M.goal[1][2]=6;
    M.goal[2][0]=7;
    M.goal[2][1]=8;
    M.goal[2][2]=0;

    M.gn = 0;

    //make matrix for 8puzzle
    M.problem.push_back(std::vector<int>(3, 1));
    M.problem.push_back(std::vector<int>(3, 2));
    M.problem.push_back(std::vector<int>(3, 3));

    cout << "Welcome to Lauren Boyd's 8 Tile Puzzle Solver!" << endl;
    int problem = 0;
    cout << "Type 1 to use a default puzzle, or 2 to enter your own puzzle: ";
    cin >> problem;
    cout << endl;



    if(problem == 1){
        M.problem[0][0]=1;
        M.problem[0][1]=2;
        M.problem[0][2]=3;
        M.problem[1][0]=4;
        M.problem[1][1]=0;
        M.problem[1][2]=6;
        M.problem[2][0]=7;
        M.problem[2][1]=5;
        M.problem[2][2]=8;
    }
    else if(problem == 2){
        int one, two, three, four, five, six, seven, eight, nine;
        cout << "\tEnter your puzzle (use a 0 to represent the blank):" << endl;
        cout << "\tEnter the first row (use a space or tab to separate numbers):\t";
        cin >> one >> two >> three;
        cout << "\tEnter the second row (use a space or tab to separate numbers):\t";
        cin >> four >> five >> six;
        cout << "\tEnter the thrid row (use a space or tab to separate numbers):\t";
        cin >> seven >> eight >> nine;

        M.problem[0][0]=one;
        M.problem[0][1]=two;
        M.problem[0][2]=three;
        M.problem[1][0]=four;
        M.problem[1][1]=five;
        M.problem[1][2]=six;
        M.problem[2][0]=seven;
        M.problem[2][1]=eight;
        M.problem[2][2]=nine;
    }


    //user inputs their choice of algorithm
    int choice = 0;
    cout << "\tEnter your choice of algorithm:" << endl;
    cout << "\t1. Uniform Cost Search" << endl;
    cout << "\t2. A* with the Misplaced Tile Heuristic" << endl;
    cout << "\t3. A* with the Manhattan Distance Heuristic" << endl << "\t";
    cin >> choice;
    cout << endl;
    
    if(choice < 1 || choice > 3){
        cout << "Enter a number 1,2, or 3: ";
        cin >> choice;
        cout << endl;
    }

    //run general search on the problem and choice of algorithm
    generalSearch(M, choice);

    return 0;
}

bool checkIfGoal(vector <vector<int> > M)
{
    if(M[0][0] ==1 && M[0][1] ==2 && M[0][2] ==3 && M[1][0] ==4 && M[1][1] == 5 && M[1][2] == 6 && M[2][0] == 7 && M[2][1] == 8 && M[2][2] == 0) 
        return true;
    return false;
}
