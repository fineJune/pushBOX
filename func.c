#include"func.h"

extern Map map[_MAXMAPHEIGHT_][_MAXMAPWIDTH_];
extern LOC curWorkerX;
extern LOC curWorkerY;
extern char mapFileName[];
extern char _WALLPIC_[];
extern char _BOX_OKPIC_[];
extern char _BOX_NOTOKPIC_[];
extern char _WAYPIC_[];
extern char _LEFTPIC_[];
extern char _RIGHTPIC_[];
extern char _UPPIC_[];
extern char _DOWNPIC_[];
extern char _DESPIC_[];
extern DIREC curDire;

void run()
{
    loadMapFromFile(mapFileName);
    drawMap();

    while(!isFin()){
        printMap();
        getInput();
        drawMap();
    }
}

Status isFin()
{
    int i,j;
    for(i=0;i<_MAXMAPHEIGHT_;i++)
    {
        for(j=0;j<_MAXMAPWIDTH_;j++)
        {
            if(map[i][j].type==WAYWITHBOX) return NOTOK;
        }
    }
    return OK;
}

void getInput()
{
    char ch=getch();
    // printf("%c\n\n\n",ch);
    switch (ch)
    {
    case _W_UP_:
    case _w_UP_:
    case _UP_: {push(-1,0);
                curDire=UP;}break;

    case _S_DOWN_:
    case _s_DOWN_:
    case _DOWN_:{push(1,0);
                 curDire=DOWN;}break;

    case _A_LEFT_:
    case _a_LEFT_:
    case _LEFT_:{push(0,-1);
                curDire=LEFT;}break;

    case _D_RIGHT_:
    case _d_RIGHT_:
    case _RIGHT_:{push(0,1);
                  curDire=RIGHT;}break;
    default:
        break;
    }

}
void workerMove(LOC x, LOC y)
{   
    map[curWorkerX][curWorkerY].type-=WORKER;
    map[curWorkerX+x][curWorkerY+y].type+=WORKER;      
    curWorkerY+=y;
    curWorkerX+=x;
}

void push(LOC x,LOC y)
{
    Map next=map[curWorkerX+x][curWorkerY+y];
    Map nextNext=map[curWorkerX+2*x][curWorkerY+2*y];
    Map worker=map[curWorkerX][curWorkerY];

   switch (next.type)
   {
   case WALL:                        //下一步是墙
       /* 无需移动 */
       break;
   case WAYWITHDESTINATION:           //下一步是目的地
   case WAYNOBOX:{                   //下一步是箱子
        workerMove(x,y);

   };break;

   case WAYWITHBOXWITHDES:          //箱子在目的地上
   case WAYWITHBOX:{                
        switch(nextNext.type){
            case WALL:
            case WAYWITHBOX:
            case WAYWITHBOXWITHDES:
            break;

            case WAYNOBOX:
            case WAYWITHDESTINATION:{
                map[curWorkerX+x][curWorkerY+y].type-=next.type-WAYNOBOX;
                map[curWorkerX+2*x][curWorkerY+2*y].type+=next.type-WAYNOBOX;
                workerMove(x,y);
            }
            
        }
   }break;
   default:
       break;
   }

}

void drawPic(char picName[],int x,int y)
{
    typedef HWND (WINAPI *PROCGETCONSOLEWINDOW)();
    PROCGETCONSOLEWINDOW GetConsoleWindow;
    HMODULE hKernel32 = GetModuleHandle("kernel32");
    GetConsoleWindow= (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32,"GetConsoleWindow");
    HWND cmd=GetConsoleWindow();
    HDC dc = GetDC(cmd);
    HBITMAP hBitmap;
    hBitmap=(HBITMAP)LoadImage(NULL,picName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
    HDC cmdmem = CreateCompatibleDC(dc);
    SelectObject(cmdmem , hBitmap);
    BitBlt(dc , x ,y+10 , 64 , 64 , cmdmem , 0 , 0 , SRCCOPY);
}

void printMap()
{
    FILE* file;
    if((file=fopen("fileName.txt","w"))==NULL){
        printf("发现文件失败\n");
        exit(0);
    }
    int i,j;
    for(i=0;i<_MAXMAPHEIGHT_;i++)
    {
        for(j=0;j<_MAXMAPWIDTH_;j++)
        {
            fprintf(file,"%c",map[i][j].type+'0');
            fprintf(file,"%c",' ');
        }
        fprintf(file,"\n");
    }
    fprintf(file,"\n\n\n");
}

void drawMap()
{
    int i,j;
    system("CLS");
    for(i=0;i<_MAXMAPHEIGHT_;i++)
    {
        for(j=0;j<_MAXMAPWIDTH_;j++)
        {
            switch(map[i][j].type){
                case WALL:drawPic(_WALLPIC_,j*64,i*64);break;
                case WAYNOBOX:drawPic(_WAYPIC_,j*64,i*64);break;
                case WAYWITHBOX:drawPic(_BOX_NOTOKPIC_,j*64,i*64);break;
                case WAYWITHBOXWITHDES:drawPic(_BOX_OKPIC_,j*64,i*64);break;
                case WAYWITHWORKERWITHDES:
                case WAYWITHWORKER:
                    switch(curDire){
                        case DOWN:drawPic(_DOWNPIC_,j*64,i*64);break;
                        case UP:drawPic(_UPPIC_,j*64,i*64);break;
                        case LEFT:drawPic(_LEFTPIC_,j*64,i*64);break;
                        case RIGHT:drawPic(_RIGHTPIC_,j*64,i*64);break;
                    }break;
                case WAYWITHDESTINATION:drawPic(_DESPIC_,j*64,i*64);break;
            }
        }
    }
}
void loadMapFromFile(char* fileName)
{
    FILE* file;
    if((file=fopen(fileName,"r"))==NULL){
        printf("�ļ��Ҽ���ʧ��?\n");        
    }
    int i,j;
    for(i=0;i<_MAXMAPHEIGHT_;i++)
    {
        for(j=0;j<_MAXMAPWIDTH_;j++)
        {
            char ch=fgetc(file);
            switch(ch-'0'){
                case WALL:map[i][j].type=WALL;break;
                case WAYNOBOX:map[i][j].type=WAYNOBOX;break;
                case WAYWITHBOX:map[i][j].type=WAYWITHBOX;break;
                case WAYWITHBOXWITHDES:map[i][j].type=WAYWITHBOXWITHDES;break;
                case WAYWITHWORKER:{
                    map[i][j].type=WAYWITHWORKER;
                    curWorkerX=i;
                    curWorkerY=j;
                }break;
                case WAYWITHWORKERWITHDES:map[i][j].type=WAYWITHWORKERWITHDES;break;
                case WAYWITHDESTINATION:map[i][j].type=WAYWITHDESTINATION;break;
            }
            fgetc(file);
        }
    }
}