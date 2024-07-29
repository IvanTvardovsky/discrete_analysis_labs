#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <string>
#include <utility>
#include <map>

using namespace std;

const int SPECIAL_VALUE = -1;
const string TERMINATOR = "$";

class SuffixTree {
public:
    explicit SuffixTree(string s);
    string minString();
    ~SuffixTree() = default;

private:
    struct Node {
        Node *link;
        int start;
        int *end;
        map<char, Node*> children;
        bool is_leaf;

        Node(int start, int *end, bool is_leaf) {
            this->start = start;
            this->end = end;
            link = nullptr;
            this->is_leaf = is_leaf;
        }

        ~Node() {
            for (auto &it: children) {
                delete (it.second);
            }
        }
    };

    void insert(const int &position);

    Node* root;
    Node* active_node;
    Node* last_node;
    int active_edge;
    int active_length;
    int suffixes_to_add;
    string text;
    int global_end;
};

SuffixTree::SuffixTree(string s) : text(move(s)) {
    root = new Node(SPECIAL_VALUE, new int(SPECIAL_VALUE), false);
    active_node = root;
    global_end = SPECIAL_VALUE;
    active_edge = SPECIAL_VALUE;
    active_length = 0;
    suffixes_to_add = 0;
    for (int i = 0; i < text.size(); ++i) {
        insert(i);
    }
}

void SuffixTree::insert(const int &text_position) {
    last_node = nullptr;
    ++suffixes_to_add;
    ++global_end;
    while (suffixes_to_add > 0) {
        if (active_length == 0) {
            active_edge = text_position;
        }
        
        if (!active_node->children[text[active_edge]]) {
            active_node->children[text[active_edge]] = new Node(text_position, &global_end, true);
            if (last_node != nullptr) {
                last_node->link = active_node;
                last_node = nullptr;
            }
        } else {
            Node* next_node = active_node->children[text[active_edge]];
            int edge_length = *(next_node->end) - next_node->start + 1;
            
            if (active_length >= edge_length) {
                active_edge += edge_length;
                active_length -= edge_length;
                active_node = next_node;
                continue;
            }

            if (text[next_node->start + active_length] == text[text_position]) {
 
                if (last_node != nullptr) {
                    last_node->link = active_node;
                    last_node = nullptr;
                }
                ++active_length;
                break;
            }

            Node* to_add = new Node(next_node->start, new int(next_node->start + active_length - 1), false);
            active_node->children[text[active_edge]] = to_add;
            next_node->start += active_length;
            pair<char, Node*> first = make_pair(text[text_position],
                                                           new Node(text_position, &global_end, true));
            pair<char, Node*> second = make_pair(text[next_node->start], next_node);
            to_add->children.insert(first);
            to_add->children.insert(second);
            if (last_node != nullptr) {
                last_node->link = to_add;
            }
            last_node = to_add;
        }
        --suffixes_to_add;
        if (active_node == root && active_length > 0) {
            ++active_edge;
            --active_length;
        } else if (active_node != root) {
            active_node = active_node->link;
        }
    }
}

string SuffixTree::minString() {
    string result_string;
    size_t length = (text.size() - 1) / 2;
    Node *next = root;
    while (result_string.size() < length) {
        auto it = next->children.begin();
        if (it->first == '$') {
            ++it;
        }
        next = it->second;
        for (int i = next->start; i <= *(next->end); ++i) {
            result_string += text[i];
            if (result_string.size() == length) {
                break;
            }
        }
    }
    return result_string;
}

int main() {
    string input;
    cin >> input;
    
    auto *tree = new SuffixTree(input + input + TERMINATOR);
    string result = tree->minString();
    cout << result << "\n";
    
    delete tree;
    return 0;
}
