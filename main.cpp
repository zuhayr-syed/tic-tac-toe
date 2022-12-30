#include <iostream>
#include "def.cpp"
using namespace std;

int main() {

	while(1) {

		reset_states();
		
		introduction();
		in_progress();
		end_game();
		
		while(getchar() != '\n'); // clear buffer
		cout << "Press [ENTER] to restart the game... ";
		getchar();
		
		cout<<"\n";
		cout<<"---------------------------------------------------------"<<endl;
		cout<<"\n";
	}
	
	return 0;
}