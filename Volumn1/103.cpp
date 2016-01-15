/*
 * 103.cpp
 *
 *  Created on: Apr 27, 2013
 *      Author: Tzu-Yu Chuang
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Box {
public:
   Box(size_t id, vector<int> inn) : _index(id), _length(0), _boxSize(inn) {
      sorting();
      for (size_t i = 0; i < _boxSize.size(); ++i)
         _length += _boxSize[i];
   }
   int& operator [] (size_t i) { return _boxSize[i]; }
   const int& operator [] (size_t i) const { return _boxSize[i]; }
   
   size_t& getIndex(void) { return _index; }
   int& getLength(void) { return _length; }
   void printBox(void) {
      cout << "Box index: " << _index << " Length = " << _length << endl;
      for (size_t i = 0; i < _boxSize.size(); ++i)
         cout << _boxSize[i] << " ";
      cout << endl;
   }

private:
   size_t         _index;
   int            _length;
   vector<int>    _boxSize;
   // helper functions
   void sorting(void);
};

int n, dim;
vector<Box> boxList;
vector< vector<size_t> > possibleNext;
vector<size_t> answer;

bool checkBox(size_t, size_t);
void sortBox(void);
void input(void);
void process(void);
void findNest(size_t, vector<size_t>&);

int main(void) {
   while (true) {
      n = 0;
      cin >> n >> dim;
      if (cin.eof())
         break;
      input();
      process();
   }
   return 0;
}

void Box::sorting(void)
{
   for (size_t i = 0; i < _boxSize.size() - 1; ++i) {
      for (size_t j = i + 1; j < _boxSize.size(); ++j) {
         if (_boxSize[i] > _boxSize[j]) {
            int tmp = _boxSize[j];
            _boxSize[j] = _boxSize[i];
            _boxSize[i] = tmp;
         }
      }
   }
}

void process(void)
{
   possibleNext.clear();

   sortBox();
   //cout << endl;
   //for (size_t i = 0; i < boxList.size(); ++i)
   //   boxList[i].printBox();

   for (size_t i = 0; i < boxList.size(); ++i) {
      vector<size_t> tmpList;
      for (size_t j = i + 1; j < boxList.size(); ++j) {
         if (boxList[j].getLength() >= boxList[i].getLength() + dim) {
            if (checkBox(i, j)) {
               tmpList.push_back(j);
            }
         }
      }
      possibleNext.push_back(tmpList);
   }

   //for (size_t i = 0; i < possibleNext.size(); ++i) {
   //   cout << "Box # " << boxList[i].getIndex() << " is followed by : ";
   //   for (size_t j = 0; j < possibleNext[i].size(); ++j) {
   //      cout << boxList[possibleNext[i][j]].getIndex() << " ";
   //   }
   //   cout << endl;
   //}

   answer.clear();
   vector<size_t> tmpAns;
   for (size_t i = 0; i < boxList.size(); ++i) {
      tmpAns.clear();
      findNest(i, tmpAns);
   }

   cout << answer.size() << endl;
   for (size_t i = 0; i < answer.size(); ++i) {
      cout << answer[i] << " ";
   }
   cout << endl;
}

void findNest(size_t n, vector<size_t>& list)
{
   list.push_back(boxList[n].getIndex());
   //cout << "List: ";
   //for (size_t i = 0; i < list.size(); ++i)
   //   cout << list[i] << " ";
   //cout << endl;
   if (possibleNext[n].empty()) {
      if (list.size() > answer.size()) {
         answer.clear();
         for (size_t i = 0; i < list.size(); ++i)
            answer.push_back(list[i]);
      }
      list.pop_back();
   } else {
      for (size_t i = 0; i < possibleNext[n].size(); ++i) {
         findNest(possibleNext[n][i], list);
         if (i == possibleNext[n].size() - 1)
            list.pop_back();
      }
   }
}

bool checkBox(size_t i, size_t j) // check if box i less than box j
{
   for (int k = 0; k < dim; ++k) {
      if (boxList[i][k] >= boxList[j][k])
         return false;
   }
   return true;
}

void sortBox(void) // sort box according to their length
{
   for (size_t i = 0; i < boxList.size() - 1; ++i) {
      for(size_t j = i + 1; j < boxList.size(); ++j) {
         if (boxList[i].getLength() > boxList[j].getLength()) {
            Box temp = boxList[i];
            boxList[i] = boxList[j];
            boxList[j] = temp;
         }
//         if (boxList[i].getLength() == boxList[j].getLength()) {
//            if (boxList[i].getIndex() > boxList[j].getIndex()) {
//               Box temp = boxList[i];
//               boxList[i] = boxList[j];
//               boxList[j] = temp;
//            }
//         } 
      }
   }
}

void input(void)
{
   boxList.clear();
   vector<int> b;
   int tmp;
   for (int i = 0; i < n; ++i) {
      b.clear();
      for (int j = 0; j < dim; ++j) {
         cin >> tmp;
         b.push_back(tmp);
      }
      boxList.push_back(Box(i + 1, b));
   }
}
