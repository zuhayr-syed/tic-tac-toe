#include <iostream>
#include "def.cpp"
using namespace std;

int main() {
	introduction();
    player_setup();
	take_turn();
	end_game();

    // int n = 0;
    // cout << "Enter: " << endl;
    // cin >> n;
    // cout << "You Entered: " << n << endl;
	return 0;
}