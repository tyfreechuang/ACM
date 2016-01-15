#include <iostream>
#include <stdio.h>
#include <vector>

#define MAX 20

using namespace std;

void trans(vector<int>& seq, vector<int>& rank)
{
   for (size_t i = 0; i < rank.size(); ++i)
      seq[rank[i] - 1] = i;
}

int main(void) {
   size_t n;

   // read correct rank
   scanf("%ld", &n);
   vector<int> rank(n, 0);
   for (size_t i = 0; i < n; ++i) {
      scanf("%d", &rank[i]);
   }

   // transfer to correct sequence
   vector<int> correct(n, 0);
   trans(correct, rank);

   // build reference map
   vector<int> map(n, 0);
   for (size_t i = 0; i < n; ++i) {
      map[correct[i]] = i;
   }
   

   while (scanf("%d", &rank[0]) == 1) {
      // read student's answer
      for (size_t i = 1; i < n; ++i)
         scanf("%d", &rank[i]);

      vector<int> aSeq(n, 0), ans(n, 0);
      trans(aSeq, rank);

      for (size_t i = 0; i < n; ++i) {
         ans[i] = map[aSeq[i]];
      }

      // LIS
      vector<int> best(n, 0);
      size_t length = 1;

      best[0] = ans[0];

      for (size_t i = 1; i < n; ++i) {
         for (size_t j = 0; j < length; ++j) {
            if (ans[i] < best[j]) {
               best[j] = ans[i];
               break;
            }
         }
         if (ans[i] > best[length - 1]) {
            best[length++] = ans[i];
         }
      }
      printf("%ld\n", length);
   }
   return 0;
}
