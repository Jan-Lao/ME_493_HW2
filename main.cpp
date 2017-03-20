//
//  main.cpp
//  GridWorld Homework 2 Draft 2
//
//  Created by Jan Lao on 2/26/17.
//  Copyright © 2016 University Nevada, Reno. All rights reserved.
//

#include <iostream>
#include <assert.h>

using namespace std;

/////================== Class: Agent ========================
class Agent{
public:
    void set_state(int s);
    void get_action(); // POLICY 2 CHANGE
    int state;
    int prevstate;
    int action; // POLICY 2 CHANGE
};

/////--------------- Agent Functions -------------------------
//// Set state function
void Agent::set_state(int s){
    state = s;
}

/////============== Class: GridWorld =========================
class GridWorld {
public:
    void calc_agentstate();
    int get_action(); //POLICY 2 CHANGE
    void start(); //Start program -> Run parameters
    int TestA();
    int TestB(); //The Run Function
    int TestC();
    
    int state;
    int prevstate;
    int action; //POLICY 2 CHANGE
    int choice; //POLICY 2 CHANGE
    int answer;
    int answer_; //To perform Test A
    int x_dim;
    int y_dim;
    int body_x;
    int body_y;
    int target_x;
    int target_y;
    Agent* p1;
};

/////------------ Gridworld functions -----------------------
//// Calc_agentstate() function
void GridWorld::calc_agentstate(){
    prevstate = state;
    state = body_x + body_y * x_dim; //Calculates each cell, which is indexed numerically
    p1->set_state(state);
}

//// Start() Function
void GridWorld::start(){
    x_dim = 4;
    y_dim = 4;
    body_x = 0;
    body_y = 0;
    target_x = 2;
    target_y = 3;
}

//// Get_action() function (POLICY 2 CHANGE)
int GridWorld::get_action(){
    // Some form of directional adjustment toward the goal. Look for less distance.
    if(target_x - body_x > 0){
        // If say distance from target to body is a positive number than move to the right
        action = 4; // Go Right
    }
    if(target_x - body_x < 0) {
        action = 1; // Go Left
    }
    if(target_y - body_y > 0){
        action = 3; // Go Up
    }
    if(target_y - body_y < 0){
        action = 2; // Go down
    }
    //else if(target_x - body_x == 0 && target_y - body_y == 0){
    //cout << "Congratulations, the agent is at the goal.\n";
    //}
    return action;
}

//// TestB() Function
int GridWorld::TestB(){
    start();
    calc_agentstate();
    cin >> answer;
    while(body_x != target_x || body_y != target_y){ //while loop
        int moves = 0;
        while(body_x != target_x || body_y != target_y){
            int z = 0;
            cout << "============================================================" << endl;
            if (answer == 5){
                cout << endl << "Test B: Human Controlled" << endl;
                cout << "-------------------------------------------------" << endl;
                cout << "Direction keys: 1 (left), 2 (down), 3 (up), or 4 (right)\n";
                cout << "For debug sake: the Goal is at (x,y)= (" << target_x << "," << target_y << ")" << endl;
                cout << "   Before Choice: X-Location: ((" << body_x << "))    " << "Y_Location: ((" << body_y << "))" << endl << endl;
                cin >> choice; // POLICY 1
            }
            else if (answer == 6){
                TestC();
            }
            
            /// Actual Movement
            if (choice == 1 ){
                body_x--;
            }
            if (choice == 2){
                body_y--;
            }
            if (choice == 3){
                body_y++;
            }
            if (choice == 4){
                body_x++;
            }
            if (choice != 1 && choice != 2 && choice != 3 && choice != 4){
                cout << "That is not a valid choice. Please enter 1, 2, 3, or 4" << endl;
            }
            cout << "The choice made was: " << choice << endl << endl;
            
            /// Boundary Teleportation
            while(body_x<0){
                body_x++;
                cout << "   ...Test A: Agent/Human bounced back into GridWorld" << endl;
            }
            while(body_y<0){
                body_y++;
                cout << "   ...Test A: Agent/Human bounced back into GridWorld" << endl;
            }
            while(body_x > x_dim){
                body_x--;
                cout << "   ...Test A: Agent/Human bounced back into GridWorld" << endl;
            }
            while(body_y>y_dim){
                body_y--;
                cout << "   ...Test A: Agent/Human bounced back into GridWorld" << endl;
            }
            
            /// New restrictions: Walls in the way of the Goal and the Learner
            //Form a wall between A & G at (2,1), (2,2), and (2,3)
            //Reason: Heuristic makes it go right first and then up!
            while(body_y == 2 && body_x == 1){
                //int state1 = body_x + body_y * x_dim;
                body_y--; //bounce down
                //int state2 = body_x + body_y * x_dim;
                //if (choice == 3){ //goes up again into the wall
                    //assert(state2 = state1);
                //}
                cout << "...Agent hit the wall: It is bounced back to (1,1)" << endl;
            }
            while(body_y == 2 && body_x == 2){
                body_y--;
                cout << "...Agent hit the wall: It is bounced back to (1,2)" << endl;
            }
            while(body_y == 2 && body_x == 3){
                body_y--;
                cout << "...Agent hit the wall: It is bounced back to (1,3)" << endl;
            }
            
            while(body_x == 1 && body_y == 3){
                //int state1 = body_x + body_y * x_dim;
                body_x--; //bounce left
                
                if (moves == 1000){
                    z = 5;
                }
                cout << "...Agent hit the wall: It is bounced back to (0,3)" << endl;
            }
            
            while(body_x == 1 && body_y == 2){
                body_x--;
                cout << "...Agent hit the wall: It is bounced back to (0,2)" << endl;
            }
            
            calc_agentstate();
            moves++;
            cout << "   After Choice: X-Location: ((" << body_x << "))    " << "Y_Location: ((" << body_y << "))" << endl << endl;
            cout << "The Agent/Human has not yet met the Goal..." << endl << endl;
            assert(z != 5);
        }
        cout << "...THE AGENT/HUMAN HAS MET THE GOAL" << endl << endl;
        cout << "============================================================" << endl;
        cout << "The moves taken are: " << moves << endl << endl;
        cout << "============================================================" << endl;
    }
    return 2;
}

