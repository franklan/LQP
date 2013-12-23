#include<fstream>
#include<vector>
#include<omp.h>
#include<iostream>
using namespace std;

class svmscale
{
public:
	svmscale();
	void printrange(double *array,int dimension,int num,fstream &output_range);
	void printscale(double *array,int dimension,int num,fstream &output_scale);
private:
	vector<double> bigarray;
	vector<double> smallarray;
};
