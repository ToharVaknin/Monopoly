#include <string>
#include <iostream>
#include"Board.h"
#define   _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
class Player;
void ExecuteMonopoly();

int main()
{
	ExecuteMonopoly(); 
	std::cout << "Leaks: " << _CrtDumpMemoryLeaks() << std::endl;
	return 0;
}

void ExecuteMonopoly()
{
	Board monopoly;
	std::cout << monopoly;
	Player players[2] = { Player("Player-1",&monopoly, 350),Player("Player-2",&monopoly, 350) };
	int numberOfPlayers = sizeof(players) / sizeof(Player);
	monopoly.SetNumberOfPlayers(numberOfPlayers);
	monopoly.play(players);
}

int Random(int start, int end)  // Receive range and return random number in this range.
{
	const int num = start + (rand() % ((end + 1) - start));
	return num;
}




