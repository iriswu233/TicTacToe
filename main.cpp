//
//  main.cpp
//  Tic-Tac-Toe
//
//  Created by XINYI WU on 2022/8/2.
//

//  This program is for one human player to play with the AI, human player will begin first as player 1.

//  After my testing, the AI can make the best desicions and win or tie most of the times.
//  However, if player 1 inputs 3,8,9 and 6, the AI will lose.
//  I think this is because my AI doesn't take the possibility of opponent winning in each position into consideration.
//  The only thing it does to prevent opponent from winning is stopping the opponent if they are one move away from a win.
//  Besides this, I am very satisfied with my AI
//  Hope you will like it too.

#include <iostream>

using namespace std;

char grid[9] = {'1', '2','3','4','5','6','7','8','9'};

//lines stores 8 combinaton of winning
//the fourth element stores the state of the winning line
//0 represents no X or O on this line
//1 represents there are X on this line but no O
//2 represents there are O on this line but no X
//-1 represents both X and O are on this line

int lines[8][4] = {{1,2,3,0},{4,5,6,0},{7,8,9,0},{1,4,7,0},{2,5,8,0},{3,6,9,0},{1,5,9,0},{3,5,7,0}};

//possibilities stores the possibility of winning on each position, it is recalculated each turn.
int possibilities[9] = {3,2,3,2,4,2,3,2,3};


//block() checks if opponent is one move away from a win.
int block(){
    for(int i=0; i<8; i++){
        if(lines[i][3] == 1){
            int Xs = 0;
            int pos = -1;
            for(int j=0; j<3; j++){
                if(grid[lines[i][j]-1] == 'X'){
                    Xs++;
                }else{
                    pos =lines[i][j];
                }
            }
            
            if(Xs == 2){
                return pos;
            }
        }
    }
    
    return -1;
}

//calculating the possibilities
//if the whole line containing the position is avaliable(no X on the line), add 1
//if there is a O or two Os on the line containing the position, add the number of Os
//if the position has been occupied, then the possibility will be -1

int count_possibilities(){
    for(int i=0; i<9; i++){
        if(possibilities[i] > -1){
            possibilities[i] = 0;
        }
    }
    
    for(int i=0; i< 8; i++){
        if(lines[i][3] == 0){
            for(int j=0; j<3; j++){
                possibilities[lines[i][j]-1]++;
            }
        }else if(lines[i][3] == 2){
            int Os = 0;
            for(int j=0; j<3; j++){
                if(grid[lines[i][j]-1] == 'O'){
                    Os++;
                }
            }
            
            //AI is one move from win, directly do the move
            if(Os == 2){
                for(int j=0; j<3; j++){
                    if(grid[lines[i][j]-1] != 'O'){
                        return lines[i][j];
                    }
                }
            }
            
            for(int j=0; j<3; j++){
                if(possibilities[lines[i][j]-1] > -1){
                    possibilities[lines[i][j]-1] = possibilities[lines[i][j]-1] + Os;
                }
            }
        }
    }
    
    return -1;
}

void print_grid(){
    cout << grid[0] << ' ' << grid[1] << ' ' << grid[2] <<endl;
    cout << grid[3] << ' ' << grid[4] << ' ' << grid[5] <<endl;
    cout << grid[6] << ' ' << grid[7] << ' ' << grid[8] <<endl;
}

//turning the state of a position into integer.
int is_filled(char ch){
    if(ch == 'X'){
        return 1;
    }else if(ch == 'O'){
        return 2;
    }else{
        return 0;
    }
}

//checks if input is valid
bool valid(int num){
    if(cin.fail()){
        return false;
    }
    
    if(num <1 || num >9){
        return false;
    }
    
    if(is_filled(grid[num-1]) != 0){
        return false;
    }
    
    return true;
}

//checks if the grid is all filled
bool all_filled(){
    for(int i =0; i<9; i++){
        if(possibilities[i] != -1){
            return false;
        }
    }
    
    return true;
}

//checks if any of the lines has been filled by the same character
int win(){
    if(is_filled(grid[0])){
        if((grid[0] == grid[3] && grid[0] == grid[6]) || (grid[0] == grid[1] && grid[0] == grid[2]) || (grid[0] == grid[4] && grid[0] == grid[8])){
            return is_filled(grid[0]);
        }
    }
    
    if(is_filled(grid[1])){
        if(grid[1] == grid[4] && grid[1] == grid[7]){
            return is_filled(grid[1]);
        }
    }
    
    if(is_filled(grid[2])){
        if((grid[2] == grid[4] && grid[2] == grid[6]) || (grid[2] == grid[5] && grid[2] == grid[8])){
            return is_filled(grid[2]);
        }
    }
    
    if(is_filled(grid[3])){
        if(grid[3] == grid[4] && grid[3] == grid[5]){
            return is_filled(grid[3]);
        }
    }
    
    if(is_filled(grid[6])){
        if(grid[6] == grid[7] && grid[6] == grid[8]){
            return is_filled(grid[6]);
        }
    }
    
    return 0;
}

//resturns the game result
int end_game(){
    if(win() != 0){
        return win();   //one player wins
    }else if(all_filled()){
        return 0;       //tie
    }
    
    return -1;      //the game is not end yet
}

int main(int argc, const char * argv[]) {
    
    bool player_1 = true;       //stores whose turn it is
    
    while(end_game() == -1){
        
        print_grid();
        
        if(player_1){
            int num;
            cout << "player 1 please enter the number of an empty cell: ";
            cin >> num;
            while(!valid((num))){
                cout << "please enter a valid number: ";
                cin.clear();
                cin.ignore(256,'\n');
                cin >> num;
            }
            
            //changing grid, possibilities and next turn will be the AI
            grid[num-1] = 'X';
            possibilities[num-1] = -1;
            player_1 = false;
            
            //changing the states of lines affected by player 1's choice
            for(int i=0; i<8 ;i++){
                for(int j=0; j<3; j++){
                    if(lines[i][j] == num){
                        if(lines[i][3] == 0){
                            lines[i][3] = 1;
                        }else if(lines[i][3] == 2){
                            lines[i][3] = -1;
                        }
                    }
                }
            }
            
        }else{
            //AI's turn
            
            int pos;
            
            if(count_possibilities() > -1){     //checks if one move from win
                pos =count_possibilities();
            }else if(block() > -1){         //checks if the opponent is one move from win
                pos =block();
            }else{
                
                //the game will not end in one or two moves
                //choose the position with highest possibility
                
                count_possibilities();
                
                int max = possibilities[4];
                pos = 4;
                
                for(int i=0; i<9; i++){
                    if(possibilities[i] >max){
                        max = possibilities[i];
                        pos = i;
                    }
                }
                pos++;
            }
            
            //changing grid, possibilities and next turn will be player 1
            grid[pos-1] = 'O';
            possibilities[pos-1] = -1;
            player_1 = true;
            
            //changing the states of lines affected by AI's choice
            for(int i=0; i<8 ;i++){
                for(int j=0; j<3; j++){
                    if(lines[i][j] == pos){
                        if(lines[i][3] == 0){
                            lines[i][3] = 2;
                        }else if(lines[i][3] == 1){
                            lines[i][3] = -1;
                        }
                    }
                }
            }
            
            cout << "the computer chooses number " << pos << endl;
        }
    }
    
    //game ends, output the result
    print_grid();
    if(end_game() == 1){
        cout << "player 1 wins." << endl;
    }else if(end_game() == 2){
        cout << "the computer wins." << endl;
    }else if(end_game() == 0){
        cout << "no one wins." << endl;
    }
    
    return 0;
}
