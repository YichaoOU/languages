#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
// Yichao Li
// 9-16-2015 first version
// 9-20-2015 final version
// Dynamic programming for subset sum
// ref:
// http://www.geeksforgeeks.org/dynamic-programming-subset-sum-problem/
// Slide Leture 3a
// usage:
// g++ subsetSum.cpp
// ./a.out t1.dat > t1.out

bool DPSS(vector<int> a, int t, int l){
	int i;
	int j;
	bool **c = new bool*[l+1];
	for (i = 0;i<=l;i++){
		c[i] = new bool[t+1];
	}
	// bool c[l+1][t+1]; 
	// The above code has a segmentation fault
	
	
	// first column, where t = 0, so they should be true
	for (i = 1; i<=l; i++){
		c[i][0]=true;
	}
	// first row, where a is empty, so they should be false
	for (j = 0; j<=t; j++){
		c[0][j]=false;
	}
	// This seems to be redundent, implemented according to the pseudocode in slides
	for (j=1;j<=t;j++){
		if (j == a[0]){
			c[1][j]=true;
		}
		else{
			c[1][j]=false;
		}
	}
	// main code here, implemented according to the pseudocode in slides
	for (i = 2; i<=l; i++){
		for (j=1;j<=t;j++){
			if ((j-a[i-1])<0){
				c[i][j]=c[i-1][j];
			}
			else{
				c[i][j]= c[i-1][j] || c[i-1][j-a[i-1]];
			}
		}
	}
	
	// back trace the solution
    if(c[l][t]){
		printf("\nThere is a solution:\n");

		i=l;
		j=t;
		while (i>0){
			while(j>0){
				if(c[i][j] == true &&  c[i-1][j] == false){
					cout << a[i-1] << endl;
					j=j-a[i-1];
				}
				i--;
				
			}
			i--;
		}
    }
	else{
		printf("\nThere is NO solution\n");
	}
	

	
	return c[l][t];
}

int main(int argc, char* argv[])
{
	// array for set of integers
	vector<int> a;
	// file input
	ifstream file(argv[1]);
	// prepare reading file
	int num;
	string line;
	// read the first line, target value
	getline(file,line);
	istringstream tmp(line);
	tmp >> num;
	int t = num;
	
	cout << "Target = " << t << endl;
	cout << "Set = " << endl;
	
	// read the second line, array
	getline(file,line);
	istringstream tmp1(line);
	while(tmp1 >> num){
		a.push_back(num);
		
	}
	
	int s = a.size();
	// outupt array
    for(int i = 0;i < s;i++)
    {
    	cout << a[i] << " ";
   	}
	
	// DPSS requires 3 paras:
	// the list of integers, the target value, the size of the list
	DPSS(a,t,s);
	return 0;
	
}


