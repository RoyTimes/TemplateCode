namespace Splay_Tree
{
template<typename _Tp> class splay_node;
template<typename _Tp> class splay_tree;
template<typename _Tp>
class splay_node
{
private:
    _Tp val;
    int cnt, size;
    splay_node<_Tp> *son[2], *par;

public:
    friend class splay_tree<_Tp>;

    splay_node()
        : val(), cnt(), size(), son(), par() { }

    splay_node(const _Tp &_v, int _c = 0)
        : val(_v), cnt(_c), size(_c), son(), par() { }

    inline void add(int x){
        cnt += x, size += x;
    }
    inline void makeleaf(splay_node<_Tp> *x){
        son[0] = son[1] = x;
    }
    inline int check(){
        return par -> son[1] == this;
    }
    inline void combine(splay_node<_Tp> *x, int d){
        son[d] = x;
        x->par = this;
    }
    inline void pushup(){
        size = son[0]->size + son[1]->size + cnt;
    }
};

template<typename _Tp>
class splay_tree
{
private:
    typedef splay_node<_Tp> node;
    typedef splay_tree<_Tp> tree;
    node *nil, *root;

public:
    splay_tree() { }

    splay_tree(const _Tp &mint, const _Tp &maxt)
        : nil(), root()
    {
        nil = new node();
        root = new node(mint, 1);
        root->par = nil;
        root->makeleaf(nil);
        root->combine(new node(maxt, 1), 1);
        root->son[1]->makeleaf(nil);
        root->pushup();
    }

    ~splay_tree()
    {
        clear(root);
        delete nil;
    }

    inline int size()
    {
        return root->size - 2;
    }

    inline int count()
    {
        return root->cnt;
    }

    inline node *end()
    {
        return nil;
    }

    inline _Tp rank(int x)
    {
        splay(rank(root, x + 1), nil);
        return root->val;
    }

    inline int find(const _Tp &x)
    {
        splay(find(root, x), nil);
        return root->son[0]->size;
    }

    inline int count(const _Tp &x)
    {
        splay(find(root, x), nil);
        return root->son[0]->cnt;
    }

    inline _Tp prec(const _Tp &x)
    {
        splay(prec(root, x), nil);
        return root->val;
    }

    inline _Tp succ(const _Tp &x)
    {
        splay(succ(root, x), nil);
        return root->val;
    }

    inline bool empty()
    {
        return root->size <= 2;
    }

    inline void clear()
    {
        clear(1, size());
    }

    inline void clear(int l, int r)
    {
        clear(getseg(l + 1, r + 1));
        root->son[1]->son[0] = nil;
        root->son[1]->pushup();
        root->pushup();
    }

    void clear(node *x)
    {
        if (x == nil) return;
        clear(x->son[0]);
        clear(x->son[1]);
        delete x;
    }

    inline void rotate(node *x)
    {
        node *k = x->par;
        int d = !x->check();
        k->combine(x->son[d], d ^ 1);
        k->par->combine(x, k->check());
        x->combine(k, d);
        k->pushup(); x->pushup();
    }

    inline void splay(node *x, node *aim)
    {
        while (x->par != aim)
        {
            if (x->par->par != aim)
                x->check()^x->par->check() ?
                rotate(x) : rotate(x->par);
            rotate(x);
        }
        if (aim == nil) root = x;
    }

    node *rank(node *x, int k)
    {
        if (x == nil) return x;
        if (k <= x->son[0]->size)
            return rank(x->son[0], k);
        k -= x->son[0]->size;
        if (k <= x->cnt) return x;
        return rank(x->son[1], k - x->cnt);
    }

    node *find(node *x, const _Tp &k)
    {
        if (x == nil) return x;
        if (k < x->val)
            return find(x->son[0], k);
        if (x->val < k)
            return find(x->son[1], k);
        return x;
    }

    node *prec(node *x, const _Tp &k)
    {
        if (x == nil) return x;
        int d = k <= x->val ? 0 : 1;
        if (!d) return prec(x->son[0], k);
        node *re = prec(x->son[1], k);
        return re == nil ? x : re;
    }

    node *succ(node *x, const _Tp &k)
    {
        if (x == nil) return x;
        int d = k < x->val ? 0 : 1;
        if (d) return succ(x->son[1], k);
        node *re = succ(x->son[0], k);
        return re == nil ? x : re;
    }

    inline node *getseg(int l, int r)
    {
        splay(rank(root, l - 1), nil);
        splay(rank(root, r + 1), root);
        return root->son[1]->son[0];
    }

    inline void insert(const _Tp &t, int c = 1)
    {
        node *temp = find(root, t);
        if (temp != nil)
        {
            splay(temp, nil), temp->add(c);
            return;
        }
        splay(prec(root, t), nil);
        splay(succ(root, t), root);
        root->son[1]->combine(new node(t, c), 0);
        root->son[1]->son[0]->makeleaf(nil);
        root->son[1]->pushup();
        root->pushup();
    }

    inline void insert(tree &t)
    {
        t.rank(0);
        while (t.root->son[1] != t.end())
        {
            t.succ(t.root->val);
            insert(t.root->val, t.count());
        }
    }

    inline void erase(const _Tp &t, int c = 1)
    {
        node *temp = find(root, t);
        if (temp != nil)
        {
            splay(temp, nil);
            if (temp->cnt <= c)
                clear(root->son[0]->size, root->son[0]->size);
            else temp->add(-c);
            root->son[1]->pushup();
            root->pushup();
        }
    }

    friend ostream &operator << (ostream &out, splay_tree &x)
    {
        out << '{';
        for (int i = 1; i <= x.size(); i += x.count())
            out << '(' << x.rank(i) << ',', out << x.count() << ')';
        out << '}';
        return out;
    }
};
}
