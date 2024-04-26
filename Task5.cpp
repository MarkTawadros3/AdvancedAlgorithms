#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;

class Node
{
    public:
        string data;
        Node* left;
        Node* right;
        
        Node(string d)
        {
            data = d;
            left = NULL;
            right = NULL;
        }
    
        ~Node()
        {
            delete left;
            delete right;
        }
};

class Tree
{
    public:
        Node* root;
        
        Tree()
        {
            root = NULL;
        }
        
        ~Tree()
        {
            delete root;
        }

        double runCalcResult()
        {
            return calcResult(root);
        }

        double calcResult(Node* curr)
        {
            if (curr->left == NULL && curr->right == NULL)
            {
                return stod(curr->data);
            }
            else
            {
                string x = curr->data;
                if (x == "+")
                {
                    return calcResult(curr->left) + calcResult(curr->right);
                }
                if (x == "-")
                {
                    return calcResult(curr->left) - calcResult(curr->right);
                }
                if (x == "*")
                {
                    return calcResult(curr->left) * calcResult(curr->right);
                }
                else
                {
                    return calcResult(curr->left) / calcResult(curr->right);
                }
            }
        }
        
        void runExpTree(string str)
        {
            root = expTree(str);
        }
        
        Node* expTree(string str)
        {
            stack<int> s;
            vector<int> v;
            string newStr = cleanString(str);
            int n = newStr.length();
            for (int i = 0; i < n; i++)
            {
                char currElement = newStr[i];
                if (currElement == '(')
                {
                    s.push(i);
                }
                else if (currElement == ')')
                {
                    s.pop();
                }
                else if (s.size() == 0 && (currElement == '+' || currElement == '-' || currElement == '*' || currElement == '/'))
                {
                    v.push_back(i);
                }
            }
            int x;
            if (v.size() == 0)
            {
                return new Node(newStr);
            }
            else if (v.size() == 1)
            {
                x = v.at(0);
            }
            else
            {
                int operSymbolIndex = precedence(newStr, v);
                x = v.at(operSymbolIndex);
            }
            Node* node1 = new Node(newStr.substr(x, 1));
            node1->left = expTree(newStr.substr(0, x));
            node1->right = expTree(newStr.substr(x+1, n-x-1));
            return node1;
        }
        
        string cleanString(string str)
        {
            stack<int> s;
            vector<int> v;
            int n = str.length();
            for (int i = 0; i < n - 1; i++)
            {
                char currElement = str[i];
                if (currElement == '(')
                {
                    s.push(i);
                }
                else if (currElement == ')')
                {
                    s.pop();
                }
            }
            if (s.size() == 1 && s.top() == 0)
            {
                return str.substr(1, n-2);
            }
            return str;
        }
        
        int precedence(string str, vector<int> v)
        {
            for (char operSign : {'-', '+', '*', '/'})
            {
                for (int i = 0; i < v.size(); i++)
                {
                    if (str[v.at(i)] == operSign)
                    {
                        return i;
                    }
                }
            }
        }
        
        void runExpTreeTrav()
        {
            expTreeTrav(root);
        }
        
        void expTreeTrav(Node* root)
        {
            if (!root)
            {
                return;
            }
            cout << "(";
            expTreeTrav(root->left);
            cout << root->data;
            expTreeTrav(root->right);
            cout << ")";
        }
        
        int height(Node* root)
        {
            if (root == nullptr)
            {
                return 0;
            }
            return 1 + max(height(root->left), height(root->right));
        }
        
        int getcol(int h)
        {
            if (h == 1)
            {
                return 1;
            }
            return getcol(h - 1) + getcol(h - 1) + 1;
        }
        
        void printTree(string **M, Node *root, int col, int row, int height)
        {
            if (root == NULL)
            {
                return;
            }
            M[row][col] = root->data;
            printTree(M, root->left, col - pow(2, height - 2), row + 1, height - 1);
            printTree(M, root->right, col + pow(2, height - 2), row + 1, height - 1);
        }
        
        void printExpTree()
        {
            int h = height(root);
            int col = getcol(h);
            string **M = new string*[h];
            for (int i = 0; i < h; i++)
            {
                M[i] = new string[col];
            }
            printTree(M, root, col / 2, 0, h);
            for (int i = 0; i < h; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (M[i][j] == "")
                    {
                        cout << " ";
                    }
                    else
                    {
                        cout << M[i][j];
                    }
                }
                cout << endl;
            }
        }
};


int main()
{
    Tree* tree = new Tree();
    string a = "(((5+2)*(2-1))/((2+9)+((7-2)-1))*8)";
    tree->runExpTree(a);
    cout << "Expression tree:" << endl;
    tree->printExpTree();
    cout << endl;
    cout << "Value: " << tree->runCalcResult() << endl;
    cout << endl;
    return 0;
}