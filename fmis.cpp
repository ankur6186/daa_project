#include<iostream>
#include<chrono>
#include<stdlib.h>
#include<time.h>
#define nov 6

using namespace std;
using namespace std::chrono;

float density = 0.3;
int noe = 3;

int Graph[nov][nov];
bool Visit[nov];
int Max_Ind_Set[nov]={-1};
int Ind_Set[nov]={-1};
int G[nov]={-1};
int size1;
int max_size=0;
int G1[nov]={-1};

void Generate_Random_Graph()
{
	int a,b;
	for(int i=0;i<nov;i++)
	{
		Visit[i] = false;
		for(int j=0;j<nov;j++)
			Graph[i][j]=0;
	}
	Graph[0][1] = 1;
	Graph[1][0] = 1;
	Graph[2][3] = 1;
	Graph[3][2] = 1;
	Graph[4][5] = 1;
	Graph[5][4] = 1;
}

int Degree()
{
	int deg = 0;
	for(int i=0;i<nov;i++)
	{
		if(deg>0)
			break;
		if(Visit[i]!=false)
			continue;
		for(int j=0;j<nov;j++)
		{
			if(Graph[i][j]==1 and Visit[j]==false)
				deg++;
			if(deg>0)
				break;
		}
	}
	return deg;
}

int Select()
{
	int max1,max2=0,r=0;
	for(int i=0;i<nov;i++)
	{
		max1=0;
		if(Visit[i]!=false)
			continue;
		for(int j=0;j<nov;j++)
			if(Graph[i][j]==1 and Visit[j]==false)
				max1++;
		if(max1>max2)
		{
			r=i;
			max2=max1;
		}
	}
	return r;
}

void Conflict()
{
	int c=0,del=0,rm,J=0;
	for(int i=0;i<size1;i++)
	{
		c = 0;
		for(int j=0;j<size1;j++)
		{
			if(Graph[Ind_Set[i]][Ind_Set[j]]==1)
				c++;
			if(c > del)
			{
				del = c;
				rm = Ind_Set[i];
			}
		}
		if(del > 0)
		{
			size1--;
			J=0;
			for(int i=0;i<nov;i++)
			{
				if(rm!=Ind_Set[i] and J<size1)
					G1[J++] = Ind_Set[i];
			}
			for(int i=0;i<J;i++)
				Ind_Set[i] = G1[i];
			size1 = J;
			Conflict();
		}
	}
}

void Gen()
{
	int v,counter=0,x=0;
	if(Degree()==0)
	{
		for(int i=0;i<nov;i++)
		{
			if(Visit[i]==false)
				counter++;
		}
		if(counter>max_size)
		{
			for(int i=0;i<nov;i++)
			{
				if(Visit[i]==false)
				{
					Max_Ind_Set[x++]=i;
					max_size = x;
					size1 = x;
				}
			}
		}
	}
	else
	{
		v = Select();
		size1 = 0;
		for(int i=0;i<nov;i++)
		{
			if(Graph[v][i]==0 and Visit[i]!=true)
				Ind_Set[size1++] = i;
		}
		if(size1>2 and size1>max_size)
		{
			cout<<max_size<<" "<<size1<<"\n";
			Conflict();
		}
		if(size1>max_size)
		{
			max_size = size1;
			for(int i=0;i<max_size;i++)
				Max_Ind_Set[i] = Ind_Set[i];
		}
		Visit[v] = true;
		Gen();
	}
}

int main()
{
	Generate_Random_Graph();
	for(int i=0;i<nov;i++)
	{
		for(int j=0;j<nov;j++)
			cout<<Graph[i][j]<<" ";
		cout<<"\n";
	}

	auto start = high_resolution_clock::now();
	Gen();	

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout<<"Time taken: "<<duration.count()<<"\n";
	for(int i=0;i<max_size;i++)
		cout<<Max_Ind_Set[i]<<" ";
	cout<<"\n";
	return 0;
}