#ifndef _INTRPL_H
#define _INTRPL_H
#include "stddef.h"
#include "stdbool.h"

/* 
    1. #define the number of points of your dataset
        #define N_POINTS 64
    2. create 2 float arrays x[N_POINTS], y[N_POINTS] filled with your dataset
    3. create 1 float array for cache: cache[(N_POINTS-1)*2]
    4. create 1 bool (uint8_t) array for cache: bcache[N_POINTS-1]
    5. create interp_t variable: interp_t interp;
    6. initialize interp_t interp with interp_init(...):
        interp_init(interp,
                    x,
                    y,
                    cache,
                    bcache,
                    n_points)
    7. calculate wanted y(x) with interp_calc(interp_t *obj, float x, float *y_calc):
        interp_calc(interp, x, &y_calc);    // calculated value will be stored in y_calc
    8. ???
    9. feel free to rewrite the code if needed

*/

typedef struct interp_t {
    float   *x;         /*!< ptr to an array of x values
                             size = [number of points] */

    float   *y;         /*!< ptr to an array of y values
                             size = [number of points] */

    size_t   n_points;  /*!< used to store the number of points
                             size = [number of points] */

    float   *cache;     /*!< ptr to an array of float
                             used to store already calculated data
                             size = [(number of points - 1) * 2]      */

    bool    *got_cache; /*!< ptr to an array of bool (uint8_t)
                             to remember if cache is present for the point
                             size = [number of points - 1]          */
}interp_t;


void interp_init(interp_t *obj, float x_ds[], float y_ds[], float cache[], bool cache_ctl[], size_t n_points);
void interp_calc(interp_t *obj, float x, float *y_calc);

#endif