#ifndef VERTEX_H
#define VERTEX_H
#include "Angel.h"
struct Vertex2D
{
    Vertex2D(vec2 pos, vec4 color) : Position(pos), Color(color){};
    vec2 Position;
    vec4 Color;

};
#endif
