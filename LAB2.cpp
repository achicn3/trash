#include <cstdio>
#include <queue>
#define PLUS 1
#define MUL 2
using namespace std;
struct Data{
	int used;
	int clock;
	int data1;
	int data2;
	int output;
	Data(){
		used =0;
	}
};
struct Restrict{
	int mul;
	int plus;
	bool *useMul;
	bool *usePlus;
	setUP(){
		useMul = new bool[mul];
		usePlus = new bool[plus];
		for(int i=0;i<mul;i++){
			useMul[i] = false;
			usePlus[i] = false;
		}
	}
};
int main(){
	/* open file pointer */
	FILE *file1;
	FILE *file2;
	/* store file1 or file2 size */
	int size1,size2;
	/* Resource restrict */
	Restrict res;
	/* open file */
	if((file1=	fopen("DFG1.txt","r"))==NULL || (file2 = fopen("DFG2.txt","r"))==NULL ){
		printf("Open file failed.\n");
		return 0;
	}
	/* read how many file in file1 and file2 and store in size1 and size2 */
	fscanf(file1,"%d",&size1);
	fscanf(file2,"%d",&size2);
	/* store file data */
	Data *DFG1,*DFG2;
	DFG1 = new Data[size1];
	DFG2 = new Data[size2];
	int index=0,flag=1;
	/* read file1's data into DFG1 */
	while(	fscanf(file1,"%d %d %d %d",&DFG1[index].clock,&DFG1[index].data1,
			&DFG1[index].data2,&DFG1[index].output)!=EOF)
		index++;
	index=0;
	/* read file2's data int DFG2 */
	while(	fscanf(file1,"%d %d %d %d",&DFG2[index].clock,&DFG2[index].data1,
			&DFG2[index].data2,&DFG2[index].output)!=EOF)
		index++;
	printf("Please input your resource constarint:");
	scanf("%d %d",&res.mul,&res.plus);
	res.setUP();
	const int plus = res.plus;
	const int mul = res.mul;
	int MulTick=0,MulTick2=0,PlusTick=0,PlusTick2=0,clock=1;
	int PlusTag=0;
	int MulTag=0;
	int i=0;
	for(;i<size1  ;){
		while(DFG1[i].used && i<size1)
			i++;
		if(i == size1)break;
		PlusTag=i+1;
		MulTag=i+1;
		for(;flag;clock++){
			/* 2 adder */
			if(plus ==2 && DFG1[i].clock == PLUS && res.usePlus[0] == false && res.usePlus[1]==false){
				while(DFG1[PlusTag].clock!=PLUS && DFG1[PlusTag].used==0 ){
					PlusTag++;
				}
				
				DFG1[PlusTag].used=1;
				PlusTick++;
				PlusTick2++;
				res.usePlus[0]=true;
				res.usePlus[1]=true;
				printf("data:%d %d plus setup\n",i,PlusTag);
			}
			/* 1 adder */
			else if(plus ==1 && DFG1[i].clock == PLUS && res.usePlus[0] == false ){
				PlusTick++;
				res.usePlus[0] = true;
				printf("data:%d plus setup\n",i);
			}
			/* 2 multiplier */
			else if(mul == 2 && DFG1[i].clock == MUL && res.useMul[0]==false && res.useMul[1]==false ){
				while(DFG1[MulTag].clock!=MUL){
					MulTag++;
				}
				printf("data:%d %d mul setup\n",i,MulTag);
				res.useMul[0] = true;
				res.useMul[1] =true;
				DFG1[MulTag].used=1;
				MulTick++;
				MulTick2++;
			}
			/* 1 multiplier */
			else if(mul == 1 && DFG1[i].clock == MUL && res.useMul[0] == false){
				res.useMul[0] = true;
				printf("data:%d mul setup\n",i);
				MulTick++;
			}
			/* if there is 2 multiplier is using */
			else if(mul == 2 && res.useMul[0]==true && res.useMul[1] == true && MulTick == 1&& MulTick2==1 ){
				MulTick++;
				MulTick2++;
			}
			else if(mul == 1 && res.useMul[0]==true && MulTick == 1 ){
				MulTick++;
			}
			/* Check if end */
			if(plus == 2 && res.usePlus[0]== true && res.usePlus[1]==true && PlusTick==1 && PlusTick==1){
				PlusTick= 0;
				PlusTick2= 0;
				res.usePlus[0] = false;
				res.usePlus[1] = false;
				printf("data:%d plus unsetup\n",i);
				flag=0;
			}
			else if(plus == 1 && res.usePlus[0]== true && PlusTick==1 ){
				PlusTick= 0;
				res.usePlus[0] = false;
				flag=0;
				printf("data:%d plus uninstall\n",i);
			}
			else if(mul == 2 && res.useMul[0] == true && res.useMul[1]==true && MulTick ==2 && MulTick2==2){
				MulTick= 0;
				MulTick2= 0;
				res.useMul[0] = false;
				res.useMul[1] = false;
				printf("data:%d mul uninstall\n",i);
				flag=0;
			}
			else if(mul == 1 && res.useMul[0] == true && MulTick == 2){
				printf("data:%d mul uninstall\n",i);
				MulTick= 0;
				res.useMul[0] = false;
				flag=0;
			}
			printf("Now CLOCK:%d\n",clock);
		}
		flag=1;
		i++;
	}
		
}
