// #include <stdio.h>
// #include <stdlib.h>
#include "Grid.h"
// #include "class.h"
// #include "wip/SortedLinkedList.h"


// int nodeCost(int ValX, int ValY, int DestX, int DestY, int SourceX, int SourceY)
// {
    
//     int H = abs(DestX - ValX) + abs(DestY - ValY);
//     int G = abs(SourceX - ValX) + abs(SourceY - ValY);
//     return G + H;
// }

// int doStuff(int ValX, int ValY, int EntryNodeX, int EntryNodeY, int ExitNodeX, int ExitNodeY)
// {
//     //If a node has visited set to true, it is in the closed array
//     //If a node has visited set to false, and the colour is red, it is in the open array
//     int f = nodeCost(ValX, ValY, ExitNodeX, ExitNodeX, EntryNodeX, EntryNodeY);
//     if (ranArray[ValX][ValY].type != underscore && ranArray[ValX][ValY].visited == true)//If neighbour is not traversable or neighbour is in closed
//     {
//         return 0;//Skip to the next neighbour
//     }
//     else if((ranArray[ValX][ValY].colour == 8 || ranArray[ValX][ValY].visited == false)|| ranArray[ValX][ValY].distance > f)   //If neighbour is not in open, or the previous cost of the adjacent node is greater than the f value
//     {
//         ranArray[ValX][ValY].distance = f;//Set the distance of that node to the parent value
//         if (ranArray[ValX][ValY].colour != 2)   //if it is in the open set
//         {
//             ranArray[ValX][ValY].colour = 2;    //add to the open set
//             return 1;
//         }
//     }
//     return 0;
// }

// int main()
// {
//     OrderedList OpenList;
//     OrderedList *current;
//     int EntryNodeX, EntryNodeY, ExitNodeX, ExitNodeY, valX, valY;
//     setlocale(LC_CTYPE, "");
//     wchar_t charecter;
//     int height = 30;
//     int width = 30;
//     int closed[height * width][2];
//     makeGrid(height, width);
//     EntryNodeX = 3;
//     EntryNodeY = 7;
//     ranArray[EntryNodeX][EntryNodeY].type= enterSymbol;
//     ExitNodeX = 24;
//     ExitNodeY = 21;
//     ranArray[ExitNodeX][ExitNodeY].type = exitSymbol;
//     insert_sll(p2r, nodeCost(EntryNodeX, EntryNodeY, ExitNodeX, ExitNodeY, EntryNodeX, EntryNodeY), EntryNodeX, EntryNodeY);
    
//     for (int i = 4; i < height - 1; i++)
//         {
//             ranArray[i][width / 2].distance = 999;
//             ranArray[i][width / 2].visited = true;
//             ranArray[i][width / 2].type = whiteBlock;
//         }
        

//     while(!isEmpty_sll(p2r))
//     {
//         current = *p2r;
//         pop_sll(p2r);
//         valX = current->x;
//         valY = current->y;
//         ranArray[valX][valY].visited = true;
//         ranArray[valX][valY].colour = 2;
//         int tempX, tempY;
//         usleep(50000);
//         printGrid(height, width);
//         clear();
        
//         if (valX == ExitNodeX && valY == ExitNodeY)
//         {
//             break;
//         }
//         else
//         {
//             tempX = valX;
//             tempY = valY - 1;
//             if(doStuff(tempX, tempY, EntryNodeX, EntryNodeY, ExitNodeX, ExitNodeY) && ranArray[tempX][tempY].visited == false)
//             {
//                 ranArray[tempX][tempY].parentNode[0] = valX;
//                 ranArray[tempX][tempY].parentNode[1] = valY;
//                 insert_sll(p2r, ranArray[tempX][tempY].distance, tempX, tempY);
//             }
//             tempX = valX;
//             tempY = valY + 1;
//             if(doStuff(tempX, tempY, EntryNodeX, EntryNodeY, ExitNodeX, ExitNodeY) && ranArray[tempX][tempY].visited == false)
//             {
//                 ranArray[tempX][tempY].parentNode[0] = valX;
//                 ranArray[tempX][tempY].parentNode[1] = valY;
//                 insert_sll(p2r, ranArray[tempX][tempY].distance, tempX, tempY);
//             }
//             tempX = valX -1;
//             tempY = valY;
//             if(doStuff(tempX, tempY, EntryNodeX, EntryNodeY, ExitNodeX, ExitNodeY) && ranArray[tempX][tempY].visited == false)
//             {
//                 ranArray[tempX][tempY].parentNode[0] = valX;
//                 ranArray[tempX][tempY].parentNode[1] = valY;
//                 insert_sll(p2r, ranArray[tempX][tempY].distance, tempX, tempY);
//             }
//             tempX = valX + 1;
//             tempY = valY;
//             if(doStuff(tempX, tempY, EntryNodeX, EntryNodeY, ExitNodeX, ExitNodeY) && ranArray[tempX][tempY].visited == false)
//             {
//                 ranArray[tempX][tempY].parentNode[0] = valX;
//                 ranArray[tempX][tempY].parentNode[1] = valY;
//                 insert_sll(p2r, ranArray[tempX][tempY].distance, tempX, tempY);
//             }
//         }
//         ranArray[valX][valY].colour = 3;
//     }

