#include<iostream>//no math library!!!
using namespace std;
long double sqrt1(double num,int n=2,int precision=10,long double decimal=1,long double root=0){
	int a=num;
	long double b=1;
	if(decimal<1){
		a=10;
	}//a is num when you are gettig the integer root, but any decimal places, then a is 10
	for(long double i=0;i<a;i+=decimal){//.1  .2  .3  ....
		for(int j=0;j<n;j++){
			b*=(root+i);//root is the lastsquare root we got, muplity b by the root plus a possible next point
		}
		if(b>num){//if when we multiply it, its too big, break out of the loop
			root+=i-decimal;
			break;
		}
		if(b==num){
			return(root+i);
		}
		b=1;
	}
	decimal/=10;
	precision--;
	if(precision!=-1){
		return(sqrt1(num,n,precision,decimal,root));//get the next digit of the number recursively
	}
	return(root);
}
int main(){
	long double a;
	int n;
	cout<<"What number would you like the nth root of?";
	cin>>a;
	cout<<"What is n?";
	cin>>n;
	cout<<"The "<<n<<"th root of "<<a<<" is "<<sqrt1(a,n)<<endl;
}