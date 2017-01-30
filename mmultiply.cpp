#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/time.h>
#include <time.h>
#include "counters.h"

void opt_simd_sgemm(float *Y, float *A, float *B, int n);
void opt_scalar1_sgemm(float *Y, float *A, float *B, int n);
void opt_scalar0_sgemm(float *Y, float *A, float *B, int n);
void naive_sgemm(float *Y, float *A, float *B, int n);

int main(int argc, char *argv[])
{
  int n = (1<<10); // 1 << 10 = 2 ^ 10
  float* A = new float[n*n];
  float* B = new float[n*n];
  float* Y = new float[n*n];

// Initializing
struct timeval tv;
struct timeval tv2;

hwCounter_t c;
c.init = false;
initInsns (c);

hwCounter_t c1;
c1.init = false;
initInsns (c1);

gettimeofday(&tv, 0);
uint64_t current_time = getTicks(c1);
uint64_t count = getInsns(c);
naive_sgemm(Y, A, B, n);
uint64_t executed = getInsns(c) - count;
uint64_t elapsed = getTicks(c1) - current_time;
gettimeofday(&tv2, 0);
double time1 = tv.tv_sec + 1e-6 * tv.tv_usec;
double time2 = tv2.tv_sec + 1e-6 * tv2.tv_usec;
printf("Naive Instructions: %lu\n", executed);
printf("IPC               : %lf\n", executed / elapsed);
printf("Naive Time        : %lf\n", time2- time1);
float trash = Y[n*n - 1] + A[n*n - 1] + B[n*n - 1];


// Get current instruction count
gettimeofday(&tv, 0);
current_time = getTicks(c1);
count = getInsns(c);
opt_simd_sgemm(Y, A, B, n);
executed = getInsns(c) - count;
elapsed = getTicks(c1) - current_time;
gettimeofday(&tv2, 0);
time1 = tv.tv_sec + 1e-6 * tv.tv_usec;
time2 = tv2.tv_sec + 1e-6 * tv2.tv_usec;
printf("opt_simd_sgemm: %lu\n", executed);
printf("opt_simd_sgemm Time        : %lf\n", time2 - time1);
printf("IPC               : %lf\n", executed / elapsed);
float trash2 = Y[n*n - 1] + A[n*n - 1] + B[n*n - 1];

// Get current instruction count
gettimeofday(&tv, 0);
current_time = getTicks(c1);
count = getInsns(c);
opt_scalar1_sgemm(Y, A, B, n);
executed = getInsns(c) - count;
elapsed = getTicks(c1) - current_time;
gettimeofday(&tv2, 0);
time1 = tv.tv_sec + 1e-6 * tv.tv_usec;
time2 = tv2.tv_sec + 1e-6 * tv2.tv_usec;
printf("opt_scalar1_sgemm: %lu\n", executed);
printf("opt_scalar1_sgemm Time        : %lf\n", time2 - time1);
printf("IPC               : %lf\n", executed / elapsed);
float trash3 = Y[n*n - 1] + A[n*n - 1] + B[n*n - 1];

// Get current instruction count
gettimeofday(&tv, 0);
current_time = getTicks(c1);
count = getInsns(c);
opt_scalar0_sgemm(Y, A, B, n);
executed = getInsns(c) - count;
elapsed = getTicks(c1) - current_time;
gettimeofday(&tv2, 0);
time1 = tv.tv_sec + 1e-6 * tv.tv_usec;
time2 = tv2.tv_sec + 1e-6 * tv2.tv_usec;
printf("opt_scalar0_sgemm: %lu\n", executed);
printf("opt_scalar0_sgemm Time        : %lf\n", time2 - time1);
printf("IPC               : %lf\n", executed / elapsed);
float trash4 = Y[n*n - 1] + A[n*n - 1] + B[n*n - 1];
printf("%f%f%f%f",trash, trash2, trash3, trash4);

delete [] A;
delete [] B;
delete [] Y;


}