#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"parson.h"

const char *file_path = "calendar_json.json";
const char *empty = "NULL";

void textcolor(int colorNum)                                                                 // 텍스트 색깔 변경
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);  //특정 컬러 이름 입력시 해당 색깔로 출력
}

void xy_out(int x, int y)                                                                    // x , y 좌표에서부터 출력
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

enum f_t{
    N,
    Y,
    error_type = -1
}f_t_type;

char Y_N; // Yes or NO 를 받는 용도


enum Color_Type
{
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
}Color;


JSON_Value *rootValue;
JSON_Object *rootObject;

JSON_Array *schedule_array;
JSON_Object *schedule_json;
JSON_Array *content_array;

JSON_Array *d_day_array;
JSON_Object *d_day_json;

JSON_Array *three_star_array;
JSON_Object *three_star_json;


void json_end()                                                     // json 저장 및 초기화
{
    if (rootValue == NULL) {
        printf("JSON root value is NULL. Cannot save.\n");
        return;
    }

    if (json_serialize_to_file_pretty(rootValue, file_path) != JSONSuccess) {
        printf("Failed to write updated JSON to file.\n");
    } else {

    }

    // 메모리 해제
    json_value_free(rootValue);
    rootValue = NULL; // 포인터 초기화
}

char *switching_int_to_color(int color)                             // int 값을 color 문자로 반환
{
    switch (color) {
        case BLACK: return "BLACK";
        case DARK_BLUE: return "DARK_BLUE";
        case DARK_GREEN: return "DARK_GREEN";
        case DARK_SKYBLUE: return "DARK_SKYBLUE";
        case DARK_RED: return "DARK_RED";
        case DARK_VOILET: return "DARK_VOILET";
        case DAKR_YELLOW: return "DAKR_YELLOW";
        case GRAY: return "GRAY";
        case DARK_GRAY: return "DARK_GRAY";
        case BLUE: return "BLUE";
        case GREEN: return "GREEN";
        case SKYBLUE: return "SKYBLUE";
        case RED: return "RED";
        case VIOLET: return "VIOLET";
        case YELLOW: return "YELLOW";
        case WHITE: return "WHITE";
        default: return "WHITE";    // 디폴트는 화이트
    }
}

int switching_color_to_int(char *name)                              // color 문자를 int 값으로 반환.
{
    if (strcmp(name, "BLACK") == 0) {
        return BLACK;
    } else if (strcmp(name, "DARK_BLUE") == 0) {
        return DARK_BLUE;
    } else if (strcmp(name, "DARK_GREEN") == 0) {
        return DARK_GREEN;
    } else if (strcmp(name, "DARK_SKYBLUE") == 0) {
        return DARK_SKYBLUE;
    } else if (strcmp(name, "DARK_RED") == 0) {
        return DARK_RED;
    } else if (strcmp(name, "DARK_VOILET") == 0) {
        return DARK_VOILET;
    } else if (strcmp(name, "DAKR_YELLOW") == 0) {
        return DAKR_YELLOW;
    } else if (strcmp(name, "GRAY") == 0) {
        return GRAY;
    } else if (strcmp(name, "DARK_GRAY") == 0) {
        return DARK_GRAY;
    } else if (strcmp(name, "BLUE") == 0) {
        return BLUE;
    } else if (strcmp(name, "GREEN") == 0) {
        return GREEN;
    } else if (strcmp(name, "SKYBLUE") == 0) {
        return SKYBLUE;
    } else if (strcmp(name, "RED") == 0) {
        return RED;
    } else if (strcmp(name, "VIOLET") == 0) {
        return VIOLET;
    } else if (strcmp(name, "YELLOW") == 0) {
        return YELLOW;
    } else if (strcmp(name, "WHITE") == 0) {
        return WHITE;
    }

    return WHITE;
}

int  switching_y_n()                                                // Y 는 1 N 은 0 을 출력
{
    switch(Y_N){
        case 'y': return Y;
        case 'n': return N;
    }

    switch(Y_N){
        case 'Y': return Y;
        case 'N': return N;
    }

    return 0;
}

int set_d_day_json()                                                // d_day json 초기화 오류 발생시 error_type 반환
{
        rootValue = json_parse_file(file_path);
    if (rootValue == NULL) {
        printf("Failed to parse JSON file.\n");
        return error_type;
    }

    rootObject = json_value_get_object(rootValue);
    if (rootObject == NULL) {
        printf("Failed to get JSON root object.\n");
        json_value_free(rootValue);
        return error_type;
    }
    d_day_array = json_object_get_array(rootObject, "d_day");
    if (d_day_array == NULL) {
        printf("Failed to get 'd_day' array.\n");
        json_value_free(rootValue);
        return error_type;
    }

    d_day_json = json_array_get_object(d_day_array,0); // d_day 배열 가져오기
}

