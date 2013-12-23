#include"LQP.h"



LQP::LQP()
{
	cerr<<"bad initialization"<<endl;
}





LQP::LQP(IplImage* input)
{
	img = input;
}




LQP::~LQP()
{
	cvReleaseImage(&img);
}





int LQP::cal_LQP(int R,ofstream &output)
{

	//img = resize1(input_img);
	for(int i=0;i!=img->height;i+=HeightStep)
	{
		for(int j=0;j!=img->width;j+=WidthStep)
		{
			cal_block(output,R,i,j);
		}
	}
	return 0;
}




int LQP::cal_block(ofstream &output,int R,int i,int j)
{
	int itempx;
        int itempy;
        double tempx=0.0;
        double tempy=0.0;
        double dx=0.0;
        double dy=0.0;
        int Img1;
        int Img2;
        int Img3;
        int Img4;
        int value;
        int newvalue;
        int Midvalue;


	for(int m=i;m<i+HeightStep;m++)
        {
		for( int n=j;n<j+WidthStep;n++)
                {
			for(int radius=R;radius!=0;--radius)
			{
                        	Midvalue = pixval8(img,m,n); // y,x
				for (int k=0;k<8*radius;k++)
        	                {
                	                tempx= n+ radius* cos(2.0*CV_PI*k/8/radius);
                        	        tempy= m- radius* sin(2.0*CV_PI*k/8/radius);
                                	itempx=static_cast<int>(floor(tempx));
	                                itempy=static_cast<int>(floor(tempy));
					dx= (tempx- itempx);
                	                dy= (tempy- itempy);
                        	        Img1     = pixval8(img,itempy,itempx); //(x,y)
                                	Img2     = pixval8(img,itempy+1,itempx); //(x,y+1)
      	                               Img3     = pixval8 (img,itempy,itempx+1); //(x+1,y)
        	                       Img4     = pixval8(img,itempy+1,itempx+1);//(x+1,y+1)
                	               value= static_cast<int>(Img1*(1-dx)*(1-dy) + Img2*(1-dx)*dy+ Img3*dx*(1-dy)+Img4*dx*dy);


					output<<( Midvalue>=(value+5)  ? 2 : (Midvalue<=(value-5) ? 0 : 1) )<<" ";
				}
			}
			output<<endl;
		}
	}
	return 0;
}





IplImage* LQP::resize1(IplImage *ima)
{
	if(!ima){cerr<<"could not open image"<<endl;}


        // resize the image
        IplImage *dst = 0;
        CvSize dst_cvsize;
        dst_cvsize.width = img->width;
        dst_cvsize.height = img->height;
        dst = cvCreateImage( dst_cvsize, ima->depth, ima->nChannels);
        cvResize(ima, dst, CV_INTER_LINEAR);


        //color to gray
        if (dst){
	        int height = dst->height;
        	int width = dst->width;
	        IplImage *imaMid = cvCreateImage(cvSize(width,height), IPL_DEPTH_8U, 1);
        	if(dst->nChannels == 3)
	        cvCvtColor(dst, imaMid, CV_RGB2GRAY);
        	else
	        cvCopy(dst, imaMid);
		cvReleaseImage(&dst);
//		cvSaveImage("res.jpg",imaMid);
		return imaMid;
	}
	else
		cerr<<"resize error"<<endl;
	
}



int LQP::cal_LQP_histogram( int R , int digit , float**clucenter , int dimension , double* histo)
{

//        img = resize1(input_img);
	//cout<<"H:"<<HeightStep<<" W:"<<WidthStep<<endl;

	int offset = 0;
	for(int y=0;y!=img->height;y+=HeightStep)
	{
		for(int x=0;x!=img->width;x+=WidthStep)
		{
			cal_LQP_histogram_Core(R,digit,clucenter,dimension,histo+offset,x,y);
			offset += dimension;
		//	cout<<endl<<"offset:"<<offset<<"x y:"<<x<<" "<<y<<endl;
		}
	}
}
	

int LQP::cal_LQP_histogram_Core( int R , int digit , float**clucenter , int dimension , double* histo, int x,int y)
{
	float* LQP_fea = new float [digit];
	for(int i=0;i!=digit;i++)
		*(LQP_fea+i) = 0;
	float* distance = new float [dimension];


	

	int itempx;
        int itempy;
        double tempx=0.0;
        double tempy=0.0;
        double dx=0.0;
        double dy=0.0;
        int Img1;
        int Img2;
        int Img3;
        int Img4;
        int value;
        int newvalue;
        int Midvalue;

	int count;
	float min;
	int minflag = -1;
        
	for(int m=x;m<x+WidthStep;m++)
        {
                for( int n=y;n<y+HeightStep;n++)
                {
//			cout<<"m:"<<m<<" n:"<<n<<endl;
			count = 0;
                        for(int radius=R;radius!=0;--radius)
                        {
                                Midvalue = pixval8(img,m,n); // y,x
                                for (int k=0;k<8*radius;k++)
                                {
                                        tempx= n+ radius* cos(2.0*CV_PI*k/8/radius);
                                        tempy= m- radius* sin(2.0*CV_PI*k/8/radius);
                                        itempx=static_cast<int>(floor(tempx));
                                        itempy=static_cast<int>(floor(tempy));
                                        dx= (tempx- itempx);
                                        dy= (tempy- itempy);
                                        Img1     = pixval8(img,itempy,itempx); //(x,y)
                                        Img2     = pixval8(img,itempy+1,itempx); //(x,y+1)
                                       Img3     = pixval8 (img,itempy,itempx+1); //(x+1,y)
                                       Img4     = pixval8(img,itempy+1,itempx+1);//(x+1,y+1)
                         
			               value = static_cast<int>(Img1*(1-dx)*(1-dy) + Img2*(1-dx)*dy+ Img3*dx*(1-dy)+Img4*dx*dy);
					
					*(LQP_fea+count) = value > (pixval8(img,m,n)+7) ?  2   :
								(	value < (pixval8(img,m,n)-7) ? 0 : 1 );
					count++;
				}
			}
	

			min = VeryMin;
			for(int i=0;i<dimension;i++)
				distance[i]=0;
			for(int i=0;i<dimension;i++)
			{
				for(int j=0;j<digit;j++)
				{
					distance[i] += (*(LQP_fea+j) - clucenter[i][j]) * (*(LQP_fea+j) - clucenter[i][j]);
				}
            			if(distance[i]<min){
                                        min = distance[i];
                                        minflag = i;
                                }
			}
			if(minflag != -1)
				histo[minflag]++;
			
		}
	}

	for(int i=0;i<dimension;i++)
	{
//		cout<<histo[i]<<" ";
		histo[i] = sqrt(histo[i]/100);
	}

	delete [] distance;
	delete [] LQP_fea;
	return 0;
}	
