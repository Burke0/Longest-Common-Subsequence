/*
 * LCS.cpp
 * J. Alex Burke 
 * 11/15/21
 */


#include <bits/stdc++.h>


using namespace std;
/*
 * This bottom-up dynamic programming algorithm calculates the value of the longest common subsequence by walking
 * through both strings and filling a 2d array LCS acting as a table structure. The table LCS is iteratively filled and
 * the bottom right corner is the solution which is returned.
 */
int LCSBottomUp(char* firstString, char* secondString, int firstLength, int secondLength)
{
	//first row and column initialized to all 0's to act as the base case.
	int LCS[firstLength+1][secondLength+1];
	for(int i=0; i<=firstLength; i++)
		LCS[i][0]=0;
	for(int j=0; j<secondLength; j++)
		LCS[0][j]=0;

	for(int i= 1; i<=firstLength; i++)
		for(int j = 1; j<=secondLength; j++)
		{
			if(firstString[i-1] == secondString[j-1])
				LCS[i][j] = 1+LCS[i-1][j-1];
			else
				LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1]);
		}
	return LCS[firstLength][secondLength];

}
/*
 * This function calculates the longest common subsequence of two strings using a top down memoization approach.
 * Solutions to the sub-problems of the algorithm are stored in a 2d vector array.
 * So, before a subproblem is recalculated, it checks to see if its solution is already stored in the extra memory.
 * Input: The two strings, their lengths x and y and
 *        IMPORTANT: a 2d vector of integers with all values initialized to -1.
 *        -1 is used as a flag to state nothing has been stored yet.
 */
int LCSTopDown(char* firstString, char* secondString, int x, int y, vector<vector<int>> &LCS )
{

	//base case
	if(x==0||y==0)
		return 0;
	if(LCS[x][y]<0)
	{
		if(firstString[x-1] == secondString[y-1])
			LCS[x][y] = 1 + LCSTopDown(firstString,secondString, x-1, y-1, LCS);
		else
			LCS[x][y] = max(LCSTopDown(firstString, secondString, x, y-1,LCS), LCSTopDown(firstString, secondString, x-1, y,LCS));
	}
	return LCS[x][y];

}

/*
* takes command line arguments for <InputFile> <-b|-t>
* input file format: second and third lines are two strings to be used.
* -b|-t chooses algorithm bottom up or top down approach.
*/
int main(int argc, char** argv)
{

	string inFile, bottomUpOrTopDown, temp, str1, str2;
	double time_taken;
	int LCS, str1len, str2len;

	if( argc == 3)
	{
		inFile= argv[1];
		bottomUpOrTopDown=argv[2];
	}
	else
	{
		cout<< "Usage: ./cppfile <InputFile> <-b|-t>"<<endl;
		return 1;
	}

	if(bottomUpOrTopDown=="-b")
		cout<<"Algorithm choice: Bottom Up"<<endl;
	else if(bottomUpOrTopDown=="-t")
		cout<<"Algorithm Choice: Top Down"<<endl;

	//load file and store data in str1 and str2
	ifstream file;
	file.open(inFile);
	getline(file, temp);
	getline(file,str1);
	getline(file,str2);

	str1len=str1.length();
	str2len=str2.length();

	//walks through varied sequence lengths from 100 to 1000 in increments of 100.
	for(int i=99; i<min(str1len, str2len); i+=100)
	{
		char* first	= new char[i+2] ;
		char* second= new char[i+2] ;
		// copy's over the shortened sequence into temporary char arrays.
		for( int j= 0; j<=i; j++)
		{
			first[j]=str1[j];
			second[j]=str2[j];
		}
		//Null terminator to prevent strange output
		first[i+1]='\0';
		second[i+1]='\0';
		auto start=chrono::high_resolution_clock::now();
		if(bottomUpOrTopDown=="-b")
			LCS=LCSBottomUp(first,second, i, i);
		else if(bottomUpOrTopDown=="-t")
		{
			// 2d vector of integers initialized to -1 to store values in.
			//required for top down function to work properly
			vector<vector<int>> LCSTable(i+1,vector<int>(i+1,-1));
			LCS=LCSTopDown(first,second, i, i, LCSTable);
		}
		else
			cerr<<"something went wrong"<<endl;
		auto end=chrono::high_resolution_clock::now();
		time_taken=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
		time_taken *= 1e-9;

		cout<<"String length: "<<i+1<<endl;
		cout<<first<<"\n"<<second<<endl;
		cout<<"LCS: "<<LCS<<" time taken:"<<fixed<<setprecision(6)<<time_taken<<" sec \n" << endl;

		//free up mem
		delete [] first;
		delete [] second;

	}


	return 0;

}
