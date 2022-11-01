#include <iostream>
#include <vector>

class BST{
    public:
        BST();
        ~BST();
        void insertKey(int newKey);
        bool hasKey(int searchKey);
        std::vector<int> inOrder();
        int getHeight();
    private:
        // your implementation goes here
        class Node{
            public:
                Node(int value);
                ~Node();
                int val;
                Node *left;
                Node *right;
        };
        Node *root;
        void insertKey(int newKey, Node* newNode);
        bool hasKey(int searchKey, Node* node);
        void inOrder(Node* node);
        int getHeight(Node* node);
        std::vector<int> inOrderNumber;
        int height;
};

BST::Node::Node(int value){
    val = value;
    left = nullptr;
    right = nullptr;
}

BST::Node::~Node(){
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
}

BST::BST(){ 
    height = 0;
    root = nullptr;
}

BST::~BST(){ 
    delete root; 
}

int BST::getHeight(){
    return getHeight(root);
}

int BST::getHeight(Node* node){ 
    if (node == nullptr) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    if (leftHeight >= rightHeight) { return leftHeight + height; }
    else{ return rightHeight + height; }
}

void BST::insertKey(int newKey){
    if (root == nullptr){
        root = new BST::Node(newKey);
        height++;
    }
    else {
        insertKey(newKey, root);
    }   
}

void BST::insertKey(int newKey, BST::Node* root){
    if (newKey < root->val){
        if (root->left == nullptr){
            root->left =  new BST::Node(newKey);
        }
        else if (root->left != nullptr){
            insertKey(newKey, root->left);
        }
    }
    else if(newKey > root->val){
        if (root->right == nullptr){
            root->right =  new BST::Node(newKey);
        }
        else if (root->right != nullptr){
            insertKey(newKey, root->right);
        }
    }
}

bool BST::hasKey(int searchKey) {
    int key = hasKey(searchKey, root);
    if (hasKey(searchKey, root) == true) return true;
    return false;
}

bool BST::hasKey(int searchKey, Node* node){
    if (node == nullptr) return false;
    if (node->val == searchKey) return true;
    else {
	    if (node->val < searchKey) return hasKey(searchKey, node->right);
	    else return hasKey(searchKey, node->left);
	}
}

std::vector<int> BST::inOrder() {
    inOrder(root);
    return inOrderNumber;
}

void BST::inOrder(Node* node){
    if (node == nullptr) return;
    if (node != nullptr) {
        inOrder(node->left);
        inOrderNumber.push_back(node->val);
        inOrder(node->right);
    }
}

int main(){
    BST tree;
    int input;
    std::cout << "Enter the numbers to be stored (end with a letter): ";
    while (std::cin >> input){
        tree.insertKey(input);
    }
    std::cin.clear(); 
    std::cin.ignore();

    int search;
    std::cout << "Which number do you want to look up? ";
    std::cin >> search;
    if (tree.hasKey(search) == true) std::cout << search << " is in the tree: yes"; 
    else std::cout << search << " is in the tree: no";

    std::vector<int> inOrderNumbers = tree.inOrder();
    std::cout << "\nThe numbers in sorted order: ";
    for (int i = 0; i < inOrderNumbers.size(); i++){
        std::cout << inOrderNumbers.at(i) << ' ';
    }

    std::cout << "\nHeight of the tree: " << tree.getHeight() << std::endl;
    
    return 0;
}