#ifndef SLOT_H
#define SLOT_H
#include<iostream>
#define   _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
class Player;


class Slot
{
public:
	Slot(int slotNumber);  // initialization of slot number.
	virtual ~Slot()=0{};
	virtual bool play(Player* p) = 0;
	virtual std::string get_name() const = 0;
protected:
	int m_SlotNumber;

};

class Asset : public Slot
{
public:
	Asset(std::string city = "", std::string assetName = "", int slotNumber = 1);
	Asset(const Asset& rhs);
	bool play(Player* p); // TODO: implement this function.
	void SetOwner(std::string owner);
	std::string get_name() const;
	void SetPlayerPointer(Player* playerPointer);
	Player* GetPlayerPointer() const;
	int GetHomePrice() const;
	int GetRentalPayment() const;
	std::string GetOwner() const;
	std::string GetCity() const;
	std::string GetAssetName() const;
	Asset& operator=(const Asset& rhs);
private:
	std::string m_city;
	std::string m_assetName;
	int m_housePrice;
	int m_rentalPayment;
	std::string m_owner;
	Player* m_playerPointer;
};

class Go : public Slot
{
public:
	Go(std::string text, int slotNumber);
	bool play(Player* p) { return true; }
	std::string get_name() const;

private:
	std::string m_goText;
};

class Jail : public Slot
{
public:
	Jail(std::string jail, int slotNumber);
	std::string get_name() const;
	bool play(Player* p);
private:
	std::string m_jailText;
};

class Chance : public Slot
{
public:
	Chance(std::string text, int gift,int slotNumber);
	std::string get_name() const;
	bool play(Player* p);

private:
	std::string m_chanceText;
	int m_gift;

};




#endif

