#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include<strings.h>
#include <time.h>
#include <string.h>
#include "colors.h"
#define SIZE 60

FILE*f1;
FILE*f2;
FILE*f3;
FILE*top;
FILE*debugging_file;
typedef struct{
char name[20];
int score;
}rankok;
rankok rankarray[10]={"...",0};
typedef struct
{
    char name[20] ;
    char letter ;
    int moves;
    int score;
} players;


time_t start, end ;
void computer_move(int  size, char a[size] [size],int *ii,int *jj);
void Read_first(char points[5],int n,int *x);
void check_box(int n,int size,char a[size][size],char letter,int *w) ;
void Read_points(char points[5]);
void print_arr(int size,char a[size][size]);
void analyze_points(char points[5],int n,int *x) ;
void find_index(char points[5],int n,int size,char a[size][size], int turn,int *x) ;
void det_winner(players player1,players player2) ;
void change_save(char *slot);
int  check_file(char slot);
void save(int size,char a[size][size],players x,players y,char type[2],int turn,int total_lines, int clock,char slot,char mode);
void undo_turn (int turn, players *player1, players *player2,int w );
void general_turn (int turn, players (*player1), players (*player2),int w );
void display (players player1, players player2, int y, int time,int tutn);
void display2 (players player1, players computer, int y, int time, int turn);
void Winner(players x,players y);
void check_for_undo(int n,int size,char a[size][size],char letter,int *w);
void gotoxy(int,int);
void print_word();



