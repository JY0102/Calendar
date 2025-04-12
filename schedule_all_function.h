#include "all_function.h"


enum direction_ascii_type
{
    ctrl_a =1,          // - 1달
    ctrl_d = 4,         // + 1달
    ctrl_w = 23,        // - 1년
    ctrl_s = 19,        // + 1년


    a = 97,             // - 1일
    d = 100,            // + 1일
    w = 119,            // - 1주일
    s = 115,            // + 1주일.
}ascii;



void plus_year(int *year,int *month,int *day)
{
    (*year) ++;
}
void plus_month(int *year,int *month,int *day)
{
    if(*month == 12){ // 12월에서 +1월이라면 오버플로우 발생
        *month = 1;
        (*year) ++;
    }
    else{
        (*month) ++;
    }
}
void plus_day(int *year,int *month,int *day)
{
    if(*day == last_day_calculation(*year,*month)){ // 마지막날 일수라면 오버플로우 발생
        *day =1;
        plus_month(year,month,day);
    }
    else{
        (*day)++;
    }
}
void plus_week(int *year,int *month,int *day)
{

    if(*day +7 > last_day_calculation(*year,*month)){  // 7일 더했을 때 오버플로우가 발생했다면
        *day = *day + 7 -last_day_calculation(*year,*month);
        plus_month(year,month,day);
    }
    else{
        *day += 7;
    }
}
void minus_year(int *year,int *month,int *day)
{
    if(*year == 1){
        xy_out(50,12);printf(" 오류 발생 ");
    }
    else{
        (*year) --;
    }
}
void minus_month(int *year,int *month,int *day)
{
    if(*month == 1){        //언더플로우
        *month = 12;
        (*year) --;
    }
    else{
        (*month) --;
    }
}
void minus_day(int *year,int *month,int *day)
{
    if(*day==1){
        minus_month(year,month,day);
        *day= last_day_calculation(*year,*month);
    }
    else{
        (*day) -=1;
    }
}
void minus_week(int *year,int *month,int *day)
{
    if(*day <= 7){
        minus_month(year,month,day);
        *day= last_day_calculation(*year,*month) + *day - 7;
    }
    else{
        *day -= 7;
    }
}
void plus_minus_ymd(int *year,int *month,int *day,char check)
{

    switch(check){
        case ctrl_a: minus_month(year,month,day);break;
        case ctrl_d: plus_month(year,month,day);break;
        case ctrl_w: minus_year(year,month,day);break;
        case ctrl_s: plus_year(year,month,day);break;
        case a: minus_day(year,month,day); break;
        case d: plus_day(year,month,day);break;
        case w: minus_week(year,month,day);break;
        case s: plus_week(year,month,day);break;
        case 'A': minus_day(year,month,day); break;
        case 'D': plus_day(year,month,day);break;
        case 'W': minus_week(year,month,day);break;
        case 'S': plus_week(year,month,day);break;
    }
}

void rebuilding_star(char *date,char *text[5])   // 중요도 순서대로 text 배열을 정렬
{
    char *star[4] = {"","*","**","***"};
    char *sequence[5];
    int  count = call_content_count(date);

    int num =0;

    int check_three_star;

    call_content(date,text); // json 파일 안에 있는 content를 불러옴.

    for(int i=0; i<5; i++){
        sequence[i] = malloc(256);
        strcpy(sequence[i],text[i]);  // content 들을 sequence 에 배열에 이동함.
        memset(text[i],0,256); // 배열 초기화
    }


    for(int i=3; i>=0; i--){
        for(int j=0; j<5 - count; j++){
            if(strcmp(sequence[j],"") == 0 ){ // 문자열이 비어있을 때는 아무것도 하지 않기.

            }
            else if(i == 0){ // sequnce 가 비어있지 않고 중요도 content 가 다 끝났으면 나머지 옮기기.
               strcpy(text[num++],sequence[j]);
            }
            else if(strncmp(sequence[j],star[i],i) == 0){  // 별 3개부터 중요도 확인
                strcpy(text[num++],sequence[j]);
                memset(sequence[j],0,256);
                    if(i == 3){
                        check_three_start_schedule(date); // 만약에 중요도 3개의 content가 추가가 됐다면 three_star_schedule_json 배열을 생성
                    }
            }
        }
    }
    for(int i=0; i<5; i++){free(sequence[i]);} // 메모리 해제
}