int set_three_star_schedule_json()                                  //오류 발생 시 error_type 반환
{
    rootValue = json_parse_file(file_path);
    if (rootValue == NULL) {
        printf("Failed to parse JSON file.\n");
        return error_type;
    }

    rootObject = json_value_get_object(rootValue);
    if (rootObject == NULL) {
        printf("Failed to get JSON root object.\n");
        json_value_free(rootValue);
        return error_type;
    }

    // "three_star_array" 배열 가져오기
    three_star_array = json_object_get_array(rootObject, "three_star_array");
    if (three_star_array == NULL) {
        printf("Failed to get 'three_star_array' array.\n");
        json_value_free(rootValue);
        return error_type;
    }

}

int set_schedule_json()                                             //초반 json 초기화 오류 발생시 error_type 반환
{
    rootValue = json_parse_file(file_path);
    if (rootValue == NULL) {
        printf("Failed to parse JSON file.\n");
        return error_type;
    }

    rootObject = json_value_get_object(rootValue);
    if (rootObject == NULL) {
        printf("Failed to get JSON root object.\n");
        json_value_free(rootValue);
        return error_type;
    }

    // "schedule" 배열 가져오기
    schedule_array = json_object_get_array(rootObject, "schedule");
    if (schedule_array == NULL) {
        printf("Failed to get 'schedule' array.\n");
        json_value_free(rootValue);
        return error_type;
    }

    schedule_json = json_array_get_object(schedule_array, 0);
}

int check_d_day_json()                                              // d_day에 일정이 있는지 체크 Y 와 N 로 리턴
{
    if(set_d_day_json() == error_type){
        return error_type;
    }

    d_day_json = json_array_get_object(d_day_array,0);

    int check = (int)json_object_get_number(d_day_json,"check_value");

    if( check == N){
        // printf("d_day 가 비어있습니다.\n");
    return N;
    }
    else if(check == Y)return Y;

}

int what_num(char *date)                                            // 입력받은 date가 몇 번째 배열에 있는지 탐색
{
    for(int i=0; i<json_array_get_count(schedule_array); i++){      // 배열의 첫 번째 요소 가져오기

        schedule_json = json_array_get_object(schedule_array, i);

            if (schedule_json == NULL) {
                printf("Failed to get the [%d] object from 'schedule' array.\n",i);
                json_value_free(rootValue);
                return error_type;
                }
            else if(strcmp(date,json_object_get_string(schedule_json, "date")) == 0){
                return i;
            }
    }
    return error_type;
}

int call_content_count(char *date)                                  // date의 content가 몇 개 있는지 탐색.
{
    set_schedule_json();

    int i = what_num(date);  // 배열 번호 찾기.

    schedule_json = json_array_get_object(schedule_array,i);  // date와 일치하는 배열의 주소 가져옴
    content_array = json_object_get_array(schedule_json,"content"); // content 배열의 위치를 가져옴

    int content_count = json_array_get_count(content_array); // content 수를 출력

    return content_count;
}

int what_index(char *content,int num)                               // 입력받은 content가 배열에서 몇 번째에 있는지 탐색
{
    int content_count = json_array_get_count(content_array);

    for(int i=0; i<content_count; i++){
        if(strcmp(content,json_array_get_string(content_array,i)) == 0){
            return i;
        }
    }

    return error_type;
}

int out_text_color_json(int year,int month,int day)                 // schedule 배열에 있는 text_color 를 인트로 변환한 값 출력
{
    char date[32];
    int color;

    snprintf(date,32,"%d-%02d-%02d",year,month,day);

    set_schedule_json();
    int num = what_num(date);

    schedule_json = json_array_get_object(schedule_array, num);

    strcpy(date,json_object_get_string(schedule_json,"text_color"));

    return switching_color_to_int(date);
}


int check_text_color_json(int year,int month,int day)               // year month day 에 해당하는 색깔이 있을 시 값 반환
{
    char date[32];

    set_schedule_json();

    snprintf(date,32,"%d-%02d-%02d",year,month,day);

    if(what_num(date) == error_type){
        return error_type;
    }
    else{
        return json_object_get_number(schedule_json,"text_color");
    }
}