char points[6];
int main()
{

    print_word();
    label:
    setTextColor(stdout,TC_BLACK);
    int c_move;
    char slot;
    system("cls");
    setTextColor(stdout, TC_LIGHTCYAN);
    gotoxy(48,9);
    printf("Welcome to Dots & Boxs: \n\n");
    gotoxy(45,12);
    printf("1.New game.");
    gotoxy(45,13);
    printf("2.Load game.");
    gotoxy(45,14);
    printf("3.Top ten.");
    gotoxy(45,15);
    printf("4.About the game");
    gotoxy(45,16);
    printf("5.EXit.\n");
    gotoxy(40,17);
    printf("please, press from 1 to 5 :");
    char game ;
    fflush(stdin);
    scanf("%c",&game);
    while(getchar()!='\n'){goto oho;}
    system("cls");
    while (game!='1'&&game!='2'&&game!='3'&&game!='4'&&game!='5')
    {
        oho:
        gotoxy(40,18);
        printf("please,Enter a valid choice: ");
        Sleep(500);
        goto label;}
    system("cls");


    if(game=='1')
    {   char mode;
        load:
        if(game=='1'||game=='2'){
        if(game=='1'){
                setTextColor(stdout, TC_LIGHTCYAN);
                gotoxy(45,11);
                printf("Choose the game difficulty :");
                gotoxy(45,13);
                printf("1-Easy");
                gotoxy(45,14);
                printf("2-Hard");
                gotoxy(40,16);
                printf("please, press 1 or 2 : ");
                gotoxy(40,20);
                printf("To back the start menu press (b):");
                gotoxy(64,16);
                scanf(" %c",&mode);
                while(getchar()!='\n'){goto hoh;}
                system("cls");
                if (mode=='b') goto label;

                while (mode!='1'&&mode !='2'){
                        hoh:
                    gotoxy(40,16);
                    printf("please,Enter a valid choice: ");
                    Sleep(500);
                    system("cls");
                    goto load;
                    }}
        else{
                if(slot=='a'){
                    f1=fopen("file1.txt","r");
                    mode=getc(f1);}
                else if(slot=='b'){
                        f2=fopen("file2.txt","r");
                        mode=getc(f2);}
                else{
                     f3=fopen("file3.txt","r");
                     mode=getc(f3);}}


        int n;
        if(mode=='1'){n=2;}
        else{n=5;}
        int size=(n+1)*2;
        char a[size][size] ;
        int i,j,row=49,col=49;
        for(i=0; i<size; i++){
            for(j=0; j<size; j++){
                if(i==0&&j%2!=0){
                    a[i][j]=row;
                    row++;}
                else if(j==0&&i%2!=0 ){
                    a[i][j]=col;
                    col++;}
                else if (i%2!=0 && j%2!=0){a[i][j]=254;}
                else  a[i][j]=' ';}}
        system("cls");
        char type[2];
        if(game=='1'){
                star:
               setTextColor(stdout, TC_LIGHTCYAN);
                        gotoxy(45,12);
                        printf("Choose the game type :");
                        gotoxy(45,13);
                        printf("1-player vs player.");
                        gotoxy(45,14);
                        printf("2-player vs computer.");
                        gotoxy(40,16);
                        printf("please, press 1:2 to make your choice: ");
                        scanf("%c",&type[0]);
                        while(getchar()!='\n'){goto ziko ;}
                        system("cls");
                    while (type[0]!='1'&&type[0]!='2'){
                        ziko:
                        system("cls");
                        gotoxy(40,16);
                        printf("please,Enter a valid choice: ");
                        Sleep(400);
                        system("cls");
                        goto star;}
                system("cls");
                setTextColor(stdout, TC_LIGHTGRAY);}
        else{
                if(slot=='a'){fgets(type,2,f1);}
                else if(slot=='b'){fgets(type,2,f2);}
                else{fgets(type,2,f3);}}

        if(type[0]=='1')
        {
            players player1;
            players player2;
            int turn,x=0,total_lines,score,w,time_taken=0,move_time;
            if(game=='1'){
                setTextColor(stdout, TC_LIGHTRED);
                gotoxy(43,10);
                printf("enter first player name: ");
                scanf("%s",player1.name);
                setTextColor(stdout, TC_LIGHTGRAY);
                system("cls");
                setTextColor(stdout, TC_LIGHTBLUE);
                gotoxy(43,10);
                printf("enter second player name: ");
                scanf("%s",player2.name);
                system("cls");
                setTextColor(stdout, TC_LIGHTGRAY);
                system("cls");
                player1.score=0;
                player1.moves=0;
                player2.score=0;
                player2.moves=0;
                w=0;score=0;x=0;
                turn=1;
                total_lines=size*n;}
                else{
                 if(slot=='a'){
                 fread(a,sizeof(char),size*size,f1);
                 turn=getw(f1);
                 fread(&player1,sizeof(players),4,f1);
                 fread(&player2,sizeof(players),4,f1);
                 total_lines=getw(f1);
                 time_taken=getw(f1);
                fclose(f1);}
                else if(slot=='b'){
                fread(a,sizeof(char),size*size,f2);
                 turn=getw(f2);
                 fread(&player1,sizeof(players),4,f2);
                 fread(&player2,sizeof(players),4,f2);
                 total_lines=getw(f2);
                 time_taken=getw(f2);
                  fclose(f2);}
                else{
                 fread(a,sizeof(char),size*size,f3);
                 turn=getw(f3);
                 fread(&player1,sizeof(players),4,f3);
                 fread(&player2,sizeof(players),4,f3);
                 total_lines=getw(f3);
                 time_taken=getw(f3);
                  fclose(f3);}}

            print_arr(size,a);

            while(1)
            {
                w=0;
                move_time=0;
                if(turn==1){
                    if(total_lines==0){
                        Sleep(500);
                        Beep(500,20);
                        remove("debug.txt");
                        system("cls");
                        det_winner( player1,player2);
                        Sleep(5000);
                        char b[2];
                        system("cls");
                        setTextColor(stdout, TC_YELLOW);
                        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t1.To main menu\n");
                        printf("\t\t\t\t\t\t any key.To Exit\n ");
                        printf("\t\t\t\t\t\press 1 or any key  >>> ");
                        scanf("%s",b);
                        setTextColor(stdout, TC_LIGHTGRAY);
                        system("cls");
                        if(b[0]!='1'){goto newm ;}
                        else goto label ;}
                    start =time(NULL);
                    score = 0;
                    display(player1,player2,total_lines,time_taken,turn);
                    print_arr(size,a);
                    find_index(points,n,size,a,turn,&x);
                    save(size,a,player1,player2,type,turn,total_lines,time_taken,'d',mode);
                    if(strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0){
                        check_box(n,size,a,' ',&w);
                        if(w==0){turn=0;}
                        score=w;
                        undo_turn(turn,&player1,&player2,score);
                        total_lines+=2;}
                    else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0){
                        check_box(n,size,a,'A',&w);
                        score=w;
                        general_turn(turn,&player1,&player2,score);}
                    else if(strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"save")==0||strcmp(points,"s")==0){
                        system("cls");
                        w=-1;
                        change_save(&slot);
                        save(size,a,player1,player2,type,turn,total_lines,time_taken,slot,mode);
                        total_lines+=1;
                        x=0;}
                    else if(strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"exit")==0||strcmp(points,"e")==0){
                        system("cls");
                        remove("debug.txt");
                        goto label;}


                    else{
                        check_box(n,size,a,'A',&w);
                        print_arr(size,a);
                        score =w;
                        general_turn(turn,&player1,&player2,score);}

                        system("cls");
                        if (w!=0)turn=1;
                        else turn=0;
                        total_lines--;
                        end =time(NULL);
                        move_time=end-start;
                        time_taken+=move_time;}

                move_time=0;
                if(turn==0)
                {
                    if(total_lines==0){
                        Sleep(500);
                        Beep(500,20);
                        remove("debug.txt");
                        system("cls");
                        det_winner( player1,player2);
                        Sleep(5000);
                        char b[2];
                        system("cls");
                        setTextColor(stdout, TC_YELLOW);
                        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t1.To main menu\n");
                        printf("\t\t\t\t\t\t any key.To Exit\n ");
                        printf("\t\t\t\t\t\press 1 or any key  >>> ");
                        scanf("%s",b);
                        setTextColor(stdout, TC_LIGHTGRAY);
                        system("cls");
                        if(strcmp(b,"1")!=0){goto newm ;}
                        else goto label ;}

                    start =time(NULL);
                    system("cls");
                    score =0 ;
                    display(player1,player2,total_lines,time_taken,turn);
                    print_arr(size,a);
                    find_index(points,n,size,a,turn,&x);
                    save(size,a,player1,player2,type,turn,total_lines,time_taken,'d',mode);
                    if(strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0){
                        check_box(n,size,a,' ',&w);
                        if(w==0)
                        {turn=1;}
                        score=w;
                        undo_turn(turn,&player1,&player2,score);
                        total_lines +=2 ;}
                    else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0){
                        check_box(n,size,a,'B',&w);
                        score=w;
                        general_turn(turn,&player1,&player2,score);}
                    else if(strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"save")==0||strcmp(points,"s")==0){
                     system("cls");
                     w=-1;
                     change_save(&slot);
                     x=0;
                     save(size,a,player1,player2,type,turn,total_lines,time_taken,slot,mode);
                     total_lines+=1;}
                    else if(strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"exit")==0||strcmp(points,"e")==0){
                        system("cls");
                        remove("debug.txt");
                        goto label;}
                    else{
                        check_box(n,size,a,'B',&w);
                        print_arr(size,a);
                        score=w ;
                        general_turn(turn,&player1,&player2,score);}
                    system("cls");
                    if (w!=0) turn=0;
                    else turn=1;
                    total_lines--;
                    end =time(NULL);
                    move_time=end-start;
                    time_taken+=move_time;}}}


        else{
            static int index1[SIZE],index2[SIZE];
            int s=2,g=0,x=0,in11=0,in22=0,iii=0;
            int turn,total_lines,score,w,time_taken,move_time;
            players player1;
            players comp= {"Computer",'B',0,0};;
            if(game=='1'){
            gotoxy(43,10);
            setTextColor(stdout, TC_LIGHTRED);
            printf("enter player name: ");
            scanf("%s",player1.name);
            setTextColor(stdout, TC_LIGHTGRAY);
            system("cls");
            turn=1;
            player1.score=0;
            player1.moves=0;
            w=0;score=0;
            total_lines=size*n;
            time_taken=0;
            x=0;}
            else{
                if(slot=='a'){
                fread(a,sizeof(char),size*size,f1);
                 turn=getw(f1);
                 fread(&player1,sizeof(players),4,f1);
                 fread(&comp,sizeof(players),4,f1);
                 total_lines=getw(f1);
                 time_taken=getw(f1);
                  fclose(f1);}
                else if(slot=='b'){
                 fread(a,sizeof(char),size*size,f2);
                 turn=getw(f2);
                 fread(&player1,sizeof(players),4,f2);
                 fread(&comp,sizeof(players),4,f2);
                 total_lines=getw(f2);
                 time_taken=getw(f2);
                  fclose(f2);}
                else{
                 fread(a,sizeof(char),size*size,f3);
                 turn=getw(f3);
                 fread(&player1,sizeof(players),4,f3);
                 fread(&comp,sizeof(players),4,f3);
                 total_lines=getw(f3);
                 time_taken=getw(f3);
                 fclose(f3);}}


            while(1)
            {
                w=0;
                move_time=0;
                if(turn==1)

                {
                    iii=0;
                    start =time(NULL);
                    system("cls");
                    score = 0;
                    display2(player1,comp,total_lines,time_taken,turn);
                    print_arr(size,a);
                    find_index(points,n,size,a,turn,&x);
                    save(size,a,player1,comp,type,turn,total_lines,time_taken,'d',mode);
                    if(strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0){
                        total_lines+=2;
                        if(g==1){
                            check_box(n,size,a,' ',&w);
                            score=w;
                            undo_turn(turn,&player1,&comp,score);
                            iii=0;
                            g=0;}
                        else{
                                turn=0;
                                in11--;
                                in22--;
                                a[index1[in11]][index2[in22]]=' ';
                                int un_done=0;
                                check_box(n,size,a,' ',&un_done);
                                check_for_undo(n,size,a,'A',&iii);
                                undo_turn(turn,&player1,&comp,un_done);
                                comp.moves=comp.moves-s/2+1;
                                turn=1;
                                undo_turn(turn,&player1,&comp,g);
                                total_lines+=s/2;}w=1;}

                    else if (strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0){
                        check_box(n,size,a,'A',&w);
                        check_for_undo(n,size,a,'A',&iii);
                        score=w;
                        general_turn(turn,&player1,&comp,score);}
                    else if(strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"exit")==0||strcmp(points,"e")==0){
                        system("cls");
                        remove("debug.txt");
                        goto label;}
                    else if(strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"save")==0||strcmp(points,"s")==0){
                        system("cls");
                        w=-1;
                        change_save(&slot);
                        save(size,a,player1,comp,type,turn,total_lines,time_taken,slot,mode);
                        total_lines+=1;
                        x=0;}
                    else{
                        check_box(n,size,a,'A',&w);
                        check_for_undo(n,size,a,'A',&iii);
                        print_arr(size,a);
                        score =w;
                        general_turn(turn,&player1,&comp,score);}
                    system("cls");
                    if (w!=0){
                            turn=1;
                            if (iii)g=1;}
                    else{
                        turn=0;
                        g=0;}

                    total_lines--;
                    end =time(NULL);
                    move_time=end-start;
                    time_taken+=move_time;
                    s=2;
                    if(total_lines==0)
                    {   Sleep(500);
                        Beep(500,20);
                        remove("debug.txt");
                        system("cls");
                        det_winner( player1,comp);
                        Sleep(5000);
                        char b[2];
                        system("cls");
                        setTextColor(stdout, TC_YELLOW);
                        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t1.To main menu\n");
                        printf("\t\t\t\t\t\t any key.To Exit\n ");
                        printf("\t\t\t\t\t\press 1 or any key  >>> ");
                        scanf("%s",b);
                        setTextColor(stdout, TC_LIGHTGRAY);
                        system("cls");
                        if(strcmp(b,"1")!=0){goto newm ;}
                        else goto label ;}}
                    move_time=0;

                if(turn==0)
                {
                    int i,j,temp;
                    start =time(NULL);
                    system("cls");
                    score =0 ;
                    display2(player1,comp,total_lines,time_taken,turn);
                    print_arr(size,a);
                    computer_move(size,a,&i,&j);
                    index1[in11]=i;in11++;
                    index2[in22]=j;in22++;
                    check_box(n,size,a,'B',&w);
                    print_arr(size,a);
                    score=w ;
                    general_turn(turn,&player1,&comp,score);
                    system("cls");
                    if (w!=0){
                        turn=0;
                        s+=2;}
                    else{turn=1;}
                    total_lines--;
                    end =time(NULL);
                    move_time=end-start;
                    time_taken+=move_time;
                    if(total_lines==0)
                      { Sleep(500);
                        Beep(500,20);
                        remove("debug.txt");
                        system("cls");
                        det_winner( player1,comp);
                        Sleep(5000);
                        char b[2];
                        system("cls");
                        setTextColor(stdout, TC_YELLOW);
                        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t1.To main menu\n");
                        printf("\t\t\t\t\t\tAny key.To Exit\n ");
                        printf("\t\t\t\t\t\tpress 1 or Any key >>");
                        scanf("%s",b);
                        setTextColor(stdout, TC_LIGHTGRAY);
                        system("cls");
                        if(strcmp(b,"1")!=0){goto newm ;}
                        else  goto label ;}}}}}}
