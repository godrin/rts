#include <iostream>

void init_AGApplication();

extern "C" {
  
  
  void Init_rts_api() {
    std::cout<<"HI"<<std::endl;
    init_AGApplication();
  }
}