//     int backX = ExitNodeX;
//     int backY = ExitNodeY;
//     int tempX, tempY;

//     while(ranArray[backX][backY].type != enterSymbol)
//     {
//         ranArray[ExitNodeX][ExitNodeY].type = exitSymbol;
//         ranArray[ExitNodeX][ExitNodeY].colour = 8;
//         ranArray[EntryNodeX][EntryNodeY].colour = 8;
//         ranArray[backX][backY].colour = 4;
//         ranArray[backX][backY].type = dot;
//         tempX = ranArray[backX][backY].parentNode[0];   //Probably inneficient
//         tempY = ranArray[backX][backY].parentNode[1];
//         backX = tempX;
//         backY = tempY;
//         usleep(100000);
//         clear();
//         printGrid(height, width);
//     }
//     system("clear");
//     printGrid(height, width);
//     freeGrid(height, width);
// }

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
/* and not not_eq */
#include <iso646.h>
/* add -lm to command line to compile with this header */
#include <math.h>
 
#define map_size_rows 10
#define map_size_cols 10
 
char map[map_size_rows][map_size_cols] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
 
/* description of graph node */
struct stop {
    double col, row;
    /* array of indexes of routes from this stop to neighbours in array of all routes */
    int * n;
    int n_len;
    double f, g, h;
    int from;
};
 
int ind[map_size_rows][map_size_cols] = {
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};
 
/* description of route between two nodes */
struct route {
    /* route has only one direction! */
    int x; /* index of stop in array of all stops of src of this route */
    int y; /* intex of stop in array of all stops od dst of this route */
    double d;
};
 
