#define LIPO_DS_POINTS 12

typedef struct point_t {
    float *U;
    float *soc;
}point_t;

float lipo_U[LIPO_DS_POINTS] = {                     
    3,
    3.4561,
    3.5309,
    3.5836,
    3.6077,
    3.6356,
    3.6878,
    3.7778,
    3.8614,
    3.9537,
    4.0565,
    4.2
};

float lipo_soc[LIPO_DS_POINTS] = {
    0,
    9.72,
    18.75,
    27.78,
    36.81,
    45.84,
    54.86,
    63.89,
    72.92,
    81.95,
    90.97,
    100
};

point_t lipo_ds_points = {.U = lipo_U, .soc = lipo_soc};