int check_direction(char check)                                                             //달력 방향키를 맞게 설정했는지 확인 해주는 기능
{
    if(check == a - 32)check=a;     // 대문자 , 소문자 인지 확인.
    if(check == d - 32)check=d;
    if(check == w - 32)check=w;
    if(check == s - 32)check=s;

    switch(check){
        case ctrl_a: return Y;
        case ctrl_d: return Y;
        case ctrl_w: return Y;
        case ctrl_s: return Y;
        case a: return Y;
        case d: return Y;
        case w: return Y;
        case s: return Y;
    }

    return N;
}

int pass_to_json(char *date,char *content,char *text_color,int check_value)                 // json에 저장장
{
    if(check_value == Y){ // schedule을 추가하는 목적이라면
        plus_content_json(date,content);
    }
    else{
        creat_schedule_json(date,content,text_color);
    }
}

void show_color()                                                                           // 어떤 한 색을 사용할 건지 출력력
{
    char *color_names[] = {
            "BLACK",
            "DARK_BLUE",
            "DARK_GREEN",
            "DARK_SKYBLUE",
            "DARK_RED",
            "DARK_VOILET",
            "DAKR_YELLOW",
            "GRAY",
            "DARK_GRAY",
            "BLUE",
            "GREEN",
            "SKYBLUE",
            "RED",
            "VIOLET",
            "YELLOW",
            "WHITE",
        };

    xy_out(0,11);
    for(int i=0; i<35; i++){
        printf("-");
    }
    for(int i=12; i<30; i++){
        xy_out(0,i);
        printf("|");
        xy_out(35,i);
        printf("|");
    }
    printf("\n");
    for(int i=0; i<35; i++){
        printf("-");
    }

    for(int i=0; i<15; i++){
        printf("");
    }
    int i=11;
    for(int color_type=BLACK; color_type <= WHITE; color_type++){
        xy_out(2,i++);
        textcolor(color_type);
        printf("[%d] - %s",color_type,color_names[color_type]);
    }
    textcolor(WHITE);
}

