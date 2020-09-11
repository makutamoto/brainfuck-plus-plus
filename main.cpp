#include<iostream>
#include<fstream>
#include<array>
#include<stack>

#define BUFFER_SIZE 30000

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Specify a file to run." << std::endl;
        return -1;
    }
    std::ifstream file(argv[1]);
    std::string program((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if(program.empty()) std::cout << "No program to run." << std::endl;
    std::array<char, BUFFER_SIZE> buffer;
    std::stack<int> stack;
    int skippingStackCount = 0;
    char *p = &buffer.front();
    for(int index = 0;index < program.size();index++) {
        if(program[index] == ']' && skippingStackCount && stack.size() == skippingStackCount) stack.pop(), skippingStackCount = 0;
        else if(program[index] == ']' && skippingStackCount) stack.pop();
        else if(program[index] =='[' && skippingStackCount) stack.push(index);
        else if(skippingStackCount);
        else if(program[index] == '>') p++;
        else if(program[index] == '<') p--;
        else if(program[index] == '+') ++*p;
        else if(program[index] == '-') --*p;
        else if(program[index] == '.') putchar(*p);
        else if(program[index] == ',') *p = getchar();
        else if(program[index] == '[' && *p) stack.push(index);
        else if(program[index] == '[') stack.push(index), skippingStackCount = stack.size();
        else if(program[index] == ']') index = stack.top() - 1, stack.pop();
    }
    return 0;
}
