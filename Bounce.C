#include <conio.h>

#include <graphics.h>

#include <stdlib.h>

#include <stdio.h>

#define FPS 30

#define BALL_BOUND 20
#define MX 500

int JMPSPD = 5;
int XSPD = 2;

#define GROUND 250
const int JMPLMT = 120;
#define RAD 10
#define SAFE 10
#define ONE 220
const int ONGROUND = GROUND - SAFE;

void appendscore(char playername[16], int score);
int * vert;
int peak_x = MX;
int peak_y;
int hr;
void rnd() {
  int i = 0;
  int hrand[3];
  hrand[0] = 220;
  hrand[1] = 200;
  hrand[2] = 210;
  randomize();
  i = random(3);
  hr = hrand[i];
}

void peaks() {
  vert[0] = peak_x;
  vert[1] = 250;
  vert[2] = peak_x + 10;
  rnd();
  vert[3] = hr; /// not impl
  peak_y = vert[3];
  vert[4] = peak_x + 20;
  vert[5] = 250;
  drawpoly(3, vert);
}

void main() {
  int x, y;
  char crash[] = "xxxCRASHEDxxx";
  int gd = DETECT, gm, i = 0;
  int ball_x = SAFE, ball_y = (GROUND - RAD), jump = 0;
  char input = 0, ch;
  char player_name[16];
  int score = 0;
  int b_obs_data[10];
  int cnt = 0;
  float disp = 0;
  initgraph( & gd, & gm, "c:\\tc\\bgi");
  // cleardevice();
  //   circle(ball_x, ball_y, RAD);
  L:
    while (1) {
      cleardevice();
      settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);

      /* output a messagE*/

      outtextxy(150, getmaxy() / 2 + 50, "BOUNCE GAME");

      // ellipse(ball_x, ball_y,0,360,RAD,RAD);
      setfillstyle(SOLID_FILL, RED);
      fillellipse(ball_x, ball_y, RAD, RAD);
      // draw the polygon
      peaks();
      peak_x -= XSPD;
      if (peak_x < -20) {
        peaks();
        peak_x = MX;
        vert[0] = peak_x;
        vert[1] = 250;
        vert[2] = peak_x + 10;
        rnd();
        vert[3] = hr; /// not impl
        peak_y = vert[3];
        vert[4] = peak_x + 20;
        vert[5] = 250;

      }
      setlinestyle(cnt, 1, 20);
      line(0, GROUND, MX + 100, GROUND);

      /// Code for getting the keyboard input
      if (kbhit()) {
        input = getch();

        if (input == 'q')
          break;

        else if (jump == 0 && input == ' ') {
          jump = 1;
          cnt++;
        }
      }
      /// End of keyboard input Code
      /// Code controlling the jump and fall animation of the ball
      if (jump == 1) {
        ball_y -= JMPSPD;
        if (ball_y <= JMPLMT)
          jump = -1;
      } else if (jump == -1) {
        ball_y += JMPSPD;
        if (ball_y >= ONGROUND) {
          jump = 0;
          ball_y = ONGROUND;
          score++;
        }
      }
      /// End of code containing the jump animation of the ball

      ///Code for testing whether the obstracle and the ball are colliding
      if (peak_x <= BALL_BOUND && peak_x >= (BALL_BOUND - 30)) {
        if (peak_y <= ball_y) {

          setcolor(RED);
          settextstyle(3, HORIZ_DIR, 10);

          /* output a message */
          outtextxy(60, 60, "CRASH");
          //        settextstyle(3);
          break;
        }
      }
      setbkcolor(cnt + 1);
      if (cnt >= 4) {
        XSPD++;
        JMPSPD++;
        cnt = 0;

      }
      /// End of collision test
      /// Controls the fps of the game 30 ms delay equals 30 - delta frames per second of gameplay
      delay(FPS);
    }
  printf("\n\t\tScore: %d", score);
  printf("\n\nEnter your name:");
  gets(player_name);
  appendscore(player_name, score); /// function is not implemented...
  closegraph();
}

void appendscore(char player_name[16], int score) {

  FILE * fp;
  fp = fopen("HIGH.txt", "a");
  fprintf(fp, "NAME : %s\t\tSCORE : %d\n", player_name, score);
  fclose(fp);
  clrscr();
  printf("THANK YOU");
  /// FileIO operation in Text Mode so that everyone can view their high-score
}
