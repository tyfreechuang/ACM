#include <iostream>
#include <stdio.h>

using namespace std;

class ArrayList {
public:
    ArrayList(){ _size = 0; }
    void clear() { _size = 0; }
    void print() { 
        for (size_t i = 0; i < _size - 1; ++i)
            printf("%c,", _data[i]);           
        printf("%c", _data[_size - 1]);
    } 
    void swap(size_t x, size_t y) {
        size_t tmp = _data[x];
        _data[x] = _data[y];
        _data[y] = tmp;
    }
    void push_back(size_t input) {
        _data[_size++] = input;
    }
    size_t pop_head(void) {
        size_t head = _data[0];
        for (size_t i = 0; i < _size; ++i)
            _data[i] = _data[i + 1];
        --_size;
        return head;
    }
    int& operator [] (size_t i) { return _data[i]; }
    const int& operator [] (size_t i) const { return _data[i]; } 
    size_t& size(void) { return _size; }
private:
    int _data[32];
    size_t _size;
};

void printSeq(char c, int length) {
    for (int i = 0; i < length - 1; ++i)
        printf("%c,", c + i);
    printf("%c", c + length - 1);
}

void indense(size_t num) {
    for (size_t i = 0; i < num; ++i)
        printf("  ");
}

void metaSort(ArrayList &ls, int insertChar, int bound) {
    // terminal condition
    if (insertChar == bound) {
        indense(insertChar - 'a');
        printf("writeln(");
        ls.print();
        printf(")\n");
        return;
    }

    // insert char to the tail first
    ls.push_back(insertChar);

    indense(insertChar - 'a');
    printf("if %c < %c then\n", ls[ls.size() - 2], ls[ls.size() - 1]);

    metaSort(ls, insertChar + 1, bound);

    // insert char to every space
    for (size_t i = ls.size() - 1; i != 0; --i) {
        ls.swap(i, i - 1);
        // -----------------------
        indense(insertChar - 'a');
        if ( i == 1)
            printf("else\n");
        else
            printf("else if %c < %c then\n", ls[i - 2], ls[i - 1]);
        //------------------------

        metaSort(ls, insertChar + 1, bound);
    }

    ls.pop_head(); // delete head
}

int main(void) {
    ArrayList ls;
    size_t times, max;
    scanf("%ld", &times);
    for (size_t i = 0; i < times; ++i) {
      scanf("%ld", &max);
      // ---------------
      printf("program sort(input,output);\nvar\n");
      printSeq('a', max);
      printf(" : integer;\nbegin\n  readln(");
      printSeq('a', max);
      printf(");\n");
      // ---------------
    
      ls.push_back('a');
      metaSort(ls, 'b', 'a' + max);
      ls.clear();

      // ------------
      printf("end.\n");
      if (i != times - 1)
         printf("\n");
      // ------------
    }
    return 0;
}
