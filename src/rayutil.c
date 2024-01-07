
#include "rayutil.h"
#include <stdio.h>
#include <raygui.h>
#include <string.h>

void DrawTextInRectangle(Font font, const char *text, Rectangle rec, float font_size, Color color) {
  if (font.texture.id == 0) font = GetFontDefault();  // Security check in case of not valid font
  
  int size = TextLength(text);    // Total size in bytes of the text, scanned by codepoints in loop

  int textOffsetY = 0;            // Offset between lines (on linebreak '\n')
  float textOffsetX = 0.0f;       // Offset X to next character to draw

  float scaleFactor = font_size/font.baseSize;         // Character quad scaling factor
  float spacing = scaleFactor;
  

  for (int i = 0; i < size;)
  {
    // Get next codepoint from byte string and glyph index in font
    int codepointByteCount = 0;
    int codepoint = GetCodepointNext(&text[i], &codepointByteCount);
    int index = GetGlyphIndex(font, codepoint);

    if (codepoint == '\n' || textOffsetX >= rec.width)
    {
        // NOTE: Line spacing is a global variable, use SetTextLineSpacing() to setup
        textOffsetY += ((float)font.recs[index].width*scaleFactor + spacing) * 2;
        textOffsetX = 0.0f;
    }
    else
    {
      if ((codepoint != ' ') && (codepoint != '\t'))
      {
        DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, font_size, color);
      }

      if (font.glyphs[index].advanceX == 0)
        textOffsetX += ((float)font.recs[index].width*scaleFactor + spacing);
      else
        textOffsetX += ((float)font.glyphs[index].advanceX*scaleFactor + spacing);
    }

    i += codepointByteCount;   // Move text bytes counter to next codepoint
  }
}


U8 *LoadFileDataArena(Arena *arena, const char *filepath, U32 *bytes_read) {
  FILE *fp = fopen(filepath, "rb");
  
  if (fp) {
    fseek(fp, 0, SEEK_END);
    *bytes_read = ftell(fp);
    rewind(fp);

    U8 *buffer = ArenaPushNoZero(arena, *bytes_read);
    fread(buffer, *bytes_read, 1, fp);

    fclose(fp);

    return buffer;

  } else TraceLog(LOG_INFO, "couldn't open file \"%s\"", filepath);

  return NULL;
}

