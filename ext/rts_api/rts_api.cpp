#include <iostream>

extern "C" {
  void Init_rts_api() {
    std::cout<<"HI"<<std::endl;
  }
}