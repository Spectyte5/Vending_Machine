#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include "vendingmachine.h"

bool is_numeric(const std::string& str)
{
	auto iter = str.begin();
	while (iter != str.end() && std::isdigit(*iter))
	{
		iter++;
	}
	return (!str.empty() && iter == str.end());
}

Products::Products(int id, int ammount, bool ressuply, int prize) {
		this->id = id;
		this->ammount = ammount;
		this->ressuply = ressuply;
		this->prize = prize;
	}

void read_stock(std::vector <Products>& vec) {
	std::ifstream file("list.txt");
	std::string line;
	std::vector <std::string> table;
	std::ofstream temp("temp.txt");

	while (std::getline(file, line))
	{
		table.push_back(line);
		std::string id = line.substr(line.size() - 7, 1);
		std::string prod = line.substr(line.size() - 5, 1);
		std::string res = line.substr(line.size() - 3, 1);
		std::string prz = line.substr(line.size() - 1, 1);


		if (is_numeric(id)) {
			int a = std::stoi(id);
			int b = std::stoi(prod);
			int c = std::stoi(res);
			int d = std::stoi(prz);

			vec[a].ammount = b;
			vec[a].prize = d;
			if (c == 1) {
				vec[a].ammount = 10;
			}
		}
	}
	file.close();
}

void print_stock(std::vector <Products>& vec) {

	std::ofstream file("list.txt");
	std::cout << "Products avaible in the stock:" << "\n" << std::endl;

	for (int i = 0; i < vec.size(); i++) {

		if (vec[i].ammount == 0) {
			vec[i].ressuply = 1;
		}
		else {
			vec[i].ressuply = 0;
		}

		file << "Product: " << vec[i].id << " " << vec[i].ammount << " " << vec[i].ressuply << " " << vec[i].prize << std::endl;
		std::cout << "Product: " << vec[i].id << " In stock: " << vec[i].ammount << " Prize: " << vec[i].prize << " zł " << std::endl;
	}
	std::cout << "\n";
	file.close();
}


	Coins::Coins(int coin, int money) {
		this->coin = coin;
		this->money = money;
	}

void read_money(std::vector <Coins>& vec2) {

	int cnt = 0;
	std::ifstream file("list2.txt");

	while (cnt<vec2.size() && file >> vec2[cnt].money) {
		cnt++;
	}

	file.close();
}

void print_money(std::vector <Coins>& vec2) {

	std::ofstream file("list2.txt");

	for (int i = 0; i < vec2.size(); i++) {
		file << vec2[i].money << std::endl;
	}
	file.close();
}

void start_machine(std::vector <Products>& vec, std::vector <Coins>& vec2) {

	int w = 0;
	int coin_a = 0;
	int amm = 0;
	int x = 0;
	int c = 0;
	std::vector <int> cnt = { 0,0,0,0,0,0 };
	int credit = 0;
	std::vector <int> money = { 0,0,0,0,0,0 };
	int cost = 0;

	//executes loop if the input fails (e.g., no characters were read)
	while (std::cout << "Choose a product (0-4)" && !(std::cin >> x) || (x > vec.size() - 1) && x != 255 && x != 256 && x != 257 || x < 0) {
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "Invalid input; please re-enter.\n";
	}
	if (x == 255) {

		while (std::cout << "Supply mode, choose which product you want to resupply : " && !(std::cin >> x) || (x > vec.size() - 1) || x < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input; please re-enter.\n";
		}
		while (std::cout << "Choose ammount : " && !(std::cin >> amm) || amm < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input; please re-enter.\n";
		}
		vec[x].ammount += amm;
	}
	if (x == 256) {

		std::cout << "Machine turning off..." << "\n" << std::endl;
		exit(0);
	}

	if (x == 257) {
		while (std::cout << "Money Pool Edit mode, choose which coin you want to resupply [0-5] where 0 = 10gr and 5 = 5zł: " && !(std::cin >> w) || (w > 5) || w < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid coin; please re-enter.\n";
		}
		while (std::cout << "Choose ammount : " && !(std::cin >> coin_a) || coin_a < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid ammount; please re-enter.\n";
		}
		vec2[w].coin += coin_a;
	}

	while (std::cout << "Choose ammount: " && !(std::cin >> amm) || amm > vec[x].ammount || amm < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input; please re-enter.\n";
	}

	cost = vec[x].prize * amm * 100;
	int cost_left = cost;
	std::cout << "The cost is: " << cost / 100.0 << "zł" << std::endl;

	for (int i = 0; i < money.size(); i++) {

		while (std::cout << "\n Please, input ammount of coin : " << vec2[i].coin / 100.0 << " zł " && !(std::cin >> money[i])) {
			std::cin.clear(); //clear bad input flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			std::cout << "Ammount paid is insufficient\n";
		}

		if (money[i]) {
			cost_left -= (money[i] * vec2[i].coin);
		}
		if (cost_left < 0) {
			cost_left = 0;
		}

		std::cout << "\n Cost left : " << cost_left / 100.0 << " zł" << std::endl;
		c = vec2[i].coin * money[i];
		credit += c;
		vec2[i].money += money[i];
	}
	int change = credit - cost;
	std::cout << "\nCredit available: " << credit / 100.0 << " zł" << std::endl;
	std::cout << "\nChange to return: " << change / 100.0 << " zł" << std::endl;

	if (change > 0) {
		for (int k = 5; k > -1; k--) {
			while (change - vec2[k].coin >= 0 && vec2[k].money - 1 >= 0 && vec2[k].money > 20) {
				change -= vec2[k].coin;
				vec2[k].money -= 1;
				cnt[k]++;
			}
		}
		for (int k = 5; k > -1; k--) {
			while (change - vec2[k].coin >= 0 && vec2[k].money - 1 >= 0) {
				change -= vec2[k].coin;
				vec2[k].money -= 1;
				cnt[k]++;
			}
		}
	}
	//if there are no coins left  
	if (change > 0) {
		std::cout << "\n";
		for (int f = 0; f < vec2.size(); f++) {
			vec2[f].money -= money[f];
			std::cout << "Sorry,cannot give you change, try paying with deducted coins, giving back your credit: " << money[f] << " x " << vec2[f].coin / 100.0 << " zł \n" << std::endl;
		}
	}
	else {
		for (int f = 0; f < vec2.size(); f++) {
			std::cout << "\nYour change: " << cnt[f] << " x " << vec2[f].coin / 100.0 << " zł" << std::endl;
		}
		std::cout << "\nThank you for your purchase!\n" << std::endl;
		vec[x].ammount -= amm;
	}
}