int get_content(char *date,int check_value,int num_y)                                       // 해당 date에 일정과 text_color 를 입력받고 json 에 저장
{
    int a;
    int i;

    char check;
    char *text_color = malloc(32);
    char *content = malloc(1290);
    char *text[5];
    for (int j = 0; j < 5; j++) {
        text[j] = malloc(256); // 각 포인터에 256바이트 할당
        memset(text[j],0,256); // 포인터 초기화
    }

    if(check_value == Y){  // 만약 데이터일정이 있는데 추가하는 거라면.
        int content_count = call_content_count(date); // 해당 date에 content가 몇 개 있는지 값 반환환

        if( (5 - content_count) == 0){  // 만약 content에 일정이 5개라면 N 값 리턴
            return N;
        }

        xy_out(50,num_y); printf(" 일정을 써 주세요.(최대%d개)",(5-content_count));num_y++;
        xy_out(50,num_y); printf(" 더 이상 추가하지 않을려면 N입력.");num_y += 2;

        for(int j=0; j<5 - content_count; j++ ){ // 5개 이하라면 최대 갯수 출력 및 일정 입력 받기
            xy_out(50,num_y); printf(" 입력:");   num_y++;
            fflush(stdin); // 버퍼비우기
            scanf("%255s",text[j]); // 일정 받기
            if(strcmp(text[j],"N")==0){
                memset(text[j],0,256); //비우기
                break;
            }
        }
    }
    else{ // content가 있는 date가 아니라면
        xy_out(50,num_y); printf(" 일정을 써 주세요.(최대5개)");    num_y++;
        xy_out(50,num_y++); printf(" 더 이상 추가하지 않을려면 N입력.");  num_y++;

        i = 0;
        while(i < 5){
            xy_out(50,num_y); printf(" 입력:");num_y++;
            fflush(stdin); // 버퍼비우기
            scanf("%255s",text[i]); // 일정 받기
            if(strcmp(text[i],"N")==0){
                memset(text[i],0,256); //비우기기
                break;
            }
            i++;
        }
        num_y += 2;
        xy_out(50,num_y); printf("일정 표시할 색깔을 선택해주세요");num_y++;
        show_color();
        xy_out(50,num_y); printf(" 입력:");num_y++;
        scanf("%d",&a);
        strcpy(text_color,switching_int_to_color(a)); // 색깔 값 int 형에서 문자열로 변환
    }
    rebuilding_star(date,text);  // 별 세개부터 해서 text[0] 에서 text[4]까지 순서대로 배열에 저장
    snprintf(content,1290,"%s-%s-%s-%s-%s",text[0],text[1],text[2],text[3],text[4]); // 추가할 content 생성
    pass_to_json(date,content,text_color,check_value); // content를 json에 파싱
    free(text_color);
    free(content);
    for(int i=0; i<5; i++){
        free(text[i]);
    }

    return Y;
}

int add_schedule()                                                                          // schedule 추가하기.
{
    int year,month,day,i;
    char check;
    char date[32];

    int num_y = 8;

    fflush(stdin); // 버퍼 비우기.
    while(1){ // 올바른 값을 받을 때 까지 반복문 실행
        current_calendar(); // 시작 전 초기화


        xy_out(50,3); printf(" 추가할 일정의 날짜를 입력해주세요.");
        xy_out(50,5); printf("날짜:");
        scanf("%d %d %d",&year,&month,&day);


        if(check_day(&year,&month,&day) == Y){  // year month day 값이 올바른지 확인.
            snprintf(date,32,"%d-%02d-%02d",year,month,day); // json 에 들어갈 date 문자열 생성

            if(check_schedule_json(date) == N){  // date가 존재하는지 확인. 있다면 if문 실행

                while(1){
                    fflush(stdin);
                    xy_out(50,num_y); printf(" 이미 일정이 있습니다 일정을 추가하시겠습니까?");num_y++;
                    xy_out(50,num_y); printf(" 입력:");num_y++;
                    scanf("%c",&Y_N);

                    if(switching_y_n() == Y){  // 일정 추가 물음에 Y를 누른다면
                        if(get_content(date,Y,num_y) == N){
                            xy_out(50,num_y);  printf(" 일정이 꽉 찼습니다.");num_y++;
                            xy_out(50,num_y); printf(" 다시 날짜를 쓰시겠습니까?");num_y++;
                        }
                        return Y;
                    }
                    else{
                        return N;
                    }
                }
            }
            else{ // date가 없다면.
                get_content(date,N,num_y);
                return Y;
            }
        }
    }

}

int delete_schedule()                                                                       // schedulee 삭제하기
{
    int year,month,day;
    char date[32];

    current_calendar(); //화면 초기화

    num_y = 3;
    while(1){
        xy_out(50,num_y); printf(" 일정 지울 날짜를 입력해주세요"); num_y++;
        xy_out(50,num_y); printf(" 입력:");num_y++;
        scanf("%d %d %d",&year,&month,&day);

        if(check_day(&year,&month,&day) == Y){
            snprintf(date,32,"%d-%02d-%02d",year,month,day);
            if(check_schedule_json(date) == N){
                delete_schedule_json(what_num(date));  // date에 해당하는 배열 번호 입력 받고 , 그 배열번호에 해당하는 일정 제거거
                return Y;
            }
            else{
                printf(" 일정이 없습니다.");
                return N;
            }
        }
        else{
            break;
        }
    }
}

