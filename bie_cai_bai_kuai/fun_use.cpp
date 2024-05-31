#include "fun_use.h"

unsigned short black_index[COUNT];
HWND window;

void init_window (void)
{
  initgraph(COUNT * X_UP + 1, COUNT * Y_UP + 1);
  window = GetHWnd ();
  SetWindowText (window, L"别踩白块");
}

void put_white (int j, int p)
{
  setlinecolor (LIGHTBLUE);
  setfillcolor(WHITE);

  fillrectangle((j - 1) * X_UP, (p - 1) * Y_UP, X_UP * j, Y_UP * p);
}

void put_black(int j, int p)
{
  setlinecolor(LIGHTBLUE);
  setfillcolor(BLACK);

  fillrectangle((j - 1) * X_UP, (p - 1) * Y_UP, X_UP * j, Y_UP * p);
}

void draw_map (void)
{
  for (int j = 1; j <= COUNT; j++)
  {
    for (int p = 1; p <= COUNT; p++)
    {
      put_white(j, p);
    }
  }
}

void init_black (void)
{
  for (int count = 0; count < COUNT; count ++)
  {
    black_index[count] = rand () % COUNT;
  }
}

void draw_black (void)
{
  for (int count = 0; count < COUNT; count++)
  {
    put_black(black_index[count] + 1, count + 1);
  }
}

void init_word (void)
{
  LOGFONT fontStyle;
  gettextstyle(&fontStyle);
  fontStyle.lfQuality = ANTIALIASED_QUALITY;
  settextstyle(&fontStyle);
  setbkmode (TRANSPARENT);
  settextcolor (BLACK);
  settextstyle(50, 0, L"Script_MT");
}

void put_word (int j, int p)
{
  LPCWSTR str = L"00 : %02d : %02d";
  TCHAR buffer[20];

  wsprintf (buffer, str, j, p);
  outtextxy (99, 0, buffer);
}

void play (void)
{
  int j = black_index[3], p = 3;
  int time_s = TIME, time_ds = DS_PER_SEC;
  int count_s = 0, count_ds = 60;
  int how_many_blocks = 0;
  clock_t start_clock = clock (), current_clock;
  LPCWSTR str = L"您一共点击了%d个黑色方块. ";
  TCHAR buffer[30];
  ExMessage mouse;
  time_t begin;
  bool first_click = 0;

  while (1)
  {
    if (first_click)
    {
      current_clock = clock ();
      count_s = difftime (time (0), begin);

      if (difftime (time(0), begin) > TIME)
      {
        break;
      }

      if (current_clock - start_clock >= CLOCK_PER_DS)
      {
        if (count_ds >= 60)
        {
          count_ds = 0;
        }
        count_ds ++;
        start_clock = current_clock;
      }
    }

    if (peekmessage (&mouse, EM_MOUSE))
    {
      if (mouse.message == WM_LBUTTONDOWN)
      {
        if (!first_click)
        {
          first_click = 1;
          begin = time (0);
        }

        j = mouse.x / X_UP;
        p = mouse.y / Y_UP;

        if ((j != black_index[COUNT - 1]) || (p != COUNT - 1))
        {
          break;
        }

        how_many_blocks ++;

        for (int count = COUNT - 1; count > 0; count--)
        {
          black_index[count] = black_index[count - 1];
        }

        black_index[0] = rand() % COUNT;

        draw_map ();
        
        draw_black ();
      }
    }
    put_word(TIME - count_s, DS_PER_SEC - count_ds);

    Sleep (8);
  }
  wsprintf(buffer, str, how_many_blocks);
  MessageBox(NULL, buffer, L"游戏结束", MB_OK);
}
