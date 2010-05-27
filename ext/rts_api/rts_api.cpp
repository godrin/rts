#include <iostream>

void init_AGApplication();
void init_Game();

extern "C" {
  
  
  void Init_rts_api() {
    std::cout<<"HI"<<std::endl;
    init_AGApplication();
    init_Game();
  }
}