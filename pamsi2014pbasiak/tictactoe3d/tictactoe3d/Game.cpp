#include "Game.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

Game::Game()
{
	for(int i=0;i<64;i++)
	{
		_fields[i] = 0;
		_firstMove = 0;
	}
	_firstPlayer = true;
}

void Game::getBestMoveValue(int & bestMove){
	int m, mm;
	int deep = 0;
	mm = 2;
	if(!_firstMove){
		_firstMove=1;
		bestMove = -1;
		return;
	}
	for(int i=0; i<64; i++){ // Petla przechodz¹ca przez wszystkie pola
		if(makeMove(i)){	// Je¿eli uda³o siê wykonaæ ruch...
			m = minimax(*this, deep);	// Wyznacz minimax
			undoMove(i);	// Cofnij zmiany
			if(m < mm){	// Je¿eli nowy minimax mniejszy od poprzedniego...
				mm = m;	// zapisz nowy
				bestMove = i;	// zaktualizuj najlepszy ruch
			} // IF (m > max)
		} // IF (pole puste)
	} // FOR 0-63
}

int minimax(Game & _game, int deep){
	int m, mm;
	if(_game.getResult()){
		if(_game.getResult() == 3)
			return 0;
		if(_game.getResult() == 1)
			return -1;
		return 1;
	}
	if(deep >= DEEP)
		return 0;
	if(_game.getPlayer() == 1)
		mm = 2;
	else
		mm = -2;
	for(int i=0; i<64; i++){ // Petla przechodz¹ca przez wszystkie pola
		if(_game.makeMove(i)){	// Je¿eli uda³o siê wykonaæ ruch...
			m = minimax(_game, deep+1);	// Wyznacz minimax
			_game.undoMove(i);	// Cofnij zmiany
			if(_game.getPlayer() == 1){
				if(m < mm){
					mm = m;
				}
			}
			else if(_game.getPlayer() == 2){
				if(m > mm){
					mm = m;
				}
			}				
		} // IF (pole puste)
	} // FOR 0-63
	return mm;
}

int Game::getPlayer()
{
	return _firstPlayer?1:2;
}

