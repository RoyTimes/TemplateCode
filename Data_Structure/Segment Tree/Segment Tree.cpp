#ifdef _MSC_VER
#define DEBUG
#endif

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100000
#define lson l , mid , root << 1
#define rson mid + 1 , r , root << 1 | 1
using namespace std;
int n,m;

inline int ls(int x){return x << 1;}
inline int rs(int x){return x << 1 | 1;}

long long a[N << 2],col[N << 2];


inline void PushUp(int x){a[x] = a[rs(x)] + a[ls(x)];}
/*
inline void PushUp_Add(int x){a[x] = a[ls(x)] + a[rs(x)];}
inline void PushUp_Modify(int x){a[x] = max(a[ls(s)],a[rs(s));}*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////LAZY标记///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void PushDown_Add(int root, int m)//递增版本
{
    if(col[root])
    {
        col[ls(root)] += col[root];
        col[rs(root)] += col[root];
        a[ls(root)] += (m - (m >> 1)) * col[root];
        a[rs(root)] += (m >> 1) * col[root];
        col[root] = 0;
    }
}
void PushDown_Modify(int root, int m)//修改版本
{
    if(col[root])
    {
        col[ls(root)] += col[root];
        col[rs(root)] += col[root];
        a[ls(root)] += (m - (m >> 1)) * col[root];
        a[rs(root)] += (m >> 1) * col[root];
        col[root] = 0;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////构建///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void LeafNode(int root)
{
    //a[root] = 1;
    scanf("%lld",&a[root]);
}
////////////////////////////////
void Build_Points(int l,int r,int root) //AC
{
    if(l == r) {LeafNode(root);return;}
    int mid = (r + l) >> 1;
    Build_Points(lson),Build_Points(rson),PushUp(root);
}
void Build_Seg(int l,int r,int root)//AC
{
    col[root] = 0;
    if(l == r){LeafNode(root);return;}
    int mid = (r + l) >> 1;
    Build_Seg(lson),Build_Seg(rson),PushUp(root);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////更新操作////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Update_Seg_Modify(int x, int y, int weight,int l,int r,int root) //AC
{
    if(x <= l && r <= y){
        col[root] = weight;
        a[root] = weight * (r - l + 1);
        return;
    }
    PushDown_Modify(root, r - l + 1);
    int mid = (l + r) >> 1;
    if(x <= mid) Update_Seg_Modify(x,y,weight,lson);
    if(y > mid) Update_Seg_Modify(x,y,weight,rson);
    PushUp(root);
}
void Update_Seg_Add(int x, int y, int Val, int l, int r, int root) //AC
{
    if(x <= l && r <= y){
        col[root] += Val;
        a[root] += (long long)Val * (r - l + 1);
        return;
    }
    PushDown_Add(root, r - l + 1);
    int mid = (l + r) >> 1;
    if(x <= mid) Update_Seg_Add(x,y,Val,lson);
    if(y > mid) Update_Seg_Add(x,y,Val,rson);
    PushUp(root);
}
///////////////////////////////////////////////////////////
void Update_Points_Modify(int pos,int Val,int l,int r,int root) //AC
{
    if(r == l){a[root] = Val;return;}
    int mid = (r + l) >> 1;
    if(pos <= mid) Update_Points_Modify(pos, Val, lson);
    else Update_Points_Modify(pos,Val,rson);
    PushUp(root);
}
void Update_Points_Add(int pos, int Val, int l, int r, int root)
{
    if(l == r){a[root] += Val;return;}
    int mid = (l + r) >> 1;
    if(pos <= mid) Update_Points_Add(pos,Val,lson);
    else Update_Points_Add(pos,Val,rson);
    PushUp(root);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////查询///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
int Ask_Max_Points(int x, int y, int l, int r, int root) //AC
{
    if(x <= l && r <= y) return a[root];
    int mid = (l + r) >> 1,ans = 0;
    if(x <= mid) ans = max(ans, Ask_Max_Points(x,y,lson));
    if(y > mid) ans = max(ans, Ask_Max_Points(x,y,rson));
    return ans;
}
int Ask_Sum_Points(int x, int y, int l, int r, int root)
{
    if(x <= l && r <= y) return a[root];
    int mid = (l + r) >> 1, ans = 0;
    if(x <= mid) ans += Ask_Sum_Points(x,y,lson);
    if(y > mid) ans += Ask_Sum_Points(x,y,rson);
}
//////////////////////////////////////////////////////修改版本 区间询问
int Ask_Max_Seg_Modify(int x, int y, int l, int r, int root) //AC
{
    if(x <= l && r <= y) return a[root];
    PushDown_Modify(root, r - l + 1);
    int mid = (l + r) >> 1,ans = 0;
    if(x <= mid) ans = max(ans, Ask_Max_Seg_Modify(x,y,lson));
    if(y > mid) ans = max(ans, Ask_Max_Seg_Modify(x,y,rson));
    return ans;
}
int Sum_seg(int x, int y, int l, int r, int root)
{
    if(x <= l && r <= y) return a[root];
    PushDown(root, r - l + 1);
    int mid = (l + r) >> 1;
    unsigned int ans = 0;
    if(x <= mid) ans += Sum_seg(x,y,lson);
    if(y > mid) ans += Sum_seg(x,y,rson);
    return ans;
}
////////////////////////////////////////////////////// 递增版本 区间查询
int Ask_Max_Seg_Add(int x, int y, int l, int r, int root) //AC
{
    if(x <= l && r <= y) return a[root];
    PushDown_Add(root, r - l + 1);
    int mid = (l + r) >> 1,ans = 0;
    if(x <= mid) ans = max(ans, Ask_Max_Seg_Add(x,y,lson));
    if(y > mid) ans = max(ans, Ask_Max_Seg_Add(x,y,rson));
    return ans;
}
long long Ask_Sum_Seg_Add(int x, int y, int l, int r, int root)//AC
{
    if(x <= l && r <= y) return a[root];
    PushDown_Add(root, r - l + 1);
    int mid = (l + r) >> 1;
    long long ans = 0;
    if(x <= mid) ans += Ask_Sum_Seg_Add(x,y,lson);
    if(y > mid) ans += Ask_Sum_Seg_Add(x,y,rson);
    return ans;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
#ifdef DEBUG
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif

    int n,q; cin>>n>>q;
	Build_Seg(1,n,1);
	for (int i = 0; i < q; i ++)
	{

	}
    return 0;
}
