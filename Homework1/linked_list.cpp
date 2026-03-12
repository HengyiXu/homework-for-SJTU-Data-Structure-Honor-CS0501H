/*
输入：
先输入第一个多项式的项数 n，再输入 n 组系数和指数；
再输入第二个多项式的项数 m，再输入 m 组系数和指数。
已知输入时各项按指数从小到大排列。

处理：
采用单链表存储多项式，使用头插法建表；
将两个多项式合并求和，并对结果链表进行逆置。

输出：
输出第一个多项式；
输出第二个多项式；
输出两个多项式相加后的结果。

目的：
练习链表的头插法、合并和逆置操作。
*/


#include<bits/stdc++.h>
using namespace std;

class LinkNode {
    public:
        double coefficient;
        int exponent;
        LinkNode* next;

    
        LinkNode(double coe = 0, int exp = 0) {
            coefficient = coe, exponent = exp;
            next = nullptr;
        }

};

class Link {
    public:
        LinkNode* head;
        Link() {
            head = new LinkNode();
        }

        ~Link() {
            LinkNode* current = head;
            while(current != nullptr) {
                LinkNode* temp = current;
                current = current->next;
                delete temp; 
            }
        }

        void AddLinkNode(double coe, int exp) {
            LinkNode* p = new LinkNode(coe, exp);
            p->next = head->next;
            head->next = p;
        }

        void PrintLink() {
            if(head->next == nullptr) return;
            LinkNode* current = head->next;
            cout << current->coefficient << "x^"<< current->exponent;

            while(current->next != nullptr) {
                current = current->next;
                char op = (current->coefficient < 0 ? '-' : '+'); 
                cout <<" "<< op << " "<<fabs(current->coefficient) << "x^"<< current->exponent;
            }
            cout <<endl;
        }
};
void LinkMerge(const Link& Link1, const Link& Link2, Link& Linksum) {
    LinkNode* current1 = Link1.head->next;
    LinkNode* current2 = Link2.head->next;
    while (current1 != nullptr && current2 != nullptr) {
        if(current1->exponent == current2->exponent) {
            double coesum = current1->coefficient + current2->coefficient;
            if(coesum != 0) Linksum.AddLinkNode(coesum, current1->exponent);
            current1 = current1->next;
            current2 = current2->next;
        }
        else if(current1->exponent > current2->exponent){
            Linksum.AddLinkNode(current1->coefficient, current1->exponent);
            current1 = current1->next;        
        }
        else {
            Linksum.AddLinkNode(current2->coefficient, current2->exponent);
            current2 = current2->next; 
        }
    }
    while (current1 != nullptr) {
        Linksum.AddLinkNode(current1->coefficient, current1->exponent);
        current1 = current1->next;
    }

    while (current2 != nullptr) {
        Linksum.AddLinkNode(current2->coefficient, current2->exponent);
        current2 = current2->next;
    }
    
    return;
} 
void LinkReverse(Link& link) {
    LinkNode* current = link.head->next;
    LinkNode* last = nullptr;
    while(current != nullptr) {
        LinkNode* Next = current->next;
        Next = current->next;
        current->next = last;
        last= current;
        current = Next;
    }
    link.head->next = last;
}
int main() {
    int n, m;
    int exp;
    double coe;
    cin >> n;
    Link Poly1;
    for (int i = 1; i <= n; ++i) {
        cin >> coe >> exp;
        Poly1.AddLinkNode(coe, exp);
    }

    cin >> m;
    Link Poly2;
    for (int i = 1; i <= m; ++i) {
        cin >> coe >> exp;
        Poly2.AddLinkNode(coe, exp);
    }
    Poly1.PrintLink();
    Poly2.PrintLink();

    Link Polysum;
    LinkMerge(Poly1, Poly2, Polysum);
    LinkReverse(Polysum);
    Polysum.PrintLink();
    return 0;
}
