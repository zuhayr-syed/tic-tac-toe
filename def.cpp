#include <iostream>
#include <cstdlib>
#include "dec.h"
using namespace std;

class Score {
    int user_wins = 0;
    int computer_wins = 0;
    public:
        void set_computer(int);
        void set_user(int);
        int get_computer() {
            return computer_wins;
        }
        int get_user() {
            return user_wins;
        }
};
void Score::set_computer(int n) {
    computer_wins = n;
}
void Score::set_user(int m) {
    user_wins = m;
}

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
Score player_wins;
bool setup = true;

// game variables
int game_won = 0;
bool turn1 = true;
bool turn2 = false;
string board[9] = {" ", " ", " ", " ", " ", " ", " ", " ", " "};
bool computer_first = true;
int turn_count = 0;

void reset_states() {
    game_won = 0;
    turn1 = true;
    turn2 = false;
    for(int y=0; y<9; y++) {
        board[y] = " ";
    }
    computer_first = true;
    turn_count = 0;
}

void introduction() {
    cout<<"\n";
    cout<<"   *****************\n";
    cout<<"      Tic-Tac-Toe\n";
    cout<<"   *****************\n";
    cout<<"\n";

    string name;
    if(setup) {
        cout<<"Enter your name to begin: "<<endl;
        cin >> name;
        cout<<"\n";
    }
    else {
        if(player1.get_name() == "Computer") {
            name = player2.get_name();
        }
        else {
            name = player1.get_name();
        }
    }
    cout<<"\n";

    player_setup(name);
    
    cout<<"The grid is shown below:\n\n";
    
    show_grid();

    if(setup) {
        while(getchar() != '\n'); // clear buffer from '\n'
        setup = false;
    }
    cout << "Press [ENTER] to start the game... ";
    getchar();
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
    // random number [1,2]	
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
    
    turn_count += 1;
    cout<<"     TURN #"<<turn_count<<" --> Player "<<player<<": "<<user.get_name()<< " ("<<user.get_move()<<")"<<endl;
    cout<<"\n";

    int pos = 0;
    
    if(user.get_name() != "Computer") {
        // user move
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
        int computer_move = -1;

        // check for first computer move, if so place on random position
        if(computer_first) {
            int move = first_position();
            board[move] = user.get_move();
            computer_move = move;

            computer_first = false;
        }

        // check if computer can win and find the last position
        if(computer_move == -1) {
            int win_position = block_win(user.get_move());
            if(win_position != -1) {
                board[win_position] = user.get_move();
                computer_move = win_position;
            }
        }

        // check if user is about to win and block position
        if(computer_move == -1) {
            // get the users move string 
            string checks;
            if(player1.get_name() != "Computer") {
                checks = player1.get_move();
            }
            else {
                checks = player2.get_move();
            }

            int block = block_win(checks);
            if(block != -1) {
                board[block] = user.get_move();
                computer_move = block;
            }
        }

        // find position where computer already placed to setup a win (to create 2 in-a-row)
        // if there is no position, place randomly on board 
        if(computer_move == -1) {
            int move = second_pos(user.get_move());
            if(move != -1) {
                board[move] = user.get_move();
                computer_move = move;
            }
            else {
                int move = first_position();
                board[move] = user.get_move();
                computer_move = move;
            }
        }

        if(computer_move != -1) {
            cout<<"Computer placed on position: "<<computer_move + 1<<endl;
            cout<<"\n";
        }
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

    string move = user.get_move();
    if(board[0] == move && board[1] == move && board[2] == move) {
        game_won = player;
    }
    else if(board[0] == move && board[3] == move && board[6] == move) {
        game_won = player;
    }
    else if(board[0] == move && board[4] == move && board[8] == move) {
        game_won = player;
    }
    else if(board[1] == move && board[4] == move && board[7] == move) {
        game_won = player;
    }
    else if(board[2] == move && board[5] == move && board[8] == move) {
        game_won = player;
    }
    else if(board[2] == move && board[4] == move && board[6] == move) {
        game_won = player;
    }
    else if(board[3] == move && board[4] == move && board[5] == move) {
        game_won = player;
    }
    else if(board[6] == move && board[7] == move && board[8] == move) {
        game_won = player;
    }

    if(game_won == 0) {
        cout<<"No winner found"<<endl;
        cout<<"\n";
    }
    else {
        cout<<"Winner found!"<<endl;
        cout<<"\n";
    }

    // if board is full
    if(board[0] != " " && board[1] != " " && board[2] != " " && board[3] != " " && board[4] != " " && board[5] != " " &&
        board[6] != " " && board[7] != " " && board[8] != " ") {
        game_won = -1;
    }

}

void end_game() {
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"\n";

    Player user;
    if(game_won == 1) {
        user = player1;

        if(user.get_name() == "Computer") {
            cout<<"--- YOU LOST D: ---"<<endl;
        }
        else {
            cout<<"--- YOU WON :D ---"<<endl;
        }

        cout<<"Player "<<game_won<<": "<<user.get_name()<< " ("<<user.get_move()<<") WON THE GAME!"<<endl;
        cout<<"\n";
    }
    else if (game_won == 2) {
        user = player2;

        if(user.get_name() == "Computer") {
            cout<<"--- YOU LOST D: ---"<<endl;
        }
        else {
            cout<<"--- YOU WON :D ---"<<endl;
        }

        cout<<"Player "<<game_won<<": "<<user.get_name()<< " ("<<user.get_move()<<") WON THE GAME!"<<endl;
        cout<<"\n";
    }
    else {
        cout<<"No Players won: DRAW"<<endl;
        cout<<"\n";
    }

    show_board();

    cout<<"\n";
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"\n";
}

int first_position() {
    int x = -1;
    while(x == -1 || board[x - 1] != " ") {
	// random number [1,9]
        srand((unsigned) time(0));
        x = (rand() % 9) + 1;
    }
    return x - 1;
}

int second_pos(string type) {
    if(board[0] == type && board[1] == " " && board[2] == " ") {
        return 1;
    }
    else if(board[1] == type && board[0] == " " && board[2] == " ") {
        return 0;
    }
    else if(board[2] == type && board[1] == " " && board[2] == " ") {
        return 1;
    }

    else if(board[3] == type && board[4] == " " && board[5] == " ") {
        return 4;
    }
    else if(board[4] == type && board[3] == " " && board[5] == " ") {
        return 3;
    }
    else if(board[5] == type && board[3] == " " && board[4] == " ") {
        return 3;
    }

    else if(board[6] == type && board[7] == " " && board[8] == " ") {
        return 7;
    }
    else if(board[7] == type && board[6] == " " && board[8] == " ") {
        return 6;
    }
    else if(board[8] == type && board[6] == " " && board[7] == " ") {
        return 6;
    }

    else if(board[0] == type && board[3] == " " && board[6] == " ") {
        return 3;
    }
    else if(board[3] == type && board[0] == " " && board[6] == " ") {
        return 0;
    }
    else if(board[6] == type && board[0] == " " && board[3] == " ") {
        return 0;
    }

    else if(board[1] == type && board[4] == " " && board[7] == " ") {
        return 4;
    }
    else if(board[4] == type && board[1] == " " && board[7] == " ") {
        return 1;
    }
    else if(board[7] == type && board[1] == " " && board[4] == " ") {
        return 1;
    }

    else if(board[2] == type && board[5] == " " && board[8] == " ") {
        return 5;
    }
    else if(board[5] == type && board[2] == " " && board[8] == " ") {
        return 2;
    }
    else if(board[8] == type && board[2] == " " && board[5] == " ") {
        return 2;
    }

    else if(board[0] == type && board[4] == " " && board[8] == " ") {
        return 4;
    }
    else if(board[4] == type && board[0] == " " && board[8] == " ") {
        return 0;
    }
    else if(board[8] == type && board[0] == " " && board[4] == " ") {
        return 0;
    }

    else if(board[2] == type && board[4] == " " && board[6] == " ") {
        return 4;
    }    
    else if(board[4] == type && board[2] == " " && board[6] == " ") {
        return 2;
    }
    else if(board[6] == type && board[2] == " " && board[4] == " ") {
        return 2;
    }
    else {
        return -1;
    }
}

int block_win(string checks) {
    if(board[0] == checks && board[1] == checks && board[2] == " ") {
        return 2;
    }
    else if(board[1] == checks && board[2] == checks && board[0] == " ") {
        return 0;
    }
    else if(board[0] == checks && board[2] == checks && board[1] == " ") {
        return 1;
    }
    else if(board[3] == checks && board[4] == checks && board[5] == " ") {
        return 5;
    }
    else if(board[4] == checks && board[5] == checks && board[3] == " ") {
        return 3;
    }
    else if(board[3] == checks && board[5] == checks && board[4] == " ") {
        return 4;
    }
    else if(board[6] == checks && board[7] == checks && board[8] == " ") {
        return 8;
    }
    else if(board[7] == checks && board[8] == checks && board[6] == " ") {
        return 6;
    }
    else if(board[6] == checks && board[8] == checks && board[7] == " ") {
        return 7;
    }
    else if(board[0] == checks && board[3] == checks && board[6] == " ") {
        return 6;
    }
    else if(board[3] == checks && board[6] == checks && board[0] == " ") {
        return 0;
    }
    else if(board[0] == checks && board[6] == checks && board[3] == " ") {
        return 3;
    }
    else if(board[1] == checks && board[4] == checks && board[7] == " ") {
        return 7;
    }
    else if(board[4] == checks && board[7] == checks && board[1] == " ") {
        return 1;
    }
    else if(board[1] == checks && board[7] == checks && board[4] == " ") {
        return 4;
    }
    else if(board[2] == checks && board[5] == checks && board[8] == " ") {
        return 8;
    }
    else if(board[5] == checks && board[8] == checks && board[2] == " ") {
        return 2;
    }
    else if(board[2] == checks && board[8] == checks && board[5] == " ") {
        return 5;
    }
    else if(board[0] == checks && board[4] == checks && board[8] == " ") {
        return 8;
    }
    else if(board[4] == checks && board[8] == checks && board[0] == " ") {
        return 0;
    }
    else if(board[0] == checks && board[8] == checks && board[4] == " ") {
        return 4;
    }
    else if(board[2] == checks && board[4] == checks && board[6] == " ") {
        return 6;
    }    
    else if(board[4] == checks && board[6] == checks && board[2] == " ") {
        return 2;
    }
    else if(board[2] == checks && board[6] == checks && board[4] == " ") {
        return 4;
    }
    else {
        return -1;
    }
}
