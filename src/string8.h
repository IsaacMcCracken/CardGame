#include <basetypes.h>

typedef struct String8 String8;
struct String8 {
  U8 *ptr;
  U64 len;
}