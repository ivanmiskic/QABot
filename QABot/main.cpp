#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <stdio.h>

using namespace std;

class Pair
{
public:
	size_t num;
	string lat;
	vector<string> hrv;

	Pair();
	Pair(string, string);
};
Pair::Pair(){}
Pair::Pair(string l, string h)
{
	lat = l;

	num = 0;
	string left, right;
	size_t pos;
	while (h.find(',') != std::string::npos)
	{
		pos = h.find(",");
		if (h[pos + 1] == ' ')
			right = h.substr(pos + 2);              //offset from "," (ex: ", ")
		else right = h.substr(pos + 1);
		if (h[pos - 1] == ' ')
			left = h.substr(0, pos - 1);            //offset from "," (ex: " ,")
		else left = h.substr(0, pos - 0);
		hrv.push_back(left);

		if (right.find(",") == std::string::npos)
		{
			pos = h.find(",");
			if (h[pos + 1] == ' ')
				right = h.substr(pos + 2);          //offset from "," (ex: ", ")
			else right = h.substr(pos + 1);
			hrv.push_back(right);
		}
		h = right;
		num++;
	}
	if (num > 0)
		return;
	else hrv.push_back(h);
}


int main(void)
{
	ifstream f("latinski.txt");

	std::vector<Pair> list;
	size_t pos, lineCounter = 0;
	string str, lat, hrv, razmak = "-";
	while (getline(f, str))
	{
		pos = str.find("-");
		if (pos == std::string::npos)
			std::cout << "pos of substr not found\n";

		if (str[pos + 1] == ' ')
			hrv = str.substr(pos + 2);              //offset from "-" (ex: "- ")
		else hrv = str.substr(pos + 1);

		if (str[pos - 1] == ' ')
			lat = str.substr(0, pos - 1);           //offset from "-" (ex: " -")
		else lat = str.substr(0, pos);

		cout << lat << " - " << hrv << endl;

		list.push_back(Pair(lat, hrv));
		lineCounter++;
	}

	//Better rand below turned out with some predictive outputs for some reason
	//std::random_device rd;
	//std::mt19937 rng(rd());
	//std::uniform_int_distribution<int> uni(0, lineCounter - 1);
	srand(time(NULL));

	vector<string> correct_answers;
	while (1)
	{
		size_t r = (float)rand() / (float)RAND_MAX *(lineCounter - 1);
		//string input, task = list[uni(rng)].lat;
		string input, task = list[r].lat;
		cout << "Unesite prijevod za " << task << ": ";
		//cin >> input;
		getline(cin, input, '\n');

		bool tocno = false;
		for (std::vector<Pair>::iterator it = list.begin(); it != list.end(); it++)
		{
			if (it->lat == task)
			{
				for (int i = 0; i <= it->num; i++)
				{
					if (it->hrv[i] == input)
					{
						cout << "Tocan odgovor!" << endl;
						tocno = true;
						break;
					}
				}
				if (!tocno)
					correct_answers = it->hrv;
			}
			if (tocno)
				break;
		}
		if (!tocno)
		{
			cout << "Netocan odgovor, tocni odgovori su: ";
			for (std::vector<string>::iterator it = correct_answers.begin(); it != correct_answers.end(); it++)
				cout << *it << ", ";
			cout << endl;
		}
		cout << endl;
	}

	f.close();
	return 0;
}