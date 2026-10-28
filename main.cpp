/*
 * Jaiden Benway
 * Section 1
 * Assignment 9
 * 4/3/26
*/
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<cstdlib>
using namespace std;
// Declaration of the square class
class square{
    private:
	int move;
	string message;
	char symbol;
	int coin;
    public:
	square();
	void print();
	int action();
	void set(int,char,int, string);
};
// Function Prototypes
void print_board(square[], int, int);
void read_board(square[]);
void check_position(int &);
// Global variables
const int board_length = 20;
void print_intro(){
    cout << "This is off-brand Mario Kart. Make it to the finish line before your opponent.\n";
    cout << "HOWEVER, you must have more coins than your opponent when the game ends to actually win.\n";
    cout << "Reaching the finish line first gives you bonus coins.\n";
    cout << "There are also power-ups AND debuffs on the board. If you land on them, they will activate.\n";
    cout << "3\n2\n1\nGO!!!\n";
}
int current_player = 1;
int player1_score = 0, player2_score = 0;

int main(){
    int roll;
    int player1_position = 0, player2_position = 0;
    print_intro();
    square the_board[board_length]; // declare an array of squares
    srand(time(NULL));
    read_board(the_board);
    print_board(the_board,player1_position,1);
    print_board(the_board,player2_position,2);
    do{
	cout<<"\n\n\nPlayer "<<current_player<<" type enter to roll.\n";
	cin.ignore();
	roll = 1 + (rand() % 5);
	cout << "Player "<<current_player<<" rolled a "<<roll<<".\n";
	if(current_player == 1){
	    player1_position += roll;
	    check_position(player1_position);
	    player1_position += the_board[player1_position].action();
	    check_position(player1_position);
	}
        else{
	    player2_position += roll;
	    check_position(player2_position);
	    player2_position += the_board[player2_position].action();
	    check_position(player2_position);
	}
	print_board(the_board,player1_position,1);
	print_board(the_board,player2_position,2);
	current_player = (current_player % 2 + 1);
    }while((player1_position<board_length-1) && (player2_position<board_length-1));
    current_player = (current_player % 2) + 1;
//----------coin stuff------------//
    cout << "Player " << current_player << " reached the goal first! +3 coins!!!";
    if(current_player == 1)
	player1_score += 3;
    else
	player2_score += 3;
    cout << "\nPlayer 1 has " << player1_score << " coins!";
    cout << "\nPlayer 2 has " << player2_score << " coins!";
    if(player1_score > player2_score){
        cout << "\nPlayer 1 Wins!!!\n";
    }
    if(player2_score > player1_score){
	cout << "\nPlayer 2 Wins!!!\n";
    }
    if(player1_score == player2_score){
	cout << "\nIts a tie...\n";
    }
    cin.ignore();
    return 0;
}

void read_board(square b[]){
    ifstream infile;
    infile.open("game.txt");
    int square_number, square_move, coin;
    string square_message;
    char square_symbol;
    while(!infile.eof()){
	infile >> square_number >> square_move >> square_symbol >> coin;
	getline(infile,square_message);
	if(square_number < board_length)
	    b[square_number].set(square_move, square_symbol, coin, square_message);
    }
}

void print_board(square b[], int player_position, int player_number){
    for (int i = 0; i < board_length; i++) {
        // Print player if on this square
        if (i == player_position)
            cout << player_number;
        else
            b[i].print();
        // Print separator unless it’s the last square
        if (i < board_length - 1)
            cout << '|';
    }
    cout << "Goal\n";
}

void check_position(int &p){
    if(p < 0)
	p = 0;
    if(p >= board_length)
	p = board_length-1;
}
// Functions of the class square
square::square(){
    symbol = ' ';
    move = 0;
    coin = 0;
    message = "";
}

int square::action(){
    cout << message << endl;

    if(current_player == 1) {
        player1_score += coin;
    } else {
        player2_score += coin;
    }

    return move;
}

void square::print() {
    if(symbol == ' ')
        cout << '-';
    else
        cout << symbol;

}

void square::set(int m, char s, int c, string a_message) {
    move = m;
    symbol = s;
    message = a_message;
    coin = c;
}

