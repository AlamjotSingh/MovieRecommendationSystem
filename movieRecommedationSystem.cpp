#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<iterator>
#include<algorithm>
#include<iostream>
using namespace std;

int main()
{
	int i,j;
	ifstream infile;
	infile.open("movies.csv");
	if(!infile)
	{
    	cout<<"\nError in Opening File\n";
        exit(1);
    } 
    
    vector<string> name;
	vector<int> year;
	vector<float> rating;
	vector<int> vote;
	vector<vector<string> > gener;
	int total_movie;

	vector<string> temp;
    string value,line;
    getline(infile,line);
    while (getline(infile,line))
    {
		stringstream str1(line);       
		getline(str1,value,',');
		name.push_back(value);
		
		getline(str1,value,',');	
		stringstream str2(value);
		getline(str2,value,'-');
		getline(str2,value,'-');
		getline(str2,value,'-');
		year.push_back(atoi(&value[0]));
		
		getline(str1,value,',');
		rating.push_back(atof(&value[0]));
		
		getline(str1,value,',');	
		vote.push_back(atoi(&value[0]));
		
		while(getline(str1,value,'"'))
		{
			if(!value.compare("Action")||!value.compare("Fantasy")||
			!value.compare("Adventure")||!value.compare("Thriller")||
			!value.compare("Science Fiction")||!value.compare("Family")||
			!value.compare("Romance")||!value.compare("Animation")||
			!value.compare("Comedy")||!value.compare("Drama")||
			!value.compare("Western")||!value.compare("War")||
			!value.compare("Crime")||!value.compare("Mystery"))
			{
				transform(value.begin(), value.end(), value.begin(), ::tolower);
				temp.push_back(value);
			}
		}
		gener.push_back(temp);
		temp.clear();
    }
    
    total_movie=name.size();
	
	vector<int> n;
	
	string gener_name;
	cout<<"\nAction, Family, Adventure, Fantasy, Thriller, Science Fiction,";
	cout<<"\nRomance, Animation, Comedy, Drama, Western, War, Crime, Mystery";
	cout<<"\nEnter the Gener:";
	cin>>gener_name;
	transform(gener_name.begin(), gener_name.end(), gener_name.begin(), ::tolower);
	vector<string>::iterator it;
	for(i=0;i<total_movie;i++)
   	{
		it=find(gener[i].begin(),gener[i].end(),gener_name); 
    	if(it!=temp.end())
    		n.push_back(i);
	}
	
	vector<int> sorted,top_20;
	int num,index,t;
	float max;
	for(i=0;i<n.size();i++)
	{ 
    	max=-1;
		for(j=0;j<n.size();j++)
		{
			if(rating[n[j]]>max)
			{
				max=rating[n[j]];
				index=n[j];	
				t=j;
			}	
		}
		sorted.push_back(index);
		n.erase(n.begin()+t);	
	}
		
	int k=0;
	for(i=0;i<sorted.size();)
	{
		num=vote[sorted[i]];
		j=i;
		while(rating[sorted[i]]==rating[sorted[j]]&&j<sorted.size())
		{
			if(vote[sorted[j]]>=num)
			index=j;
			j++;
		}
		top_20.push_back(sorted[index]);
		k++;
		if(k==20)
			break;
		i=j;
	}
		//for(i=0;i<top_20.size();i++)
		//cout<<rating[top_20[i]]<<"\t"<<vote[top_20[i]]<<"\n";
	vector<float> weight;
	float Wy,Wr,Wg;	
	for(i=0;i<top_20.size();i++)
	{
		k=0;
		j=0;
		while(j<total_movie)
		{
			if(year[top_20[i]]==year[j])
				k++;
				
			j++;	
		}
		Wy=float(k)/total_movie;
		
		if(vote[top_20[i]]<=1000)
			Wr=rating[top_20[i]];
		else if(vote[top_20[i]]>1000&&vote[top_20[i]]<=10000)
			Wr=2*rating[top_20[i]];
		else
			Wr=3*rating[top_20[i]];
		
		k=0;
		j=0;
		bool flag;
		while(j<total_movie)
		{
			flag=false;
			for(vector<string>::iterator it =gener[top_20[i]].begin();it!=gener[top_20[i]].end();it++)
			{
				vector<string>::iterator itt=find(gener[i].begin(),gener[i].end(),*it);
				if(it!=gener[i].end())
					flag=true;		
			}	
			if(flag)
				k++;
				
			j++;	
		}
		Wg=float(k)/total_movie;		
		cout<<Wr<<"\t"<<Wy<<"\t"<<Wg<<"\n";		
	}
	return 0;
}