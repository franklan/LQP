#include"hash.h"



hash::hash(ifstream &input)
{
	string pattern;
	while(getline(input,pattern))
	{
		pattern_map[pattern]++;
	}
}





int hash::get_pattern(ofstream &output)
{
	map<string,int>::iterator loc;
	int count=0;

        for(loc=pattern_map.begin();loc!=pattern_map.end();++loc)
        {
                if(loc->second>10){
			output<<loc->second<<" "<<loc->first<<endl;
			count++;
		}
	}

	return count;
}
