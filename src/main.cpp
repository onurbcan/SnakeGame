#include "menu.h"

int main() {
  Menu menu;
  menu.GameLoop();
  menu.~Menu();
  return 0;
}