else if (game=='2'){
        re:
        while(1){
                int a,b,c;
                a=check_file('a');
                b=check_file('b');
                c=check_file('c');
                gotoxy(35,0);
                if(a)printf("(have data)");
                else printf ("(empty!)");
                gotoxy(35,1);
                if(b)printf("(have data)");
                else printf ("(empty!)");
                gotoxy(35,2);
                if(c)printf("(have data)");
                else printf ("(empty!)");
                gotoxy(0,0);
                printf("Pick which Slot:\ta:slot1    \n    \t\t\tb:slot2  \n   \t\t\tc:slot3  \n");
                printf("1-To go back main menu\n");
                printf("2-To clear data form all slots\n");
                scanf("   %c",&slot);
                fflush(stdin);
                if(slot=='1'){
                    system("cls");
                    goto label;}
                if(slot =='2'){
                    remove("file1.txt");
                    remove("file2.txt");
                    remove("file3.txt");
                    system("cls");
                    goto re;}
                if(slot!='a'&&slot!='b'&&slot!='c'){
                    printf("please,Enter a valid choice: ");
                    Sleep(500);
                    system("cls");}
                else {
                    c_move=check_file(slot);
                    if(c_move==0){
                    printf("\t\t\tError.File is empty!\a\n");
                    Sleep(1000);
                    system("cls");}
                    else break;}}
                goto load;}

        else if (game =='3'){
            top=fopen("rank.txt","r");
            fread(rankarray,sizeof(rankok),10,top);
            printf("Names\tScore\n");
            for(int i=9;i>=0;i--){
            printf("%s\t%d\n",rankarray[i].name,rankarray[i].score);}
            fclose(top);
            char b[2];
            setTextColor(stdout, TC_YELLOW);
            printf("\t\t\t\t\t1.To main menu\n");
            printf("\t\t\t\t\tAny key.To Exit\n ");
            printf("\t\t\t\t\tpress 1:Any key  >> ");
            scanf("%s",b);
            setTextColor(stdout, TC_LIGHTGRAY);
            system("cls");
            if(strcmp(b,"1")!=0){goto newm ;}
            else goto label ;}
  else if (game=='4'){
        char back;
        about :
        setTextColor(stdout,TC_LIGHTMAGENTA);
        gotoxy(45,3);
        printf("ABOUT THE GAME");
        setTextColor(stdout,TC_YELLOW);
        gotoxy(2,5);
        printf("1-Dots and Boxes is a pencil-and-paper game for two players (sometimes more). ");
        gotoxy(3,6);
        printf("It was first published in the 19th century by French mathematician Edouard Lucas, ");
        gotoxy(3,7);
        printf("who called it la pipopipette It has gone by many other names,including the dots and dashes,");
        gotoxy(3,8);
        printf("game of dots, dot to dot grid. boxes, and pigs in a pen.");
        gotoxy(2,10);
        printf("2-The game starts with an empty grid of dots. Usually two players take turns");
        gotoxy(3,11);
        printf("adding a single horizontal or vertical line between two unjoined adjacent dots.");
        gotoxy(3,12);
        printf("A player who completes the fourth side of a 1×1 box earns one point and takes another turn.");
        gotoxy(3,13);
        printf(" A point is typically recorded by placing a mark that identifies the player in the box,such as an initial");
        gotoxy(3,14);
        printf("The game ends when no more lines can be placed. ");
        gotoxy(3,15);
        printf("The winner is the player with the most points. The board may be of any size grid.");
        gotoxy(3,16);
        printf("When short on time, or to learn the game, a 2 * 2 board (3 * 3 dots) is suitable for beginners. ");
        gotoxy(3,17);
        printf("A 5*5 board, on the other hand, is good for experts.");
        setTextColor(stdout,TC_LIGHTMAGENTA);
        gotoxy(45,19);
        printf("HOW TO PLAY!");
        setTextColor(stdout,TC_YELLOW);
        gotoxy(2,21);
        printf("1- To make a line choose two points , each point is chosen by row and column respectively ex: 1112.");
        gotoxy(5,22);
        printf("11 is represent the first point and 12 is represent the second point");
        gotoxy(2,23);
        printf("2-To undo a move press u , U , undo or Undo");
        gotoxy(2,24);
        printf("3-To redo a move press r , R , redo or Redo");
        gotoxy(2,25);
        printf("4-To save  the current game press s , S , save or Save");
        gotoxy(2,26);
        printf("5-To exit the game press e , E , exit or Exit");
        setTextColor(stdout,TC_LIGHTCYAN);
        gotoxy(2,27);
        printf("to return to main menu press b:");
        scanf("%c",&back);
        while (back!='b'){
            system("cls");
            goto about;
    }
        fflush(stdin);
        goto label;

        }
  else if (game=='5'){
        newm :
        setTextColor(stdout,TC_YELLOW);
        gotoxy(25,20);
        printf("Thanks for playing Dots And Boxes");
        gotoxy(25,21);
        printf("This project made by ");
        setTextColor(stdout,TC_BLUE);
        printf("Ahmed Samir ");
        setTextColor(stdout,TC_YELLOW);
        printf(" and ");
        setTextColor(stdout,TC_RED);
        printf("Yossef Elmedny");
        setTextColor(stdout, TC_LIGHTGRAY);
  }

