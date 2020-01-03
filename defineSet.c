#include"defineSet.h"

char mapFileName[]="map.txt";
Map map[_MAXMAPHEIGHT_][_MAXMAPWIDTH_];
LOC curWorkerX;
LOC curWorkerY;
char _WALLPIC_[]="IMG/wall.bmp";
char _BOX_OKPIC_[]= "IMG/boxok.bmp";
char _BOX_NOTOKPIC_[]= "IMG/boxnotok.bmp";
char _WAYPIC_[]="IMG/way.bmp";
char _LEFTPIC_[]="IMG/left.bmp";
char _RIGHTPIC_[]="IMG/right.bmp";
char _UPPIC_[]="IMG/up.bmp";
char _DOWNPIC_[]= "IMG/down.bmp";
char _DESPIC_[]= "IMG/des.bmp";

DIREC curDire=UP;