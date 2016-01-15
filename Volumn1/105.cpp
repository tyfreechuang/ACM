#include <iostream>
#include <vector>

using namespace std;

class Building {
public:
   Building(size_t l, size_t r, size_t h) : _left(l), _right(r), _height(h) {}

   size_t& left (void) { return _left; }
   size_t& right (void) { return _right; }
   size_t& height (void) { return _height; }
private:
   size_t _left;
   size_t _right;
   size_t _height;
};

void input(void);
void process(void);

vector<Building> bs;

int main(void) {
   input();
   process();
 
   return 0;
}


void process(void) 
{
   //for (size_t i = 0; i < bs.size(); ++i)
   //   cout << "Building " << i << endl
   //        << "(" << bs[i].left() << ", "
   //        << bs[i].right() << ", "
   //        << bs[i].height() << ")" << endl;

   vector<size_t> skyline; // skyline[i] : i - (i + 1);
   skyline.reserve(10000);
   skyline.push_back(0); // 0 - 1;
   for (size_t i = 0; i < bs.size(); ++i) {
      for (size_t j = skyline.size(); j <= bs[i].right(); ++j)
         skyline.push_back(0);

      for (size_t j = bs[i].left(); j < bs[i].right(); ++j) {
         if (skyline[j] < bs[i].height())
            skyline[j] = bs[i].height();
      }
   }

   size_t h = 0;

   //for (size_t i = 1; i < skyline.size() - 1; ++i)
   //   cout << skyline[i] << " "; 
   //cout << endl;
   for (size_t i = 1; i < skyline.size() - 1; ++i) {
      if (skyline[i] != h) {
         h = skyline[i];
         cout << i << " " << h << " ";
      } 
   }
   cout << skyline.size() - 1 << " 0" << endl;
}
void input(void)
{
   size_t left;
   size_t right;
   size_t height;
   while (cin >> left >> height >> right) {
      bs.push_back(Building(left, right, height));
   }
}
