// void dummy(int a, int b) {
//   int c = a + b;
// }

static void bb_tracer(int x)
{
  // printf("bb_tracer called with %d \n", x);
  return;
}

int main(int argc, char **argv) {
  int x;

  if ( argc <= 1 )
    x = 0;
  else
    x = 100;

  bb_tracer(x);

  return x;
}
