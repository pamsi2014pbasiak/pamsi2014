#pragma once

#define DEEP 2

class Game
{
bool _firstPlayer;
    int _fields[64]; // 0 - no move, 1 - player 1, 2 - player 2
public:
	bool _firstMove;
	Game();
	int getResult(); // check if someone won; 0 - game is running, 1,2 - one's player victory, 3 - draw
	bool makeMove(int fieldId); // true - movement was available; false - movement was forbidden
	void undoMove(int fieldId);
	void resetTable(); // reset state of table
	void drawTable(); // drawing table with values of fields
	int getPlayer();
	void getBestMoveValue(int & bestMove);

};

int minimax(Game & _game, int deep);