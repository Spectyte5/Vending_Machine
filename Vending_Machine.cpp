#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include "vendingmachine.h"


	int main() {
		Products Prod0(0, 1, 0, 1), Prod1(1, 1, 0, 1), Prod2(2, 1, 0, 1), Prod3(3, 1, 0, 1), Prod4(4, 1, 0, 1);
		Coins coin01(10, 20), coin02(20, 30), coin05(50, 10), coin10(100, 20), coin20(200, 10), coin50(500, 5);
		std::vector <Products> vec = {Prod0, Prod1, Prod2, Prod3, Prod4};
		std::vector <Coins> vec2 = {coin01, coin02 , coin05 , coin10 , coin20 , coin50};
		read_stock(vec);
		read_money(vec2);
		print_stock(vec);
		print_money(vec2);

		while (true) {
			start_machine(vec, vec2);
			print_money(vec2);
			print_stock(vec);
		}
	}