#include "Board.h"
#include "Slot.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

string center(int width, const string& str) {
	int len = str.length();
	if (width < len) { return str; }
	int diff = width - len;
	int pad1 = diff / 2;
	int pad2 = diff - pad1;
	return string(pad1, ' ') + str + string(pad2, ' ');
}

void draw_edge_line(int width, const string* line)
{
	cout << "|" << string((width) * 5 + 4, '-') << "|" << endl;
	cout << "|" << string((width) * 5 + 4, ' ') << "|" << endl;
	cout << "|";
	for (int col = 0; col < 5; col++)
		cout << center(width, line[col]) << "|";
	cout << endl;
	cout << "|" << string((width) * 5 + 4, ' ') << "|" << endl;
	cout << "|" << string((width) * 5 + 4, '-') << "|" << endl;
}

void draw_inner_line(int width, const string* line, bool last)
{
	cout << "|" << string(width * 5 + 4, ' ') << "|" << endl;
	cout << "|" << center(width, line[0]) << "|";
	cout << string(width * 3 + 2, ' ') << "|";
	cout << center(width, line[4]) << "|" << endl;
	cout << "|" << string(width * 5 + 4, ' ') << "|" << endl;
	if (!last)
	{
		cout << "|" << string(width, '-') << "|" << string((width * 3 + 3), ' ');
		cout << string(width, '-') << "|" << endl;
	}
}


std::ostream& operator<<(std::ostream& os, const Board& b)
{
	draw_edge_line(b.m_slot_width, b.m_board_image[0]);
	for (int row = 1; row < 5; row++)
		draw_inner_line(b.m_slot_width, b.m_board_image[row], row == 4);
	draw_edge_line(b.m_slot_width, b.m_board_image[5]);
	return os;
}

void Board::init_board_image()
{
	m_board_image[0][0] = m_arr[9]->get_name();
	m_board_image[0][1] = m_arr[10]->get_name();
	m_board_image[0][2] = m_arr[11]->get_name();
	m_board_image[0][3] = m_arr[12]->get_name();
	m_board_image[0][4] = m_arr[13]->get_name();
	m_board_image[1][0] = m_arr[8]->get_name();
	m_board_image[1][1] = "";
	m_board_image[1][2] = "";
	m_board_image[1][3] = "";
	m_board_image[1][4] = m_arr[14]->get_name();
	m_board_image[2][0] = m_arr[7]->get_name();
	m_board_image[2][1] = "";
	m_board_image[2][2] = "";
	m_board_image[2][3] = "";
	m_board_image[2][4] = m_arr[15]->get_name();
	m_board_image[3][0] = m_arr[6]->get_name();
	m_board_image[3][1] = "";
	m_board_image[3][2] = "";
	m_board_image[3][3] = "";
	m_board_image[3][4] = m_arr[16]->get_name();
	m_board_image[4][0] = m_arr[5]->get_name();
	m_board_image[4][1] = "";
	m_board_image[4][2] = "";
	m_board_image[4][3] = "";
	m_board_image[4][4] = m_arr[17]->get_name();
	m_board_image[5][0] = m_arr[4]->get_name();
	m_board_image[5][1] = m_arr[3]->get_name();
	m_board_image[5][2] = m_arr[2]->get_name();
	m_board_image[5][3] = m_arr[1]->get_name();
	m_board_image[5][4] = m_arr[0]->get_name();

	m_slot_width = 0;
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 5; col++)
			if (m_board_image[row][col].size() > m_slot_width)
				m_slot_width = m_board_image[row][col].size();
	}
	m_slot_width += 2;
}


Board::Board()
{
	srand(time(NULL));
	m_numberOfPlayers = 0;
	m_index = 0;
	m_size = 0;
	m_arr = nullptr;
	m_arr = new Slot * [18];  
	add_go_slot("GO!", m_index+1);
	m_index++; // 1
	add_asset_slot("Jerusalem", "zoo", m_index+1);
	m_index++;  // 2
	add_asset_slot("Jerusalem", "David_tower", m_index + 1);
	m_index++;  // 3
	add_asset_slot("Jerusalem", "Western_wall", m_index + 1);
	m_index++;  // 4
	add_jail_slot("JAIL! Wait 1 turn", m_index + 1);
	m_index++;  // 5
	add_asset_slot("Tel_Aviv", "Hilton", m_index + 1);
	m_index++; // 6
	int num = rand() % 1000 + 500;
	add_chance_slot("You won the lottery", num, m_index + 1);
	m_index++; // 7
	add_asset_slot("Tel_Aviv", "Azrieli", m_index + 1);
	m_index++; // 8
	add_asset_slot("Tel_Aviv", "Habima", m_index + 1);
	m_index++; // 9 
	num = rand() % 200 + 100;
	add_chance_slot("You have to pay the IRS", -num, m_index + 1);
	m_index++; // 10
	add_asset_slot("Carmiel", "Rocks_park", m_index + 1);
	m_index++; // 11
	num = rand() % 70 + 30;
	add_chance_slot("Congratulations to your birthday, get a bouquet", num, m_index + 1);
	m_index++; // 12
	add_asset_slot("Carmiel", "Big", m_index + 1);
	m_index++; // 13
	add_asset_slot("Carmiel", "Ort_Braude", m_index + 1);
	m_index++; // 14
	add_asset_slot("Eilat", "Dolpin_reef", m_index + 1);
	m_index++;  // 15
	add_asset_slot("Eilat", "Kings_town", m_index + 1);
	m_index++;  // 16
	add_asset_slot("Eilat", "Ramon_airport", m_index + 1);
	m_index++; // 17
	add_asset_slot("Eilat", "Almog_beach", m_index + 1);
	init_board_image();
}

