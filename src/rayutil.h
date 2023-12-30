/*
  This file is for raylib functionality that is not implemented raylib it's self

  
*/


#ifndef RAY_UTIL_H
#define RAY_UTIL_H

#include <basetypes.h>
#include <raylib.h>
#include "arena.h"

#define RAYUTIL inline

// Useful Macros
#define Max(a, b) (a > b)? a : b
#define Min(a, b) (a < b)? a : b


void DrawTextInRectangle(Font font, const char *text, Rectangle rec, float font_size, Color color);
U8 *LoadFileDataArena(Arena *arena, const char *filepath, U32 *bytes_read);

RAYUTIL I32 Log2(I32 x) {
  I32 result = 0;
  while (x >>= 1) result++;
  return result;
}

RAYUTIL Timer TimerStart(F64 time_in_seconds) {
  return (Timer){
    .start_time = GetTime(),
    .end_time = GetTime() + time_in_seconds,
  };
}

RAYUTIL bool TimerIsDone(Timer timer) {
  return timer.end_time >= GetTime();
}


#endif // RAY_UTIL_H