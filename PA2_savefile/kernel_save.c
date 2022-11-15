#include <math.h>
#include <float.h>
#include <stdlib.h>
#include "kernel.h"


int compare_numbers(const void* lhs, const void* rhs);
int compare_distances(const void* diff, const void* min);
void merge_conqure(void* arr, int start, int mid, int end,size_t size,int (*compare)(const void *,const void *));
void merge_divide(void *arr, int start, int arr_size,size_t size,int (*compare)(const void *,const void *));
void merge_sort(void *arr, size_t nmemb, size_t size, int (*compare)(const void *,const void *));


float get_closest_pair_1d_naive(vec1_t* a, vec1_t* b, const vec1_t* points, const int n_points) {
	float min_distance = FLT_MAX;

	for (int i = 0; i < n_points; ++i) {
		for (int j = 0; j < n_points; ++j) {
			if (i == j)
				continue;

			float diff = fabs(points[i] - points[j]);

			if (diff < min_distance) {
				*a = points[i];
				*b = points[j];

				min_distance = diff;
			}
		}
	}

	return min_distance;
}

float get_closest_pair_1d_daq(vec1_t* a, vec1_t* b, const vec1_t* points, const int n_points) {
	float min_distance = FLT_MAX;



	

	qsort(points, n_points,sizeof(float), compare_numbers);
	min_distance= daq_1d((points, n_points,sizeof(vec1_t), compare_distances,min_distance);


	// TODO: Fill this!
	/*
	
	1. 정렬
	2. p[i]-p[i+1] n번 탐색
	-------------------------이렇게 하면 절반정도 점수 줄꺼임 뿌우

	디바이드 컨커로 하셈

	*/

	*a = points[i];
	*b = points[j];
	
	return min_distance;
}

float get_closest_pair_2d_naive(vec2_t* a, vec2_t* b, const vec2_t* points, const int n_points) {
	float min_distance_sq = FLT_MAX;

	for (int i = 0; i < n_points; ++i) {
		for (int j = 0; j < n_points; ++j) {
			if (i == j)
				continue;

			float x_diff = points[i].x - points[j].x;
			float y_diff = points[i].y - points[j].y;

			float diff = x_diff*x_diff + y_diff*y_diff;

			if (diff < min_distance_sq) {
				*a = points[i];
				*b = points[j];
				
				min_distance_sq = diff;
			}
		}
	}
	
	return sqrtf(min_distance_sq);
}

float get_closest_pair_2d_daq(vec2_t* a, vec2_t* b, const vec2_t* points, const int n_points) {
	float min_distance_sq = FLT_MAX;

	// TODO: Fill this!

	/*
	
	1. x에 대해 정렬하고 x기준 divide
	2. y sort후 l.i 에서 1D로 r.min 찾기			이게 꼭 stable 해야할까 qsort쓰면 안되려나 써도 될것 같긴 한데
	3. l.i , l.(i+1) 합칠때 l.1-R.i 이진탐색으로 최소
							l.2-R.i, l.2-R.(i+1) 찾고 R.j = min (R.i, R.(i+1))
							쭉 쭉 쭉
	4. S.l, S.r 합칠 때 일단 그 안에서의 최솟값 r을 구해놓고
		기준점으로부터 x기준 -r ~ r 까지의 점들로만 구성 되어있는 점들 중 y값 당 하나씩만 점들 추출
		그안에서는 nC2
	
	
	*/
	/**********
	 * 
	 * 
	 * 
	 * 
	 * 점의 개수에 비해서 정의역? 그게 너무 넓어서 x기준 어쩌고 y기준하나씩 추출 뭐 그런게 하나도 안먹히게 생겼음
	 * 
	 * 합칠때 아이디어
	 * for( i 1~5){
	 * 	if(i<5.5-r.min)continue;
	 *  for(j 6~10){
	 * 		if(j>5.5+r.min)continue;
	 * 		if( fabs(P[i].x-p[j].x)>r.min)break;
	 * 		if( dist<r.min)r.min=dist;
	 * 	}
	 *
	 * }
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	*/
	
	return sqrtf(min_distance_sq);
}

float get_closest_pair_3d_naive(vec3_t* a, vec3_t* b, const vec3_t* points, const int n_points) {
	float min_distance_sq = FLT_MAX;

	for (int i = 0; i < n_points; ++i) {
		for (int j = 0; j < n_points; ++j) {
			if (i == j)
				continue;

			float x_diff = points[i].x - points[j].x;
			float y_diff = points[i].y - points[j].y;
			float z_diff = points[i].z - points[j].z;

			float diff = x_diff*x_diff + y_diff*y_diff + z_diff*z_diff;

			if (diff < min_distance_sq) {
				*a = points[i];
				*b = points[j];
				
				min_distance_sq = diff;
			}
		}
	}

	return sqrtf(min_distance_sq);
}

float get_closest_pair_3d_daq(vec3_t* a, vec3_t* b, const vec3_t* points, const int n_points) {
	float min_distance_sq = FLT_MAX;

	// TODO: Fill this!
	
	return sqrtf(min_distance_sq);
}

/************
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 

*/


int compare_numbers(const void* lhs, const void* rhs)
{
	int* lhs_int = (int*)lhs;
	int* rhs_int = (int*)rhs;
	if (*lhs_int > *rhs_int)return 1;  //오른이 작으면 1
	if (*lhs_int == *rhs_int)return 0;  //      같으면 0
	if (*lhs_int < *rhs_int)return -1;  //왼쪽이 작으면 -1

}
int compare_distances(const void* diff, const void* min)
{
	int* lhs_int = (int*)diff;
	int* rhs_int = (int*)min;
	if (*lhs_int > *rhs_int)return 1;  //오른이 작으면 1
	if (*lhs_int == *rhs_int)return 0;  //      같으면 0
	if (*lhs_int < *rhs_int)return -1;  //왼쪽이 작으면 -1

}

void merge_conqure(void* arr, int start, int mid, int end,size_t size,int (*compare)(const void *,const void *)){
	int i=0, j=0, k=0;
	int arr_size= end-start;
	
	char* arr_1 = (char*)arr;
	void* new_arr_void = malloc(size * (arr_size+1));
	char* new_arr=(char*)new_arr_void;
	
	while(start+i<mid&&mid+j<end){
		if(compare(arr_1+size*(start+i),arr_1+size*(mid+j))==1){
			memcpy(new_arr+size*k,arr_1+size*(mid+j),size);
			j++;
		}
		else{
			memcpy(new_arr+size*k,arr_1+size*(start+i),size);
			i++;
		}
		k++;
	}
	
	if(mid+j<end){
		memcpy(new_arr+size*k,arr_1+size*(mid+j),size*(arr_size-k));
	}
	
	if(start+i<mid){
		memcpy(new_arr+size*k,arr_1+size*(start+i),size*(arr_size-k));
	}
		
	memcpy(arr_1+size*start,new_arr,size*arr_size);
	
	free(new_arr);
}

void merge_divide(void *arr, int start, int arr_size,size_t size,int (*compare)(const void *,const void *)){
	
	if(arr_size!=1){
		
		merge_divide(arr, start, arr_size/2,size,compare);
		merge_divide(arr, start+arr_size/2,arr_size-arr_size/2,size,compare);
		merge_conqure(arr,start,start+arr_size/2,start+arr_size,size,compare);
	}
	
}
void daq_1d(void *arr, size_t nmemb, size_t size, int (*compare)(const void *,const void *),)
{
	merge_divide(arr, 0,nmemb,size,compare);

}



/****
 * 
 * 잘 모르긴 하지만 points[i].x 를 points+dimension*k+i라 하자
 * 
 * 
 * 
 * .x를 없애는 방법을 찾아야함
 * 
 * 
 *  아 뭔가 굉장히 미안해지는데
 *  하기가 힘들다
 * 뭔얘기를 어떻게 해야할까
 * ㅠ 
*/


/*

qsort( void *base, size_t nel, size_t width, int (*compare)(const void *,const void *));
base: 배열 포인터
nel: 배열 각 원소들의 총 수
width: 배열에서 원소 하나의 크기
(*compare) : 비교를 수행할 함수 포인터


예시 
qsort(arr,array_size,sizeof(int),compare);
>1
<-1
=0 일때 오름차순(1,2,6,14...)

*/