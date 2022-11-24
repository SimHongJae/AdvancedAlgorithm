#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NGRP 99

typedef struct element {
    int index;
    int value;
    int groupId[MAX_NGRP];
    /*
    groupId: 
        만약 주어진 input을 4개의 서로 다른 파티션 방법으로 파티셔닝 할 수 있다고 하자. (unique solution이 아니라는 말)    
        이 경우 각각의 솔루션에서의 해당 element가 속하는 partition이 groupId이다. 예컨대,
        1번 partition 방법에서의 element x의 group은 groupId[0]에 저장될 것이고, 
        2번 partition 방법에서의 element x의 group은 groupId[1]에 저장될 것이다, 
    */
} element;

void sort_elements(element *elements, int start, int end);

int partition_by_greedy(element* elements, int nmemb);
int partition_by_dp(element* elements, int nmemb);