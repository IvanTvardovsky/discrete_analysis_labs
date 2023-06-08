#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <sstream>
#include <cstdlib>
#include <ctime>
 
using namespace std;

struct Node {
    unsigned long long key;
    long long prior;
    string value;
    Node* l = nullptr;
    Node* r = nullptr;
 
    Node(unsigned long long _key, string _value) {
        key = _key;
        prior = rand();
        value = _value;
    }
};
 
bool comparator(string s1, string s2) {
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    int res = s1.compare(s2);
    if (res <= 0) {
        return true;
    }
    return false;
}
 
Node* minValueNode(Node* node) {
    Node* current = node;
 
    while (current && current->l != NULL)
        current = current->l;
 
    return current;
}
 
Node* deleteElement(Node* root, string value) {
    if (root == NULL)
        return root;
    string s1 = value;
    string s2 = root -> value;
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if (s1 < s2) {
        root->l = deleteElement(root->l, value);
    } else if (s1 > s2) {
        root->r = deleteElement(root->r, value);
    } else {
        if (root->l == NULL and root->r == NULL) {
            return NULL;
        } else if (root->l == NULL) {
            Node* temp = root->r;
            free(root);
            return temp;
        } else if (root->r == NULL) {
            Node* temp = root->l;
            free(root);
            return temp;
        }
 
        Node* temp = minValueNode(root->r);
 
        root->value = temp->value;
 
        root->r = deleteElement(root->r, temp->value);
    }
    return root;
}
 
Node* merge(Node* l, Node* r) {
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }
    
    if (l->prior > r->prior) {
        l->r = merge(l->r, r);
        return l;
    } else {
        r->l = merge(l, r->l);
        return r;
    }
}
 
pair<Node*, Node*> split(Node* p, string x) {
    if (!p) {
        return {nullptr, nullptr};
    }
    if (comparator(p->value, x)) {
        pair<Node*, Node*> q = split(p->r, x);
        p->r = q.first;
        return { p, q.second };
    } else {
        pair<Node*, Node*> q = split(p->l, x);
        p->l = q.second;
        return { q.first, p };
    }
}
 
bool areStringsEqual(string s1, string s2) {
    if (s1.size() != s2.size()) {
        return false;
    }
    for (int i = 0; i < s1.size(); ++i) {
        if (tolower(s1[i]) != tolower(s2[i])) {
            return false;
        }
    }
    return true;
}
 
Node* findNode(Node* root, string value) {
    if (root == nullptr) {
        return nullptr;
    }
    
    string s1 =  root->value;
    string s2 =  value;
 
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
 
    if (s1 == s2) {
        return root;
    }
    
    if (s1 < s2) {
        return findNode(root->r, s2);
    }
     
    return findNode(root->l, s2);
}
 
Node* insert(Node* root, long long key, string value) {
    Node* node = new Node(key, value);
    if (!root) {
        return node;
    }
    pair<Node*, Node*> p = split(root, value);
    root = merge(p.first, node);
    root = merge(root, p.second);
    return root;
}
 
Node* erase(Node* root, string value) {
    Node* found = findNode(root, value);
    if (!found) {
        return root;
    }
    pair<Node*, Node*> p = split(root, found->value);
    p.first = deleteElement(p.first, value);
    return merge(p.first, p.second);
}
 
int main() {
    string input;
    Node* root = nullptr;
    srand((unsigned int)time(NULL));
    while (getline(cin, input)) {
        if (input[0] == '+') {
            stringstream ss(input);
            char symbol;
            string value;
            unsigned long long key;
            ss >> symbol >> value >> key;
 
            if (findNode(root, value) == nullptr) {
                root = insert(root, key, value);
                cout << "OK\n";
            } else {
                cout << "Exist\n";
            }
        }
        else if (input[0] == '-') {
            stringstream ss(input);
            char symbol;
            string value;
            ss >> symbol >> value;
 
            if (findNode(root, value) != nullptr) {
                root = erase(root, value);
                cout << "OK\n";
            } else {
                cout << "NoSuchWord\n";
            }
        }
        else {
            stringstream ss(input);
            string value;
            ss >> value;
 
            Node* temp = findNode(root, value);
            if (temp != nullptr) {
                cout << "OK: " << temp->key << endl;
            } else {
                cout << "NoSuchWord\n";
            }
        }
 
        input = "";
    }
 
    return 0;
}