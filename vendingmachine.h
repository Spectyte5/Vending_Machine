#pragma once
#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

bool is_numeric(const std::string& str);

class Products {

public:
	int id;
	int ammount;
	bool ressuply;
	int prize;

	Products(int id, int ammount, bool ressuply, int prize);
};

void read_stock(std::vector <Products>& vec); 
void print_stock(std::vector <Products>& vec); 

class Coins {
public:
	int coin;
	int money;

	Coins(int coin, int money);
};

void read_money(std::vector <Coins>& vec2); 

void print_money(std::vector <Coins>& vec2); 

void start_machine(std::vector <Products>& vec, std::vector <Coins>& vec2);

#endif // !VENDINGMACHINE_H
