#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

static size_t bottles[9 + 3];

size_t count_movement(size_t a, size_t b, size_t c)
{
   size_t m = 0;
   for (size_t i = 0; i < 9; ++i) {
      if (i != a && i != b && i != c)
         m += bottles[i];
   }
   return m;
}

int main()
{
   while (scanf("%lu", &bottles[0]) != EOF) {
      for (size_t i = 1; i < 9; ++i)
         scanf("%lu", &bottles[i]);
      
      char output_str[3 + 3];
      size_t movement[6];
      size_t min_movement = 0x0 - 0x1;
      char combinations[6][3 + 2] = { "BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};

      // Brown index : 0 3 6
      // Green index : 1 4 7
      // Clear index : 2 5 8
      
      movement[0] = count_movement(0, 5, 7); // BCG
      movement[1] = count_movement(0, 4, 8); // BGC
      movement[2] = count_movement(2, 3, 7); // CBG
      movement[3] = count_movement(2, 4, 6); // CGB
      movement[4] = count_movement(1, 3, 8); // GBC
      movement[5] = count_movement(1, 5, 6); // GCB

      for (size_t i = 0; i < 6; ++i) {
         if (movement[i] < min_movement) {
            min_movement = movement[i];
            strcpy(output_str, combinations[i]);
         }
      }
      
      printf("%s %lu\n", output_str, min_movement);
   }
   return 0;
}


