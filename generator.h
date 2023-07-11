#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <bitset>
#include <ctime>
using namespace std

class generator
{	
	string alf; 
	map <char, int> mp;
	string value; 

public:
	generator(string alf, int len);
	void head();
	string get_string();
	map <char, int> get_map();
};


generator::generator(string _alf, int len)
{
	alf = _alf;
	srand(time(NULL));

	string alfp = "";
	int count = 1;
	for (char letter : alf)
	{
		for (int count_letter = 0; count_letter < count; count_letter++) {
			alfp.push_back(letter);
		}
		count++;
	}

	
	for (char i : alf) { mp[i] = 0; }
	int elem;
	for (int i = 0; i < len; i++){
		elem = alfp[rand() % alfp.length()];
		value.push_back(elem);
		mp[elem]++;
	}
	
}

void generator::head()
{	
	cout  << "Head: " ;
	if (value.length() < 60) {
		std::cout << value;
	}
	else {
		std::cout << value.substr(0, 60);
	}
	std::cout <<"..." << endl;
	cout  << "count liter: \n";
	for (auto i : mp)
		cout << "\t"  << i.first << ": " << i.second<< endl;

}

string generator::get_string()
{
	return value;
}

map <char, int> generator::get_map()
{
	return mp;
}

