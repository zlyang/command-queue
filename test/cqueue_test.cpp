#include "cqueue.hpp"

#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

CQueue <int, 5>cq;
std::mutex lock_cout;

void cosumer(int id) {
  int rcv = 0;
  int ret = 0;

  while (true) {
    ret = cq.dequeue(rcv, 5);
    if (ret < 0) {
      continue;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    {
      std::lock_guard<std::mutex> lk(lock_cout);
      std::cout << "id:" << id << " rcv:" << rcv << std::endl;
    }
  }
}

int main(int argc, char const *argv[]) {
  for(int i=0; i<10; i++) {
    cq.enqueue(i);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::thread t1 = std::thread(cosumer, 1);
  std::thread t2 = std::thread(cosumer, 2);

  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "finish!!!" << std::endl;

  exit(0);
}
