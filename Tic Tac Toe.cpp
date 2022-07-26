#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "windows.h"

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int randomNum(int low = 0, int high = 0) {
	if (low == 0 && high == 0) {
		return rand() % 101;
	}

	if (low != 0 && high == 0) {
		if (low > 100) {
			return (rand() % (low - 100 + 1)) + 100;
		} else {
			return (rand() % (100 - low + 1)) + low;
		}
	}

	return (rand() % (high - low + 1)) + low;
}

template <typename T>
T validateNum(std::string str = "")
{
	T x;
	while (!(std::cin >> x))
	{
		(str == "") ? std::cout << "Invalid input. Please try again: " : std::cout << str;
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}

	std::cin.clear();
	std::cin.ignore(100, '\n');

	return x;
}

void printGrid(char grid[][3], int size) {
	int i = 0, j = 0;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (j == size - 1) {
				if (grid[i][j] == 'X') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
				}
				else if (grid[i][j] == 'O') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				}
				cout << " " << grid[i][j];
				SetConsoleTextAttribute(hConsole, 15);
			} else {
				if (grid[i][j] == 'X') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
				}
				else if (grid[i][j] == 'O') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				}
				cout << " " << grid[i][j];
				SetConsoleTextAttribute(hConsole, 15);
				cout << " |";
			}
		}
		cout << endl;
		if (i < size - 1) {
			for (j = 0; j < size; j++) {
				(j == size - 1) ? cout << "---" << endl : cout << "--- ";
			}
		}
	}
}

bool checkWinner(char grid[][3], char mark[], int size, int turn){

	bool row1, row2, row3, col1, col2, col3, diagonal1, diagonal2;
	row1 = (grid[0][0] == mark[turn] && grid[0][1] == mark[turn] && grid[0][2] == mark[turn]);
	row2 = (grid[1][0] == mark[turn] && grid[1][1] == mark[turn] && grid[1][2] == mark[turn]);
	row3 = (grid[2][0] == mark[turn] && grid[2][1] == mark[turn] && grid[2][2] == mark[turn]);
	col1 = (grid[0][0] == mark[turn] && grid[1][0] == mark[turn] && grid[2][0] == mark[turn]);
	col2 = (grid[0][1] == mark[turn] && grid[1][1] == mark[turn] && grid[2][1] == mark[turn]);
	col3 = (grid[0][2] == mark[turn] && grid[1][2] == mark[turn] && grid[2][2] == mark[turn]);
	diagonal1 = (grid[0][0] == mark[turn] && grid[1][1] == mark[turn] && grid[2][2] == mark[turn]);
	diagonal2 = (grid[0][2] == mark[turn] && grid[1][1] == mark[turn] && grid[2][0] == mark[turn]);

	if (row1 || row2 || row3 || col1 || col2 || col3 || diagonal1 || diagonal2)	{
		return true;
	} else {
		return false;
	}
}

void game(char grid[][3], bool marked[], char mark[], int turn, bool autoplay = false) {
	int choice = 0, counter = 1;
	bool winner = false;

	do {
		system("CLS");
		cout << "Grid" << endl << endl;
		printGrid(grid, 3);
		if (autoplay and turn == 1) {
			do {
				choice = randomNum(1, 9);
			} while (marked[choice - 1] == true);
		} else { 
			cout << endl << "Player " << mark[turn] << ", make your choice: ";
			do {
				choice = validateNum<int>("Player " + to_string(mark[turn]) + ", make your choice: ");
				if (choice < 1 || choice > 9 || marked[choice - 1] == true) {
					cout << "Player " + to_string(mark[turn]) + ", make your choice: ";
				}
			} while (choice < 1 || choice > 9 || marked[choice - 1] == true);
		}

		marked[choice - 1] = true;

		if (choice == 1) grid[0][0] = mark[turn];
		else if (choice == 2) grid[0][1] = mark[turn];
		else if (choice == 3) grid[0][2] = mark[turn];
		else if (choice == 4) grid[1][0] = mark[turn];
		else if (choice == 5) grid[1][1] = mark[turn];
		else if (choice == 6) grid[1][2] = mark[turn];
		else if (choice == 7) grid[2][0] = mark[turn];
		else if (choice == 8) grid[2][1] = mark[turn];
		else if (choice == 9) grid[2][2] = mark[turn];
		winner = checkWinner(grid, mark, 3, turn);
		if (counter == 9 && winner == false) {
			cout << "Game has ended in draw." << endl;
			break;
		}else if (winner == false) {
			(turn == 0) ? turn = 1 : turn = 0;
			counter++;
		} else {
			system("CLS");
			cout << "Current grid state" << endl << endl;
			printGrid(grid, 3);
			cout << endl <<"Winner is: Player " << mark[turn] << "!" << endl;
		}

	} while (winner == false);
}
int main() {
	SetConsoleTextAttribute(hConsole, 15);
	//Variables
	srand(time(NULL));
	int input = 0, i = 0, j = 0, player_turn = 0;
	char grid[][3]{ {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
	char mark[]{ 'X', 'O' };
	bool autoplay = false;
	bool marked[]{ false, false, false, false, false, false, false, false, false };

	do {
		//Beginning
		cout << "== Tic Tac Toe ==" << endl << endl;
		cout << "1. Start a game (2 players)" << endl;
		cout << "2. Start a game (computer)" << endl;
		cout << "3. Manual" << endl;
		cout << "4. Exit" << endl << endl;
		cout << "Input: ";

		input = validateNum<int>("Input: ");

		if (input == 1) {//Start the 2 player game
			game(grid, marked, mark, player_turn);
		}
		else if (input == 2) { //Start the game against the computer
			autoplay = true;
			game(grid, marked, mark, player_turn, autoplay);
		}
		else if (input == 3) { //Read the manual
			system("CLS");
			cout << " == How to play ==" << endl;
			cout << "Fill in the grid by inputting corresponding numbers that refer to each mark on the grid." << endl << endl;
			printGrid(grid, 3);
			cout << endl << "The goal is to fill 3 marks in a row.\nFirst player to do so wins." << endl << endl;

			do {
				cout << "Input 0 to return to the main menu: ";
				input = validateNum<int>("Input 0 to return to the main menu: ");

			} while (input != 0);

			system("CLS");
			continue;
		}
		else if (input == 4) {
			break;
		}
		else system("CLS");
	} while (input < 1 || input > 4);

	system("pause");
	return 0;
}