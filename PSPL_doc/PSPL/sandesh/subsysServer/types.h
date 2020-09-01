///////////////////////////////////////////////////////////////////////////////////////////////////
// PROJECT           : GMRT
// File              : TYPES.H
// Author            :
// Version           :
// Last Modification : 19-09-2006
// Reason            :
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _TYPES_H_
#define _TYPES_H_

#define true    0x01
#define false   0x00

typedef int            BOOL;
typedef short int      WORD;
typedef char           string40[40];
typedef char           string20[20];

typedef union
{
  WORD W;
  BYTE B[2];
}WordByte;



typedef struct
{
 unsigned char  B0 : 8;
 unsigned char  B1 : 8;
 unsigned char  B2 : 8;
 unsigned char  B3 : 8;
}LONG32BIT;

typedef struct
{
 unsigned   B0 : 1;
 unsigned   B1 : 8;
 unsigned   B2 : 8;
 unsigned   B3 : 8;
 unsigned   B4 : 7;

}LONG17BIT;

typedef union
{
  long L;
  WORD W[2];
  BYTE B[4];
}Long;

typedef union
{
 long L;
 LONG32BIT LB;
}FXDREAL;

typedef union
{
 long L;
 LONG17BIT LB;
}ENC17BIT;

typedef struct 
{
 int deg;
 int arcmin;
 int arcsec;
}ANGLE;

typedef struct 
{
  BYTE    hrs;
  BYTE    min;
  BYTE    secs;
  WORD    milsec;
}TIME;

typedef struct
{
  BYTE    date;
  BYTE    month;
  int     year;
}DATE;

typedef struct
{
  int    cmd;
  ANGLE  AzAngle;
  ANGLE  ElAngle;
  TIME   TrackTime;
}COMMAND;

const char *ftoa(float f, int n);

#endif


