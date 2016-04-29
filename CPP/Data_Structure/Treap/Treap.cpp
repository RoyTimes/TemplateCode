#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

struct Tree
{
    int RadomNumber,KeyValue,NumberCount,Size;
    Tree *SonNode[2];
    Tree(){Size = 1;RadomNumber = rand();SonNode[1] = NULL; SonNode[0] = NULL;}
    
    inline void Maintain(){
        Size = NumberCount;
        if(SonNode[1] != NULL) Size += SonNode[1] -> Size;
        if(SonNode[0] != NULL) Size += SonNode[0] -> Size;
    }
    
    inline int Compare(int x){
        if(x == KeyValue) return -1;
        return x > KeyValue;
    }
}*root;

void Rotate(Tree *& Object , int Direction)
{
    Tree * New = Object -> SonNode[Direction ^ 1];
    Object -> SonNode[Direction ^ 1] = New -> SonNode[Direction];
    New -> SonNode[Direction] = Object;
    Object -> Maintain(), New -> Maintain();
    Object = New;
}


void Insert(Tree *& Object, int Value)
{
    if(Object == NULL){
        Object = new Tree;
        Object -> NumberCount = Object -> Size = 1;
        Object -> KeyValue = Value;
        return;
    }
    int Direction = Object -> Compare(Value);
    if(Direction == -1) Object -> NumberCount++;
    else
    {
        Insert(Object -> SonNode[Direction], Value);
        if(Object -> SonNode[Direction] -> RadomNumber > Object -> RadomNumber)
            Rotate(Object, Direction ^ 1);
    }
    Object -> Maintain();
}

void Delate(Tree *& Object , int DelateObject)
{
    int Direction = Object -> Compare(DelateObject);
    if(Direction != -1) Delate(Object -> SonNode[Direction], DelateObject);
    else
    {
        if(Object -> NumberCount > 1) Object -> NumberCount --;
        else
        {
            if(Object -> SonNode[0] == NULL) Object = Object -> SonNode[1];
            else if(Object -> SonNode[1] == NULL) Object = Object -> SonNode[0];
            else
            {
                int _Direction = (Object -> SonNode[0] -> RadomNumber > 
                					Object -> SonNode[1] -> RadomNumber) ? 1: 0;
                Rotate(Object, _Direction);
                Delate(Object -> SonNode[_Direction], DelateObject);
            }
        }
    }
    if(Object != NULL) Object -> Maintain();
}

int Find(Tree *Object, int Position)//Locate
{
    int Direction = Object -> Compare(Position);
    if(Direction == -1) return Object -> SonNode[0] == NULL ? 0 : Object -> SonNode[0] -> Size;
    if(!Direction) return Find(Object -> SonNode[0], Position);
    return (Object -> SonNode[0] == NULL ? 0 : Object -> SonNode[0] -> Size) + Object -> NumberCount + Find(Object -> SonNode[1],Position);
}
int FindK(Tree * Object, int Num)//K
{
    int temp = 0;
    if(Object -> SonNode[0] != NULL) temp = Object -> SonNode[0] -> Size;
    if(Num <= temp) return FindK(Object -> SonNode[0], Num);
    if(Num > temp + Object -> NumberCount) return FindK(Object -> SonNode[1], Num - temp - Object -> NumberCount);
    return Object -> KeyValue;
}
int FindPre(Tree * Object, int Position, int Best)
{
    if(Object == NULL) return Best;
    if(Object -> KeyValue >= Position) return FindPre(Object -> SonNode[0], Position ,Best);
    return FindPre(Object -> SonNode[1],Position, Object -> KeyValue);
}
int FindNext(Tree * Object, int Position , int Best)
{
    if(Object == NULL) return Best;
    if(Object -> KeyValue > Position) return FindNext(Object -> SonNode[0],Position , Object -> KeyValue);
    return FindNext(Object -> SonNode[1],Position,Best);
}
int main()
{
    srand((unsigned int)time(NULL));
    
    int cas,flag,x; cin>>cas;
    while(cas --)
    {
        scanf("%d%d",&flag,&x);
        if(flag == 1) Insert(root, x);
        else if(flag == 2) Delate(root,x);
        else if(flag == 3) printf("%d\n",Find(root,x) + 1);
        else if(flag == 4) printf("%d\n",FindK(root,x));
        else if(flag == 5) printf("%d\n",FindPre(root,x,0));
        else if(flag == 6) printf("%d\n",FindNext(root,x,0));
    }
    return EXIT_SUCCESS;
}
