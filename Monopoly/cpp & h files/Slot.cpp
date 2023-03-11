#include"Slot.h"
#include"Board.h"
#define MAX_RANGE 150
#define MIN_RANGE 50
int Random(int start, int end);

Slot::Slot(int slotNumber)
{
	m_SlotNumber = slotNumber;
}

Asset::Asset(std::string city, std::string assetName,int slotNumber) : Slot(slotNumber)
{
	m_housePrice = Random(MIN_RANGE, MAX_RANGE);  // Random value in range 50 - 150
	m_rentalPayment = Random(MIN_RANGE, MAX_RANGE);
	m_city = city;
	m_assetName = assetName;
	m_owner = ""; // No owner in the beginnig of the game
	m_playerPointer = nullptr;
}

Asset::Asset(const Asset& rhs) : Slot(rhs.m_SlotNumber)
{
	this->m_assetName = rhs.m_assetName;    
	this->m_city = rhs.m_city;
	this->m_housePrice = rhs.m_housePrice;
	this->m_owner = rhs.m_owner;
	this->m_rentalPayment = rhs.m_rentalPayment;
	this->m_playerPointer = rhs.m_playerPointer;
}


Asset& Asset::operator=(const Asset& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	this->m_assetName = rhs.m_assetName;
	this->m_city = rhs.m_city;
	this->m_housePrice = rhs.m_housePrice;
	this->m_owner = rhs.m_owner;
	this->m_rentalPayment = rhs.m_rentalPayment;
	this->m_playerPointer = rhs.m_playerPointer;
	return *this;
}

std::string Asset::get_name() const
{
	return std::to_string(m_SlotNumber) + ( ") " + m_city + " " + m_assetName);
}

int Asset::GetHomePrice() const
{
	return m_housePrice;
}

int Asset::GetRentalPayment() const
{
	return m_rentalPayment;
}

std::string Asset::GetOwner() const
{
	return m_owner;
}

void Asset::SetOwner(std::string owner)
{
	m_owner = owner;
}

void Asset::SetPlayerPointer(Player* playerPointer)
{
	m_playerPointer = playerPointer;
}

Player* Asset::GetPlayerPointer() const
{
	return m_playerPointer;
}

std::string Asset::GetCity() const
{
	return m_city;
}

std::string Asset::GetAssetName() const
{
	return m_assetName;
}


bool Asset::play(Player* p) // Input: pointer to player , Output: return true if the player has enough money
{															   // return false if the player has no enough money
	std::string answer;
	if (this->GetOwner() != "") // The asset is not vacant
	{
		if (this->GetOwner() != p->GetPlayerName()) // Check if the asset belong to this player
		{ // The player has to pay rent  
			std::cout << p->GetPlayerName() << " ,you have to pay " << this->GetRentalPayment() << " to " << this->GetOwner() << std::endl;
			if (p->pay_rent(this->GetRentalPayment()))
			{
				p->SetBalance(-(this->GetRentalPayment())); // Decrease the rental payment from blance of this player
				this->GetPlayerPointer()->SetBalance(this->GetRentalPayment()); // Rental payment to owner of this asset
				return true;  // The player has enough money to pay the rent
			}
			return false; // The player has not enough money and assets 
		}
		std::cout << this->GetAssetName() << " in " << this->GetCity() << " already belongs to you!!! " << std::endl;
		return true;  // The asset belong to this player
	}
	else // The asset is vacant
	{
		std::cout << p->GetPlayerName();
		std::cout << " ,Do you want to buy " << this->m_assetName << " in " << this->m_city << " for " << this->m_housePrice << " NIS?" << std::endl;
		std::cout << "If yes ,press (1) " << std::endl;
		std::cout << "If no ,press any other key " << std::endl;
		std::cin >> answer;
		if (answer == "1")
		{
			return p->add_asset(this);
		}
		else 
		{
			std::cout << p->GetPlayerName();
			std::cout << " ,you refused to buy a new asset..." << std::endl;
			return true;
		}
	}
}

Go::Go(std::string text, int slotNumber) : Slot(slotNumber)
{
	m_goText = text;
}

std::string Go::get_name() const
{
	return std::to_string(m_SlotNumber) + ") Go!";
}

Jail::Jail(std::string jail, int slotNumber) :Slot(slotNumber)
{
	m_jailText = jail;
}

std::string Jail::get_name() const
{
	return std::to_string(m_SlotNumber) + ") jail";
}

bool Jail::play(Player* p)
{
	std::cout << m_jailText << std::endl;
	p->SetJailStatus(true);
	return true;
}

Chance::Chance(std::string text, int gift,int slotNumber) : Slot(slotNumber)
{
	m_chanceText = text;
	m_gift = gift;
}

std::string Chance::get_name() const
{
	return std::to_string(m_SlotNumber) + ") Chance";
}

bool Chance::play(Player* p)
{
	std::cout << m_chanceText + " " + std::to_string((m_gift < 0) ? -(m_gift) : m_gift) + " NIS" << std::endl;
	p->SetBalance(m_gift);
	if (p->GetBalance() < 0)
	{
		return false; // No money to the player
	}
	return true;
}
