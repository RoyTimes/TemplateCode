#ifdef _MSC_VER  
#define DEBUG  
#endif  

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)  
{ 
#ifdef DEBUG    
  freopen("../stdin.txt","r",stdin);  
  freopen("../stdout.txt","w",stdout);   
#endif    
  return 0;  
}  
