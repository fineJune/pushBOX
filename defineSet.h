#ifndef __DEFINESET_H__

#define __DEFINESET_H__

/**
 * 主要定义一些类型与变量以及头文件包含
 * 
*/

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>


typedef enum{   WALL=0,                     //墙
                WAYNOBOX=1,                 //路
                BOX=2,                      //墙的分量，方便理解
                WAYWITHBOX=3,               //路 + 箱子
                DESTINATION=3,              //目的地的分量，方便理解
                WAYWITHDESTINATION=4,       //路 + 目的地
                WORKER=4,                   //工人分量，方便理解
                WAYWITHWORKER=5,            //路 + 工人
                WAYWITHBOXWITHDES=6,        //路 + 箱子 + 目的地
                WAYWITHWORKERWITHDES=8      //路 + 工人 + 目的地
            }TYPESET;

typedef int Status;
typedef int LOC;
typedef int Type;

typedef struct{
    LOC x;
    LOC y;
    Type type;
}Map;

typedef enum{UP=0,DOWN,LEFT,RIGHT}DIREC;

#define FAIL 0
#define SUCCESS 1
#define ERROR 0
#define OK 1
#define NOTOK 0

#define _UP_ 72
#define _W_UP_ 87
#define _w_UP_ 119
#define _DOWN_ 80
#define _S_DOWN_ 83
#define _s_DOWN_ 115
#define _LEFT_ 75
#define _A_LEFT_ 65
#define _a_LEFT_ 97
#define _RIGHT_ 77
#define _D_RIGHT_ 68
#define _d_RIGHT_  100

#define _MAXMAPWIDTH_ 10                    //宽
#define _MAXMAPHEIGHT_ 10                   //高



#endif