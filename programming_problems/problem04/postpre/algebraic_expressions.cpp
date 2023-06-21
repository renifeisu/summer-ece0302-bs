#include <string>
using std::string;

#include <iostream>

#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

#include <stack>

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix) {

  if(!isPost(postfix)) // postfix must be a valid postfix expression
  {
    return;
  }
  else
  {
    std::stack<string> stack; // stack to push operands into
    for(int i = 0; i < postfix.size(); i++)
    {
      if(!isoperator(postfix[i])) // push operands into stack
      {
        stack.push(string(1, postfix[i]));
      }
      else // detect operator
      {
        string s1 = stack.top(); // pop second operand
        stack.pop(); 
        string s2 = stack.top(); // pop first operand
        stack.pop();
        prefix = string(1, postfix[i]) + s2 + s1; // temp prefix expression (inverse of postfix expression)
        stack.push(prefix); // temp prefix expression is pushed back into stack (to be nested in other prefix expressions)
      }
    }
    prefix = stack.top(); // after the for loop, only the final prefix expression should be at the top of the stack
  }
  
}
