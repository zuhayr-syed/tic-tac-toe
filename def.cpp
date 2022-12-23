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

void take_turn() {
    
}

void end_game() {
    
}