#include <algorithm>
#include <iostream>
#include <map>
#include <mutex>
#include <string>

using namespace std;
map<int, string> m{{1, "one"}, {2, "two"}, {10, "ten"}};
mutex mx;

bool shared_flag = true; // guarded by mx
int getValue() { return 42; }

int main() {
  if (auto it = m.find(10); it != m.end()) {
    cout << it->second << "\n";
  }

  if (int x = getValue(); x == 42) {
    cout << "x is 42\n";
  }

  if (lock_guard<mutex> lock(mx); shared_flag) {
    cout << "setting shared_flag to false\n";
    shared_flag = false;
  }
  string s{"if"};
  if (auto keywords = {"if", "for", "while"};
      any_of(keywords.begin(), keywords.end(),
             [&s](const char *kw) { return s == kw; })) {
    cout << "Error! Token must not be a keyword\n";
  }
}