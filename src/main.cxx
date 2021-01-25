#include <coroutine>
#include <iostream>

#include "awaitable/awaitable.h"
#include "generator/generator.h"

awaitable foo() {
  std::cout << "Hello\n";
  co_await std::suspend_always();
  std::cout << "world\n";
}

generator bar() {
  int i = 1;
  for (;;) {
    co_yield i;
    i += 1;
  }
}
int main() {
  auto handle = bar();
  std::cout << (handle.next(), handle.current_value()) << std::endl;
  std::cout << (handle.next(), handle.current_value()) << std::endl;
  std::cout << (handle.next(), handle.current_value()) << std::endl;
  std::cout << (handle.next(), handle.current_value()) << std::endl;
}