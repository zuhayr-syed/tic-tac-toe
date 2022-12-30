#ifndef TIC_TAC_TOE_DEC_H
#define TIC_TAC_TOE_DEC_H
using namespace std;

void reset_states();
void introduction();
void show_grid();
void player_setup(string name);
void in_progress();
void take_turn(int player);
int block_win(string checks);
int first_position();
int second_pos(string type);
void show_board();
void check_board(int player);
void end_game();

#endif