Board::~Board()
{
	if (m_arr != nullptr)
	{
		for (int i = 0; i < 18; i++)
		{
			delete m_arr[i];
		}
		delete[] m_arr;
	}
}

void Board::add_go_slot(std::string goText, int slotNumber)
{
	m_arr[m_index] =  new Go(goText, slotNumber);
}

void Board::add_asset_slot(std::string city, std::string asset, int slotNumber)
{
	m_arr[m_index] = new Asset(city, asset, slotNumber);
}

void Board::add_jail_slot(std::string jailText, int slotNumber)
{
	m_arr[m_index] = new Jail(jailText, slotNumber);
}

void Board::add_chance_slot(std::string chanceText, int gift, int slotNumber)
{
	m_arr[m_index] = new Chance(chanceText, gift, slotNumber);
}
 
int Board::GetSlotNumber() const 
{
	return m_index + 1; // The slot number in range 1-18 and index in range 0-17
}

int Board::size() const
{
	return m_size;
}

Slot* Board::operator[](int idx) const
{
	try
	{
		return m_arr[idx];
		throw std::invalid_argument("Out of range index for m_arr");
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what() << std::endl;
		exit;
	}
}

Slot* Board::GetBoardAccess(int index) const
{
	return m_arr[index];
}

int Board::GetNumberOfPlayers() const
{
	return m_numberOfPlayers;
}

void Board::SetNumberOfPlayers(int size)
{
	m_numberOfPlayers = size;
}

void Board::play(Player* players)
{
	char answer;
	int playerIndex = 0;
	bool defaultFlag = false; // For case that the input of the player is invalid (not belong one of the options) or the palyer asked to print the game board.
	while (true)
	{
		std::cout << players[playerIndex].GetPlayerName() + "'s turn: " << std::endl;
		std::cout << "To continue press (1)" << std::endl;
		std::cout << "To print game board press (2)" << std::endl;
		std::cout << "To print your balance press (3)" << std::endl;
		std::cout << "To print your asset press (4)" << std::endl;
		std::cout << "To end game press (5)" << std::endl;
		std::cin >> answer;
		switch (answer)
		{
		case PLAY:
			if (!players[playerIndex].draw_dice())
			{
				std::cout << players[playerIndex].GetPlayerName() << " ,you have not enough money to pay the rent! " << std::endl;
				std::cout << players[playerIndex].GetPlayerName() << " lose the game" << std::endl;
				std::cout << "Game over !!!" << std::endl;
				return;
			}
			defaultFlag = false;
			break;
		case PRINT_BOARD:
			std::cout << *(players->GetBoardPointer());
			defaultFlag = true; // If the player asked to print the game board, his turn saved and not pass to other player.
			break;
		case PRINT_BALANCE:
			std::cout << "Your balance: " << players[playerIndex].GetBalance() << " NIS" << std::endl;
			defaultFlag = true;
			break;
		case PRINT_ASSETS:
			if (players[playerIndex].GetListOfPlayerAsset().GetSize() == 0)
			{
				std::cout << "no assets..." << std::endl;
			}
			else
			{
				std::cout << "Your asset: " << std::endl;
				players[playerIndex].GetListOfPlayerAsset().PrintQueue();
			}
			defaultFlag = true;
			break;
		case END_GAME:
			std::cout << players[playerIndex].GetPlayerName();
			std::cout << " retired from the game.." << std::endl;
			std::cout << "Game over !" << std::endl;
			return;
		default:
			std::cout << "Invalid input , Please select one of the options above ..." << std::endl;
			defaultFlag = true;
			break;
		}
		if (!defaultFlag)
		{
			players[playerIndex].PrintPlayerStatus(); // Print the status of the player
			playerIndex = (playerIndex + 1) % m_numberOfPlayers;
			std::cout << std::endl;
		}
	}
}

