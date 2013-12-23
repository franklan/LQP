#include"svmscale.h"

svmscale::svmscale()
{
}
void svmscale::printrange(double *array,int dimension,int num,fstream &output_range)
{
	output_range<<"x"<<"\n"<<0<<" "<<1<<endl;
	for(int i=0;i!=dimension;++i)
	{
		double bigest=-999999,smallest=999999;
		for(int j=0;j!=num;++j)
		{
			bigest = (bigest>*(array+j*dimension+i)) ? bigest : *(array+j*dimension+i);
			smallest = (smallest<*(array+j*dimension+i)) ? smallest : *(array+j*dimension+i);
		}
		smallarray.push_back(smallest);
		bigarray.push_back(bigest);
		output_range<<i+1<<" "<<smallest<<" "<<bigest<<endl;
	}
}
void svmscale::printscale(double *array,int dimension,int num,fstream &output_scale)
{
	#pragma omp parallel
	{
	#pragma omp for
	for(int i=0;i!=dimension;++i)
	{
		for(int j=0;j!=num;++j)
		{
			if(bigarray[i]-smallarray[i]!=0)
			{
				*(array+j*dimension+i)=(*(array+j*dimension+i)-smallarray[i])/(bigarray[i]-smallarray[i]);
			}
		}
	}
	}
	/*
	for(int j=0;j!=num;++j)
        {
		for(int i=0;i!=dimension;++i)
		{
			output_scale<<*(array+j*dimension+i)<<" ";
		}
		output_scale<<endl;
	}*/
}

