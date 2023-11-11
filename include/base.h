#ifndef ME_BASE
#define ME_BASE



typedef void (*Func)(void*);
typedef void (*Proc)(void);

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

#if !defined(RL_VECTOR2_TYPE)
// Vector2 type
typedef struct Vector2 {
    float x;
    float y;
} Vector2;
#define RL_VECTOR2_TYPE
#endif

#if !defined(RL_VECTOR3_TYPE)
// Vector3 type
typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;
#define RL_VECTOR3_TYPE
#endif

#if !defined(RL_VECTOR4_TYPE)
// Vector4 type
typedef struct Vector4 {
    float x;
    float y;
    float z;
    float w;
} Vector4;
#define RL_VECTOR4_TYPE
#endif

#if !defined(RL_QUATERNION_TYPE)
// Quaternion type
typedef Vector4 Quaternion;
#define RL_QUATERNION_TYPE
#endif

#if !defined(RL_MATRIX_TYPE)
// Matrix type (OpenGL style 4x4 - right handed, column major)
typedef struct Matrix {
    float m0, m4, m8, m12;      // Matrix first row (4 components)
    float m1, m5, m9, m13;      // Matrix second row (4 components)
    float m2, m6, m10, m14;     // Matrix third row (4 components)
    float m3, m7, m11, m15;     // Matrix fourth row (4 components)
} Matrix;
#define RL_MATRIX_TYPE
#endif



#include <stdio.h>

#define Assert(condition, ...) do {if (!(condition)) {fprintf(stderr, __VA_ARGS__); (*(volatile int *)0 = 0);} } while (0)


#define Log(...) do { printf("LOG: %s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); putchar('\n'); } while (0)

#define EvalPrintI(x) printf("%s = %lld\n", #x, (long long)(x))
#define EvalPrintF(x) printf("%s = %f\n", #x, (double)(x))
#define EvalPrintB(x) printf("%s = %s\n", #x, (char*)((x)?"True":"False"))

#define MATH_E      2.7182818285
#define MATH_PI     3.1415926536
#define MATH_TAU    6.2831853072

#define Min(a, b)   (((a)<(b))?(a):(b))
#define Max(a, b)   (((a)>(b))?(a):(b))

#define Kilobytes(n) ((n) << 10)
#define Megabytes(n) ((n) << 20)
#define Gigabytes(n) (((u64)(n)) << 30)

/* Loop Macros */
#define LoopZeroToN(n)  long ___i___i = 0; ___i___i < (n); ___i___i++


/* Str8ings And Memory */
typedef struct Str8 Str8;
struct Str8 {
    char* str;
    u64 len;
};

typedef struct Arena Arena;
struct Arena
{
  u64 pos;
  u64 commit_pos;
  u64 align;
  u64 size;
  void *ptr;
  u64 _unused_[3];
};

typedef struct ArenaTemp ArenaTemp;
struct ArenaTemp
{
  Arena *arena;
  u64 pos;
};


typedef struct PoolFreeNode PoolFreeNode;
struct PoolFreeNode {
	PoolFreeNode *next;
};

typedef struct {
    Arena arena;
    u64 chunkSize;
    PoolFreeNode* head;
} Pool;



/* Arena Memory Stuff UwU */
Arena *ArenaInit(u64 size);
Arena *ArenaInitDefault(void);
void ArenaDeinit(Arena *arena);
void *ArenaPushNoZero(Arena *arena, u64 size);
void *ArenaPushAligner(Arena *arena, u64 alignment);
void *ArenaPush(Arena *arena, u64 size);
void ArenaPopTo(Arena *arena, u64 pos);
void ArenaSetAutoAlign(Arena *arena, u64 align);
void ArenaPop(Arena *arena, u64 size);
void ArenaReset(Arena *arena);
u64 ArenaPos(Arena *arena);
/* Temporary Arena MMMMmmm*/
ArenaTemp ArenaTempBegin(Arena *arena);
void ArenaTempEnd(ArenaTemp temp);
/* Pool Memory Stuff */
Pool PoolInit(u64 chunkSize);


Str8 Str8Lit(char* str);
Str8 Str8Cat(Arena* arena, Str8 a, Str8 b);
void Str8CatNoArena(Str8 *dest, Str8 src, u64 buffSize);
int Str8CmpI(Str8 a, Str8 b);
void Str8Cpy(Str8* dest, const Str8 source);
void Str8InsertChar(Str8* s, char c, u64 index);
void Str8RemoveChar(Str8* s, u64 index);
void Str8Print(Str8 s);


#endif /* ME_BASE */

