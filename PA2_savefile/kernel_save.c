#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include "kernel.h"


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
	float min_distance= FLT_MAX;;
		
	qsort(points, n_points,sizeof(vec1_t), Vec1Cmp);
	min_distance = daq_1d(points, n_points, a, b, sizeof(vec1_t));

	return min_distance;
	
	/*
	
	1. 정렬
	2. p[i]-p[i+1] n번 탐색
	-------------------------이렇게 하면 절반정도 점수 줄꺼임 뿌우

	디바이드 컨커로 하셈

	*/
	
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
	
	qsort(points, n_points,sizeof(vec2_t), Vec2Cmp);
	min_distance_sq = daq_2d(points, n_points, a, b, sizeof(vec2_t));

	return sqrtf(min_distance_sq);


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
	*/
	
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
	
	qsort(points, n_points,sizeof(vec3_t), Vec3Cmp);
	min_distance_sq = daq_3d(points, n_points, a, b, sizeof(vec3_t));

	return sqrtf(min_distance_sq);
}


int Vec1Cmp(const void* a, const void* b)
{
   float det = *(vec1_t*)a > *(vec1_t*)b;

   if (det < 0.0)
       return -1;
   else if (det > 0.0)
       return 1;
   else
       return 0;

	   /*********
		* 여기부분은 int로 반환해야하는거엿음!
	   **********/
}

int Vec2Cmp(const void* a, const void* b)
{
	vec2_t *aa= (vec2_t*)a;
	vec2_t *bb= (vec2_t*)b;
   float det = (*aa).x > (*bb).x;

   if (det < 0.0)
       return -1;
   else if (det > 0.0)
       return 1;
   else
       return 0;

	 
}

int Vec2CmpY(const void* a, const void* b)
{
	vec2_t *aa= (vec2_t*)a;
	vec2_t *bb= (vec2_t*)b;
   float det = (*aa).y > (*bb).y;

   if (det < 0.0)
       return -1;
   else if (det > 0.0)
       return 1;
   else
       return 0;

	 
}

int Vec3Cmp(const void* a, const void* b)
{
	vec3_t *aaa= (vec3_t*)a;
	vec3_t *bbb= (vec3_t*)b;
   float det = (*aaa).x > (*bbb).x;

   if (det < 0.0)
       return -1;
   else if (det > 0.0)
       return 1;
   else
       return 0;

	 
}

float dist_1d(vec1_t a, vec1_t b){
	return fabs(a- b);
}

float dist_2d(vec2_t a, vec2_t b){
	return (float)sqrtf((float)(a.x- b.x)*(a.x- b.x)+(a.y- b.y)*(a.y- b.y));
}

float dist_3d(vec3_t a, vec3_t b){
	return (float)sqrtf((float)(a.x- b.x)*(a.x- b.x)+(a.y- b.y)*(a.y- b.y)+(a.z-b.z)*(a.z-b.z));
}


vec1_pair_t vec1_daq_conquer(void* arr, int mid, vec1_pair_t p1, vec1_pair_t p2){
	
	vec1_t* arr_vec1 = (vec1_t*) arr;
	vec1_pair_t min_p,p3;
	float dist1, dist2, dist3;

	p3.a= arr_vec1[mid-1];
	p3.b= arr_vec1[mid];
		
	dist1= dist_1d(p1.a,p1.b);
	dist2= dist_1d(p2.a,p2.b);
	dist3= dist_1d(p3.a,p3.b);


	float min_dist= min(min(dist1,dist2),dist3);
	if(min_dist==dist1){
		min_p=p1;
	}
	if(min_dist==dist2){
		min_p=p2;
	}
	if(min_dist==dist3){
		min_p=p3;
	}

	return min_p;

}

vec1_pair_t vec1_daq_divide(void *arr, int start, int arr_size){
	
	
	vec1_pair_t p;
	if(arr_size!=1){
		vec1_pair_t p1, p2;
		
		p1 = vec1_daq_divide(arr, start, arr_size/2);
		p2 = vec1_daq_divide(arr, start+arr_size/2, (arr_size+1)/2);
		p = vec1_daq_conquer(arr, start+arr_size/2, p1, p2);

		return p;

	}

	if(arr_size==1){
		vec1_t* arr_vec1 = (vec1_t*) arr;
		p.a = arr_vec1[start];
		p.b = FLT_MAX;
		
		return p;
		
	}
	
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
		 * a,b좌표를 계속 파라미터로 넘겨주니깐 segfault발생
		 * 리턴을 여러개 받는 방법이 뭐가 있을까 찾아보니 a,b를 구조체로 묶어서 사용하면 되는거였음!
		 * 룰루~~
		 * 
		 * 
		*/

}

float daq_1d(void *arr, size_t nmemb ,vec1_t* a, vec1_t* b, size_t size){
	vec1_pair_t p;
	p=vec1_daq_divide(arr, 0,nmemb);
	*a=p.a;
	*b=p.b;

	return fabs(*a - *b);

}

//-----------------------------------------2d