//// Test C Function
int GridWorld::TestC(){
    cout << endl << "Test C: Rule of Thumb" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "For debug sake: the Goal is at (x,y)= (" << target_x << "," << target_y << ")" << endl;
    cout << "   Before Choice: X-Location: ((" << body_x << "))    " << "Y_Location: ((" << body_y << "))" << endl << endl;
    get_action(); // POLICY 2 CHANGE
    choice = action;
    p1->action=action;
    cout << "The current action is: " << action << endl;
    return 3;
}

//// Test A Function
int GridWorld::TestA(){
    cout << "============================================================" << endl;
    cout << endl << "PERFORMING TEST A" << endl << endl;;
    start();
    
    /// PUTTING THE AGENT OUT OF BOUNDS
    body_x = -1;
    body_y = 0;
    
    cout << "The Agent is out of bounds...Coordinates are:  (" << body_x << "," << body_y << ")" << endl << endl;;
    
    cout << "Putting it back" << endl;
    /// Boundary Teleportation~~~Copied Straight from Test b
    while(body_x<0){
        body_x++;
        cout << "   ...Test A: Agent/Human bounced back into GridWorld" << endl;
    }
    while(body_y<0){
        body_y++;
        cout << "   ...Test A: Agent/Human bounced back into GridWorld" << endl;
    }
    while(body_x > x_dim){
        body_x--;
        cout << "   ...Test A: Agent/Human bounced back into GridWorld" << endl;
    }
    while(body_y>y_dim){
        body_y--;
        cout << "   ...Test A: Agent/Human bounced back into GridWorld" << endl;
    }
    cout << endl << "The Agent is back in the GridWorld...Coordinates are:  (" << body_x << "," << body_y << ")" << endl;
    
    return 1;
}

////==================== MAIN =============================================
int main(){
    cout << "Welcome to GridWorld, Human/Agent!" << endl;
    GridWorld grid;
    Agent agent;
    grid.p1 = &agent;
    
    cout << "Is this GridWorld run by a human (TEST B) or the agent (TEST C);" << endl;
    cout << "(ENTER 5 or 6)"<< endl;
    cout << "(5)---Human (TEST B);     (6)---Agent (TEST C);" << endl;
    cout << "============================================================" << endl;
    cout << "Ans: ";
    
    // Grid pointer a = agent pointer a. Inputting the agent to the grid
    assert(grid.TestB() == 2);
        //If assert fails the program will stop here
    cout << "GAME TERMINATED." << endl << endl << endl;
    
    // Seeing if the actual functions pull through and return the pre-assigned value
        //If assert succeeds, assert alert does not show.
    assert(grid.TestA() == 1);
    
    // Seeing if actual function in its piece will == the preassigned value
    cout << endl << endl <<"============================================================" << endl;
    cout << endl << "ASSERTING FOR TEST C" << endl;
    assert(grid.TestC() == 3);
    
    cout << endl << "GAME AND TESTS ARE COMPLETED ^.^ Thanks for playing!" << endl << endl;
    
    return 0;
}