int check_schedule_json(char *date)                                 // json 파일에 date 가 이미 있는지 확인.
{
    set_schedule_json();

    for(int i=0; i<json_array_get_count(schedule_array); i++){  // year month day 중복이 있는지 확인.
        schedule_json = json_array_get_object(schedule_array, i);

        if (strcmp(date,json_object_get_string(schedule_json, "date")) == 0){ // date 파일이 이미 있다면 return N
              // printf(" \n\n 이미 일정이 있습니다..");
            return N;
        }

    }

    return Y;

}

void call_content(char *date,char *text[5])                         // 모든 일정 가져옴
{
    int num;
    int count;
    set_schedule_json();

    count = call_content_count(date);
    num = what_num(date);

    schedule_json = json_array_get_object(schedule_array,num);
    content_array = json_object_get_array(schedule_json,"content");

    for(int i=5-count; i<5; i++){
        strcpy(text[i],json_array_get_string(content_array,i));
    }

}

void print_content(int num,int x,int y)                             // content 배열 안에 있는 모든 일정 출력
{
    const char *task = (char *)malloc(64 * sizeof(char));


    schedule_json = json_array_get_object(schedule_array, num);

    content_array = json_object_get_array(schedule_json, "content"); // content 배열 주소를 가짐.
    int content_count = json_array_get_count(content_array);

    for (int j = 0; j < content_count; j++) {
        task = json_array_get_string(content_array, j);  // 배열의 각 항목을 가져옴
        xy_out(x,y++);
        printf(" - %s", task);
    }
}

void print_all_schedule_json()                                      // json 파일 전부 출력
{
    set_schedule_json(); // json 파일 초기설정.

    for(int i=0; i<json_array_get_count(schedule_array); i++){      // 배열의 첫 번째 요소 가져오기
        schedule_json = json_array_get_object(schedule_array, i);

            if (schedule_json == NULL) {
                printf("Failed to get the [%d] object from 'schedule' array.\n",i);
                json_value_free(rootValue);
                return;
                }

        printf("날짜: %s\n", json_object_get_string(schedule_json, "date"));
        printf("일정:\n");
        print_content(i,5,5);
        printf("색깔: %s\n", json_object_get_string(schedule_json, "text_color"));
    }

    json_value_free(rootValue);
}

int print_three_star_schedule(char *date)  // date 값을 받고 해당 되는 3개의 중요도 content를 출력
{
    int year,month,day;
    int x,y,num;
    x = 2;
    y = 16;

    sscanf(date, "%d-%d-%d", &year, &month, &day);  // date 문자열을 인트형으로 쪼개기

    if(set_schedule_json() == error_type)return error_type; // json 초기설정.


    if(check_schedule_json(date) == Y){
        // printf(" 해당날짜의 일정이 없습니다.\n");
        return N;
    }
    else{
        xy_out(0,14);
        for(int i=0; i<41; i++){
            printf("-");
        }
        for(int i=15; i<24; i++){
            xy_out(0,i);
            printf("|");
            xy_out(40,i);
            printf("|");
        }
        printf("\n");
        for(int i=0; i<40; i++){
            printf("-");
        }

        num = what_num(date);

        textcolor(out_text_color_json(year,month,day));
        xy_out(x,y++);
        printf(" 날짜 : %s\n", json_object_get_string(schedule_json, "date"));
        xy_out(x,y++);
        printf(" 일정 : ");
        print_content(num,x,y);
        textcolor(WHITE);

        json_end();
        return Y;
    }

    json_end();
    return N;
}

int call_all_three_star_content()        //별 3개 중요도의 일정이 있다면 모두 출력
{
    char *date;

    date = malloc(256);

    if(set_three_star_schedule_json() != error_type){
        return error_type;
    }

    for(int i=0; i<json_array_get_count(three_star_array); i++){  // 첫번째 배열부터 천천히 훑음
        three_star_json = json_array_get_object(three_star_array, i);

        strcpy(date,json_object_get_string(three_star_json,"date")); //배열 복사 후 출력
        printf("%s\n",date);
    }

    json_end();
    free(date);
}

int delete_three_star_schedule(char *date)  // 해당 date와 일치하는 three star shcedule 을 삭제
{
    if(set_three_star_schedule_json() == error_type){
        return error_type;
    }
    for(int i=0; i<5; i++){
        three_star_json = json_array_get_object(three_star_array,i);

        if(strcmp(date,json_object_get_string(three_star_json,"date"))== 0){
            json_array_remove(schedule_array, i);
        }
    }

    json_end();
}