vec2_pair_t vec2_daq_conquer(void* arr, int start,int arr_size, vec2_pair_t p1, vec2_pair_t p2){
	
	vec2_t* arr_vec2 = (vec2_t*) arr;
	vec2_pair_t min_p, p3;
	float dist1_sq, dist2_sq, dist3_sq;
	float min_dist, dist1, dist2, dist3;

	if(p1.b.x==FLT_MAX && p2.b.x == FLT_MAX ){
		min_dist= FLT_MAX;
	}
	else{

		dist1=dist_2d(p1.a,p1.b);	
		dist2=dist_2d(p2.a,p2.b);

		min_dist= min(dist1,dist2);

		if(min_dist==dist1){
			min_p=p1;
		}
		if(min_dist==dist2){
			min_p=p2;
		}
	}


/*
	int left_start_in_d,right_end_in_d;
	int copy_arr_size=0;
	vec2_t copy_arr_vec2[arr_size];

	for(int i=(start + arr_size/2 - 1); i>=start; i--,copy_arr_size++){

		copy_arr_vec2[copy_arr_size]=arr_vec2[i];
		if(arr_vec2[i].x<arr_vec2[start+arr_size/2].x-min_dist){
			break;
		}
	}
	
	for(int j=start+arr_size/2;j<start+arr_size;j++,copy_arr_size++){
		
		copy_arr_vec2[copy_arr_size]=arr_vec2[j];
		if(arr_vec2[j].x>arr_vec2[start+arr_size/2 - 1].x+min_dist){
			break;
		}

	}
	

	qsort(copy_arr_vec2,copy_arr_size,sizeof(vec2_t),Vec2CmpY);

	

	for(int i=0;i<copy_arr_size;i++){
		for(int j=i+1;j<copy_arr_size;j++){
			if((copy_arr_vec2[j].y - copy_arr_vec2[i].y)>min_dist){
				break;
			}

			p3.a= copy_arr_vec2[i];
			p3.b= copy_arr_vec2[j];

			dist3= dist_2d(p3.a,p3.b);
				
			if(min_dist > dist3){
				min_dist = dist3;
				min_p=p3;
			}	
		}
	}
	
*/


	for(int i=(start + arr_size/2 - 1); i>=start; i--){

		if(arr_vec2[i].x<arr_vec2[start+arr_size/2].x-min_dist)
		break;

		for(int j=start+arr_size/2;j<start+arr_size;j++){
				
			if(arr_vec2[j].x>arr_vec2[start+arr_size/2 - 1].x+min_dist)break;

			p3.a= arr_vec2[i];
			p3.b= arr_vec2[j];

			dist3= dist_2d(p3.a,p3.b);
				
			if(min_dist > dist3){
				min_dist = dist3;
				min_p=p3;
			}

		}
	}



	return min_p;

}

vec2_pair_t vec2_daq_divide(void *arr, int start, int arr_size){
	
	vec2_pair_t p;
	if(arr_size!=1){

		vec2_pair_t p1, p2;
		
		p1 = vec2_daq_divide(arr, start, arr_size/2);
		p2 = vec2_daq_divide(arr, start+arr_size/2, (arr_size+1)/2);
		p = vec2_daq_conquer(arr, start,arr_size, p1, p2);

		return p;	
	}

	if(arr_size==1){

		vec2_t* arr_vec2 = (vec2_t*) arr;
		p.a = arr_vec2[start];
		p.b.x = FLT_MAX;
		p.b.y = FLT_MAX;
		
		return p;	
	}

}

float daq_2d(void *arr, size_t nmemb ,vec2_t* a, vec2_t* b, size_t size){
	vec2_pair_t p;
	p=vec2_daq_divide(arr, 0,nmemb);
	*a=p.a;
	*b=p.b;

	float dist_sq= dist_2d(*a,*b)*dist_2d(*a,*b);
	
	return dist_sq;

}

//--------------------------------------3d

vec3_pair_t vec3_daq_conquer(void* arr, int start,int arr_size, vec3_pair_t p1, vec3_pair_t p2){
	
	vec3_t* arr_vec3 = (vec3_t*) arr;
	vec3_pair_t min_p, p3;
	float dist1_sq, dist2_sq, dist3_sq;
	float min_dist, dist1, dist2, dist3;

	if(p1.b.x==FLT_MAX && p2.b.x == FLT_MAX ){
		min_dist= FLT_MAX;
	}

	else{
		
		dist1=dist_3d(p1.a,p1.b);
		dist2=dist_3d(p2.a,p2.b);

		min_dist= min(dist1,dist2);

		if(min_dist==dist1){
			min_p=p1;
		}
		if(min_dist==dist2){
			min_p=p2;
		}
	}


	for(int i=(start + arr_size/2 - 1); i>=start; i--){

		if(arr_vec3[i].x<arr_vec3[start+arr_size/2].x-min_dist)break;

		for(int j=start+arr_size/2;j<start+arr_size;j++){
				
			if(arr_vec3[j].x>arr_vec3[start+arr_size/2 - 1].x+min_dist)break;

			p3.a= arr_vec3[i];
			p3.b= arr_vec3[j];

			dist3= dist_3d(p3.a,p3.b);
				
			if(min_dist > dist3){
				min_dist = dist3;
				min_p=p3;
			}

		}
	}
	
	return min_p;
}

vec3_pair_t vec3_daq_divide(void *arr, int start, int arr_size){
	
	vec3_pair_t p;
	if(arr_size!=1){
		vec3_pair_t p1, p2;
		
		p1 = vec3_daq_divide(arr, start, arr_size/2);
		p2 = vec3_daq_divide(arr, start+arr_size/2, (arr_size+1)/2);
		p = vec3_daq_conquer(arr, start,arr_size, p1, p2);

		return p;
		
	}

	if(arr_size==1){
		vec3_t* arr_vec3 = (vec3_t*) arr;
		p.a = arr_vec3[start];
		p.b.x = FLT_MAX;
		p.b.y = FLT_MAX;
		p.b.z = FLT_MAX;

		return p;
		
	}
}

float daq_3d(void *arr, size_t nmemb ,vec3_t* a, vec3_t* b, size_t size){
	vec3_pair_t p;
	p=vec3_daq_divide(arr, 0,nmemb);
	*a=p.a;
	*b=p.b;

	float dist_sq= dist_3d(*a,*b)*dist_3d(*a,*b);
	
	return dist_sq;

}