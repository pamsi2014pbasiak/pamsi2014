#include "Interface.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>

Interface::Interface()
{
}

void Interface::CPUmove(int lvl)
{
	if(lvl==0)
		return;
	else if(lvl==1)
	{
		while(!_game.makeMove(rand()%64));
	}
	else
	{
//miejsce na implementacje Twojego algorytmu
//przykladowy wybor ruchu:
		int bestMove;
		_game.getBestMoveValue(bestMove);
		if(bestMove<0){
			while(!_game.makeMove(rand()%64));
		}else
			_game.makeMove(bestMove);
	}
}

void Interface::startNewGame(int firstCPU, int secondCPU)
{
	_game.resetTable();
	_firstCPU = firstCPU;
	_secondCPU = secondCPU;
	while(_game.getResult() == 0)
	{
		printGameTable();
		std::cout << _game.getPlayer() << " player's turn";
		if((_game.getPlayer()==1) && (_firstCPU > 0))
		{
			CPUmove(_firstCPU);
		}
		else if((_game.getPlayer()==2) && (_secondCPU >0 ))
		{
			CPUmove(_secondCPU);
		}
		else // ruch gracza typu HUMAN
		{
			std::cout << std::endl;
			int level;
			unsigned char row, column;
			std::string lvl;
			std::cout << "choose level [1-4]: " << std::endl;
			std::cin >> lvl;
			level = atoi(lvl.c_str());
			if(level<1) level=1;
			if(level>4) level=1;
			std::cout << "choose row [q-r]: " << std::endl;
			std::cin >> row;
			std::cout << "choose column [a-f]: " << std::endl;
			std::cin >> column;
			int level1, level2;

			switch(row)
			{
			case 'q': level1 = 0;
				break;
			case 'w': level1 = 1;
				break;
			case 'e': level1 = 2;
				break;
			case 'r': level1 = 3;
				break;
			default: level1 = 0;
			}

			switch(column)
			{
			case 'a': level2 = 0;
				break;
			case 's': level2 = 1;
				break;
			case 'd': level2 = 2;
				break;
			case 'f': level2 = 3;
				break;
			default: level2 = 0;
			}

			if(!_game.makeMove((level-1)*16+level1*4+level2))
			{
				std::cout << "An impossible move! " << std::endl;
			}
		}
	}
	printGameTable();
	std::cout << "Play again? [y/n]" << std::endl;
	char n;
	std::cin >> n;
	if(n=='y') startNewGame(_firstCPU, _secondCPU);
	else std::cout << "Byebye! " << std::endl;
}

void Interface::printGameTable()
{
	_game.drawTable();
	std::cout << std::endl;	
	std::cout << "game status: ";
	switch(_game.getResult())
	{
	case 0: std::cout << "Game is running";
		break;
	case 1: std::cout << "1st player won!";
		break;
	case 2: std::cout << "2nd player won!";
		break;
	case 3: std::cout << "DRAW!";
	}	
	std::cout << std::endl;	
}