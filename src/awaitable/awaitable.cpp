#include "awaitable.h"

// promise_type interface

awaitable::promise_type::coro_handle awaitable::promise_type::from_promise() {
  return coro_handle::from_promise(*this);
}

awaitable::promise_type::coro_handle
awaitable::promise_type::get_return_object() {
  return coro_handle::from_promise(*this);
}

std::suspend_always awaitable::promise_type::initial_suspend() {
  return std::suspend_always{};
}

std::suspend_always awaitable::promise_type::final_suspend() {
  return std::suspend_always{};
}

void awaitable::promise_type::return_void() { return; }

void awaitable::promise_type::unhandled_exception() { std::terminate(); }

// coroutine interface
awaitable::awaitable(coro_handle handle) : handle_(handle) {}

awaitable::awaitable(awaitable&& other) : handle_(std::move(other.handle_)) {
  other.handle_ = nullptr;
}

bool awaitable::next() {
  if (!handle_.done()) handle_.resume();
  return !handle_.done();
}

awaitable::~awaitable() {
  if (handle_) handle_.destroy();
}