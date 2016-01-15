#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

#define SIZE 1000001

void calc(size_t, size_t, size_t&);
size_t algo(size_t);

static size_t table[SIZE];

int main() {
   size_t a, b, tmp, length = 0;
   table[1] = 1;
   while (true) {
      cin >> a >> b;
      if (cin.eof())
         break;
      if ( a <= b) {
         for (size_t i = a; i <= b; ++i) {
            tmp = algo(i);
            if (tmp > length)
               length = tmp;
         }
      } else {
         for (size_t i = b; i <= a; ++i) {
            tmp = algo(i);
            if (tmp > length)
               length = tmp;
         }
      }
      cout << a << " " << b << " " << length << endl;
      length = 0;
   }
   return 0;
}

size_t algo(size_t n)
{
   if (n < SIZE && table[n])
      return table[n];
   if (n & 1) {
      if (n < SIZE) {
         table[n] = 2 + algo((3 * n + 1) >> 1);
         return table[n];
      } else {
         return 2 + algo((3 * n + 1) >> 1);
      }
   } else {
      if (n < SIZE) {
         table[n] = 1 + algo(n >> 1);
         return table[n];
      } else {
         return 1 + algo(n >> 1);
      }
   }
}
