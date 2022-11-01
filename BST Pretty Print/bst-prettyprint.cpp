#include <iostream>
#include <vector>
#include <ios>
#include <iomanip>

class BST{
    public:
        BST();
        ~BST();
        void insertKey(int newKey);
        bool hasKey(int searchKey);
        std::vector<int> inOrder();
        int getHeight();
        void prettyPrint();
    private:
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
        int getIndex(int key);
        void getLine(Node* node, int level, std::vector<int>& nodeByLine);
        std::vector<int> inOrderNumber;
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
    if (leftHeight > rightHeight) { return leftHeight + 1; }
    else{ return rightHeight + 1; }
}

void BST::insertKey(int newKey){
    if (root == nullptr){
        root = new BST::Node(newKey);
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

int BST::getIndex(int key){
    int index;
    for (int i=0; i<inOrderNumber.size(); i++){
        if (key == inOrderNumber.at(i)) index = i;
    }
    return index;
}

void BST::prettyPrint(){
    if (root == nullptr) return;
    int columns = inOrderNumber.size();
    int indexNodeByLine = 0;
    std::vector<int> nodeByLine;

    for (int i = 1; i <= getHeight(root); i++){
        int count=0;
        getLine(root, i, nodeByLine);
        std::cout << std::setfill('-') << std::setw(5*inOrderNumber.size()+1) << "" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << '|';
        for (int j = 0; j<columns; j++){
            int position = getIndex(nodeByLine.at(indexNodeByLine));
            if (j == position){
                std::cout << std::setw(4) << std::right << nodeByLine.at(indexNodeByLine) << '|';
                count++;
                indexNodeByLine++;
            }
            else if (j != position){
                std::cout << std::setw(5) << std::right << '|';
                count++;
            }
            if (indexNodeByLine >= nodeByLine.size()){
                break;
            }
        }
        for (int k =0; k < columns-count; k++){
            std::cout << std::setw(5) << std::right << '|';
        }
        std::cout << std::endl;
    }
    std::cout << std::setfill('-') << std::setw(5*inOrderNumber.size()+1) << "" << std::endl;
    std::cout << std::setfill(' ');
}

void BST::getLine(Node* node, int level, std::vector<int>& nodeByLine){
    if (node == nullptr)
        return;
    if (level == 1) {
       nodeByLine.push_back(node->val);
    }
    else if (level > 1){
        getLine(node->left, level-1, nodeByLine); 
        getLine(node->right, level-1, nodeByLine);
    }
}

int main(){
    BST tree;
    
    int input;
    std::cout << "Enter the numbers to be stored: ";
    while (std::cin >> input){
        tree.insertKey(input);
    }

    std::vector<int> inOrderNumbers = tree.inOrder();
    std::cout << "The numbers in sorted order: ";
    for (int i = 0; i < inOrderNumbers.size(); i++){
        std::cout << inOrderNumbers.at(i) << ' ';
    }
    std::cout << std::endl;

    tree.getHeight();
    tree.prettyPrint();
    
    return 0;
}