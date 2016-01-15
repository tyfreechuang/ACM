#include <iostream>
#include <cstdio>
#include <cmath>

#define esp (1e-8)

using namespace std;

size_t a; //= (N+1) ^ k
size_t b; //= N ^ k
int main(void) {
   while (cin >> a >> b) {
      if (a == 0 && b == 0)
         break;
      if (a == b && b == 1)
         cout << "0 1" << endl;
      else {
         for (size_t k = 0; ;++k) {
            double n = pow(b, 1.0/k);
            if (fabs(a - pow(1 + n, k)) < esp) {
               double m;
               if (n > 1)
                  m = (pow(n, k + 1) - 1) / (n - 1) - b;
               else m = k;
               double t = 1, s = 1;
               for (size_t i = 1; i <= k; ++i) {
                  t *= n / (n + 1);
                  s += t;
               }
               s *= a;
               printf("%.0f %.0f\n",m,s);
               break;
            }
         }
      }   
   }
}