int direct_schedule_interface()                                                             // schedule 관리하는 인터페이스.
{
    int check;
    fflush(stdin); // 버퍼 비우기.

    xy_out(50,3); printf(" [1] : 일정 추가하기");
    xy_out(50,6); printf(" [2] : 일정 지우기");

    xy_out(250,250);
    check = _getch();

    if(check == num1 || check == num2 || check == ESC ){
            switch(check){                  // check 값에 따라 해당하는 기능 함수를 실행
                case num1:return add_schedule();
                case num2:return delete_schedule();
                case ESC:return ESC;  // 뒤로가기기
        }
    }
}

int direct_schedule()                                                                       // schedule 추가 / 삭제 선택.
{

    while(1){
        current_calendar(); //시작 전 초기화

        if(direct_schedule_interface() == ESC)break; //ESC 입력할 시 뒤로가기

    }

}

void scan_ymd(int *year,int *month,int *day)                                                // year , month , day 스캔.
{
    xy_out(50,10);printf("날짜입력:");
    scanf("%d %d %d",year,month,day);
}

void around_interface()                                                                     // 달력 둘러보는 인터페이스창.
{
    xy_out(50,3); printf(" ASWD 로 일수를 옮길 수 있습니다. (대소문자 구별없음.)");
    xy_out(50,4); printf(" 컨트롤 + A/D 는 월 수를 옮길 수 있습니다.");
    xy_out(50,5); printf(" 컨트롤 + W/S 는 년 수를 옮길 수 있습니다.");
    xy_out(50,6); printf(" 특정 날짜를 입력하고싶으면 엔터를 누르고 입력해주세요.");
    xy_out(50,7); printf(" 날짜 입력은 Y M D 유형으로 입력해주세요");
}

int look_around_calendar()                                                                  // 달력 둘러보는 알고리즘.
{
    int year = current_ymd.year;
    int month = current_ymd.month;
    int day = current_ymd.day;

    char change_string[64];
    char check;  // 방향 또는 년 월 일을 입력받음

    while(select_calendar(year,month,day) != N){

        around_interface();
        print_select_schedule_json(year,month,day);  // 일정 출력

        check=_getch();

        while(check_direction(check)== Y)       // asdw 를 입력 받으면 바로 실행.
        {
            plus_minus_ymd(&year,&month,&day,check); // 입력받은 값을 토대로 연산 진행
            select_calendar(year,month,day);        // 입력받은 값을 달력으로 출력.
            around_interface();                     //인터페이스 재등장
            print_select_schedule_json(year,month,day);  // 일정 출력
            check = _getch();
        }

        if(check == '\r' || check == ESC )  // '\r' => 엔터
                switch(check){                  // check 값에 따라 해당하는 기능 함수를 실행
                    case '\r':scan_ymd(&year,&month,&day);break;
                    case ESC:return ESC;  // 프로그램 종료.
        }

    }

}

int schedule_interface()                                                                    //달력 둘러보기 , 일정관리하기 중 택
{
    char check;
    int f;

    xy_out(50,3); printf(" [1] : 달력 둘러보기");
    xy_out(50,6); printf(" [2] : 일정 관리하기");

   // 1 2 ESC 받기 전까지 무한 반복문
    xy_out(250,250);
    check = _getch();

        if(check == num1 || check == num2 || check == ESC ){
                switch(check){                  // check 값에 따라 해당하는 기능 함수를 실행
                    case num1:return look_around_calendar();
                    case num2:return direct_schedule_interface();
                    case ESC:return ESC;  // 프로그램 종료.
        }
    }
}

void schedule_function()
{
    int input_year;
    int input_month;
    int input_day;

    current_calendar(); // 화면 초기화.

    while(schedule_interface() != ESC){
        current_calendar();
    }

}



