#include <stdlib.h>
#include <string.h>
#include "gbacolor.h"
#include "gbagraphics.h"
#include "gbautils.h"
#include "gbabios.h"
#include "gbadma.h"
#include "gbaio.h"

VideoBuffer _video_buffer = M4_PAGE1;

void flip_vid_page()
{
  if (_video_buffer == M4_PAGE1)
  {
    cpu_zero_memory((void*) M4_PAGE2, 0x2580);
    _video_buffer = M4_PAGE2;
  }
  else
  {
    cpu_zero_memory((void*) M4_PAGE1, 0x2580);
    _video_buffer = M4_PAGE1;
  }

  REG_DISPCNT ^= DISPCNT_TOGGLE_PAGE;
}

void m4_draw_pixel(uint32_t x, uint32_t y, uint32_t color_index)
{
  uint16_t *dst = m4_get_pixel(x, y);
  if (x & 1)
  {
    // Odd x-coordinate.
    *dst = (*dst & 0x00FF) | (color_index << 8);
  }
  else
  {
    // Even x-coordinate.
    *dst = (*dst & 0xFF00) | color_index;
  }
}

void m4_draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color_index)
{
  x0 = CLAMP(x0, 0, SCREEN_WIDTH - 1);
  x1 = CLAMP(x1, 0, SCREEN_WIDTH - 1);
  y0 = CLAMP(y0, 0, SCREEN_HEIGHT - 1);
  y1 = CLAMP(y1, 0, SCREEN_HEIGHT - 1);

  int32_t dx = abs(x1 - x0);
  int32_t dy = abs(y1 - y0);
  int32_t sx = (x0 < x1) ? 1 : -1;
  int32_t sy = (y0 < y1) ? 1 : -1;
  int32_t err = dx - dy;
  m4_draw_pixel(x0, y0, color_index);
  while (x0 != x1 || y0 != y1)
  {
    int32_t epsilon = err << 1;
    if (epsilon > -dy)
    {
      err -= dy;
      x0 += sx;
    }
    if (epsilon < dx)
    {
      err += dx;
      y0 += sy;
    }

    m4_draw_pixel(x0, y0, color_index);
  }
}

void m4_draw_circle_fill(int32_t x0, int32_t y0, uint32_t radius, uint32_t color_index)
{
  if (radius < 1)
  {
    return;
  }

  int32_t x = radius;
  int32_t y = 0;
  int32_t decisionOver2 = 1 - x;
  while (x >= y)
  {
    m4_draw_line(y + x0, x + y0, x0 - y, x + y0, color_index);
    m4_draw_line(x + x0, y + y0, x0 - x, y + y0, color_index);
    m4_draw_line(y + x0, y0 - x, x0 - y, y0 - x, color_index);
    m4_draw_line(x + x0, y0 - y, x0 - x, y0 - y, color_index);
    y++;
    if (decisionOver2 <= 0)
    {
      decisionOver2 += (y << 1) + 1;
    }
    else
    {
      x--;
      decisionOver2 += ((y - x) << 1) + 1;
    }
  }
}

void m4_draw_circle(int32_t x0, int32_t y0, uint32_t radius, uint32_t color_index)
{
  if (radius < 1)
  {
    return;
  }

  int32_t x = radius;
  int32_t y = 0;
  int32_t decisionOver2 = 1 - x;
  while (x >= y)
  {
    m4_draw_pixel(x + x0, y + y0, color_index);
    m4_draw_pixel(x0 - x, y + y0, color_index);
    m4_draw_pixel(y + x0, x + y0, color_index);
    m4_draw_pixel(x0 - y, x + y0, color_index);
    m4_draw_pixel(x0 - x, y0 - y, color_index);
    m4_draw_pixel(x + x0, y0 - y, color_index);
    m4_draw_pixel(x0 - y, y0 - x, color_index);
    m4_draw_pixel(y + x0, y0 - x, color_index);
    y++;
    if (decisionOver2 <= 0)
    {
      decisionOver2 += (y << 1) + 1;
    }
    else
    {
      x--;
      decisionOver2 += ((y - x) << 1) + 1;
    }
  }
}

void m4_draw_rect_fill(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color_index)
{
  int32_t dx = abs(x1 - x0);
  int32_t dy = abs(y1 - y0);
  int32_t x = (x0 < x1) ? x0 : x1;
  int32_t y = (y0 < y1) ? y0 : y1;
  for (dy++; dy > 0; dy--, y++)
  {
    m4_draw_line(x, y, x + dx, y, color_index);
  }
}

void m4_draw_rect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color_index)
{
  m4_draw_line(x0, y0, x1, y0, color_index);
  m4_draw_line(x0, y0, x0, y1, color_index);
  m4_draw_line(x1, y0, x1, y1, color_index);
  m4_draw_line(x0, y1, x1, y1, color_index);
}

