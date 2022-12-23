#include <iostream>
#include "dec.h"
using namespace std;

void introduction() {
    cout<<"\n";
    cout<<"   *****************\n";
    cout<<"      Tic-Tac-Toe\n";
    cout<<"   *****************\n";
    cout<<"\n";

    cout<<"Press [Enter] to begin: ";
	getchar(); // to pause screen  
	cout<<"\n";
    cout<<"\n";
	
    cout<<"Player 1 --> You: X\n";
    cout<<"Player 2 --> Computer: O\n";
    cout<<"\n";
    
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

void player_setup() {
    
}

void take_turn() {
    
}

void end_game() {
    
}