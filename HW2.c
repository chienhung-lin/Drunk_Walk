#include <stdio.h>      /*default io stream*/
#include <stdbool.h>    /*bool type in c99*/
#include <stdlib.h>     /*srand(), rand()*/
#include <time.h>       /*time(NULL)*/

void error(char *msg);

bool InputRowCol(unsigned int *Row, unsigned int *Col, unsigned int *Y, unsigned int *X);

unsigned int** CreateMap(unsigned int *Row, unsigned int *Col);
unsigned int** FreeMap(unsigned int **map);
void InitMap(unsigned int **map, unsigned int *Row, unsigned int *Col, unsigned int *Y, unsigned int *X);

void RandomWalk(unsigned int **map, unsigned int *moveStep, unsigned int *Row, unsigned int *Col, unsigned int *Y, unsigned int *X);
void OutPutResult(unsigned int **map, unsigned int *moveStep, unsigned int *Row, unsigned int *Col, unsigned int *Y, unsigned int *X);

int main(int argc, char *argv[]){

    unsigned int **map = NULL;
	unsigned int Row = 0, Col = 0;
    unsigned int x = 0, y = 0;
    unsigned int moveStep = 0;

    while( InputRowCol(&Row, &Col, &y, &x) ){

    map = CreateMap(&Row, &Col);

    InitMap(map, &Row, &Col, &y, &x);
    RandomWalk(map, &moveStep, &Row, &Col, &y, &x);
    OutPutResult(map, &moveStep, &Row, &Col,&y,&x);

    map = FreeMap(map);

    }
    return 0;
}

void error(char *msg){
    fprintf(stderr,"%s",msg);
    exit(1);
}

bool InputRowCol(unsigned int *Row, unsigned int *Col, unsigned int *Y, unsigned int *X){

    while(1){
        printf("\nPlease Enter the dimension of map\n"
                    "(input format:[Row] [Col] [X] [Y]),\n"
                    "(Range:Rol->(2:40], Col->[2:20], X->[0,Col), Y->[0.Row))\n"
                    "(exit input: 0 0 0 0)\n"
                    ": ");
        scanf("%u %u %u %u",Row,Col,Y,X);
        if( *Row == 0 && *Col == 0 && *X == 0 && *Y == 0){
            printf("exit file\n");
            return false;
        }
        else if( (*Row <= 2 || *Row > 40) || (*Col < 2 || *Col > 20) )
		    fprintf(stderr,"Error Input, ([Row],[Col])=([2:40],[2:20])\n");
        else if( ( *Y < 0 || *Y > *Row ) || ( *X < 0 || *X > *Col) )
            fprintf(stderr,"X or Y out of the range of Rol or Col\n");
        else{
            //test
            //printf("Row: %u, Col: %u, X: %u, Y: %u\n", *Row, *Col, *X, *Y);
            //test
            return true;
        }
    }
}

unsigned int** CreateMap(unsigned int *Row, unsigned int *Col){
    unsigned int *longMap = malloc(sizeof(unsigned int)*(*Row)*(*Col));
    unsigned int **map = malloc(sizeof(unsigned int *)*(*Row));
    if( (longMap == NULL) || (map == NULL) )
        error("Error in malloc space");
    for(unsigned int j = 0 ; j < (*Row) ; ++j ){
        map[j] = longMap + j*(*Col) ;
    }
    //test
    //printf("successfully create map\n");
    //test
    return map;
}

unsigned int** FreeMap(unsigned int **map){
    free(*map);
    free(map);
    return map;
    //test free
    //printf("successfully free map\n");
    //test
}

void InitMap(unsigned int **map, unsigned int *Row, unsigned int *Col, unsigned int *Y, unsigned int *X){
    for( unsigned int Rindex = 0 ; Rindex < (*Row) ; ++Rindex )
        for( unsigned int Cindex = 0 ; Cindex < (*Col) ; ++Cindex )
            map[Rindex][Cindex] = 0;
    map[*Y][*X] = 1;

    //test map content
    /*
    printf("    ");
    for(unsigned int i = 0 ; i < *Col ; ++i)
        printf(" C%2u",i);
    printf("\n");
    for(unsigned int j = 0 ; j < *Row ; ++j){
        printf("R%2u",j);
        for(unsigned int i = 0 ; i < *Col ; ++i)
            printf("%4u",map[j][i]);
        printf("\n");
    }
    */
    //printf("successfully inital map\n");
}

void RandomWalk(unsigned int **map, unsigned int *moveStep, unsigned int *Row, unsigned int *Col, unsigned int *Y, unsigned int *X){

    unsigned int ibug = *X;
    unsigned int jbug = *Y;
    unsigned int itmpt = 0, jtmpt = 0;
    unsigned int noZero = (*Row) * (*Col) - 1 ;
    int imove[8] = {-1, 0, 1, 1, 1, 0,-1, 1};
    int jmove[8] = { 1, 1, 1, 0,-1,-1,-1, 0};

    (*moveStep) = 0;

    srand(time(NULL));
  
    /*
    for(unsigned int i = 0 ; i < *Col ; ++i)
        printf(" C%2u",i);
    printf("\n");
    for(unsigned int j = 0 ; j < *Row ; ++j){
        printf("R%2u",j);
        for(unsigned int i = 0 ; i < *Col ; ++i)
            printf("%4u",map[j][i]);
        printf("\n");
    }
    */

    
    for(;(noZero!=0) && ((*moveStep+1)<=50000);){
        itmpt = ibug + imove[(unsigned int)(rand()/(RAND_MAX+1.0)*8.0)];
        jtmpt = jbug + jmove[(unsigned int)(rand()/(RAND_MAX+1.0)*8.0)];
        if( (itmpt < 0 || itmpt > (*Col-1)) || (jtmpt < 0 || jtmpt > (*Row-1)) )
            continue;
        ++(*moveStep);
        if( !map[jtmpt][itmpt] )
            --noZero;
        ++map[jtmpt][itmpt];
        ibug = itmpt;
        jbug = jtmpt;
    }
}

void OutPutResult(unsigned int **map, unsigned int *moveStep, unsigned int *Row, unsigned int *Col, unsigned int *Y, unsigned int *X){
    
    printf("\n      ");
    for(unsigned int Cindex = 0 ; Cindex < *Col ; ++Cindex)
        printf("%5uC",Cindex);
    printf("\n\n");
    for(unsigned int Rindex = 0 ; Rindex < *Row ; ++Rindex ){
        printf("%5uR",Rindex);
        for(unsigned int Cindex = 0 ; Cindex < *Col ; ++Cindex)
            printf("%6u",map[Rindex][Cindex]);
        printf("\n");
    }

    /*
    for(unsigned int j = 0 ; j < *Row ; ++j)
        for(unsigned int i = 0 ; i < *Col ; ++i)
            printf("%2u-%2u: %u\n",j,i,map[j][i]);
    */
    printf("\nRow:%u, Col:%u, Y:%u, X:%u\n",*Row,*Col,*Y,*X);
    printf("Total Move Step: %u\n",*moveStep);
}
