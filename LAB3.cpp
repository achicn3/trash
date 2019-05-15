#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <algorithm>
using std::vector;
using std::string;
using std::map;
typedef struct a{
	char name[10];
	int start;
	int end;
	

}Data;

int cmp(Data a,Data b){
	return a.start<b.start;
}
void Remove(vector<Data>& input,Data now){
	for(int i=0;i<input.size();i++){
		if(strcmp(input[i].name,now.name)==0){
			input.erase(input.begin()+i);
			return;
		}
	}
}
Data Next(vector<Data> &input,Data now){
	int index=0;
	for(int i=0;i<input.size();i++){
		if(strcmp(input[i].name,now.name)==0)
			index=i;
	}
	return input[index+1];
}
void Left_edge(vector<Data> &input,map<char*,int> MAP){
	int reg_index=0;
	int next=1;
	vector<Data> name = input;
	while(input.size()!=1){
		reg_index+=1;
		Data curr_var = input.front();
		int last = 0;
		while(strcmp(curr_var.name,"END")!=0){
			if(curr_var.start>=last){
				printf("Set : %s %d\n",curr_var.name,reg_index);
				MAP[curr_var.name] = reg_index;
				last = curr_var.end;
				Data temp_var = curr_var;
				curr_var = Next(input,curr_var);
				Remove(input,temp_var);
			}
			else
				curr_var = Next(input,curr_var);
		}
	}
	for(int i=1;i<=reg_index;i++){
		for(int j=0;j<name.size()-1;j++)
			if(MAP[name[j].name]==i)
				printf("%d %s \n",i,name[j].name);
	}
}

int main(){
	/*----Open File----*/
	FILE *file1,*file2,*file3;
	if(	(file1 = fopen("Lifetime1.txt","r"))==NULL || (file2 = fopen("Lifetime2.txt","r"))==NULL|| 
		(file3 = fopen("Lifetime3.txt","r"))==NULL)
			fprintf(stderr,"[Error] File open failed.\n");
	/*----Read File and stroe in vector----*/
	vector<Data> life1,life2,life3;
	map<char*,int> map1,map2,map3;
	Data temp;
	/*---Lifetime1---*/
	while(fscanf(file1,"%s %d %d",&temp.name,&temp.start,&temp.end)!=EOF){
		map1[temp.name] = 0;
		life1.push_back(temp);
	}
	/*---Lifetime2---*/
	while(fscanf(file2,"%s %d %d",&temp.name,&temp.start,&temp.end)!=EOF){
		map2[temp.name] = 0;
		life2.push_back(temp);
	}
	/*---Lifetime3---*/
	while(fscanf(file3,"%s %d %d",&temp.name,&temp.start,&temp.end)!=EOF){
		map3[temp.name] = 0;
		life3.push_back(temp);
	}
	/*---Sort life time---*/
	sort(life1.begin(),life1.end(),cmp);
	sort(life2.begin(),life2.end(),cmp);
	sort(life3.begin(),life3.end(),cmp);
	/*---Test---*/
	/*for(auto &i:life1){
		printf("%s %d %d\n",i.name,i.start,i.end);
	}*/
	printf("-------Life1--------\n");
	Left_edge(life1,map1);

	printf("\n\n-------Life2--------\n\n");
	Left_edge(life2,map2);
	printf("\n\n-------Life3--------\n");
	Left_edge(life3,map3);
}
 