getch();
gotoxy(100,100);

    return 0;
}
/*##########################################################functions##########################################################*/
void print_arr(int size,char a[size][size])
{
    int position_x=60,position_y=10,i,j;
    for( i=0; i<size; i++)
    {
        gotoxy(position_x,position_y);
        for( j=0; j<size; j++)
        {
            if(a[i][j]=='z')
            {
                setTextColor(stdout, TC_LIGHTRED);
                printf("%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if(a[i][j]=='x')
            {
                setTextColor(stdout, TC_LIGHTRED);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y-1);
                printf("%c",179);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y);
                printf("%c",179);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y+1);
                printf("%c",179);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if(a[i][j]=='c')
            {
                setTextColor(stdout, TC_LIGHTBLUE);
                printf("%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if (a[i][j]=='v')
            {
                setTextColor(stdout, TC_LIGHTBLUE);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y-1);
                printf("%c",179);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y);
                printf("%c",179);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y+1);
                printf("%c",179);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if(a[i][j]=='A')
            {
                setTextColor(stdout, TC_RED);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y+1);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y-1);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                setTextColor(stdout, TC_LIGHTGRAY);

            }
            else if(a[i][j]=='B')
            {
                setTextColor(stdout, TC_BLUE);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y+1);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y-1);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if(i%2==0 && j%2!=0 )
            {
                printf("%c",a[i][j]);
            }
            else if (a[i][j]==' ' &&  j!=0)
            {
                printf("        ");
            }
            else
                printf("%c",a[i][j]);

        }
        if(i!=0)
            position_y+=2;
        else
            position_y++ ;
    }
}
void Read_points(char points[5])
{
    reread:
    gotoxy(0,27);
    printf(" Enter the input: ");
    scanf("%s",points);
    while( strlen(points)>4)
    {
        gotoxy(0,28);
        printf("Error,Invalid input!");
        goto reread ;
    }
}
void Read_first(char points[5],int n,int *x)
{
    static int i;
    if((*x)!=0)
    {
        gotoxy(5,33);
        printf("press e to Exit");
        gotoxy(0,0);
            gotoxy(0,15);
            printf("Enter Point Coordinates or (u) to undo last play");
            gotoxy(0,16);
            printf("Enter Point coordinates or pass (r) to redo");
        while(1)
        {
            Read_points(points);
            if (strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"e")==0||strcmp(points,"exit")==0){break;}
            else if (strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"s")==0||strcmp(points,"save")==0){break;}

            else if (strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0)
            {          i=1;
                      (*x)--;
                    break;}
            else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0)
            {
                    (*x)++;
                    break;}
            else
            {
                i=0;

                if ((points[0]<'1')||(points[0]>n+'1')||(points[1]<'1')||(points[1]>n+'1')||(points[2]<'1')||(points[2]>n+'1')||(points[3]<'1')||(points[3]>n+'1'))
                {
                    gotoxy(0,31);
                    printf("Error,Invalid input!");


                }
                else
                {
                    (*x)++;
                    break;}}}}

    else
    {
        (*x)++;
        while(1)
        {
            Read_points(points);
            if (i=1&&(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0)){(*x)++;
                    break;}
            if ((points[0]<'1')||(points[0]>n+'1')||(points[1]<'1')||(points[1]>n+'1')||(points[2]<'1')||(points[2]>n+'1')||(points[3]<'1')||(points[3]>n+'1'))
                printf("Error,Invalid input!");
            else
            {

                i=0;
                break;}}}}
