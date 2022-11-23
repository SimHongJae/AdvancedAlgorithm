#ifndef KERNEL_H_
#define KERNEL_H_

#define min(x, y) (x) < (y) ? (x) : (y)

typedef int (*compare_t)(const void *, const void *);

typedef float vec1_t;

typedef struct vec1_pair {
	vec1_t a, b;
} vec1_pair_t;

typedef struct vec2 {
	float x, y;
} vec2_t;

typedef struct vec2_pair {
	vec2_t a, b;
} vec2_pair_t;

typedef struct vec3 {
	float x, y, z;
} vec3_t;

typedef struct vec3_pair {
	vec3_t a, b;
} vec3_pair_t;

vec1_pair_t vec1_daq_conquer(void* arr, int mid, vec1_pair_t p1, vec1_pair_t p2);
vec2_pair_t vec2_daq_conquer(void* arr, int start,int arr_size, vec2_pair_t p1, vec2_pair_t p2);
vec3_pair_t vec3_daq_conquer(void* arr, int start,int arr_size, vec3_pair_t p1, vec3_pair_t p2);

float daq_1d(void *arr, size_t nmemb ,vec1_t* a, vec1_t* b, size_t size);
float daq_2d(void *arr, size_t nmemb ,vec2_t* a, vec2_t* b, size_t size);
float daq_3d(void *arr, size_t nmemb ,vec3_t* a, vec3_t* b, size_t size);

int Vec1Cmp(const void* a, const void* b);
int Vec2Cmp(const void* a, const void* b);
int Vec3Cmp(const void* a, const void* b);

float dist_1d(vec1_t a, vec1_t b);
float dist_2d(vec2_t a, vec2_t b);
float dist_3d(vec3_t a, vec3_t b);

float get_closest_pair_1d_naive(vec1_t* a, vec1_t* b, const vec1_t* points, const int n_points);

float get_closest_pair_2d_naive(vec2_t* a, vec2_t* b, const vec2_t* points, const int n_points);

float get_closest_pair_3d_naive(vec3_t* a, vec3_t* b, const vec3_t* points, const int n_points);

float get_closest_pair_1d_daq(vec1_t* a, vec1_t* b, const vec1_t* points, const int n_points);

float get_closest_pair_2d_daq(vec2_t* a, vec2_t* b, const vec2_t* points, const int n_points);

float get_closest_pair_3d_daq(vec3_t* a, vec3_t* b, const vec3_t* points, const int n_points);

typedef float (*implementation_1d_t)(vec1_t* a, vec1_t* b,
		const vec1_t* points, const int n_points);

typedef float (*implementation_2d_t)(vec2_t* a, vec2_t* b,
		const vec2_t* points, const int n_points);

typedef float (*implementation_3d_t)(vec3_t* a, vec3_t* b,
		const vec3_t* points, const int n_points);

#endif // KERNEL_H_

