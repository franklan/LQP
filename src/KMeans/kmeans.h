#include<fstream>
#include<vector>
#include<list>
#include<iostream>
using namespace std;
#define container vector
const int dimension = 150;


class kmeans
{
public:
	kmeans(int a,int b);

	int run_kmeans(ifstream &input,int PatNum,int nround,ofstream &output);

	int run_distance(float* a,float* b);

private:

	int digit;

	int clunum;

	container <int> cluster[dimension];
};
