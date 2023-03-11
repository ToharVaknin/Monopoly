#include<iostream>
#include"Player.h"
#include"Board.h"
#define MIN_RANGE_DICE 1
#define MAX_RANGE_DICE 6
#define NUMBER_OF_SLOTS 18
int Random(int start, int end);

Player::Player(std::string playerName, Board* boardPtr, int Balance) : m_listOfPlayerAssets(13)
{
	
	m_Balance = Balance; // initial balance to 350 IL
	m_boardPtr = boardPtr;
	m_playerName = playerName;
	m_insideJail = false;
	m_BoardPosition = 1;  // initial position on the board
}

void Player::SetPlayerNumber(int playerNumber)
{
	m_playerNumber = playerNumber;
}

void Player::SetPlayerName(std::string playerName)
{
	m_playerName = playerName;
}

void Player::SetBalance(int Balance)
{
	m_Balance += Balance;
}

void Player::SetJailStatus(bool insideJail)
{
	m_insideJail = insideJail;
}

void Player::SetBoardPosition(int dice)
{
	int positionAndDice = m_BoardPosition + dice;
	if (positionAndDice == NUMBER_OF_SLOTS) // For the range remain 1-18
	{
		m_BoardPosition = NUMBER_OF_SLOTS;  // The range of Slot number is 1-18 
	}
	else
	{
		m_BoardPosition = (positionAndDice % NUMBER_OF_SLOTS);
	}
}

void Player::SetBoardPointer(Board* boardPtr)
{
	m_boardPtr = boardPtr;
}

void Player::AddAssetToAssetList(Asset& newAsset) 
{
	newAsset.SetOwner(this->GetPlayerName()); // Set the owner of this asset to this player
	newAsset.SetPlayerPointer(this);  // Set the pointer of this asset to point to this player
	this->m_listOfPlayerAssets.Push(newAsset);  // Add asset to assets list of this player
}

void Player::RemoveAssetFromAssetsList() 
{
	m_listOfPlayerAssets.Pop();
}

int Player::GetPlayerNumber() const
{
	return m_playerNumber;
}

std::string Player::GetPlayerName() const
{
	return m_playerName;
}

int Player::GetBalance() const
{
	return m_Balance;
}

Board* Player::GetBoardPointer() const
{
	return m_boardPtr;
}

int Player::GetBoardPosition() const
{
	return m_BoardPosition;
}

const Queue& Player::GetListOfPlayerAsset() const
{
	return m_listOfPlayerAssets;
}

int Player::GetSizeOfPlayerAssetsList() const
{
	return m_listOfPlayerAssets.GetSize();
}

bool Player::GetJailStatus() const
{
	return m_insideJail;
}

bool Player::add_asset(Asset* a) //input: Recieve pointer to asset that the player can buy.
{                               // output: always return true because we dont want stop the game if player dont have enough money to buy asset.
	if (this->m_Balance > a->GetHomePrice())
	{
		this->SetBalance(-(a->GetHomePrice()));  // Update the balance of this player
		AddAssetToAssetList(*a);  
		std::cout << "Congratulations!, added to you new asset: " << a->GetAssetName() << " in " << a->GetCity() << std::endl;
		return true;
	}
	std::cout << "Sorry " << this->GetPlayerName() << " ,you don't have enough money to Purchase this asset..." << std::endl;
	return true;  // No enough money to this player
}

bool Player::pay_rent(int amount) // input: rental payment that the palyer need to pay to another player.
{                                 // output: true if player has enough money to pay the rent , falsre if player has no enough money to pay the rent.
	if (this->m_Balance > amount)
	{
		return true;   // The player has enough money to pay the rent
	}
	else // The player has not enough money to pay the rent
	{
		while (this->GetBalance() < amount) // sale assets until the player has enough money to pay the rent.
		{
			if (!m_listOfPlayerAssets.IsEmpty())
			{
				this->SetBalance(m_listOfPlayerAssets.HousePriceOfFrontAsset()); // Add the house price of this asset to the blance of this player
				this->RemoveAssetFromAssetsList();  // Sale of the asset
			}
			else
			{
				return false; // The player has not money and assets
			}
		}
		return true;  // The player has enough money after he sale assets
	}
}

bool Player::draw_dice()  // Each turn of each player we call to this function.
{                        // Output: true if all players have enough money , false if one of the players has no enough money.
	if (this->m_insideJail)
	{
		std::cout << this->GetPlayerName() << " in jail..." << std::endl;
		this->m_insideJail = false;
		return true; // The player in the jail
	}
	int preDDicePosition = this->m_BoardPosition;
	std::cout << "Your position in the board before dice throwing: " << this->m_BoardPosition << std::endl;
	int dice = Random(MIN_RANGE_DICE, MAX_RANGE_DICE);  //  Random value in range 1-6
	std::cout << this->m_playerName << " ,you move " << dice << " steps" << std::endl;
	this->SetBoardPosition(dice); // Promotion of the player
	std::cout << "Your position in the board after dice throwing: " << this->m_BoardPosition << std::endl;
	int posDicePosition = this->m_BoardPosition;
	if (posDicePosition < preDDicePosition)
	{
		this->SetBalance(350); // One round passed on the board
	}
	return this->GetBoardPointer()->GetBoardAccess(m_BoardPosition - 1)->play(this); // The index of array of Slot* in range: 0-17
                                                                                    // The index of board position in range : 1-18
}

void Player::PrintPlayerStatus() 
{
	std::cout << "The status of " << this->GetPlayerName() << ":" << std::endl;
	std::cout << "Balance: " << this->GetBalance() << " NIS" << std::endl;
	std::cout << "List of assets: " << std::endl;
	if (m_listOfPlayerAssets.GetSize() == 0)
	{
		std::cout << "no assets..." << std::endl;
	}
	else
	{
		m_listOfPlayerAssets.PrintQueue(); // Print all the assets of the player
	}
}

Queue::Queue(int maxCapcity)
{
	m_maxCapasity = maxCapcity;
	m_arr = new Asset[m_maxCapasity];
	m_head = -1;
	m_tail = 0;
	m_size = 0;
}

Queue::~Queue()
{
	if (m_arr != nullptr)
	{
		delete[] m_arr;
	}
}

void Queue::Push(Asset& newAsset)
{
	if (!IsFull())
	{
		if (m_size == 0)
		{
			m_head = m_tail;
		}
		m_size++;
		m_arr[m_tail] = newAsset;
		m_tail = (m_tail + 1) % m_maxCapasity;
	}
}

void Queue::Pop()
{
	if (!IsEmpty())
	{
		m_arr[m_head].SetOwner(""); // Asset release
		m_arr[m_head].SetPlayerPointer(nullptr); // Asset release
		m_size--;
		m_head = (m_head + 1) % m_maxCapasity;
		if (m_size == 0)
		{
			m_head = -1;
		}
	}
}

bool Queue::IsEmpty()
{
	return m_size == 0;
}

bool Queue::IsFull()
{
	return m_size == m_maxCapasity;
}

int Queue::HousePriceOfFrontAsset()
{
	if (!IsEmpty())
	{
		return m_arr[m_head].GetHomePrice();
	}
	return 0;
}

int Queue::GetSize() const // Number of player assets
{
	return m_size;
}

void Queue::PrintQueue() const // Print player assets
{ 
	int numberOfAsset = 1;
	for (int i = m_head; i < m_tail; i = (i + 1) % m_maxCapasity)
	{
		std::cout << std::to_string(numberOfAsset) + ") " << m_arr[i].GetAssetName() << " in " << m_arr[i].GetCity() << std::endl;
		numberOfAsset++;
	}
}




