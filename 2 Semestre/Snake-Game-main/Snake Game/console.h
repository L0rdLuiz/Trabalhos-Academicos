#ifndef console_helpers
#define console_helpers

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

void clear_console() {
    system("cls"); // Clear the console on Windows
}

void set_cursor(){
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hide_cursor() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(hConsole, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(hConsole, &cursorInfo);
}

char get_input_without_enter() {
  return _getch();
}

void pause_console() {
  system("pause");
}

#else
#include <termios.h>
#include <sys/ioctl.h>

void clear_console() {
    system("clear"); // Clear the console on Linux
}

void set_cursor(){
    system("clear");
}

void hide_cursor() {
  std::cout << "\033[?25l"; // Hide the cursor using ANSI escape sequence
}

bool _kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

char get_input_without_enter() {
  struct termios old_terminal, new_terminal;
  char input;

  tcgetattr(0, &old_terminal);
  new_terminal = old_terminal;
  new_terminal.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(0, TCSANOW, &new_terminal);

  input = std::getchar();

  tcsetattr(0, TCSANOW, &old_terminal);

  return input;
}

void pause_console() {
  system("read 0 -p");
}

#endif

#endif // console_helpers