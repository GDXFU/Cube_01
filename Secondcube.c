<include <math.h>
#include <studio.h>
#include <string.h>
#include <unistd.h>

float A, B, C;

float cubewidth = 20;
int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer [160* 44];
int backgroundASCIICode = '.';
int distanceFromCam = 100;
float horizontalOffset;
float K1 = 40;

float incrementSpeed = 0.6;

float x, y, z;
float ozz;
int xp,yp;
int idx;

float calculate(int i, int j, int k) {
        return  j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
                j * cos(A) * sin(C) + k * sin(A) * sin(A) * sin(C) + i * cos(B) * cos(C)
}

float calculateY(int i, int j, int k) {
 return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
        j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin (B) * sin(C) -
        i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k) {
  return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
  x = calculateX(cubeX, cubeY, cubeZ);
  y = calculateY(cubeX, cubeY, cubeZ);
  z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

  ooz = 1 / z;

  xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
  yp = (int)(height / 2 + K1 * ooz * y);

  idx = xp + yp * width;
  if (idx >= 0 && idx < width * height) {
    if (ooz > zBuffer [idx]) {
        zBuffer[idx] = ooz;
        buffer[idx] = ch;
    }
  }
}

int main(){
  printf("\x1b[2J");
  while (1) {  
    memset(buffer, backgroundASCIICode, width * height);
    memset(zBuffer, 0, width * height * 4);
    cubewidth = 20;
    horizontalOffset = -2 * cubewidth;
    // first cube
    for (float cubeX = -cubewidth; cubeX < cubewidth; cubeX += incrementSpeed) {
        for(float cubeY = -cubewidth; cubeY < cubewidth;
            cubeY += incrementSpeed) {
          calculateForSurface(cubeX, cubeY, -cubewidth, '@');
          calculateForSurface(cubewidth, cubeY, cubeX, '$');
          calculateForSurface(-cubewidth, cubeY, -cubeX, '~');
          calculateForSurface(-cubeX, -cubewidth, -cubeY, '#');
          calculateForSurface(cubeX, -cubewidth, -cubeY, ';');
          calculateForSurface(cubeX, cubewidth, cubeY, '+' );
        }
    } 
    cubewidth = 10;
    horizontalOffset = 1 * cubewidth;
    // second cube
    for (float cubeX = -cubewidth; cubeX < cubewidth; cubeX += incrementSpeed) {
      for (float cubeY = -cubewidth; cubeY < cubewidth;
           cubeY += incrementSpeed)  {
        calculateForSurface(cubeX, cubeY, -cubewidth, '@');
        calculateForSurface(cubewidth, cubeY, cubeX, '$');
        calculateForSurface(-cubewidth, cubeY, -cubeX, '~');
        calculateForSurface(-cubeX, cubeY, cubewidth, '#');
        calculateForSurface(cubeX, -cubewidth, -cubeY, ';');
        calculateForSurface(cubeX, cubewidth, cubeY, '+');
       }
    }
    cubewidth = 5 ;
     horizontalOffset = 8 * cubewidth;
     // third cube
     for (float cubeX = -cubewidth; cubeX < cubewidth; cubeX += incrementSpeed) {
       for (float cubeY = -cubewidth; cubeY < cubewidth;
            cubeY += incrementSpeed) {
        calculateForSurface(cubeX, cubeY, -cubewidth, '@');
        calculateForSurface(cubewidth, cubeY, cubeX, '$');
        calculateForSurface(-cubewidth, cubeY, -cubeX, '~');
        calculateForSurface(-cubeX, cubeY, cubewidth, '#');
        calculateForSurface(cubeX, -cubewidth, -cubeY, ';');
        calculateForSurface(cubeX, cubewidth, cubeY, '+');       
     }
  }
  printf("\x1b[H");
  for (int k = 0; k < width * height; k++) {
        putchar(k % width ? buffer[k] : 10);
  }

  A += 0.05;
  B += 0.05;
  C += 0.01;
  usleep(8000 * 2);
 }
 return 0;
}
