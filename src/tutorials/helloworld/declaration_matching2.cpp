#include <iostream>
#include <string>
#include <string_view>

// https://stackoverflow.com/questions/40127965/how-exactly-is-stdstring-view-faster-than-const-stdstring
class Account {
public:
  Account() = default;
  Account(double dAmount, std::string_view szPassword)
      : current_balance_{dAmount}, password_{szPassword} {};
  ~Account() = default;
  double Deposit(double dAmount, std::string_view szPassword);

private:
  double current_balance_{0.0};
  std::string password_{"pswd"};
  double Deposit(double dAmount) { return current_balance_ += dAmount; }
  bool Validate(std::string_view szPassword) { return szPassword == password_; }
};

int main() {
  // NOTE: this is how we can instrument with valgrind:
  // https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks
  // invoked by this:
  // bazelisk run --run_under="valgrind --leak-check=full --show-leak-kinds=all
  //    --track-origins=yes --verbose"

  // Allocate a new object of type Account
  Account acct;
  Account &pAcct = acct;
  // Deposit $57.22. Error: calls a private function.
  //   pAcct->Deposit(57.22);

  // Deposit $57.22 and supply a password. OK: calls a public function
  std::cout << "Size of Account Class: " << sizeof(Account) << " bytes"
            << std::endl;
  std::cout << "Bad Password: " << pAcct.Deposit(52.77, "bad") << std::endl;
  std::cout << "Good Password: " << pAcct.Deposit(52.77, "pswd") << std::endl;
  std::cout << "Bad Password: " << pAcct.Deposit(52.77, "bad") << std::endl;

  return 0;
}

double Account::Deposit(double dAmount, std::string_view szPassword) {
  if (Validate(szPassword)) {
    return Deposit(dAmount);
  } else {
    return current_balance_;
  }
}