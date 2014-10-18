#include<random>
#include<iostream>
#include<time.h>
#include<cmath>
#include<iomanip>
#include<vector>
#include<ppl.h>
//#include<algorithm>
using namespace std;
using namespace concurrency;


bool isPrime(unsigned long long num);
void main(){
	random_device generator;
	unsigned long long p,q;
	uniform_real_distribution<> dist(pow(2, 30), pow(2, 32)+1);
	cout << setprecision(20);
	
	while (true){
		if (isPrime(p = floor(dist(generator))))
			break;
	}

	while (true){
		if (isPrime(q = floor(dist(generator))))
			if (q != p)
			break;
	}

	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	unsigned long long n = p * q;
	cout << "n = p x q = " << n << endl;
	unsigned long long phi_n = (p - 1)*(q - 1);
	cout << "Phi(" << n << ") = " << phi_n << endl;
}

bool isPrime(unsigned long long  num){
	for (unsigned long long i = 2; i < num; i++){
		if (num % i == 0)
			return false;
	}
	return true;
}