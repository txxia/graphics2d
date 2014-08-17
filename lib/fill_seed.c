#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

#include "Queue.h"

#include "fill_seed.h"

void seedFillSimple4c(int sx, int sy,
                      const int bx1, const int by1,
                      const int bx2, const int by2,
                      int** boundaries,
                      void (*callback)(int, int)){
    int X = bx2-bx1+1,    // width of the box
        Y = by2-by1+1;    // height of the box

    StackData pixel;
    // keeps track of pixels visited

    int **pixMap = (int **)malloc(X*sizeof(int*));
    for(int i=0; i<X; i++){
        pixMap[i] = (int *)calloc(Y, sizeof(int));
    }

    // initialize stack
    Stack* stack = stack_init();

    assert(sx>=bx1 && sx<=bx2 && sy>=by1 && sy<=by2);
    // push seed pixel
    stack_push(stack, stack_data(sx-bx1, sy-by1));

    while(!stack_empty(stack)){
        // get a pixel from the stack
        pixel = stack_pop(stack);
        sx = (int)pixel.x;      // current seed x coord
        sy = (int)pixel.y;      // current seed y coord
        int rx = sx-bx1,        // relative x coord
            ry = sy-by1;        // relative y coord

        if(!pixMap[rx][ry]){
            pixMap[rx][ry] = 1;
            callback(sx, sy);
        }
        // examine the surrounding pixels to see if they should be placed
        //  onto the stack
        if(sx+1<=bx2 && !pixMap[rx+1][ry] && !boundaries[rx+1][ry])
            stack_push(stack, stack_data(sx+1, sy));
        if(sy+1<=by2 && !pixMap[rx][ry+1] && !boundaries[rx][ry+1])
            stack_push(stack, stack_data(sx, sy+1));
        if(sx-1>=bx1 && !pixMap[rx-1][ry] && !boundaries[rx-1][ry])
            stack_push(stack, stack_data(sx-1, sy));
        if(sy-1>=by1 && !pixMap[rx][ry-1] && !boundaries[rx][ry-1])
            stack_push(stack, stack_data(sx, sy-1));
    }
    stack_delete(stack);

    for(int i=0; i<X; i++){
        free(pixMap[i]);
    }
    free(pixMap);
}

void seedFillSimple4cBFS(int sx, int sy,
                      const int bx1, const int by1,
                      const int bx2, const int by2,
                      int** boundaries,
                      void (*callback)(int, int)){

    int X = bx2-bx1+1,    // width of the box
        Y = by2-by1+1;    // height of the box

    QueueData pixel;
    // keeps track of pixels visited

    int **pixMap = (int **)malloc(X*sizeof(int*));
    for(int i=0; i<X; i++){
        pixMap[i] = (int *)calloc(Y, sizeof(int));
    }

    // initialize queue
    Queue* queue = queue_init();

    assert(sx>=bx1 && sx<=bx2 && sy>=by1 && sy<=by2);
    // push seed pixel
    queue_enqueue(queue, queue_data(sx-bx1, sy-by1));

    while(!queue_empty(queue)){
        //_printQueue(queue);
        // get a pixel from the stack
        pixel = queue_dequeue(queue);
        sx = (int)pixel.x;      // current seed x coord
        sy = (int)pixel.y;      // current seed y coord
        int rx = sx-bx1,        // relative x coord
            ry = sy-by1;        // relative y coord

        if(!pixMap[rx][ry]){
            pixMap[rx][ry] = 1;
            callback(sx, sy);
        }
        // examine the surrounding pixels to see if they should be placed
        //  onto the stack
        if(sx+1<=bx2 && !pixMap[rx+1][ry] && !boundaries[rx+1][ry])
            queue_enqueue(queue, queue_data(sx+1, sy));
        if(sy+1<=by2 && !pixMap[rx][ry+1] && !boundaries[rx][ry+1])
            queue_enqueue(queue, queue_data(sx, sy+1));
        if(sx-1>=bx1 && !pixMap[rx-1][ry] && !boundaries[rx-1][ry])
            queue_enqueue(queue, queue_data(sx-1, sy));
        if(sy-1>=by1 && !pixMap[rx][ry-1] && !boundaries[rx][ry-1])
            queue_enqueue(queue, queue_data(sx, sy-1));

//        if(sx+1<=bx2 && sy+1<=by2 && !pixMap[rx+1][ry+1] && !boundaries[rx+1][ry+1])
//            queue_enqueue(queue, queue_data(sx+1, sy+1));
//        if(sx-1>=bx1 && sy+1<=by2 && !pixMap[rx-1][ry+1] && !boundaries[rx-1][ry+1])
//            queue_enqueue(queue, queue_data(sx-1, sy+1));
//        if(sx-1>=bx1 && sy-1>=by1 && !pixMap[rx-1][ry-1] && !boundaries[rx-1][ry-1])
//            queue_enqueue(queue, queue_data(sx-1, sy-1));
//        if(sx+1<=bx2 && sy-1>=by1 && !pixMap[rx+1][ry-1] && !boundaries[rx+1][ry-1])
//            queue_enqueue(queue, queue_data(sx+1, sy-1));
    }
    queue_destroy(queue);

    for(int i=0; i<X; i++){
        free(pixMap[i]);
    }
    free(pixMap);
}
