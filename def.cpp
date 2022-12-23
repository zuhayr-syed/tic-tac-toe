#include <iostream>
#include <cstdlib>
#include "dec.h"
using namespace std;

class Player {
    string name;
    string move;
    public:
        void set_name(string);
        void set_move(string);
        string get_name() {
            return name;
        }
        string get_move() {
            return move;
        }

};

void Player::set_name(string n) {
    name = n;
}
void Player::set_move(string m) {
    move = m;
}

Player player1;
Player player2;
int game_won = 0;
bool turn1 = true;
bool turn2 = false;
string board[9] = {" ", " ", " ", " ", " ", " ", " ", " ", " "};

void introduction() {
    cout<<"\n";
    cout<<"   *****************\n";
    cout<<"      Tic-Tac-Toe\n";
    cout<<"   *****************\n";
    cout<<"\n";

    string name;
    cout<<"Enter your name to begin: "<<endl;
	cin >> name;
    cout<<"\n";
    cout<<"\n";

    player_setup(name);
    
    cout<<"The grid is shown below:\n\n";
    
    show_grid();
}

void show_grid() {
    cout << "     |     |      \n";
    cout << "  1  |  2  |  3   \n";
    cout << "_____|_____|_____ \n";
    cout << "     |     |      \n";
    cout << "  4  |  5  |  6   \n";
    cout << "_____|_____|_____ \n";
    cout << "     |     |      \n";
    cout << "  7  |  8  |  9   \n";
    cout << "     |     |      \n\n";
    cout<<"\n";
}

void player_setup(string name) {
    srand((unsigned) time(0));
    int x = (rand() % 2) + 1;
    if(x == 1) {
        cout<<"Player 1: "<<name<<" --> X"<<endl;
        cout<<"Player 2: "<<"Computer --> O"<<endl;
        cout<<"\n";
        player1.set_name(name);
        player1.set_move("X");
        player2.set_name("Computer");
        player2.set_move("O");
    }
    else {
        cout<<"Player 1: "<<"Computer --> X"<<endl;
        cout<<"Player 2: "<<name<<" --> O"<<endl;
        cout<<"\n";
        player1.set_name("Computer");
        player1.set_move("X");
        player2.set_name(name);
        player2.set_move("O");
    }
}

void in_progress() {
    while(game_won == 0) { 
        cout<<"\n";
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"\n";
        if(turn1) {
            // player 1 turn
            take_turn(1);
            check_board(1);
            turn1 = false;
            turn2 = true;
        }
        else if (turn2) {
            // player 2 turn
            take_turn(2);
            check_board(2);
            turn2 = false;
            turn1 = true;
        }
    }
}

void take_turn(int player) {
    Player user;
    if(player == 1) {
        user = player1;
    }
    else if (player == 2) {
        user = player2;
    }
    
    cout<<"     TURN --> Player "<<player<<": "<<user.get_name()<< " ("<<user.get_move()<<")"<<endl;
    cout<<"\n";

    int pos = 0;
    
    if(user.get_name() != "Computer") {
        
        show_board();
        
        bool invalid = true;
        while(invalid) {
            cout<<"Pick a position: "<<endl;
            cin >> pos;
            
            if(pos == 1 || pos == 2 || pos == 3 || pos == 4 || pos == 5 || pos == 6 || pos == 7 || pos == 8 || pos == 9) {
                if(board[pos-1] == " ") {
                    invalid = false;
                    cout<<"\n";
                }
                else {
                    cout<<"Position already taken, try again"<<endl;
                    cout<<"\n";

                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            else {
                cout<<"Invalid entry, try again"<<endl;
                cout<<"\n";

                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        board[pos-1] = user.get_move();
    }
    else {
        // computer move
    }

    cout<<"\n";
    cout<<"\n";
}

void show_board()
{
  cout<<  "          |     |                                                  |     | \n";
  cout << "       " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "                                             1 |  2  | 3\n";
  cout << "     _____|_____|_____                                        _____|_____|_____\n";
  cout << "          |     |                                                  |     | \n";
  cout << "       " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "                                             4 |  5  | 6\n";
  cout << "     _____|_____|_____                                        _____|_____|_____\n";
  cout<<  "          |     |                                                  |     | \n";
  cout << "       " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "                                             7 |  8  | 9\n";
  cout << "          |     |                                                  |     | \n";
  cout << "\n";

}

void check_board(int player) {
    Player user;
    if(player == 1) {
        user = player1;
    }
    else if (player == 2) {
        user = player2;
    }
    
    cout<<"     CHECKING BOARD for: "<<user.get_move()<<endl;
    cout<<"\n";
}

void end_game() {
    
}