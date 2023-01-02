#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>

std::time_t timeNow = std::time(nullptr);

struct birth_data {
	std::string name;
	std::tm birth_date = *std::localtime(&timeNow);
};

int main() {
	std::tm local = *std::localtime(&timeNow);
	birth_data bd;
	std::vector<birth_data> bd_cal;
	std::vector<birth_data> nearest_cal;

	std::cout << "Input name (or <end> for finish input):";
	std::cin >> bd.name;
	while (bd.name != "end") {
		std::cout << "Input birth date (YYYY/MM/DD):";
		std::cin >> std::get_time(&bd.birth_date, "%Y/%m/%d");
		bd.birth_date.tm_year += local.tm_year - bd.birth_date.tm_year;
		bd_cal.push_back(bd);

		std::cout << "Input name (or <end> for finish input):";
		std::cin >> bd.name;
	}

	for (int i = 0; i < bd_cal.size(); i++) {
		if (bd_cal[i].birth_date.tm_mon < local.tm_mon)
			bd_cal[i].birth_date.tm_year += 1;
		else if (bd_cal[i].birth_date.tm_mon == local.tm_mon) {
			if (bd_cal[i].birth_date.tm_mday < local.tm_mday)
				bd_cal[i].birth_date.tm_year += 1;
		}
	}

	int nearest_index;
	double diff_t = 1674302778;
	for (int i = 0; i < bd_cal.size(); i++) {
		std::time_t bd_t = std::mktime(&bd_cal[i].birth_date);
		if (difftime(bd_t, timeNow) < diff_t) {
			diff_t = difftime(bd_t, timeNow);
			nearest_index = i;
		}
	}

	std::cout << "------------------" << std::endl;
	std::cout << "Nearest birthdays:" << std::endl;
	std::cout << bd_cal[nearest_index].name << ":\t\t";
	std::cout << std::put_time(&bd_cal[nearest_index].birth_date, "%d %B %Y") << std::endl;

	std::vector<birth_data> nearest;
	std::time_t nearest_t = std::mktime(&bd_cal[nearest_index].birth_date);
	for (int i = 0; i < bd_cal.size(); i++) {
		std::time_t bd_t = std::mktime(&bd_cal[i].birth_date);
		if (i != nearest_index) {
			if (difftime(bd_t, nearest_t) == 0)
				nearest.push_back(bd_cal[i]);
		}
	}
	if (!(nearest.empty())) {
		for (int i = 0; i < nearest.size(); i++) {
			std::cout << nearest[i].name << ":\t\t";
			std::cout << std::put_time(&nearest[i].birth_date, "%d %B %Y") << std::endl;
		}
	}
}