int Game::getResult()
{
	bool Player1won = false;
	bool Player2won = false;
	for(int j=0; j<4; j++)
	{
		for(int k=0; k<4; k++)
		{
			int id1=j*4+k;
			if(_fields[id1]==_fields[id1+4*4]&&
				_fields[id1]==_fields[id1+2*4*4]&&
				_fields[id1]==_fields[id1+3*4*4])
			{
				if(_fields[id1]==1) Player1won = true;
				if(_fields[id1]==2) Player2won = true;
			}
		}
	}
	for(int j=0; j<4; j++)
	{
		int id1 = 4*j;
		if(_fields[id1]==_fields[id1+1*(1+4*4)]&&
			_fields[id1]==_fields[id1+2*(1+4*4)]&&
			_fields[id1]==_fields[id1+3*(1+4*4)])
		{
			if(_fields[id1]==1) Player1won = true;
			if(_fields[id1]==2) Player2won = true;
		}
		id1 = 4*j+3;
		if(_fields[id1]==_fields[id1+1*(-1+4*4)]&&
			_fields[id1]==_fields[id1+2*(-1+4*4)]&&
			_fields[id1]==_fields[id1+3*(-1+4*4)])
		{
			if(_fields[id1]==1) Player1won = true;
			if(_fields[id1]==2) Player2won = true;
		}
	}
	for(int i=0; i<4; i++)
	{
		int id1 = i;
		if(_fields[id1]==_fields[id1+1*(4+4*4)]&&
			_fields[id1]==_fields[id1+2*(4+4*4)]&&
			_fields[id1]==_fields[id1+3*(4+4*4)])
		{
			if(_fields[id1]==1) Player1won = true;
			if(_fields[id1]==2) Player2won = true;
		}
		id1 = i+4*3;
		if(_fields[id1]==_fields[id1+1*(-4+4*4)]&&
			_fields[id1]==_fields[id1+2*(-4+4*4)]&&
			_fields[id1]==_fields[id1+3*(-4+4*4)])
		{
			if(_fields[id1]==1) Player1won = true;
			if(_fields[id1]==2) Player2won = true;
		}
	}
	int id1 = 0;
	if(_fields[id1]==_fields[id1+1*(1+4+4*4)]&&
		_fields[id1]==_fields[id1+2*(1+4+4*4)]&&
		_fields[id1]==_fields[id1+3*(1+4+4*4)])
	{
		if(_fields[id1]==1) Player1won = true;
		if(_fields[id1]==2) Player2won = true;
	}
	id1 = 4*3+3;
	if(_fields[id1]==_fields[id1+1*(-1-4+4*4)]&&
		_fields[id1]==_fields[id1+2*(-1-4+4*4)]&&
		_fields[id1]==_fields[id1+3*(-1-4+4*4)])
	{
		if(_fields[id1]==1) Player1won = true;
		if(_fields[id1]==2) Player2won = true;
	}
	id1 = 3;
	if(_fields[id1]==_fields[id1+1*(-1+4+4*4)]&&
		_fields[id1]==_fields[id1+2*(-1+4+4*4)]&&
		_fields[id1]==_fields[id1+3*(-1+4+4*4)])
	{
		if(_fields[id1]==1) Player1won = true;
		if(_fields[id1]==2) Player2won = true;
	}
	id1 = 4*3;
	if(_fields[id1]==_fields[id1+1*(1-4+4*4)]&&
		_fields[id1]==_fields[id1+2*(1-4+4*4)]&&
		_fields[id1]==_fields[id1+3*(1-4+4*4)])
	{
		if(_fields[id1]==1) Player1won = true;
		if(_fields[id1]==2) Player2won = true;
	}
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			int id1=i*4*4+j*4;
			if(_fields[id1]==_fields[id1+1]&&
				_fields[id1]==_fields[id1+2]&&
				_fields[id1]==_fields[id1+3])
			{
				if(_fields[id1]==1) Player1won = true;
				if(_fields[id1]==2) Player2won = true;
			}
		}
		for(int j=0; j<4; j++)
		{
			int id1=i*4*4+j;
			if(_fields[id1]==_fields[id1+4*1]&&
				_fields[id1]==_fields[id1+4*2]&&
				_fields[id1]==_fields[id1+4*3])
			{
				if(_fields[id1]==1) Player1won = true;
				if(_fields[id1]==2) Player2won = true;
			}
		}
		int id1=i*4*4;
		if(_fields[id1]==_fields[id1+5]&&
			_fields[id1]==_fields[id1+2*5]&&
			_fields[id1]==_fields[id1+3*5])
		{
			if(_fields[id1]==1) Player1won = true;
			if(_fields[id1]==2) Player2won = true;
		}
		id1=i*4*4+3;
		if(_fields[id1]==_fields[id1+3]&&
			_fields[id1]==_fields[id1+2*3]&&
			_fields[id1]==_fields[id1+3*3])
		{
			if(_fields[id1]==1) Player1won = true;
			if(_fields[id1]==2) Player2won = true;
		}
	}

	if(Player1won && Player2won)
		return 3;
	else if(Player1won)
		return 1;
	else if(Player2won)
		return 2;
	bool noFree = true;
	for(int i=0;i<64;i++)
	{
		if(_fields[i]==0)
		{
			noFree = false;
			break;
		}
	}
	if(noFree) return 3;
	return 0;
}

bool Game::makeMove(int fieldId)
{
	if(_fields[fieldId]!=0)
	{
		return false;
	}
	_fields[fieldId] = _firstPlayer?1:2;
	_firstPlayer = !_firstPlayer;
	return true;
}

void Game::undoMove(int fieldId)
{
	_fields[fieldId] = 0;
	_firstPlayer = !_firstPlayer;
}

void Game::resetTable()
{
	for(int i=0;i<64;i++)
	{
		_fields[i] = 0;
	}
	_firstPlayer = true;
}

void Game::drawTable()
{
	for(int i=0; i<4; i++)
	{
		std::cout << "Level = "<<(i+1)<<std::endl;
		std::cout << "\ta \ts \td \tf" << std::endl;
		for(int j=0; j<4; j++)
		{
			switch(j)
			{
			case 0: std::cout << "q\t";
				break;
			case 1: std::cout << "w\t";
				break;
			case 2: std::cout << "e\t";
				break;
			case 3: std::cout << "r\t";
				break;
			}
			for(int k=0; k<4; k++)
			{

				std::cout << _fields[i*4*4+j*4+k] << "\t";
			}
			std::cout << "\n";
		}
	}
}