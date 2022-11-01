#include <iostream>
#include <limits>
#include <vector>

class Stack {
    public:
        Stack();
        bool isEmpty() const;
        int top() const;
        int pop();
        void push(int i);
        std::string toString() const;
    private:
        std::vector<int> elements;
};

Stack::Stack() {
    elements.resize(0);
}

bool Stack::isEmpty() const {
    if (elements.empty()) {
        return true;
    }
    else {
        return false;
    }
}

int Stack::top() const {
    if (Stack::isEmpty()) {
        throw std::runtime_error("stack is empty");
    }
    else {
        return elements.back();
    }
}

int Stack::pop() {
    if (Stack::isEmpty()) {
        throw std::runtime_error("stack is empty");
    }
    else {
        int a = elements.back();
        elements.pop_back();
        return a;
    }
}

void Stack::push(int i) {
    elements.push_back(i);
}

std::string Stack::toString() const {
    if (Stack::isEmpty()) {
        return "[]";
    }
    else {
        std::string s;
        for (int i = elements.size() - 1; i > 0; i--) {
            s = s + std::to_string(elements.at(i)) + ",";
        }
        s = "[" + s + std::to_string(elements.at(0)) + "]";
        return s;
    }
}

int main() {
    Stack stack;
    
    while (true) {
        try {
            std::cout << "stack> ";
            
            std::string command;
            std::cin >> command;
            
            if ( (command.compare("end") == 0) || std::cin.eof() ){
                break;
            } else if (command.compare("top") == 0) {
                std::cout << stack.top() << std::endl;
            } else if (command.compare("pop") == 0) {
                std::cout << stack.pop() << std::endl;
            } else if (command == "push") {
                if ( std::cin.eof() ) break;
                int i;
                std::cin >> i;
                bool failed = std::cin.fail();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if ( failed ){
                  throw std::runtime_error("not a number");
                }
                stack.push(i);
            } else if ( command.compare("list") == 0){
                std::cout << stack.toString() << std::endl;;
            } else {
                throw std::runtime_error("invalid command");
            }
        } catch (std::runtime_error& e) {
            std::cout << "error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}