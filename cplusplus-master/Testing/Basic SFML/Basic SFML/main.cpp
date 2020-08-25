//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include "ResourcePath.hpp"
//
//using namespace std;
//using namespace sf;
//
//int main() {
//
//}
#include <iostream>
#include <vector>

using namespace std;

vector<int> quicksort(vector<int>);

int main(){
    vector<int> a = {1,8,3,9,4,5,7};
   vector<int> b = quicksort(a);
    for(int i =0;i<b.size();i++){
        cout<<b[i]<<", ";
    }
    return 0;
}

vector<int> quicksort(vector<int> a) {
    vector<int> b;
    vector<int> c;
   
    if(a.size()>1){
    for(int i = 0; i < a.size()-1; i++){
       if (a[i]<= a[a.size()-1]){
           b.push_back(a[i]);
       } else {
           c.push_back(a[i]);
       }
   }
        vector<int> de;
    vector<int> e = quicksort(c);
    vector<int> d = quicksort(b);
    for(int i=0;i<d.size();i++){
        de.push_back(d[i]);
    }
    de.push_back(a[a.size()-1]);
    for(int i=0;i<e.size();i++){
        de.push_back(e[i]);
    }
    return de;
    }else{
        return a;
    }
}
