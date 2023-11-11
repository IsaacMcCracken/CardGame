#include <base.h>

// #include <String.h>
#include <Windows.h>

#define GIGABYTE 1073741824

#define MemSet(dest, value, size) memset((dest), (value), (size))

/* These are totally mine arena functions*/
Arena *ArenaInit(u64 size) {
  u64 size_roundup_granularity = Megabytes(64);
  size += size_roundup_granularity-1;
  size -= size%size_roundup_granularity;

  void *block = VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);
  VirtualAlloc(block, Kilobytes(4), MEM_COMMIT, PAGE_READWRITE);
  Arena *arena = (Arena*)block;
  arena->pos = sizeof(Arena);
  arena->commit_pos = Kilobytes(4);
  arena->align = 8;
  arena->size = size;
  return arena;
}

Arena *ArenaInitDefault(void) {
  Arena *arena = ArenaInit(Gigabytes(8));
  return arena;
}

void ArenaDeinit(Arena *arena) {
    VirtualFree(arena, 0, MEM_RELEASE);
}

void *ArenaPushNoZero(Arena *arena, u64 size) {
  void *result = 0;
  if(arena->pos + size <= arena->size) {
    u8 *base = (u8 *)arena;
    u64 post_align_pos = (arena->pos + (arena->align-1));
    post_align_pos -= post_align_pos%arena->align;
    u64 align = post_align_pos - arena->pos;
    result = base + arena->pos + align;
    arena->pos += size + align;

    if(arena->commit_pos < arena->pos) {
        u64 size_to_commit = arena->pos - arena->commit_pos;
        size_to_commit += Kilobytes(4) - 1;
        size_to_commit -= size_to_commit%Kilobytes(4);
        VirtualAlloc(base + arena->commit_pos, size_to_commit, MEM_COMMIT, PAGE_READWRITE);
        arena->commit_pos += size_to_commit;
    }
  }
  else {
    // NOTE(rjf): fallback Str8ategy. right now, just fail.
  }
  
  return result;
}

void *ArenaPushAligner(Arena *arena, u64 alignment) {
  u64 pos = arena->pos;
  u64 pos_rounded_up = pos + alignment-1;
  pos_rounded_up -= pos_rounded_up%alignment;
  u64 size_to_alloc = pos_rounded_up - pos;
  void *result = 0;
  if(size_to_alloc != 0) {
    result = ArenaPushNoZero(arena, size_to_alloc);
  }
  return result;
}



void *ArenaPush(Arena *arena, u64 size) {
  void *result = ArenaPushNoZero(arena, size);
  
  MemSet(result, 0, size);
  return result;
}

void ArenaPopTo(Arena *arena, u64 pos) {
  u64 min_pos = sizeof(Arena);
  u64 new_pos = Max(min_pos, pos);
  arena->pos = new_pos;
  u64 pos_aligned_to_commit_chunks = arena->pos + Kilobytes(4)-1;
  pos_aligned_to_commit_chunks -= pos_aligned_to_commit_chunks%Kilobytes(4);
  
  if(pos_aligned_to_commit_chunks + Megabytes(64) <= arena->commit_pos){
    u8 *base = (u8 *)arena;
    u64 size_to_decommit = arena->commit_pos-pos_aligned_to_commit_chunks;
    VirtualFree(base + pos_aligned_to_commit_chunks, size_to_decommit, MEM_DECOMMIT);
    arena->commit_pos -= size_to_decommit;
  }
}

void
ArenaSetAutoAlign(Arena *arena, u64 align) {
  arena->align = align;
}

void ArenaPop(Arena *arena, u64 size) {
  u64 min_pos = sizeof(Arena);
  u64 size_to_pop = Min(size, arena->pos);
  u64 new_pos = arena->pos - size_to_pop;
  new_pos = Max(new_pos, min_pos);
  ArenaPopTo(arena, new_pos);
}

void ArenaReset(Arena *arena) {
  ArenaPopTo(arena, sizeof(Arena));
}

u64 ArenaPos(Arena *arena) {
  return arena->pos;
}

////////////////////////////////
//~ rjf: Arena Temp Functions

ArenaTemp ArenaTempBegin(Arena *arena) {
  ArenaTemp temp = {0};
  temp.arena = arena;
  temp.pos = arena->pos;
  return temp;
}

void ArenaTempEnd(ArenaTemp temp) {
  ArenaPopTo(temp.arena, temp.pos);
}


Str8 Str8Lit(char* str) {
    Str8 s;
    int i = 0;
    while (str[i])
        i++;
    
    s.len = i;
    s.str = str;

    return s;
}

Str8 Str8Cat(Arena* arena, Str8 a, Str8 b) {
    u64 i;
    Str8 s;

    s.len = a.len + b.len; 

    s.str = ArenaPush(arena, s.len);

    for (i = 0; i < a.len; i++) 
        s.str[i] = a.str[i];

    for (i = 0; i < b.len; i++) 
        s.str[i + a.len] = b.str[i];
    
    return s;
}


void Str8CatNoArena(Str8 *dest, Str8 src, u64 buffSize) {
  for (size_t i = 0; i < src.len && i + dest->len < buffSize; i++) {
    dest->str[dest->len + i] = src.str[i];
  }
  dest->len = dest->len + src.len;
}

/* Str8ing Compare Alphabet*/
int Str8CmpA(Str8 a, Str8 b) {
    return 0;   
}

/* if a == b return 0 if a < b return 1 else return -1*/
int Str8CmpI(Str8 a, Str8 b) {
    u64 minLen = Min(a.len, b.len);

    for (u64 i = 0; i < minLen; i++) {
        if (a.str[i] < b.str[i])
            return -1;
        else if (a.str[i] > b.str[i])
            return 1;
        
    }

    if (a.len < b.len)
        return -1;
    else if (a.len > b.len)
        return 1;

    return 0;
}

void Str8Cpy(Str8* dest, const Str8 source) {
    for (u64 i = 0; i < source.len; i++)
        dest->str[i] = source.str[i];
    dest->len = source.len;
}

void Str8InsertChar(Str8* s, char c, u64 index) {
    s->len++;
    for (u64 i = s->len - 1; i >index; i--) {
        s->str[i] = s->str[i-1];
    }

    s->str[index] = c;
    
}


void Str8RemoveChar(Str8* s, u64 index) {
    s->len--;
    for (u64 i = index; i < s->len; i++) {
        s->str[i] = s->str[i + 1];
    }
}


void Str8Print(Str8 s) {
    WriteFile(LongToHandle(STD_OUTPUT_HANDLE), s.str, s.len, 0, NULL);
}