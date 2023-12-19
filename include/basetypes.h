#pragma once

// Unsigned Integers
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;
typedef unsigned long long U64;

// Signed Integers
typedef signed char       I8;
typedef signed short      I16;
typedef signed long       I32;
typedef signed long long  I64;

// Floats
typedef float F32;
typedef double F64;

typedef struct WorldCoord WorldCoord;
struct WorldCoord {
  I32 x;
  I32 y;
};

typedef struct WorldCoordList WorldCoordList;
struct WorldCoordList {
  WorldCoord *ptr;
  U64 len;
};


typedef struct Timer Timer;
struct Timer {
  F64 start_time;
  F64 end_time;
};
