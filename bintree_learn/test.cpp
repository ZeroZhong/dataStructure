#include "BinTree_c++.h"
#include <string>
#include <iostream>
using namespace shitong;
using std::string;

void restore(BinTree<char> &B, char *&pre, char *in, int n, int LorR, BinNodePosi(char) p = nullptr)
{
    if (n < 1)
    {
        p = p->parent;
        pre--;
        return;
    }
    int i = 0;
    while (in[i] != pre[0] && i < n)
        i++;
    if (B.empty())
    {
        cout << "root:" << pre[0] << endl;
        p = B.InsertAsRoot(pre[0]);
    }
    else if (LorR)
    {
        cout << p->data << "->left:" << pre[0] << endl;
        p = B.InsertAsLC(p, pre[0]);
    }
    else
    {
        cout << p->data << "->right:" << pre[0] << endl;
        p = B.InsertAsRC(p, pre[0]);
    }
    // if (!(i || n - 1))
    // {
    //     p = p->parent;
    //     pre--;
    // }
    // ++pre;
    restore(B, ++pre, in, i, 1, p);
    // ++pre;
    restore(B, ++pre, in + i + 1, n - i - 1, 0, p);
}

int main()
{
    BinTree<char> BT;
    //string S;
    char Spre[100];
    char Sin[100];
    int n;
    cout << "input n:";
    cin >> n;
    cout << "/r/ninput CHAR pre(<100):";
    cin >> Spre;
    cout << "/r/ninput CHAR in(<100):";
    cin >> Sin;
    cout << endl;
    // n = 8;
    char *SprePointer = Spre;
    restore(BT, SprePointer, Sin, n, 1);
    cout << "height:" << stature(BT.root()) << endl;
}