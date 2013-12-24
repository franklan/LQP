#include"kmeans.h"



kmeans::kmeans(int a , int b)
{
	digit = a;
	clunum = b;
}




int kmeans::run_kmeans(ifstream &input , int PatNum , int nround , ofstream &output)
{



	// initiate the cluster center
	float clucenter[dimension][digit];
        for(int j=0;j!=dimension;++j)
                for(int i=0;i!=digit;++i)
                {
                        int tmpint = rand() % 3;
			clucenter[j][i]=tmpint;
                }




	//  Dynamic memory allocation
	float **data = new float*[PatNum];
	for(int i=0;i!=PatNum;++i)
	{
		data[i]=new float[digit];
	}
	float *weight = new float[PatNum];




	//  input the data
	for(int i=0;i!=PatNum;++i)
	{	
		input>>weight[i];
		for(int j=0;j!=digit;++j)
			input>>data[i][j];
	}

	float sum[digit];
	for(int round=0;round<nround;++round)
	{
		cout<<"round:"<<round<<endl;
		//   put the points into clusters
		for(int i=0;i!=PatNum;++i)
		{
                        int tmpint=run_distance(data[i],(float*)clucenter);
                        cluster[tmpint].push_back(i);
			#ifdef DEBUG
			for(int m=0;m<digit;m++)
				cout<<data[i][m]<<" ";
			cout<<endl;
			cout<<"roune="<<round<<"  Pic:"<<i<<"  clu:"<<tmpint<<endl;
			#endif
		}



		//   recalculate the clustercenters
		for(int j=0;j!=dimension;++j)
		{
			float weightSum = 0;
	                for(int i=0;i!=digit; ++i)
	                        sum[i]=0;
			#ifdef DEBUG
			cout<<" j="<<j<<" size="<<cluster[j].size()<<endl;
			#endif
			for(container<int>::iterator loc=cluster[j].begin();loc!=cluster[j].end();++loc)
			{
				weightSum += weight[(*loc)];
				for(int i=0;i!=digit;++i)
				{
					sum[i] += data[(*loc)][i] * weight[(*loc)];
					#ifdef DEBUG
					cout<<sum[i]<<" ";
					#endif
				}
			}
			/*
			for(int i=0;i!=digit;++i)
                                sum[i] /= weightSum;
			*/

			if(cluster[j].size()!=0){
				for(int i=0;i!=digit;++i)
				{
					//clucenter[j][i] = sum[i] / cluster[j].size();
					clucenter[j][i] = sum[i] / weightSum;
					if(clucenter[j][i]>2){
						cerr<<"j "<<j<<" i "<<i<<endl;
						cerr<<"cluster[j].size() "<<cluster[j].size()<<endl;
						for(container<int>::iterator loc=cluster[j].begin();loc!=cluster[j].end();++loc)
						{
							sum[i] += data[(*loc)][i];
							cerr<<data[(*loc)][i]<<"   "<<sum[i]<<endl;
						}
						cerr<<"sum[i] "<<sum[i]<<" sum[i] / cluster[j].size() "<<sum[i] / cluster[j].size()<<endl;
						exit(0);	
					}
					#ifdef DEBUG
					cout<<clucenter[j][i]<<" ";
					#endif
				}
			}
		}
	}


	//   output the clustercenters
	for(int j=0;j!=dimension;++j)
	{
//		if(cluster[j].size() != 0){
			for(int i=0;i!=digit;++i)
			{
				output<<clucenter[j][i]<<" ";
			}
			output<<endl;
//		}
	}
	


	//   Dynamic memory dispose
	for(int i=0;i!=PatNum;++i)
	{
		delete[] data[i];
	}
	delete[] data;
	delete[] weight;
	return 0;
}




int kmeans::run_distance(float* a,float* b)
{
	float square_sum[dimension],min=10000;
	int flag;

	// calculate the distance	
	for(int j=0;j!=dimension;++j)
	{
		square_sum[j]=0;
		
		for(int i=0;i!=digit;++i)
		{
			square_sum[j] += (a[i]-*(b+j*digit+i))*(a[i]-*(b+j*digit+i));
		}
	}

	
	// return the min distance and flag
	for(int j=0;j!=dimension;++j)
	{
		if(square_sum[j]<min){
			min=square_sum[j];
			flag=j;
			#ifdef DEBUG
			cout<<square_sum[j]<<" ";
		        cout<<flag<<" ";
        		#endif
		}
	}
	#ifdef DEBUG
	cout<<endl<<flag<<endl;
	#endif
	return flag;
}
