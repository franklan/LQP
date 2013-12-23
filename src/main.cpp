#include"LQP.h"
#include"svmscale.h"
const int dimension = 150;

IplImage* resize1(IplImage *ima);
int main(int argc,char **argv)
{
	if(argc != 5){
		cerr<<"Usage:./extractLQP jpglist outputFile ClucenterFile option(-g=generate codebook,-e=extract LQP for PCA)\n"<<
			"./extractLQP jpglist directory ClucenterFile option(-e2=extract LQP for test)\n"
			"./extractLQP jpglist directory ClucenterFile option(-p extract LQP for pyramid PCA)\n"
			"./extractLQP jpglist directory ClucenterFile option(-p2=extract LQP pyramid for test)"<<endl;
		return -1;
	}



	// initialize the file stream
	ifstream input,clucenterinput;
	ofstream output;
	input.open(argv[1],ios::in);
	output.open(argv[2],ios::out);
	clucenterinput.open(argv[3],ios::in);
	bool optionG = strcmp("-g",argv[4]);
	bool optionE = strcmp("-e",argv[4]);
	bool optionE2 = strcmp("-e2",argv[4]);
	bool optionP = strcmp("-p",argv[4]);
	bool optionP2 = strcmp("-p2",argv[4]);

	//  Dynamic memory allocation
        float **clucenter = new float* [dimension];
        for(int i=0;i!=dimension;++i)
        {
                clucenter[i]=new float[48];
        }
        for(int i=0;i!=dimension;++i)
                for(int j=0;j!=48;++j)
                        clucenterinput>>clucenter[i][j];
	int finalDimension = dimension*PictureWidth*PictureHeight/WidthStep/HeightStep;
	double *result = new double [finalDimension];




	
	// input the pictures
	IplImage* img = NULL;
	IplImage* input_img = NULL;
	char jpgname[100];
	while(input>>jpgname)
	{
		input_img = cvLoadImage(jpgname);
		if(!input_img){
		cerr<<"error in reading image"<<endl;
		return -1;
		}
		img = resize1(input_img);
		LQP a(img);


		if(optionG == false)
		{
			a.cal_LQP(3,output);                //used for generating codebook
		}
		else if(optionE == false)
		{
			// calculate LQP histogram
        	        for(int i=0;i<finalDimension;i++)
				result[i]=0;
			a.cal_LQP_histogram( 3 , 48 , clucenter , dimension ,result);
			for(int i=0;i<finalDimension;i++)
				output<<*(result+i)<<" ";
			output<<endl;
		}
		else if(optionP == false)
		{
			// calculate LQP histogram
                        for(int i=0;i<finalDimension;i++)
                                result[i]=0;
                        a.cal_LQP_histogram( 3 , 48 , clucenter , dimension ,result);
                        for(int i=0;i<finalDimension;i++)
                                output<<*(result+i)<<" ";
			
			
		        IplImage *dst = 0;
		        CvSize dst_cvsize;
	        	dst_cvsize.width = PictureWidth / 2;
        		dst_cvsize.height = PictureHeight / 2;
		        dst = cvCreateImage( dst_cvsize, img->depth, img->nChannels);
        		cvResize(img, dst, CV_INTER_LINEAR);
			LQP a(dst);
			for(int i=0;i<finalDimension;i++)
                                result[i]=0;
			a.cal_LQP_histogram( 3 , 48 , clucenter , dimension ,result);
			for(int i=0;i<finalDimension/4;i++)
                                output<<*(result+i)<<" ";



			dst = 0;
                        dst_cvsize.width = PictureWidth * 3 / 10 ;
                        dst_cvsize.height = PictureHeight * 3 / 10;
                        dst = cvCreateImage( dst_cvsize, img->depth, img->nChannels);
                        cvResize(img, dst, CV_INTER_LINEAR);
                        LQP b(dst);
                        for(int i=0;i<finalDimension;i++)
                                result[i]=0;
                        b.cal_LQP_histogram( 3 , 48 , clucenter , dimension ,result);
                        for(int i=0;i<finalDimension/100*9;i++)
                                output<<*(result+i)<<" ";

                        output<<endl;

		}
		else if(optionE2 == false)
		{
			string strJpgname(jpgname);
			string::size_type loc = strJpgname.rfind("/");
			strJpgname = strJpgname.substr(loc+1);
			string::size_type loc2 = strJpgname.find(".");	
			strJpgname.erase(loc2,strJpgname.size());
			strJpgname = "/local/lantianyue/LFW_view2_face/featureData_wk/" + strJpgname + ".LQP";
			ofstream outputFile(strJpgname.c_str());
			outputFile<<"1 15000"<<endl;
			for(int i=0;i<finalDimension;i++)
                                result[i]=0;
                        a.cal_LQP_histogram( 3 , 48 , clucenter , dimension ,result);
                        for(int i=0;i<finalDimension;i++)
                                outputFile<<*(result+i)<<" ";
                        outputFile<<endl;
			outputFile.close();
		}
		else if(optionP2 == false)
		{
			string strJpgname(jpgname);
                        string::size_type loc = strJpgname.rfind("/");
                        strJpgname = strJpgname.substr(loc+1);
                        string::size_type loc2 = strJpgname.find(".");
                        strJpgname.erase(loc2,strJpgname.size());
                        strJpgname = "/local/lantianyue/LFW_view2_face/featureData_P/" + strJpgname + ".LQP";
                        ofstream outputFile(strJpgname.c_str());
                        outputFile<<"1 20100"<<endl;
                        for(int i=0;i<finalDimension;i++)
                                result[i]=0;
                        a.cal_LQP_histogram( 3 , 48 , clucenter , dimension ,result);
                        for(int i=0;i<finalDimension;i++)
                                outputFile<<*(result+i)<<" ";

			IplImage *dst = 0;
                        CvSize dst_cvsize;
                        dst_cvsize.width = PictureWidth / 2;
                        dst_cvsize.height = PictureHeight / 2;
                        dst = cvCreateImage( dst_cvsize, img->depth, img->nChannels);
                        cvResize(img, dst, CV_INTER_LINEAR);
                        LQP a(dst);
                        for(int i=0;i<finalDimension;i++)
                                result[i]=0;
                        a.cal_LQP_histogram( 3 , 48 , clucenter , dimension ,result);
                        for(int i=0;i<finalDimension/4;i++)
                                output<<*(result+i)<<" ";


			dst = 0;
                        dst_cvsize.width = PictureWidth * 3 / 10 ;
                        dst_cvsize.height = PictureHeight * 3 / 10;
                        dst = cvCreateImage( dst_cvsize, img->depth, img->nChannels);
                        cvResize(img, dst, CV_INTER_LINEAR);
                        LQP b(dst);
                        for(int i=0;i<finalDimension;i++)
                                result[i]=0;
                        b.cal_LQP_histogram( 3 , 48 , clucenter , dimension ,result);
                        for(int i=0;i<finalDimension/100*9;i++)
                                output<<*(result+i)<<" ";


			
                        outputFile<<endl;
                        outputFile.close();
		}
		else 
		{
			cerr<<"wrong option (-g=generate codebook,-e=extract LQP feature)"<<endl;
			return -1;
		}
		cout<<jpgname<<endl;
	}



	// Dynamic memory dispose
	delete [] result;
	for(int i=0;i!=dimension;++i)
        {
                delete[] clucenter[i];
        }
        delete[] clucenter;


	input.close();
	output.close();
	clucenterinput.close();
	return 0;
}






IplImage* resize1(IplImage *ima)
{
        if(!ima){cerr<<"could not open image"<<endl;}


        // resize the image
        IplImage *dst = 0;
        CvSize dst_cvsize;
        dst_cvsize.width = PictureWidth;
        dst_cvsize.height = PictureHeight;
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
//              cvSaveImage("res.jpg",imaMid);
                return imaMid;
        }
        else
                cerr<<"resize error"<<endl;

}

