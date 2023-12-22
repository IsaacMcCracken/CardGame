/*
  This file is for raylib functionality that is not implemented raylib it's self

  
*/


#ifndef RAY_UTIL_H
#define RAY_UTIL_H

#include <basetypes.h>
#include <raylib.h>

#define RAYUTIL inline

void DrawTextInRectangle(Font font, const char *text, Rectangle rec, float font_size, Color color);


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