void m4_draw_triangle(int32_t x, int32_t y, uint32_t base, uint32_t height, uint32_t rot, uint32_t color_index)
{
  x = CLAMP(x, 0, SCREEN_WIDTH - 1);
  y = CLAMP(y, 0, SCREEN_HEIGHT - 1);

  int32_t x0 = x, y0 = y, x1, y1;
  int32_t dx, dy, sx, sy;
  if (rot == ROTATE_270_DEG || rot == ROTATE_90_DEG)
  {
    dx = height; dy = base >> 1;
    x1 = (rot == ROTATE_90_DEG) ? (x0 - dx) : (x0 + dx);
    y1 = y0 + dy;
    sx = (rot == ROTATE_90_DEG) ? -1 : 1;
    sy = 1;
  }
  else
  {
    dx = base >> 1; dy = height;
    x1 = x0 + dx;
    y1 = (rot == ROTATE_180_DEG) ? (y0 - dy) : (y0 + dy);
    sx = 1;
    sy = (rot == ROTATE_180_DEG) ? -1 : 1;
  }

  int32_t err = dx - dy;
  m4_draw_pixel(x0, y0, color_index);
  while (1)
  {
    int32_t epsilon = err << 1;
    if (epsilon > -dy)
    {
      err -= dy;
      x += sx;
    }
    if (epsilon < dx)
    {
      err += dx;
      y += sy;
    }

    // Draw a line when we're at the base of the triangle.
    if (x == x1 && y == y1)
    {
      if (rot == ROTATE_270_DEG || rot == ROTATE_90_DEG)
      {
        m4_draw_line(x, (y0 << 1) - y, x, y, color_index);
      }
      else
      {
        m4_draw_line((x0 << 1) - x, y, x, y, color_index);
      }

      break;
    }
    else
    {
      if (rot == ROTATE_270_DEG || rot == ROTATE_90_DEG)
      {
        m4_draw_pixel(x, (y0 << 1) - y, color_index);
      }
      else
      {
        m4_draw_pixel((x0 << 1) - x, y, color_index);
      }

      m4_draw_pixel(x, y, color_index);
    }
  }
}

void m4_draw_triangle_fill(int32_t x, int32_t y, uint32_t base, uint32_t height, uint32_t rot, uint32_t color_index)
{
  x = CLAMP(x, 0, SCREEN_WIDTH - 1);
  y = CLAMP(y, 0, SCREEN_HEIGHT - 1);

  int32_t x0 = x, y0 = y, x1, y1;
  int32_t dx, dy, sx, sy;
  if (rot == ROTATE_270_DEG || rot == ROTATE_90_DEG)
  {
    dx = height; dy = base >> 1;
    x1 = (rot == ROTATE_90_DEG) ? (x0 - dx) : (x0 + dx);
    y1 = y0 + dy;
    sx = (rot == ROTATE_90_DEG) ? -1 : 1;
    sy = 1;
  }
  else
  {
    dx = base >> 1; dy = height;
    x1 = x0 + dx;
    y1 = (rot == ROTATE_180_DEG) ? (y0 - dy) : (y0 + dy);
    sx = 1;
    sy = (rot == ROTATE_180_DEG) ? -1 : 1;
  }

  int32_t err = dx - dy;
  m4_draw_pixel(x0, y0, color_index);
  while (x != x1 || y != y1)
  {
    int32_t epsilon = err << 1;
    if (epsilon > -dy)
    {
      err -= dy;
      x += sx;
    }
    if (epsilon < dx)
    {
      err += dx;
      y += sy;
    }

    if (rot == ROTATE_270_DEG || rot == ROTATE_90_DEG)
    {
      m4_draw_line(x, (y0 << 1) - y, x, y, color_index);
    }
    else
    {
      m4_draw_line((x0 << 1) - x, y, x, y, color_index);
    }
  }
}

void m4_puts(int32_t x, int32_t y, TextWriter* gptxt, const char* str, uint8_t color_index)
{
  unsigned char c;
  while ((c = *str++) != 0)
  {
    int32_t ix, iy;
    // Point to glyph; each row is one byte.
    uint8_t *pch = (uint8_t*) &gptxt->font[gptxt->char_map[c] << 1];
    for (iy = 0; iy < 8; iy++)
    {
      uint32_t row = pch[iy];
      // Plot pixels until row-byte is empty
      for (ix = x; row > 0; row >>= 1, ix++)
      {
        if (row & 1)
        {
          m4_draw_pixel(ix + x, iy + y, color_index);
        }
      }
    }

    x += gptxt->dx;
  }
}
