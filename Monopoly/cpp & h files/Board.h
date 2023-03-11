#ifndef BOARD_H
#define BOARD_H
#include <string>
#include"Slot.h"
#include"Player.h"
#define   _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

class Board
{
public:
	enum action { END_GAME = '5', PLAY = '1', PRINT_BOARD = '2', PRINT_BALANCE = '3', PRINT_ASSETS = '4' };

private:
	int m_numberOfPlayers;
	int m_index;
	int m_size;
	Slot** m_arr;
	std::string m_board_image[6][5];
	int m_slot_width;
	void init_board_image();
	void add_go_slot(std::string goText , int slotNumber);
	void add_asset_slot(std::string city, std::string asset, int slotNumber);
	void add_jail_slot(std::string jailText, int slotNumber);
	void add_chance_slot(std::string chanceText, int gift, int slotNumber);
public:
	Board();
	~Board();
	int size() const;
	int GetNumberOfPlayers() const;
	void SetNumberOfPlayers(int size);
	int GetSlotNumber() const;
	Slot* GetBoardAccess(int index) const;
	Slot* operator[](int idx) const;
	void play(Player* players);
	friend std::ostream& operator<<(std::ostream& os, const Board& b);
};


#endif

