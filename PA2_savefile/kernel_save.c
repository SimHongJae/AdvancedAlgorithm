#include <math.h>
#include <float.h>
#include <stdlib.h>
#include "kernel.h"



int compare_numbers(const void* lhs, const void* rhs);
int compare_distances(const void* diff, const void* min);
void vec1_merge_conqure(void* arr, int mid, vec1_t* a1, vec1_t* b1, vec1_t* a2, vec1_t* b2, compare_t compare);
void vec1_merge_divide(void *arr, int start, int arr_size, vec1_t* a, vec1_t* b, compare_t compare);
void merge_sort(void *arr, size_t nmemb, size_t size, compare_t compare);


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




	qsort(points, n_points,sizeof(vec1_t), compare_numbers);
	daq_1d(points, n_points,sizeof(vec1_t), compare_distances,a,b,min_distance);


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

void vec1_merge_conqure(void* arr, int mid, vec1_t* a1, vec1_t* b1, vec1_t* a2, vec1_t* b2, compare_t compare){
	
	vec1_t* arr_vec1 = (vec1_t*) arr;
	vec1_t* a3,b3;
	float dist1,dist2,dist3;

	*a3= arr_vec1[mid-1];
	*b3= arr_vec1[mid];

	dist1= fabs(*a1- *a2);
	dist2= fabs(*a2- *b2);
	dist3= fabs(*a3- *b3);

	/*****
	 * 
	 * 
	 * 
	 * 
	*/
	float min_dist= min(min(dist1,dist2),dist3);

/****
 * 
 * max 비교 하면됨
 * 
*/
/********
 * 
 * 
 * r1, r2, rnew 셋 비교해서
 * 길이 작은 점들을
 * a1,b1에 덮어씌우자
 * 
 * 
 * 
*/



}

void vec1_merge_divide(void *arr, int start, int arr_size, vec1_t* a, vec1_t* b, compare_t compare){
	
	if(arr_size!=1){
		vec1_t* a1, a2;
		vec1_t* b1, b2;
		vec1_merge_divide(arr, start, arr_size/2, &a1, &b1, compare);
		vec1_merge_divide(arr, start+arr_size/2, (arr_size+1)/2, &a2, &b2, compare);
		vec1_merge_conqure(arr, start+arr_size/2, &a1, &b1, &a2, &b2, compare);
		*a=*a1;
		*b=*b1;
	}

	if(arr_size==1){
		vec1_t* arr_vec1 = (vec1_t*) arr;
		*a = arr_vec1[start];
		*b = FLT_MAX;

		/***
		 * 
		 * 고민되는게
		 * a,b에 넘기는 정보를
		 * start점이라고 넘길까 점의 좌표를 넘길까
		 * start점이라고 넘기는게 더 정보가 많을테니 start라고 적는게 오히려 좋을 것 같다는 생각
		 * 최종에는 점의 좌표를 넘겨야하긴함
		 * 
		 * 
		 * 아 근데 start점이라고 넘길 이유가 없음
		 * 왼쪽에서의 최소거리는 여기이며 그 점은 이곳이다
		 * 라고만 알고있음 되는거라
		 * 그냥 좌표 넘기는걸로 하자
		 * 
		 * 
		*/
	}
	
}
void daq_1d(void *arr, size_t nmemb ,vec1_t* a, vec1_t* b, float min_distance, size_t size, compare_t compare){
	vec1_merge_divide(arr, 0,nmemb,a,b, compare);

}
/********
 * 
 * 



 나눌땐 반반반반 하면 되는건디
합치는 과정에서 얻어와야하는 정보가 최소거리, 그 거리를 이루는 두 점

어레이1 시작1 끝1 최소거리1  점11 점12 /// 어레이2 시작2 끝2 최소거리2 점21 점22

어레이1+2 시작1 끝2 최소거리min(1,2,a) 점 점


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