void analyze_points(char points[5],int n,int *x)
{

    while(1)
    {
        Read_first(points,n,&(*x));


        if (strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"e")==0||strcmp(points,"exit")==0)
        {
            break;
            //Exit
        }
        else if (strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"s")==0||strcmp(points,"save")==0){break;}
        else if (strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0){break;}
        else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0){break;}
        else
        {
            if ((points[0]==points[2])&&( points[1]-points[3]==1 || points[3]-points[1]==1)){break;}
            else if ((points[1]== points[3])&&( points[0]-points[2]==1 || points[2]-points[0]==1)){break ;}
            else
            {
                gotoxy(0,28);
                printf("Error,Invalid input!");}}}}
void find_index(char points[5],int n,int size,char a[size][size], int turn,int *x)
{
    static  char index1[SIZE],index2[SIZE] ;
    static int ii=0,jj=0,count=0,c;
    int v=1;
    dont:
    while(1)
    {
        analyze_points(points,n,&(*x));
        if (strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"e")==0||strcmp(points,"exit")==0){
            v=0;
            break;}
        else if (strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"s")==0||strcmp(points,"save")==0){break;}
        else if (strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0)
        {   count++;
            ii--;
            jj--;
            a[index1[ii]][index2[jj]]=' ';
            v=0;
            c=0;
            break;}
        else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0)
        {
           if(count&&c==0){
            v=0;
            count --;
            if(index1[ii]%2==1)
            {

                if(turn==1){

                    a[index1[ii++]][index2[jj++]]='z' ;}

                else{
                    a[index1[ii++]][index2[jj++]]='c';}}
            else
            {

                if(turn==1){

                    a[index1[ii++]][index2[jj++]]='x';}
                else{
                    a[index1[ii++]][index2[jj++]]='v';}

            }}
            else {
                fflush(stdin);
                gotoxy(0,28);
                printf("Error,Invalid input!");
                    goto dont;}
            break;}
        else
        {

            index1[ii]= (points[0]+points[2]-1)-2*'0';
            index2[jj]=(points[3]+points[1]-1)-2*'0';

            if(a[index1[ii]][index2[jj]]!=' ')
            {   gotoxy(0,28);
                printf("Error,Invalid input!");
                ii--;
                jj--;}
            else break;}}
    if(v==1)
    {
        c=1;
        index1[ii] = (points[0]+points[2]-1)-2*'0';
        index2[jj]=(points[3]+points[1]-1)-2*'0';
        if(turn==1)
        {
            if(points[0]==points[2]){
                a[index1[ii]][index2[jj]]='z';
                ii++;
                jj++;}
            else{
                a[index1[ii]][index2[jj]]='x';
                ii++;
                jj++;
        }}
        else
        {
            if(points[0]==points[2]){
                a[index1[ii]][index2[jj]]='c';
                ii++;
                jj++;}
            else{
                a[index1[ii]][index2[jj]]='v';
                ii++;
                jj++;}


    }}}
void   check_box(int n,int size,char a[size][size],char letter,int *w)
{
    int c1,c2,i,j;
    for(c1=0,i=2; c1<n; c1++,i+=2){
        for(c2=0,j=2; c2<n; c2++,j+=2)
        {
            if(a[i+1][j]!=' ' && a[i-1][j]!=' ' && a[i][j+1]!=' ' && a[i][j-1]!=' ' && a[i][j]==' ')
            {   a[i][j]=letter ;
                *w=*w+1;}
            if((a[i+1][j]==' ' || a[i-1][j]==' ' || a[i][j+1]==' ' || a[i][j-1]==' ') && a[i][j]!=' ')
            {
                a[i][j]=' ';
                *w=*w-1;}}}}
void   check_for_undo(int n,int size,char a[size][size],char letter,int *w)
{
    int c1,c2,i,j;
    for(c1=0,i=2; c1<n; c1++,i+=2){
        for(c2=0,j=2; c2<n; c2++,j+=2)
        {
            if(a[i+1][j]!=' ' && a[i-1][j]!=' ' && a[i][j+1]!=' ' && a[i][j-1]!=' ' && a[i][j]==letter)
            {   a[i][j]=letter;
                *w=*w+1;}
            if((a[i+1][j]==' ' || a[i-1][j]==' ' || a[i][j+1]==' ' || a[i][j-1]==' ') && a[i][j]!=' ')
            {
                a[i][j]=' ';
                *w=*w-1;}}}}
void general_turn (int turn, players *player1, players *player2,int w )
{
    if(turn==1)
    {
        (*player1).moves++;
        if(w!=0)
            (*player1).score+=w;
    }
    else
    {
        (*player2).moves++;
        if(w!=0)
            (*player2).score+=w;}}
