#include"hash.h"
#include"kmeans.h"

int main(int argc,char* argv[])
{
	if(argc != 4){
		cerr<<"Usage: ./KMeans input midres output\n";
		return -1;
	}


	// find the patterns appearing more than 10 times
	ifstream input;
	ofstream output;
	input.open(argv[1],ios::in);
	output.open(argv[2],ios::out);



	hash hash_pattern(input);
	int PatNum = hash_pattern.get_pattern(output);
	input.close();
	output.close();



	// run kmeans		
	input.open(argv[2],ios::in);
	output.open(argv[3],ios::out);



	kmeans pattern_kmeans( 48 , 150 );
	pattern_kmeans.run_kmeans(input,PatNum,10,output);
	input.close();
	output.close();

	
	return 0;
}
