#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#define   _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
class Asset;
class Board;

class Queue
{
public:
	Queue(int maxCapcity = 13);
	~Queue();
	void Push(Asset& newAsset);
	void Pop();
	bool IsEmpty();
	bool IsFull();
	int HousePriceOfFrontAsset(); // Return pointer to first asset in the list if exsit
	int GetSize() const;
	void PrintQueue() const;
private:
	Asset* m_arr;
	int m_head;
	int m_tail;
	int m_maxCapasity;
	int m_size;
};


class Player 
{
public:
	Player(std::string playerName = "", Board* boardPtr = nullptr, int Balance = 0);
	void SetPlayerNumber(int playerNumber);
	void SetPlayerName(std::string playerName);
	void SetBalance(int Balance);
	void SetJailStatus(bool insideJail);
	void SetBoardPosition(int dice);
	void SetBoardPointer(Board* boardPtr);
	void AddAssetToAssetList(Asset& newAsset);  // push to Queue
	void RemoveAssetFromAssetsList();  //  Pop from Queue
	bool GetJailStatus() const;
	int GetPlayerNumber() const;
	std::string GetPlayerName() const;
	int GetBalance() const;
	Board* GetBoardPointer() const;
	int GetBoardPosition() const;
	const Queue& GetListOfPlayerAsset() const;
	int GetSizeOfPlayerAssetsList() const;
	bool add_asset(Asset* a);
	bool pay_rent(int amount);
	bool draw_dice();
	void PrintPlayerStatus();
private:
	int m_playerNumber;
	std::string m_playerName;
	int m_Balance;
	bool m_insideJail;
	int m_BoardPosition; // The slot index
	Board* m_boardPtr; // Each player can play only one game in his turn
	Queue m_listOfPlayerAssets;
};




#endif