void creat_three_star_schedule(char *date)                         // 중요도가 3개인 content 만 따로 저장
{
    JSON_Value *newScheduleValue;
    JSON_Object *newSchedule;


    rootValue = json_parse_file(file_path);

    if (rootValue == NULL) {
        printf("Failed to parse JSON file. Creating a new one.\n");
        rootValue = json_value_init_object(); // 새 JSON 파일 생성
        rootObject = json_value_get_object(rootValue);
        json_object_set_value(rootObject, "three_star_schedule", json_value_init_array()); // "three_star_schedule" 키에 배열 추가
    } else {
        rootObject = json_value_get_object(rootValue);
    }

    if (rootObject == NULL) {
        printf("Failed to get root object.\n");
        json_value_free(rootValue);
        return;
    }
    if (rootObject == NULL) {
        printf("Failed to get root object.\n");
        json_value_free(rootValue);
        return;
    }

    // "three_star_array" 배열 가져오기
    three_star_array = json_object_get_array(rootObject, "three_star_schedule");
    if (schedule_array == NULL) {
        printf("Failed to get 'three_star_schedule' array.\n");
        json_value_free(rootValue);
        return;
    }

    newScheduleValue = json_value_init_object();  // 새로운 JSON 객체 생성
    newSchedule = json_value_get_object(newScheduleValue);

    json_object_set_string(newSchedule, "date", date);

    json_end();
}

void creat_schedule_json(char *date,char *content,char *text_color) // josn (일정) 파일 추가하기.
{
    JSON_Value *newScheduleValue;
    JSON_Object *newSchedule;

    rootValue = json_parse_file(file_path);

    if (rootValue == NULL) {
        printf("Failed to parse JSON file. Creating a new one.\n");
        rootValue = json_value_init_object(); // 새 JSON 파일 생성
        rootObject = json_value_get_object(rootValue);
        json_object_set_value(rootObject, "schedule", json_value_init_array()); // "schedule" 키에 배열 추가
    } else {
        rootObject = json_value_get_object(rootValue);
    }

    if (rootObject == NULL) {
        printf("Failed to get root object.\n");
        json_value_free(rootValue);
        return;
    }

    // "schedule" 배열 가져오기
    schedule_array = json_object_get_array(rootObject, "schedule");
    if (schedule_array == NULL) {
        printf("Failed to get 'schedule' array.\n");
        json_value_free(rootValue);
        return;
    }


    newScheduleValue = json_value_init_object();  // 새로운 JSON 객체 생성
    newSchedule = json_value_get_object(newScheduleValue);

    json_object_set_string(newSchedule, "date", date);

    JSON_Value *content_array_value = json_value_init_array();  // content 배열을 감쌀 JSON_Value 생성
    content_array = json_value_get_array(content_array_value);  // content_array는 JSON_Array로 변환

    char *task = strtok(content, "-");  // content가 -로 구분

    while (task != NULL) {
        json_array_append_string(content_array, task);  // 배열에 문자열을 추가
        task = strtok(NULL, "-");  // 다음 항목으로 이동
    }

    // 배열을 "content" 키로 설정
    json_object_set_value(newSchedule, "content", content_array_value);  // "content"에 배열을 설정

    json_object_set_string(newSchedule, "text_color", text_color);

    // 배열에 새 객체 추가
    json_array_append_value(schedule_array, newScheduleValue);

    json_end();


}

void print_d_day_json()                                             // d-day 출력
{
    set_d_day_json();
    if(check_d_day_json()==Y){
    xy_out(50,3); printf(" [%s] D - %.0d",json_object_get_string(d_day_json,"name"),(int)json_object_get_number(d_day_json,"date"));
    }
}

void change_d_day_json(char *name,int day)                          // d_day json 파일을 편집/추가하는 기능
{
    set_d_day_json();

    json_object_set_number(d_day_json, "check_value", 1);
    json_object_set_string(d_day_json, "name", name);
    json_object_set_number(d_day_json, "date", day);

    if (json_serialize_to_file_pretty(rootValue, file_path) != JSONSuccess) {
        printf("Failed to write JSON file.\n");
        json_value_free(rootValue);
        return;
    }

    json_end();

}

void delete_d_day_json()                                            // d_day json 을 삭제.
{
    if (set_d_day_json() == error_type) {
        printf("Failed to initialize d_day JSON.\n");
        return;
    }

    if(check_d_day_json() == N){
        printf(" d_day 설정이 안되어있습니다.");
    }
    else{
        json_object_set_number(d_day_json, "check_value", 0);
        json_object_set_string(d_day_json, "name", empty);
        json_object_set_number(d_day_json, "date", 0);
    }
    json_end();
}

int delete_schedule_json(int num)                                   // num 의 schedule date를 삭제
{
    set_schedule_json();

    schedule_json = json_array_get_object(schedule_array, num);

    if(schedule_json == NULL){
        return N;
    }

    json_array_remove(schedule_array, num);

    json_end();
}