void display (players player1, players player2, int y, int time, int turn)
{
    gotoxy(0,0);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Players Names :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,0);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%s",player1.name);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,0);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%s",player2.name);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,2);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Moves :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,2);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%d",player1.moves);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,2);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%d",player2.moves);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,4);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Score :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,4);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%d",player1.score);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,4);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%d",player2.score);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(90,0);
    setTextColor(stdout, TC_LIGHTGREEN);
    printf("Time : %d : %d",time/60,time%60);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,10);
    setTextColor(stdout, TC_LIGHTMAGENTA);
    printf("Total lines left :     %d",y);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,6);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Player Turn :");
    setTextColor(stdout, TC_LIGHTGRAY);
    if(turn==1)
    {
        gotoxy(30,6);
        setTextColor(stdout, TC_LIGHTRED);
        printf("^");
        setTextColor(stdout, TC_LIGHTGRAY);
    }
    else
    {
        gotoxy(60,6);
        setTextColor(stdout, TC_LIGHTBLUE);
        printf("^");
        setTextColor(stdout, TC_LIGHTGRAY);
    }


}
void display2 (players player1, players computer, int y, int time, int turn)
{
    gotoxy(0,0);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Players Names :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,0);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%s",player1.name);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,0);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%s",computer.name);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,2);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Moves :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,2);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%d",player1.moves);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,2);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%d",computer.moves);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,4);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Score :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,4);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%d",player1.score);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,4);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%d",computer.score);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(90,0);
    setTextColor(stdout, TC_LIGHTGREEN);
    printf("Time : %d : %d",time/60,time%60);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,10);
    setTextColor(stdout, TC_LIGHTMAGENTA);
    printf("Total lines left :     %d",y);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,6);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Player Turn :");
    setTextColor(stdout, TC_LIGHTGRAY);
    if(turn==1)
    {
        gotoxy(30,6);
        setTextColor(stdout, TC_LIGHTRED);
        printf("^");
        setTextColor(stdout, TC_LIGHTGRAY);
    }
    else
    {
        gotoxy(60,6);
        setTextColor(stdout, TC_LIGHTBLUE);
        printf("^");
        setTextColor(stdout, TC_LIGHTGRAY);
    }
}
void undo_turn (int turn, players (*player1), players (*player2),int w )
{
    if(turn==1){
        (*player1).moves--;
        if(w!=0)
            (*player1).score+=w;}
    else{
        (*player2).moves--;
        if(w!=0)
            (*player2).score+=w;}}
void computer_move(int  size, char a[size] [size],int *ii,int *jj)
{
    int i,j,flag=0;
    for(i=1; i<size; i+=2)
    {
        for(j=2; j<size; j+=2)
        {
            if(a[i][j] == ' ')
            {
                *ii=i;
                *jj=j;
                a[i][j] = 'c';
                flag=1;
                break;
            }
        }
        if(flag==1)
            break;
    }
    if(flag==0)
    {
        for(i=2; i<size; i+=2)
        {
            for(j=1; j<size; j+=2)
            {
                if(a[i][j] == ' ')
                {
                    *ii=i;
                    *jj=j;
                    a[i][j] = 'v';
                    flag=1;
                    break;
                }
            }
            if(flag==1)
                break;
        }
    }}
void det_winner(players player1,players player2)
{

    if(player1.score>player2.score)

    {
        gotoxy(50,1);
        printf("%s Wins",player1.name);
    }
    else if(player1.score<player2.score)

    {
        gotoxy(50,1);
        printf("%s Wins",player2.name);


    }
    else
    {
        gotoxy(50,1);
        printf("DRAW");
    }
    gotoxy(0,4);
    Winner(player1,player2);
}
void save(int size,char a[size][size],players x,players y,char type[2],int turn,int total_lines, int clock,char slot,char mode)
{
        if(slot=='a'){
        f1=fopen("file1.txt","w");
        putc(mode,f1);
        fputs(type,f1);
        fwrite(a,sizeof(char),size*size,f1);
        putw(turn,f1);
        fwrite(&x,sizeof(players),4,f1);
        fwrite(&y,sizeof(players),4,f1);
        putw(total_lines,f1);
        putw(clock,f1);
        fclose(f1);}
        else if(slot=='b'){
        f2=fopen("file2.txt","w");
        putc(mode,f2);
        fputs(type,f2);
        fwrite(a,sizeof(char),size*size,f2);
        putw(turn,f2);
        fwrite(&x,sizeof(players),4,f2);
        fwrite(&y,sizeof(players),4,f2);
        putw(total_lines,f2);
        putw(clock,f2);
        fclose(f2);}
        else if(slot=='c'){
        f3=fopen("file3.txt","w");
        putc(mode,f3);
        fputs(type,f3);
        fwrite(a,sizeof(char),size*size,f3);
        putw(turn,f3);
        fwrite(&x,sizeof(players),4,f3);
        fwrite(&y,sizeof(players),4,f3);
        putw(total_lines,f3);
        putw(clock,f3);
        fclose(f3);}
        else if (slot=='d'){
        debugging_file=fopen("debug.txt","a");
        putc(mode,debugging_file);
        fputs(type,debugging_file);
        fwrite(a,sizeof(char),size*size,debugging_file);
        putw(turn,debugging_file);
        fwrite(&x,sizeof(players),4,debugging_file);
        fwrite(&y,sizeof(players),4,debugging_file);
        putw(total_lines,debugging_file);
        putw(clock,debugging_file);
        fclose(debugging_file);}}
void change_save(char *slot)
{
    gotoxy(30,0);
    printf("Enter which slot you want to save:");
    gotoxy(25,1);
    printf("a:slot1");
    gotoxy(25,2);
    printf("b:slot2");
    gotoxy(25,3);
    printf("c:slot3");
    gotoxy(65,0);
    scanf(" %c",&(*slot));
}
int check_file(char slot){
    int x;
    if(slot=='a'){
        f1=fopen("file1.txt","r");
        if(f1==NULL)x=0;
        else x=1;
        fclose(f1);}
    else if(slot=='b'){
        f2=fopen("file2.txt","r");
        if(f2==NULL)
        x=0;
        else x=1;
        fclose(f2);}
    else if(slot=='c'){
        f3=fopen("file3.txt","r");
        if(f3==NULL)
        x=0;
        else x=1;
        fclose(f3);}return x;}