int main() {
    setlocale(LC_CTYPE, "");
    int i, j, k, l, b, found;
    int p_len = 0;
    int * path = NULL;
    int c_len = 0;
    int * closed = NULL;
    int o_len = 1;
    int * open = (int*)calloc(o_len, sizeof(int));
    double min, tempg;
    int s;
    int e;
    int current;
    int s_len = 0;
    struct stop * stops = NULL;
    int r_len = 0;
    struct route * routes = NULL;
 
    for (i = 1; i < map_size_rows - 1; i++) {
        for (j = 1; j < map_size_cols - 1; j++) {
            if (!map[i][j]) {
                ++s_len;
                stops = (struct stop *)realloc(stops, s_len * sizeof(struct stop));
                int t = s_len - 1;
                stops[t].col = j;
                stops[t].row = i;
                stops[t].from = -1;
                stops[t].g = DBL_MAX;
                stops[t].n_len = 0;
                stops[t].n = NULL;
                ind[i][j] = t;
            }
        }
        printf("\n");
    }
 
    /* index of start stop */
    s = 3;
    /* index of finish stop */
    e = s_len - 12;
 
    for (i = 0; i < s_len; i++) {
        stops[i].h = sqrt(pow(stops[e].row - stops[i].row, 2) + pow(stops[e].col - stops[i].col, 2));
    }
 
    for (i = 1; i < map_size_rows - 1; i++) {
        for (j = 1; j < map_size_cols - 1; j++) {
            if (ind[i][j] >= 0) {
                for (k = i - 1; k <= i + 1; k++) {
                    for (l = j - 1; l <= j + 1; l++) {
                        if ((k == i) and (l == j)) {
                            continue;
                        }
                        if (ind[k][l] >= 0) {
                            ++r_len;
                            routes = (struct route *)realloc(routes, r_len * sizeof(struct route));
                            int t = r_len - 1;
                            routes[t].x = ind[i][j];
                            routes[t].y = ind[k][l];
                            routes[t].d = sqrt(pow(stops[routes[t].y].row - stops[routes[t].x].row, 2) + pow(stops[routes[t].y].col - stops[routes[t].x].col, 2));
                            ++stops[routes[t].x].n_len;
                            stops[routes[t].x].n = (int*)realloc(stops[routes[t].x].n, stops[routes[t].x].n_len * sizeof(int));
                            stops[routes[t].x].n[stops[routes[t].x].n_len - 1] = t;
                        }
                    }
                }
            }
        }
    }
 
    open[0] = s;
    stops[s].g = 0;
    stops[s].f = stops[s].g + stops[s].h;
    found = 0;
 
    while (o_len and not found) {
        min = DBL_MAX;
 
        for (i = 0; i < o_len; i++) {
            if (stops[open[i]].f < min) {
                current = open[i];
                min = stops[open[i]].f;
            }
        }
 
        if (current == e) {
            found = 1;
 
            ++p_len;
            path = (int*)realloc(path, p_len * sizeof(int));
            path[p_len - 1] = current;
            while (stops[current].from >= 0) {
                current = stops[current].from;
                ++p_len;
                path = (int*)realloc(path, p_len * sizeof(int));
                path[p_len - 1] = current;
            }
        }
 
        for (i = 0; i < o_len; i++) {
            if (open[i] == current) {
                if (i not_eq (o_len - 1)) {
                    for (j = i; j < (o_len - 1); j++) {
                        open[j] = open[j + 1];
                    }
                }
                --o_len;
                open = (int*)realloc(open, o_len * sizeof(int));
                break;
            }
        }
 
        ++c_len;
        closed = (int*)realloc(closed, c_len * sizeof(int));
        closed[c_len - 1] = current;
 
        for (i = 0; i < stops[current].n_len; i++) {
            b = 0;
 
            for (j = 0; j < c_len; j++) {
                if (routes[stops[current].n[i]].y == closed[j]) {
                    b = 1;
                }
            }
 
            if (b) {
                continue;
            }
 
            tempg = stops[current].g + routes[stops[current].n[i]].d;
 
            b = 1;
 
            if (o_len > 0) {
                for (j = 0; j < o_len; j++) {
                    if (routes[stops[current].n[i]].y == open[j]) {
                        b = 0;
                    }
                }
            }
 
            if (b or (tempg < stops[routes[stops[current].n[i]].y].g)) {
                stops[routes[stops[current].n[i]].y].from = current;
                stops[routes[stops[current].n[i]].y].g = tempg;
                stops[routes[stops[current].n[i]].y].f = stops[routes[stops[current].n[i]].y].g + stops[routes[stops[current].n[i]].y].h;
 
                if (b) {
                    ++o_len;
                    open = (int*)realloc(open, o_len * sizeof(int));
                    open[o_len - 1] = routes[stops[current].n[i]].y;
                }
            }
        }
    }
 
    for (i = 0; i < map_size_rows; i++) {
        for (j = 0; j < map_size_cols; j++) {
            if (map[i][j]) {
                wprintf(L"%lc", whiteBlock);
            } else {
                b = 0;
                for (k = 0; k < p_len; k++) {
                    if (ind[i][j] == path[k]) {
                        ++b;
                    }
                }
                if (b) {
                    wprintf(L"%lc", dot);
                } else {
                    wprintf(L"%lc", underscore);
                }
            }
        }
        putchar('\n');
    }
 
    if (not found) {
        puts("IMPOSSIBLE");
    } else {
        printf("path cost is %d:\n", p_len);
        for (i = p_len - 1; i >= 0; i--) {
            printf("(%1.0f, %1.0f)\n", stops[path[i]].col, stops[path[i]].row);
        }
    }
 
    for (i = 0; i < s_len; ++i) {
        free(stops[i].n);
    }
    free(stops);
    free(routes);
    free(path);
    free(open);
    free(closed);
 
    return 0;
}
 