#include <iostream>
using namespace std;

void printMatrix(double** matrix, const int& n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= n; j++){
			cout << matrix[i][j];
			if(j == n-1)	cout << " : ";
			else cout << " ";
		}
		cout << endl;
	}
}

void solve(double** matrix, const int& n);

int main(){
	int n;
	cout << "Enter number of variables: ";
	cin >> n;
	
	char coeff = 'C';
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cout << coeff << i << j << "x" << j;
			if(j != n)	cout << " + ";
			else	cout << " = D" << i;
		}
		cout << endl;
	}

	//We will need n(n+1) number of variables dynamically allocated
	
	//Dynamically created n by n+1 matrix
	double** constants = new double*[n];
	for(int i = 0; i < n; i++){
		constants[i] = new double[n+1];
	}

	//Now take the values of the constants from user input
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= n; j++){
			if(j != n)	cout << coeff << i+1 << j+1 << " = ";
			else cout << "D" << i+1 << " = ";
			cin >> constants[i][j];
		}
	}
	cout << endl;
	//printMatrix(constants, n);
	solve(constants, n);
	
	//now dynamically allocate memory for the n variables
	double* solution = new double[n];	//stores the final solution
	for(int i = n-1; i >= 0; i--){
		double sum = 0;
		for(int j = i+1; j < n; j++){
			sum += constants[i][j]*solution[j];
		}
		solution[i] = (constants[i][n] - sum)/constants[i][i];
	}

	
	//print the final solution
	cout << "(";
	for(int i = 0; i < n; i++){
		cout << solution[i];
		if(i != n-1)	cout << ", ";
	}
	cout << ")\n";
}

void solve(double** constants, const int& n){
	int it = 1;
	for(int i = 0; i < n-1; i++){	//controls the pivot element
		double pivot = constants[i][i];
		//cout << "pivot = " << pivot << endl << endl;
		for(int j = i+1; j < n; j++){	//for the rows below pivot's row
			double num = constants[j][i];
			for(int k = i; k < n+1; k++){	//for the columns in those rows
				//cout << "(" << i << ", " << j << ", " << k << ")";
				//cout << "Transformation: ";
				//cout << "constants[" << j << "][" << k << "] -= " << num << " / " << pivot << " * " << constants[i][k] << endl;
				constants[j][k] -= num/pivot * constants[i][k];
				//printMatrix(constants, n);
				//cout << endl;
			}
		}
	}
	
	//Final matrix
	cout << "Final Matrix\n";
	printMatrix(constants, n);
}
