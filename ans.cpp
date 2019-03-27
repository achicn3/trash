#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
using namespace std;

int a[16]={-1};
int nand(int x,int y){
	return x&y ? 0 : 1;
}
int nor(int x,int y){
	return x|y ? 0 : 1;
}
int inv(int x){
	return x == 1 ? 0 : 1;
}
int circuit(int A3,int A2,int A1,int A0){
	int n1 = nand(A3,A2);
	int n2= inv(A1);
	int n3 = nor(n2,A0);
	int y= nand(n1,n3);
	return y;
}
int* trans(int x){
	int *binary = new int[4];
	fill(binary,binary+4,0);
	int index=0;
	for(int i=x;i;i>>=1)
			binary[index++]= (i&1)? 1 : 0;
	return binary;
}
int* getPos(int k,int pos){
	int *binary = trans(k);
	binary[pos] = inv(binary[pos]);
	return binary;
}
int getPos(int A3,int A2,int A1,int A0){
	return pow(A3,3)+pow(A2,2)+pow(A1,1)+A0;
}
int main(){
	int index=0;
	char temp[4];
	vector<string> ans;
	for(int i=0;i<=1;i++){
		for(int j=0;j<=1;j++){
			for(int k=0;k<=1;k++){
				for(int z=0;z<=1;z++)
					a[index++] = inv(circuit(i,j,k,z));
			}
		}
	}
	index=0;
	/*if(a[getPos(0,1,1,0)]==circuit(0,1,0,0))
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;*/
	for(int i=0;i<16;i++){
		int *binary = trans(i);
		cout<<"now:"<<binary[3]<<binary[2]<<binary[1]<<binary[0]<<endl;
		for(int j=0;j<4;j++){
			int *tempBinary=getPos(i,j);
			if(circuit(binary[3],binary[2],binary[1],binary[0]) 
				== a[getPos(tempBinary[3],tempBinary[2],tempBinary[1],tempBinary[0])]){
				sprintf(temp,"%d%d%d%d",binary[3],binary[2],binary[1],binary[0]);
				cout<<"reverse:"<<tempBinary[3]<<tempBinary[2]<<tempBinary[1]<<tempBinary[0]<<endl;
				ans.push_back(string(temp));
			}
		}
	}
	sort( ans.begin(), ans.end() );
	ans.erase( unique( ans.begin(), ans.end() ), ans.end() );
	for(auto &i:ans){
		index++;
		cout<<i<<endl;
	}
	cout<<"total:"<<index<<endl;
} 