int print_select_schedule_json(int year,int month,int day)          // 해당 날짜의 일정 출력,
{
    char date[32];
    int x,y,num;
    x = 2;
    y = 16;

    snprintf(date,32,"%d-%02d-%02d",year,month,day);

    if(set_schedule_json() == error_type)return error_type; // json 초기설정.

    if(check_schedule_json(date) == Y){
        // printf(" 해당날짜의 일정이 없습니다.\n");
        return N;
    }
    else{
        xy_out(0,14);
        for(int i=0; i<41; i++){
            printf("-");
        }
        for(int i=15; i<24; i++){
            xy_out(0,i);
            printf("|");
            xy_out(40,i);
            printf("|");
        }
        printf("\n");
        for(int i=0; i<40; i++){
            printf("-");
        }

        num = what_num(date);

        textcolor(out_text_color_json(year,month,day));
        xy_out(x,y++);
        printf(" 날짜 : %s\n", json_object_get_string(schedule_json, "date"));
        xy_out(x,y++);
        printf(" 일정 : ");
        print_content(num,x,y);
        textcolor(WHITE);

        json_end();
        return Y;
    }

    json_end();
    return N;
}

int check_content_json()                                            // content 가 5개 초과인지 확인
{
    content_array = json_object_get_array(schedule_json,"content");

    if(json_array_get_count(content_array) > 5){
        return N;
    }
    else{
        return Y;
    }
}

int plus_content_json(char *date,char *content)                     // content 배열 추가 .
{
    if(set_schedule_json() == error_type){
        return error_type;
    }

    int num = what_num(date);
    char *task = strtok(content, "-");  // content가 -로 구분

    schedule_json = json_array_get_object(schedule_array,num);
    content_array = json_object_get_array(schedule_json,"content");

    if(num == error_type){
        return error_type;
    }
    else{
        while (task != NULL) {
            json_array_append_string(content_array, task);  // 배열에 문자열을 추가
            task = strtok(NULL, "-");  // 다음 항목으로 이동
        }
    }
    json_end();
}

int delete_content_json(char *date,char *content)                   // content 삭제
{
    if(set_schedule_json() == error_type){
        return error_type;
    }

    int num = what_num(date);

    if(num == error_type){
        return error_type;
    }
    else{
        schedule_json = json_array_get_object(schedule_array, num);
        content_array = json_object_get_array(schedule_json,"content");
        int index = what_index(content,num);

        json_array_remove(content_array, index);
    }
    json_end();
}

void scan_schedule_inforamtion(char *date,char *content,char *text_color)  //schdule json 파일에 들어갈 정보 입력
{
    if(set_schedule_json() == error_type)return;

    if( check_schedule_json(date) == N)
    {
        printf(" 이미 일정이 있습니다\n");
    }

    if(check_schedule_json(date) == Y){
        creat_schedule_json(date,content,text_color);
    }
    return;
}

void rebuliding_three_star_schedule(char *date,int num)             // three star shcedule 안에 있는 date를 순서대로 정렬.
{
    const int size = json_array_get_count(three_star_array);

    char *swap[size];
    for(int i=0; i<size; i++){
        three_star_json = json_array_get_object(three_star_array,i);
        swap[i] = malloc(32);
        strcpy(swap[i],json_object_get_string(three_star_json,"date")); //JSON 파일에 있는 date 가져오기
        delete_three_star_schedule(swap[i]);  // json 파일 비우기
    }

    if(size == 5){  // date 배열에 5개 찼다면 date 하나를 지우고 새로 받은 date 값 할당
        memset(swap[0],0,256); // 0번째 자리 비우기

        for(int i=0; i<4; i++){
            if(i == num){
                strcpy(swap[i],date);  // 해당하는 자리에 입력받은 date 값 넣기.
            }
            else{
                strcpy(swap[i],swap[i+1]); // 문자열을 한 칸씩 땡김.
                memset(swap[i+1],0,32);  // 한 칸 이동 후 초기화.
            }
        }
    }
    else{
        for(int i=size; i>num; i--){ // date 가 들어가야 할 위치를 비워두고 한 칸 밀어버림.
            memset(swap[5],0,32);
            strcpy(swap[i+1],swap[i]);
            memset(swap[i],0,32);
        }
        strcpy(swap[num],date);
    }


    for(int i=0; i<5; i++){
        creat_three_star_schedule(swap[i]);  // 리빌딩한 배열 다시 json 파일에 저장
    }

}
