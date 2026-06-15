#include <iostream>
#include <vector>
#include "Log.h"

namespace
{
  struct Vertex
  {
    float x, y, z;
  };

  std::ostream &operator<<(std::ostream &stream, const Vertex &vertex)
  {
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
  }
}

// !! pass by reference to avoid copying the vector
void Function(const std::vector<Vertex> &vertices)
{
}

void DynamicArrays()
{
  // Vertex vertices[5]; // stack allocated array of 5 Vertex structs

  // vector arrays are not fragmanted in memory, they are all in line
  // if the vector needs to be resized, all data is copied to different place in memory with more available space.
  // This has disadvantage that all the data needs to be copied
  // This has advantage of faster memory access
  std::vector<Vertex> vertices;
  // In case of copying (resizing) this could be better, since the object are not copied, only the pointers vector
  // This has disadvantage in memory access
  std::vector<Vertex *> verticesPtrs;

  vertices.push_back({1, 2, 3});
  vertices.push_back({4, 5, 6});

  for (size_t i = 0; i < vertices.size(); i++)
  {
    std::cout << vertices[i] << std::endl;
  }

  // range base for loop
  // for (Vertex v : vertices) // this would be copying the vertex
  for (Vertex &v : vertices)
  {
    std::cout << v << std::endl;
  }

  vertices.erase(vertices.begin() + 1); // erase element at 1
  // vertices.clear(); // deletes the data in vector
}