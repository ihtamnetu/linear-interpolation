#include "interpol.h"
#include "stdint.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

static void interp_search_closest(float x_ds[], size_t n_points, float x, uint32_t *x1_ret, uint32_t *x2_ret);
static void interp_bsearch_closest(float x_ds[], size_t n_points, float x, uint32_t *x1_ret, uint32_t *x2_ret);
static void interp_linear_eval(float *y, float *x, float *k, float *b);
static bool interp_cache_check(interp_t *obj, uint32_t index);
static void interp_cache_write(interp_t *obj, uint32_t line_id, float *k, float *b);
static void interp_cache_read(interp_t *obj, uint32_t line_id, float *k, float* b);

void interp_calc(interp_t *obj, float x, float *y_calc) {
    uint32_t x1_id = 0, x2_id = 0, line_id = 0;
    float k, b;
    interp_bsearch_closest(obj->x, obj->n_points, x, &x1_id, &x2_id);
    line_id = x1_id;
    
    if (interp_cache_check(obj, line_id)) {
        interp_cache_read(obj, line_id, &k, &b);
    }
    else {
        k = (obj->y[x2_id] - obj->y[x1_id]) / (obj->x[x2_id] - obj->x[x1_id]);
        b = obj->y[x1_id] - k * obj->x[x1_id];
        interp_cache_write(obj, line_id, &k, &b);
    }
    interp_linear_eval(y_calc, &x, &k, &b);
}

static void interp_linear_eval(float *y, float *x, float *k, float *b) {
    *y = *k * *x + *b;
}

void interp_init(interp_t *obj, float x_ds[], float y_ds[], float cache[], bool cache_ctl[], size_t n_points) {
   obj->x = x_ds;
   obj->y = y_ds;
   obj->got_cache = cache_ctl;
   obj->cache = cache;
   obj->n_points = n_points;
 
   memset(cache_ctl, 0, n_points);
   memset(cache, 0, n_points);
}

__attribute__((unused)) static void interp_search_closest(float x_ds[], size_t n_points, float x, uint32_t *x1_ret, uint32_t *x2_ret) {
    uint32_t left = 0;
    uint32_t right = n_points-1;
    float abs_l;
    float abs_r;

    while(right - left > 1) {
        abs_l = fabsf(x_ds[left] - x);
        abs_r = fabsf(x_ds[right] - x);

        if(abs_l > abs_r) {
            left++;
        }
        else {
            right--;
        }
    }
    *x1_ret = left;
    *x2_ret = right; 
}
static void interp_bsearch_closest(float x_ds[], size_t n_points, float x, uint32_t *x1_ret, uint32_t *x2_ret) {
  size_t left = 0;
  size_t right = n_points-1;
  while(right > left + 1) {
    size_t i = (right + left)/2;
    if(x_ds[i] > x)
      right = i;
    else
      left = i;
  }
    *x1_ret = left;
    *x2_ret = right; 
}

static bool interp_cache_check(interp_t *obj, uint32_t index) {
    return (obj->got_cache[index]);
}

static void interp_cache_write(interp_t *obj, uint32_t line_id, float *k, float *b) {
   uint32_t k_id = line_id*2;
   uint32_t b_id = line_id*2+1;
   obj->cache[k_id] = *k;
   obj->cache[b_id] = *b;
   obj->got_cache[line_id] = 1;
}

static void interp_cache_read(interp_t *obj, uint32_t line_id, float *k, float* b) {
    uint32_t k_id = line_id*2;
    uint32_t b_id = line_id*2+1;
    *k = obj->cache[k_id];
    *b = obj->cache[b_id];
}
