#include<map>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class hash
{
public:
	hash(ifstream &input);

	int get_pattern(ofstream &output);

private:

	map<string,int> pattern_map;
};
