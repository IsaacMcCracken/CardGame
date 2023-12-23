#include "md.h"
#include "md.c"


int main() {
  MD_Arena *arena = MD_ArenaAlloc();

  MD_ParseResult card_parse = MD_ParseWholeFile(arena, MD_S8Lit("../metafiles/card_types.mdesk"));

  
  for (MD_EachNode(node, card_parse.node->first_child)) {
    for (MD_EachNode(tag, node->first_tag)) {
      printf("tag: \"%*.s\"\n", MD_S8VArg(tag->string));
    }
  }

  return 0;
}