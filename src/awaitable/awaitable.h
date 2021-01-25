#pragma once

#include <coroutine>
#include <exception>

class awaitable {
 public:
  struct promise_type {
    using coro_handle = std::coroutine_handle<promise_type>;

    coro_handle from_promise();

    coro_handle get_return_object();

    std::suspend_always initial_suspend();
    std::suspend_always final_suspend();

    void return_void();

    void unhandled_exception();
  };

  using coro_handle = std::coroutine_handle<promise_type>;
  awaitable(coro_handle handle);

  awaitable(const awaitable&) = delete;
  awaitable(awaitable&&);

  bool next();
  ~awaitable();

 private:
  coro_handle handle_;
};
