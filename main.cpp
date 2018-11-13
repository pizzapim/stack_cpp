#include "Stack.h"
#include <iostream>
using namespace std;
int main() {
  Stack<int> stack;
  stack.push(2);
  stack.push(3);
  stack.push(4);
  int res = stack.pop();
  res = stack.pop();
  cout << res << endl;
}