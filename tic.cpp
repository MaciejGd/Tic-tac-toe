#include "tic.hpp"
#include <limits>

//printing game field
void print_board(std::vector<std::vector<char>> board){
    std::cout<<"  0 1 2\n";
    std::cout<<"0 "<<board[0][0]<<"|"<<board[0][1]<<"|"<<board[0][2]<<"\n";
    std::cout<<"  -+-+-\n";
    std::cout<<"1 "<<board[1][0]<<"|"<<board[1][1]<<"|"<<board[1][2]<<"\n";
    std::cout<<"  -+-+-\n";
    std::cout<<"2 "<<board[2][0]<<"|"<<board[2][1]<<"|"<<board[2][2]<<"\n"; 
}

//choosing fields for user
void player_coordinates(std::vector<std::vector<char>> &board){
    try{
        int x_coordinate = 0;
        int y_coordinate = 0;
        //input of x_coordinate value:
        std::cout<<"pass x coordinate: ";
        std::cin>>x_coordinate;
        //checking if input for x_coordinate is correct
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("Zla wspolrzedna, podaj liczbe");
        }
        
        //input of y_coordinate value:
        std::cout<<"pass y coordinate: ";
        std::cin>>y_coordinate;
        std::cout<<"\n";
        //checking if input for y_coordinate is correct:
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("Zla wspolrzedna, podaj liczbe");
        }

        //checking if coordinates are correct
        if(x_coordinate>=board.size() || y_coordinate>=board.size() || board[x_coordinate][y_coordinate]!=' '){
            std::cout<<"zla wspolrzedna sprobuj jeszcze raz\n";
            player_coordinates(board);
        }
        else{
            board[x_coordinate][y_coordinate] = 'O';
        }
    }
    catch(const std::exception& e){
        std::cerr<<e.what()<<std::endl;
    }    
}
//check if there are free fields
bool playing_still(std::vector<std::vector<char>> board){
    bool still_playing = false;
    for(int i = 0; i<board.size();i++){
        if(still_playing==true){
            break;
        }
        for(int j = 0; j<board[i].size();j++){
            if(board[i][j]==' '){
                still_playing = true;
                break;
            }
        }
    }
    return still_playing;
}

//3 functions to make a computer move (used minimax algorithm) also evaluate functions is used for checking if someone won.
int evaluate(std::vector<std::vector<char>> board){

    for(int i = 0; i<board.size();i++){
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2]){
            if(board[i][0]=='X'){
                return 10;
            }
            else if(board[i][0]=='O'){
                return -10;
            }
        }
    }

    for(int j = 0; j<board.size();j++){
        if(board[0][j]==board[1][j] && board[1][j]==board[2][j]){
            if(board[0][j]=='X'){
                return 10;
            }
            else if(board[0][j]=='O'){
                return -10;
            }
        }
    }

    if(board[0][0]==board[1][1] && board[1][1]==board[2][2]){
        if(board[0][0]=='X'){
            return 10;
        }
        else if(board[0][0]=='O'){
            return -10;
        }
    }

    if(board[0][2]==board[1][1] && board[1][1]==board[2][0]){
        if(board[2][0]=='X'){
            return 10;
        }
        else if(board[2][0]=='O'){
            return -10;
        }
    }

    return 0;
}

int minimax(std::vector<std::vector<char>> board, int depth, bool isMax){

    int score = evaluate(board);

    if(score == 10){
        return score;
    }
    else if(score == -10){
        return score;
    }

    if(!playing_still(board)){
        return 0;
    }

    if(isMax){
        int best = -1000;

        for(int i = 0; i<board.size(); i++){
            for(int j = 0; j<board.size(); j++){
                if(board[i][j]==' '){
                    board[i][j]='X';

                    best = std::max(best, minimax(board, depth+1, !isMax));
                    board[i][j]=' ';
                }
            }
        }
        return best;
    }
    else{
        int best = 1000;

        for(int i = 0; i<board.size(); i++){
            for(int j = 0; j<board.size(); j++){
                if(board[i][j]==' '){
                    board[i][j]='O';

                    best = std::min(best, minimax(board, depth+1, !isMax));
                    board[i][j]=' ';
                }
            }
        }
        return best;
    }
}

void find_best(std::vector<std::vector<char>> &board){
    
    int bestVal = -1000;
    CompMove best_move;
    best_move.row = -1;
    best_move.col = -1;

    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){

            if (board[i][j]==' ')
            {

                board[i][j] = 'X';

                int moveVal = minimax(board, 0, false);
  
                board[i][j] = ' ';
                
                if (moveVal > bestVal)
                {
                    best_move.row = i;
                    best_move.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[best_move.row][best_move.col] = 'X';
}
