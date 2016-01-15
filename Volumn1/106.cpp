#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


vector<bool> flag;

size_t N;
size_t triCount;


void findTri(void);
void process(void);

int main(void) {
   
   while (cin >> N)
      process();
   return 0;
}

void findTri(void)
{
   flag.clear();
   flag.resize(N + 1, false);
   size_t mMax = (size_t)sqrt((double)N - 1);
   size_t nMax = 0;
   triCount = 0;
   for (size_t m = 2; m <= mMax; ++m) {
      nMax = (size_t)sqrt((double)N - m * m);
      nMax = (nMax >= m? m - 1: nMax);
      for (size_t n = 1; n <= nMax; ++n) {
         if (n % 2 != m % 2) {
            size_t a = m, b = n, c;
            for (size_t r = 0; (r = a % b) != 0; a = b, b = r);
            if (b == 1) {
               ++triCount;
               a = m * m - n * n;
               b = 2 * m * n;
               c = m * m + n * n;
               for (size_t k = 0; c * k <= N; ++k) {
                  flag[a * k] = flag[b * k] = flag[c * k] = true;
               }
            }
         }
      }
   }
}

void process(void)
{
   size_t count = 0;
   findTri();
   for (size_t i = 1; i <= N; count += !flag[i++]);
   cout << triCount << " " << count << endl; 
}
