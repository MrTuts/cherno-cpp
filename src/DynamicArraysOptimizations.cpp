#include <iostream>
#include <vector>
#include "Log.h"

namespace
{
  struct Vertex
  {
    float x, y, z;

    Vertex(float x, float y, float z) : x(x), y(y), z(z) {};

    // copy constructor
    Vertex(const Vertex &vertex)
    {
      Log("Copied!");
    }
  };
}

void DynamicArraysOptimizations()
{
  std::vector<Vertex> vertices;
  vertices.reserve(3); // reserve memory for 3 vertices, so no copying is needed when adding new vertices
  // std::vector<Vertex> vertices(3); // this would construct 3 vertex objects, which is not what we want, we just want to reserve enough space in memory ATM

  // This way the Vertex is constructed on the main function and then copied into the vertices vector
  // vertices.push_back(Vertex(1, 2, 3));

  // with this, we can construct the Vertex in the actual vector
  vertices.emplace_back(1, 2, 3); // we pass parametr list for the constructor, so the Vertex is constructed directly in the vector, without copying
  vertices.emplace_back(4, 5, 6);
  vertices.emplace_back(7, 8, 9);
}
