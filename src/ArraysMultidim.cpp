#include "Log.h"

void Array3DExample()
{
  // 3D array
  int ***a3d = new int **[5];
  for (int i = 0; i < 5; i++)
  {
    a3d[i] = new int *[5];
    for (int j = 0; j < 5; j++)
    {
      a3d[i][j] = new int[5];
    }
  }

  // memory cleanup
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      delete[] a3d[i][j];
    }
    delete[] a3d[i];
  }
}

void MultidimInSingleDimExample()
{
  int *array = new int[5 * 5];

  // accessing in a single loop
  for (int i = 0; i < 25; i++)
  {
    array[i] = 2;
  }

  // accessing in a two loops
  for (int y = 0; y < 5; y++)
  {
    for (int x = 0; x < 5; x++)
    {
      array[x + y * 5] = 2;
    }
  }
}

void ArrayMultidim()
{
  LogSectionTitle("Multidimensional arrays");

  // allocate memory for 5 int pointers (200 bytes)
  // These will point to our int arrays
  int **a2d = new int *[5];

  for (int i = 0; i < 5; i++)
  {
    // allocate memory for 5 ints (200 bytes) and store the pointer in our 2D array of pointers
    a2d[i] = new int[5];
  }
  // accessing the arrays
  a2d[0][0] = 0;
  a2d[0][1] = 4;
  a2d[0][2] = 5;
  /*
    This leads to memory fragmentation, each array can be anywhere in the memory, some not close at all.
    Can lead to cache misses. A cache miss is an event where CPU requests data from a high-speed cache, but the data is not there.
    Because the cache doesn't have the information, the system must pause and retrieve it from the slower main memory or database
  */
  /*
  To overcome this memory fragmentation, we can store everything in single array instead
   */
  MultidimInSingleDimExample();

  Array3DExample();

  for (int i = 0; i < 50; i++)
  {
    delete[] a2d[i];
  }
  delete[] a2d;
}