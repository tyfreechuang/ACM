#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void input(void);
void process(void);
void findPath(vector< vector< vector<int> > >&, int, int, size_t);

size_t n;
vector< vector< vector<double> > > rateTable;
vector< vector< vector<int   > > > path;

int main(void) {
   while (true) {
      n = 0;
      cin >> n;
      if (cin.eof())
         break;
      input();
      process();
   }
   return 0;
}

void findPath(vector< vector< vector<int> > >& path, int start, int end, size_t stepNum)
{
   if (path[stepNum][start][end] != -1) {
      findPath(path, start, path[stepNum][start][end], stepNum - 1);
      cout << " " << path[stepNum][start][end] + 1;
   }
}

void process(void)
{
   //cout << endl << "This is for DEBUG:" << endl;
   //for (size_t i = 0; i < n; ++i) {
   //   for (size_t j = 0; j < n; ++j)
   //      cout << right << setw(10) << rateTable[0][i][j];
   //   cout << endl;
   //}

   int start = -1;
   size_t stepNum = 0;

   for (size_t step = 1; step < n; ++step) {
      for (size_t k = 0; k < n; ++k) {
         for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
               if (rateTable[step - 1][i][k] * rateTable[0][k][j] > rateTable[step][i][j]) {
                  rateTable[step][i][j] = rateTable[step - 1][i][k] * rateTable[0][k][j];
                  path[step][i][j] = k;
                  if (i == j && rateTable[step][i][j] > 1.01) {
                     start = i;
                     stepNum = step;
                     break;
                  } 
               }
            }
            if (start != -1)
               break;
         }
         if (start != -1)
            break;
      }
      if (start != -1)
         break;
   }
   if (start == -1)
      cout << "no arbitrage sequence exists" << endl;
   else {
      cout << start + 1;
      findPath(path, start, start, stepNum);
      cout << " " << start + 1 << endl;
   }
}

void input(void)
{
   rateTable.clear();
   path.clear();
   rateTable.resize(n, vector< vector<double> >(n, vector<double>(n, -1)));
   path.resize(n, vector< vector<int> >(n, vector<int>(n, -1)));
   
   double rate;
   for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
         if (j == i) {
            rate = 1.0;
         } else {
            cin >> rate;
         }
         rateTable[0][i][j] = rate;
      }
   }
}
