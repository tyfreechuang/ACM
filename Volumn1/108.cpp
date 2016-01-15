#include <iostream>
#include <vector>

#define INF 100000

using namespace std;

vector< vector<int> > A;
size_t N;

void input(void);
void process(void);

int sequence(vector<int> const &);

int main(void) {

   while (cin >> N) {
      input();
      process();
   }

   return 0;
}

void input(void)
{
   A.clear();
   A.resize(N);
   int tmp;
   for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
         cin >> tmp;
         A[i].push_back(tmp);
      }
   }
}

void process(void)
{
   int maxSum = -INF;
   vector<int> tmpSeq;
   int tmpSum;
   for (size_t i = 0; i < N; ++i) {
      tmpSeq.clear();
      tmpSeq = A[i];
      tmpSum = sequence(tmpSeq);
      //cout << tmpSum << endl;
      if (tmpSum > maxSum)
         maxSum = tmpSum;

      for (size_t j = i + 1; j < N; ++j) {
         for (size_t k = 0; k < tmpSeq.size(); ++k)
            tmpSeq[k] += A[j][k];

         tmpSum = sequence(tmpSeq);
         //cout << tmpSum << endl;
         if (tmpSum > maxSum)
            maxSum = tmpSum;
      }
   }
   cout << maxSum << endl;
}

int sequence(vector<int> const & num)
{
   // Initialize variables here
   int maxSoFar = num[0], maxEndHere = num[0];
   // OPTIONAL: These variables can be added in to track the position of the sub array
   // size_t begin = 0;
   // size_t begin_tmp = 0;
   // size_t end = 0;

   // Find sequence by looping through
   for (size_t i = 1; i < num.size(); ++i) {
      // calculate max_ending_here
      if (maxEndHere + num[i] < num[i]) {
         maxEndHere = num[i];
         // beting_tmp = i;
      } else {
         maxEndHere += num[i];
      }

      // calculate max_so_far
      if (maxEndHere >= maxSoFar) {
         maxSoFar = maxEndHere;
         // begin = begin_tmp;
         // end = i;
      }
   }
   return maxSoFar;
}