void Winner(players x,players y){
    int l;
    strlwr(x.name);
    strlwr(y.name);
    top=fopen("rank.txt","r");
    fread(rankarray,sizeof(rankok),10,top);
    fclose(top);
    l=0;
    if(x.score>y.score){
            for(int i=0;i<10;i++){
                if(l==0){
                    if(strcmp(x.name,rankarray[i].name)==0){
                        if(x.score>rankarray[i].score)  rankarray[i].score=x.score;
                        break;}}
                else {
                    if(rankarray[i].score<x.score){
                        strcpy(rankarray[i].name,x.name);
                        rankarray[i].score=x.score;
                        break;}}
            if(i==9){
                    l=1;
                    i=0;}}}

    else if(x.score<y.score){
        if(strcmp(y.name,"computer")!=0){
            for(int i=0;i<10;i++){
            if(l==0){
            if(strcmp(y.name,rankarray[i].name)==0){
                if(y.score>rankarray[i].score) rankarray[i].score=y.score;
                break;}}
            else{
                if(rankarray[i].score<y.score){
                strcpy(rankarray[i].name,y.name);
                rankarray[i].score=y.score;
                break;}}
            if(i==9){
                l=1;
                i=0;}}}}
    for(int j=9;j>0;j--){
        for(int i=0;i<10-j;i++){
            if(rankarray[i].score>rankarray[i+1].score){
                rankok temp=rankarray[i];
                rankarray[i]=rankarray[i+1];
                rankarray[i+1]=temp;}}}


    for(int i=9;i>=0;i--){printf("%s\t%d\n",rankarray[i].name,rankarray[i].score);}
    top=fopen("rank.txt","w");
    fwrite(rankarray,sizeof(rankok),10,top);
    fclose(top);}
