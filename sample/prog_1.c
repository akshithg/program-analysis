void dummy(int a, int b) {
  int c = a + b;
}


int main(int argc, char **argv) {
  int a = 10;
  int b = 5;
  int c;

  if ( a + b % 2 == 0 )
    c = 20;
  else
    c = 50;

  return argc + c;
}
