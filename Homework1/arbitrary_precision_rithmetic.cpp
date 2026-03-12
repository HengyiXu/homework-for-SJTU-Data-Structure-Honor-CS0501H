#include<bits/stdc++.h>
using namespace std;

class LinkNode {
    public:
        int val;
        LinkNode* next;
        LinkNode(int v = 0) {
            val = v;
            next = nullptr;
        }
};

class Link {
    public:
        bool sign;
        LinkNode* head;

        Link() {
            sign = 1;
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

    
        void AddLinkNode(int val) {
            LinkNode* p = new LinkNode(val);
            p->next = head->next;
            head->next = p;
        }
        void PrintLink() {
            LinkNode* current = head->next;
            
    
            while(current != nullptr && current->val == 0 && current->next != nullptr) {
                current = current->next;
            }
            
            if(current == nullptr) {
                cout << 0 << endl;
                return;
            }
            
            if(!sign && current->val != 0) {
                cout << "-";
            }
            
            while(current != nullptr) {
                cout << current->val;
                current = current->next;
            }
            cout << endl;
        }
};

int CompareAbs(const Link& Link1, const Link& Link2) {
    vector<int> v1, v2;
    LinkNode* p1 = Link1.head->next;
    LinkNode* p2 = Link2.head->next;
    
    while(p1 != nullptr) { v1.push_back(p1->val); p1 = p1->next; }
    while(p2 != nullptr) { v2.push_back(p2->val); p2 = p2->next; }
    
    if(v1.size() != v2.size()) {
        return v1.size() > v2.size() ? 1 : -1;
    }
    
    for(int i = v1.size() - 1; i >= 0; i--) {
        if(v1[i] != v2[i]) return v1[i] > v2[i] ? 1 : -1;
    }
    return 0;
}

void AddAbs(const Link& Link1, const Link& Link2, Link& Linksum) {
    LinkNode* current1 = Link1.head->next;
    LinkNode* current2 = Link2.head->next;
    int carry = 0;
    
    while(current1 != nullptr || current2 != nullptr || carry != 0) {
        int val1 = (current1 != nullptr) ? current1->val : 0;
        int val2 = (current2 != nullptr) ? current2->val : 0;
        int sum = val1 + val2 + carry;
        
        carry = sum / 10;
        
        Linksum.AddLinkNode(sum % 10);
        
        if(current1 != nullptr) current1 = current1->next;
        if(current2 != nullptr) current2 = current2->next;
    }
}

void SubAbs(const Link& Link1, const Link& Link2, Link& Linksum) {
    LinkNode* current1 = Link1.head->next;
    LinkNode* current2 = Link2.head->next;
    int borrow = 0;
    
    while(current1 != nullptr) {
        int val1 = current1->val;
        int val2 = (current2 != nullptr) ? current2->val : 0;
        int diff = val1 - val2 - borrow;
        
        if(diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        Linksum.AddLinkNode(diff);
        
        current1 = current1->next;
        if(current2 != nullptr) current2 = current2->next;
    }
}

void BuildLinkFromString(string s, Link& link) {
    if(s.empty()) return;
    

    if(s[0] == '-') {
        link.sign = 0;
        s = s.substr(1);
    } else if(s[0] == '+') {
        link.sign = 1;
        s = s.substr(1);
    }
    

    int start = 0;
    while(start < s.length() - 1 && s[start] == '0') {
        start++;
    }
    s = s.substr(start);
    
    for(char c : s) {
        link.AddLinkNode(c - '0');
    }
}

int main() {
    string s1, s2;
    while(cin >> s1 >> s2) {
        Link Num1, Num2, NumSum;
        BuildLinkFromString(s1, Num1);
        BuildLinkFromString(s2, Num2);
        
        if(Num1.sign == Num2.sign) {
            AddAbs(Num1, Num2, NumSum);
            NumSum.sign = Num1.sign;
        } else {
            int cmp = CompareAbs(Num1, Num2);
            if(cmp == 0) {
                NumSum.AddLinkNode(0);
                NumSum.sign = 1;
            } else if(cmp > 0) {
                SubAbs(Num1, Num2, NumSum);
                NumSum.sign = Num1.sign;
            } else {
                SubAbs(Num2, Num1, NumSum);
                  
      NumSum.sign = Num2.sign;
            }
        }
        NumSum.PrintLink();
    }
    return 0;
}