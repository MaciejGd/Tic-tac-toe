#include<vector>
#include<iostream>

/*class Board{
    //vector representing game field
    char player = 'O';
    char computer = 'X';

public:
    std::vector<std::vector<char>> board = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    bool still_playing = true; 
    bool is_won = false;
    

};*/

struct CompMove{
    int row;
    int col;
};

//functions

void print_board(std::vector<std::vector<char>> board);
void player_coordinates(std::vector<std::vector<char>> &board);
bool playing_still(std::vector<std::vector<char>> board);
int evaluate(std::vector<std::vector<char>> board);
int minimax(std::vector<std::vector<char>> board, int depth, bool isMax);
void find_best(std::vector<std::vector<char>> &board);