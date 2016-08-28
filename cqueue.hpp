#ifndef __CQUEUE_HPP__
#define __CQUEUE_HPP__

#include <mutex>
#include <condition_variable>
#include <array>

template <typename T, int cap_>
class CQueue {
 private:
  std::array<T, cap_>   queue_;
  std::mutex mutex_;
  std::condition_variable  condv_;

  int head_;
  int tail_;
  volatile int size_;

 public:
  CQueue() : head_(0),tail_(0),size_(0) {}
  ~CQueue() {}

  int push(T &item) {
    std::lock_guard<std::mutex> lk(mutex_);

    if (size_ >= cap_) {
      return -1;
    }

    queue_.at(head_) = item;
    head_ = (++head_) % cap_;
    size_++;

    condv_.notify_one();
    return 0;
  }

  int pop(T &item, int timeout_ms) {
    std::unique_lock<std::mutex> lk(mutex_);

    if(size_ == 0) {
      if (condv_.wait_for(lk, std::chrono::milliseconds(timeout_ms))==
          std::cv_status::timeout) {
        return -1;
      }
    }

    item = queue_.at(tail_);
    tail_ = (++tail_) % cap_;
    size_--;

    return 0;
  }

  int pop(T &item) {
    std::unique_lock<std::mutex> lk(mutex_);

    if(size_ == 0) {
      condv_.wait(lk);
    }

    item = queue_.at(tail_);
    tail_ = (++tail_) % cap_;
    size_--;

    return 0;
  }

  int size() {
    std::lock_guard<std::mutex> lk(mutex_);
    return size_;
  }
};

#endif
