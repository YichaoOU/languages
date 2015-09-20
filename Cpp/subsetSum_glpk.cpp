#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Yichao Li
// 9-16-2015 first version
// 9-20-2015 final version
// MiLP for subset sum
// ref: 
// GLPK Doc PDF
// Slide Leture 6/7
// usage:
// g++ -c test.cpp 
// g++ test.o -lglpk -lm 
// ./a.out t1.dat > t1.out

void MiLP_subset_solver(vector<int> a,int t,int l){
	glp_term_out(GLP_OFF);
	int i;
	glp_prob *lp;
	int ia[l+1];
	int ja[l+1];
	double ar[l+1];
	lp = glp_create_prob();
	glp_set_prob_name(lp, "subset sum");
	glp_set_obj_dir(lp, GLP_MAX);
	glp_add_rows(lp, 1);
	glp_set_row_name(lp, 1, "target");
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, t);
	glp_add_cols(lp, l);
	for (i=1;i<=l;i++){
		glp_set_col_bnds( lp, i, GLP_DB, 0.0, 1.0);
		glp_set_obj_coef(lp, i, a[i-1]);
		glp_set_col_kind(lp,i,GLP_BV);
		ia[i]=1;
		ja[i]=i;
		ar[i]=a[i-1];
	}
	glp_load_matrix(lp, l, ia, ja, ar);
	glp_iocp parm;
	glp_init_iocp(&parm);
	parm.presolve = GLP_ON;
	parm.msg_lev = GLP_MSG_OFF;
	int err = glp_intopt(lp,&parm);
	// printf("\nerr = %d",err);
	// glp_simplex(lp,NULL);
	int z = glp_mip_obj_val(lp);
	// printf("\nz = %d\n",z);
	// double q = glp_mip_row_val(lp,1);
	// printf("\nq = %g\n",q);
	if(z == t){
		printf("\nThere is a solution:\n");
		for (i=1;i<=l;i++){
			int temp = glp_mip_col_val(lp,i); 
			if (temp == 1){
				cout << a[i-1] << endl;
			}
		
		}
	}
	else{
		printf("\nThere is NO solution\n");
	}
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
	
	MiLP_subset_solver(a,t,s);
	
	
	return 0;
}
