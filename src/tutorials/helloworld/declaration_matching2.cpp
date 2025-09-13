#include <iostream>
#include <string>

class Account {
public:
  Account() = default;
  double Deposit(double dAmount, const std::string szPassword);

private:
  double balance_{0.0};
  std::string password_{"pswd"};
  double Deposit(double dAmount) { return balance_ += dAmount; }
  bool Validate(const std::string szPassword) {
    return szPassword == password_;
  }
};

int main() {
  // Allocate a new object of type Account
  Account *pAcct = new Account;
  // Deposit $57.22. Error: calls a private function.
  // pAcct->Deposit(57.22);

  // Deposit $57.22 and supply a password. OK: calls a public function
  std::cout << pAcct->Deposit(52.77, "bad") << std::endl;
  std::cout << pAcct->Deposit(52.77, "pswd") << std::endl;

  return 0;
}

double Account::Deposit(double dAmount, const std::string szPassword) {
  if (Validate(szPassword)) {
    return Deposit(dAmount);
  } else {
    return 0.0;
  }
}