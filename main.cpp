#include<iostream>
#include"tic.hpp"



int main(){
    
    std::vector<std::vector<char>> board = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    bool free_fields = true;
    bool is_won = false;
    print_board(board);

    while(!is_won && free_fields){
        
        std::cout<<"\n";
        player_coordinates(board);
        print_board(board);
        std::cout<<"\n";
        find_best(board);
        print_board(board);
        
        if(!playing_still(board)){
            std::cout<<"There is no free fields :OO, game over!";
            free_fields = false;
        }

        switch(evaluate(board)){
            case 10:
                std::cout<<"Unfortunately you lost :((";
                is_won = true;
                break;
            case -10:
                std::cout<<"Congratulations, you won!!!";
                is_won = true;
                break;
            default:
                is_won = false;
        }
        std::cout<<"\n";
    }
    return 0;
}