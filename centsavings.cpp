#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int infinity = 100000000; //Max sum is 2,000*10,000 = 20,000,000

int round(int n){
	int remainder = n % 10;
	if (remainder >= 5){
		return n + (10-remainder);
	} else {
		return n - remainder;
	}
}


int main() {
	int a, b;	//# Purchases / # Dividers
	cin >> a >> b;
	vector<int> items(a);

	for(int i = 0; i < a; i++){
		int j;
		cin >> j;
		items[i] = j;
	}

	//Debug: check inputs
	/*
        cout<< "A,B: " << a << ' ' << b << endl;
        cout <<"Vector: ";
        for(size_t j = 0; j<items.size(); j++){
                cout<< items[j] << ' ';
        }
        cout << endl;
	*/


	//Build dp. Items are columns, dividers are rows
	vector<vector<int>> dp;
	dp.resize(b+1);
	for (int i = 0; i <= b; i++){
		dp[i] = vector<int>(a+1, infinity);
	}

	//Zero fill left column
	for (size_t i = 0; i < dp.size(); i++){
		dp[i][0] = 0;
	}
	//Calculate sums for top row
        for (size_t i = 1; i < dp[0].size(); i++){
                dp[0][i] = items[i-1] + dp[0][i-1];
        }

	//Fill table
	for (size_t i = 1; i < dp[0].size(); i++){
		for (size_t j = 1; j < dp.size(); j++){
			dp[j][i] = min(dp[j][i-1] + items[i-1], round(dp[j-1][i-1] + items[i-1]));
		}
	}


	//Debug: Check dp table
	/*
	cout << endl << "DP Table:" << endl;
    	for (size_t i = 0; i < dp.size(); ++i){
        	for (size_t j = 0; j < dp[i].size(); ++j){
            		cout << dp[i][j] << " ";
        	}
        cout << endl;
    	}
	*/

	int answer = infinity;
	for (int i = 0; i <= b; i++){
		answer = min(answer,round(dp[i][a]));
	}
	cout << answer << endl;



}
