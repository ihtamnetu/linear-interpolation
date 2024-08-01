# linear-interpolation
static (no heap) linear interpolation for personal usage

  1. #define the number of points of your dataset
        #define N_POINTS 64
        
 ![image](https://github.com/user-attachments/assets/0d17c237-dbf8-4e93-bfda-669d92d1feea)

  2. create 2 float arrays x[N_POINTS], y[N_POINTS] filled with your dataset
     
![image](https://github.com/user-attachments/assets/c85edfbb-d7d3-4068-ac6e-dfcd9ff38604)

  3. create 1 float array for cache: cache[(N_POINTS-1)*2]
  4. create 1 bool (uint8_t) array for cache: bcache[N_POINTS-1]
     
![image](https://github.com/user-attachments/assets/6455dcb5-564c-45cb-9d32-df6948082bb0)


  5. create interp_t variable: interp_t interp;

![image](https://github.com/user-attachments/assets/648b7990-2a73-4d8d-b5bc-786b2b197945)

  6. initialize interp_t interp with interp_init(...):
        interp_init(interp,
                    x,
                    y,
                    cache,
                    bcache,
                    n_points)
      
![image](https://github.com/user-attachments/assets/f437b08c-b214-4ae9-8f3b-6bc1657c5020)

  7. calculate wanted y(x) with interp_calc(interp_t *obj, float x, float *y_calc):
        interp_calc(interp, x, &y_calc);    // calculated value will be stored in y_calc
      
![image](https://github.com/user-attachments/assets/7222d953-cb70-442a-8dd5-0cf63dfc2369)

  8. ???
  9. feel free to rewrite the code if needed