void gotoxy(int x, int y)
{
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           (COORD){ .X=x, .Y=y });
}
void print_word()
{
    int k=100;

   setTextColor(stdout, TC_LIGHTRED);//d
   gotoxy(0,0);
   printf("Dot&Boxes");
   gotoxy(0,1);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(0,2);
   printf("Dot&BoxesDot&BoxesDot&Boxes");
   gotoxy(0,3);
   printf("Dot&Boxes\nDot&Boxes\nDot&Boxes\nDot&Boxes\nDot&Boxes");
   gotoxy(20,3);
   printf("Dot&Boxes");
   gotoxy(20,4);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(20,5);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(20,6);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(20,7);
   printf("Dot&Boxes");
   gotoxy(0,10);
   printf("Dot&Boxes");
   gotoxy(0,9);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(0,8);
   printf("Dot&BoxesDot&BoxesDot&Boxes");
   //o
   gotoxy(53,0);
   printf("Dot&Boxes");
   gotoxy(49,1);printf("Dot&BoxesDot&Boxes");
   gotoxy(44,2);printf("Dot&BoxesDot&BoxesDot&Boxes");
   gotoxy(42,3);printf("Dot&Boxes");
   gotoxy(41,4);printf("Dot&Boxes");
   gotoxy(40,5);printf("Dot&Boxes");
   gotoxy(40,6);printf("Dot&Boxes");
   gotoxy(41,7);printf("Dot&Boxes");
   gotoxy(64,3);printf("Dot&Boxes");
   gotoxy(65,4);printf("Dot&Boxes");
   gotoxy(66,5);printf("Dot&Boxes");
   gotoxy(65,6);printf("Dot&Boxes");
   gotoxy(64,7);printf("Dot&Boxes");
   gotoxy(53,10);
   printf("Dot&Boxes");
   gotoxy(49,9);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(44,8);
   printf("Dot&BoxesDot&BoxesDot&Boxes");
   //t
   gotoxy(75,0);printf("Dot&BoxesDot&BoxesDot&Boxes");
   gotoxy(75,1);printf("Dot&BoxesDot&BoxesDot&Boxes");
   gotoxy(75,2);printf("Dot&BoxesDot&BoxesDot&Boxes");
   gotoxy(84,3);printf("Dot&Boxes");
   gotoxy(84,4);printf("Dot&Boxes");
   gotoxy(84,5);printf("Dot&Boxes");
   gotoxy(84,6);printf("Dot&Boxes");
   gotoxy(84,7);printf("Dot&Boxes");
   gotoxy(84,8);printf("Dot&Boxes");
   gotoxy(84,9);printf("Dot&Boxes");
   gotoxy(84,10);printf("Dot&Boxes");
   //s
   gotoxy(101,4);printf("   Dot&Boxes");
   gotoxy(101,5);printf("Dot&Boxes ");
   gotoxy(101,6);printf("   Dot&Boxes");
   gotoxy(101,7);printf("      Dot&Boxes");
   gotoxy(101,8);printf("         Dot&Boxes");
   gotoxy(101,9);printf("        Dot&Boxes");
   gotoxy(101,10);printf("    Dot&Boxes");
   Sleep(500);
   gotoxy(30,14);
    setTextColor(stdout,TC_CYAN);
    puts("please wait........loading");
    gotoxy(20,18);
    for(int i=0;i<80;i++){
        if(i%2==0)
        setTextColor(stdout, TC_RED);
        Beep(k,1);
        k+=100;
        printf("%c",219);
        setTextColor(stdout, TC_LIGHTRED);
    }
   system("cls");
   //A
   setTextColor(stdout, TC_LIGHTRED);
   gotoxy(15,0);
   printf("Dot&Boxes");
   gotoxy(10,1);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(9,2);
   printf("Dot&Boxes     Dot&Boxes");
   gotoxy(8,3);
   printf("Dot&Boxes       Dot&Boxes");
   gotoxy(7,3);
   printf("Dot&Boxes         Dot&Boxes");
   gotoxy(6,4);
   printf("Dot&Boxes           Dot&Boxes");
   gotoxy(5,5);
   printf("Dot&Boxes             Dot&Boxes");
   gotoxy(4,6);
   printf("Dot&Boxes               Dot&Boxes");
   gotoxy(3,7);
   printf("Dot&Boxes                 Dot&Boxes");
   gotoxy(2,8);
   printf("Dot&Boxes                   Dot&Boxes");
   gotoxy(1,9);
   printf("Dot&Boxes                     Dot&Boxes");
   gotoxy(0,10);
   printf("Dot&Boxes                       Dot&Boxes");
   gotoxy(10,6);printf("Dot&BoxesDot&Boxes");
   gotoxy(12,7);printf("Dot&BoxesDot&Boxes");
   //N
   gotoxy(42,0);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,1);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,2);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,3);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,4);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,5);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,6);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,7);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,8);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,9);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(42,10);printf("Dot&Boxes                Dot&Boxes");
   gotoxy(43,0);printf("Dot&Boxes");
   gotoxy(45,1);printf("Dot&Boxes");
   gotoxy(47,2);printf("Dot&Boxes");
   gotoxy(49,3);printf("Dot&Boxes");
   gotoxy(51,4);printf("Dot&Boxes");
   gotoxy(53,5);printf("Dot&Boxes");
   gotoxy(55,6);printf("Dot&Boxes");
   gotoxy(57,7);printf("Dot&Boxes");
   gotoxy(59,8);printf("Dot&Boxes");
   gotoxy(61,9);printf("Dot&Boxes");
   gotoxy(63,10);printf("Dot&Boxes");
   //d
   gotoxy(80,0);
   printf("Dot&Boxes");
   gotoxy(80,1);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(80,2);
   printf("Dot&BoxesDot&BoxesDot&Boxes");
   gotoxy(80,3);printf("Dot&Boxes           Dot&Boxes ");
   gotoxy(80,4);printf("Dot&Boxes");
   gotoxy(80,5);printf("Dot&Boxes");
   gotoxy(80,6);printf("Dot&Boxes");
   gotoxy(80,7);printf("Dot&Boxes");
   gotoxy(80,8);printf("Dot&Boxes");
   gotoxy(80,9);printf("Dot&Boxes");
   gotoxy(80,10);printf("Dot&Boxes");
   gotoxy(100,4);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(100,5);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(100,6);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(100,7);
   printf("Dot&Boxes");
   gotoxy(80,10);
   printf("Dot&Boxes");
   gotoxy(80,9);
   printf("Dot&BoxesDot&Boxes");
   gotoxy(80,8);
   printf("Dot&BoxesDot&BoxesDot&Boxes");
   Sleep(500);
   gotoxy(30,14);
    setTextColor(stdout,TC_CYAN);
    puts("please wait........loading");
    gotoxy(20,18);
    for(int i=0;i<80;i++){
        if(i%2==0)
        setTextColor(stdout, TC_RED);
        Beep(k,1);
        k+=100;
        printf("%c",219);
        setTextColor(stdout, TC_LIGHTRED);
    }
   system("cls");
   setTextColor(stdout, TC_LIGHTRED);
   //b
   gotoxy(0,0);printf("Dot&BoxesDot&Boxes");
   gotoxy(0,1);printf("Dot&Boxes     Dot&Boxes");
   gotoxy(0,2);printf("Dot&Boxes        Dot&Boxes");
   gotoxy(0,3);printf("Dot&Boxes     Dot&Boxes");
   gotoxy(0,4);printf("Dot&Boxes    Dot&Boxes");
   gotoxy(0,5);printf("Dot&BoxesDot&Boxes");
   gotoxy(0,6);printf("Dot&Boxes     Dot&Boxes");
   gotoxy(0,7);printf("Dot&Boxes      Dot&Boxes");
   gotoxy(0,8);printf("Dot&Boxes         Dot&Boxes");
   gotoxy(0,9);printf("Dot&Boxes      Dot&Boxes");
   gotoxy(0,10);printf("Dot&BoxesDot&Boxes");
   //o
   gotoxy(0,0);printf("Dot&BoxesDot&Boxes");
   gotoxy(0,1);printf("Dot&Boxes    Dot&Boxes");
   gotoxy(0,2);printf("Dot&Boxes       Dot&Boxes");
   gotoxy(0,3);printf("Dot&Boxes    Dot&Boxes");
   gotoxy(0,4);printf("Dot&Boxes   Dot&Boxes");
   gotoxy(0,5);printf("Dot&BoxesDot&Boxes");
   gotoxy(0,6);printf("Dot&Boxes    Dot&Boxes");
   gotoxy(0,7);printf("Dot&Boxes     Dot&Boxes");
   gotoxy(0,8);printf("Dot&Boxes        Dot&Boxes");
   gotoxy(0,9);printf("Dot&Boxes     Dot&Boxes");
   gotoxy(0,10);printf("Dot&BoxesDot&Boxes");
   //o

   gotoxy(25,4);printf("          Dot&Boxes");
   gotoxy(25,5);printf("   Dot&Boxes     Dot&Boxes");
   gotoxy(25,6);printf("  Dot&Boxes        Dot&Boxes");
   gotoxy(25,7);printf(" Dot&Boxes          Dot&Boxes");
   gotoxy(25,8);printf("  Dot&Boxes        Dot&Boxes");
   gotoxy(25,9);printf("   Dot&Boxes     Dot&Boxes");
   gotoxy(25,10);printf("          Dot&Boxes");
   //x
   gotoxy(50,4);printf(" Dot&Boxes          Dot&Boxes");
   gotoxy(50,5);printf("   Dot&Boxes     Dot&Boxes");
   gotoxy(50,6);printf("    Dot&Boxes   Dot&Boxes");
   gotoxy(50,7);printf("       Dot&Boxe&Boxes");
   gotoxy(50,8);printf("     Dot&Boxes   Dot&Boxes");
   gotoxy(50,9);printf("   Dot&Boxes      Dot&Boxes");
   gotoxy(50,10);printf(" Dot&Boxes          Dot&Boxes");

   //e
   gotoxy(75,4);printf("        Dot&Boxes");
   gotoxy(75,5);printf("  Dot&Boxes    Dot&Boxes");
   gotoxy(75,6);printf(" Dot&Boxes      Dot&Boxes");
   gotoxy(75,7);printf("Dot&Boxes Dot&Boxes");
   gotoxy(75,8);printf(" Dot&Boxes  ");
   gotoxy(75,9);printf("  Dot&Boxes");
   gotoxy(75,10);printf("         Dot&Boxes");
   //s
   gotoxy(101,4);printf("   Dot&Boxes");
   gotoxy(101,5);printf("Dot&Boxes ");
   gotoxy(101,6);printf("   Dot&Boxes");
   gotoxy(101,7);printf("      Dot&Boxes");
   gotoxy(101,8);printf("         Dot&Boxes");
   gotoxy(101,9);printf("        Dot&Boxes");
   gotoxy(101,10);printf("    Dot&Boxes");
   Sleep(500);
      gotoxy(30,14);
    setTextColor(stdout,TC_CYAN);
    puts("please wait........loading");
    gotoxy(20,18);
    for(int i=0;i<80;i++){
        if(i%2==0)
        setTextColor(stdout, TC_RED);
        Beep(k,1);
        k+=100;
        printf("%c",219);
        setTextColor(stdout, TC_LIGHTRED);
    }setTextColor(stdout,TC_CYAN);
    printf("\n\n \t\t\t\t\t\t successfully loaded");

   system("cls");
    setTextColor(stdout, TC_LIGHTGRAY);}


