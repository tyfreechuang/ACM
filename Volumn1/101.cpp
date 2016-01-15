#include <iostream>
#include <vector>

using namespace std;

typedef pair<size_t,size_t> Position;

class Blocks {
public:
   Blocks(size_t s) : _size(s) {
      if (s > 0) {
         _blocks = new vector<size_t>[s];
         for(size_t i = 0; i < s; ++i) {
            (*(_blocks + i)).push_back(i);
            _pos.push_back(Position(i,0));
         }
      } else {
         cout << "error!" << endl;
      }
   }
    
   void mOnto(size_t, size_t);
   void mOver(size_t, size_t);
   void pOnto(size_t, size_t);
   void pOver(size_t, size_t);
   void print();
private:
   vector<size_t>*   _blocks;
   size_t            _size;
   vector<Position>  _pos;

   void _clear(Position);
};

int main()
{
   size_t size;
   cin >> size;
   Blocks blocks(size);
   string cmd, state;
   size_t a, b;
   while(true) {
      cin >> cmd;
      if (cmd != "quit") {
         cin >> a >> state >> b;
         if (cmd == "move") {
            if (state == "onto")
               blocks.mOnto(a,b);
            if (state == "over")
               blocks.mOver(a,b);
            //blocks.print();
         }
         if (cmd == "pile") {
            if (state == "onto")
               blocks.pOnto(a,b);
            if (state == "over")
               blocks.pOver(a,b);
            //blocks.print();
         }
      } else {
         blocks.print();
         break;
      }
   }
   return 0;
}

void Blocks::mOnto(size_t a, size_t b)
{
   Position ap = _pos[a];
   Position bp = _pos[b];

   if (ap.first == bp.first)
      return;

   _clear(ap);
   _clear(bp);

   vector<size_t>& aBlock = *(_blocks + ap.first);
   vector<size_t>& bBlock = *(_blocks + bp.first);

   bBlock.push_back(a);
   aBlock.pop_back();

   _pos[a] = Position(bp.first, bp.second + 1);
}

void Blocks::mOver(size_t a, size_t b)
{
   Position ap = _pos[a];
   Position bp = _pos[b];
  
   if (ap.first == bp.first)
      return;

   _clear(ap);

   vector<size_t>& aBlock = *(_blocks + ap.first);
   vector<size_t>& bBlock = *(_blocks + bp.first);

   bBlock.push_back(a);
   aBlock.pop_back();

   _pos[a] = Position(bp.first, bBlock.size() - 1);
}

void Blocks::pOnto(size_t a, size_t b)
{
   Position ap = _pos[a];
   Position bp = _pos[b];

   if (ap.first == bp.first)
      return;

   _clear(bp);

   vector<size_t>& aBlock = *(_blocks + ap.first);
   vector<size_t>& bBlock = *(_blocks + bp.first);

   for (size_t i = ap.second;  i < aBlock.size(); ++i) {
      bBlock.push_back(aBlock[i]);
      _pos[aBlock[i]] = Position(bp.first, bp.second + 1 + i - ap.second);
   }

   if (ap.second == 0)
      aBlock.clear();
   else
      aBlock.resize(ap.second);
}

void Blocks::pOver(size_t a, size_t b)
{
   Position ap = _pos[a];
   Position bp = _pos[b];
   
   if (ap.first == bp.first)
      return;
   vector<size_t>& aBlock = *(_blocks + ap.first);
   vector<size_t>& bBlock = *(_blocks + bp.first);

   for (size_t i = ap.second; i < aBlock.size(); ++i) {
      bBlock.push_back(aBlock[i]);
      _pos[aBlock[i]] = Position(bp.first, bBlock.size() - 1);
   }
  
   if (ap.second == 0)
      aBlock.clear();
   else
      aBlock.resize(ap.second);
}

void Blocks::print()
{
   for (size_t i = 0; i < _size; ++i) {
      cout << i << ":";
      vector<size_t>& tmp = *(_blocks + i);
      for (size_t j = 0; j < tmp.size(); ++j)
         cout << " " << tmp[j];
      cout << endl;
   }
}

void Blocks::_clear(Position pos)
{
   vector<size_t>& tmp = *(_blocks + pos.first);
   while (tmp.size() != pos.second + 1) {
      size_t b = tmp.back();
      (*(_blocks + b)).push_back(b);
      _pos[b] = Position(b,0);
      tmp.pop_back();
   }
}
