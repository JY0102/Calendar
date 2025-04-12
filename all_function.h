#include<time.h>
#include <conio.h>
#include"cal_json.h"

#pragma once            //충돌 예방.
#define ESC 27

int num_y=3; // y 좌표 출력 위치 용도
char Y_N; // Yes or NO 를 받는 용도

enum last_or_next_month
{
    last = 0,
    next = 1,
    this_month = 3,
}last_or_next;
enum number
{
    num1 = 49,
    num2
}number_;
struct d_day
{
    char name[16];
    int day;
    int check;   // Y와 0 으로 만들었는지 안만들었는지 유무 확인
}d_day_value;
struct start_goal_day
{
    int g_year;
    int g_month;    // 목표일
    int g_day;
}se_value;

struct current
{
    int year;
    int month;
    int day;
    int wday; // 요일
    int yday; // 1월 1일 부터 현재까지 지난 일수.
}current_ymd;

struct callendar_information{
    int day_color;
    int last_month_day;
    int next_month_day;
    int day;
}calendar[6][7];

void set_current_day()                                                                       // 현재 날짜 받아옴.
{
    time_t timer;
    struct tm* t;

    time(&timer); // time 함수로 timer 초기화
    t = localtime(&timer); // timer를 이용해 현재 지역 시간 구조체 포인터 얻기

    if (t == NULL) {
        perror("localtime failed");
        return; // localtime 실패 시 에러 처리
    }

    current_ymd.year = t->tm_year+1900;     // 몇년인지 받아옴.
    current_ymd.month = t->tm_mon+1;        // 몇월인지 받아옴
    current_ymd.day = t->tm_mday;           // 며칠인지 받아옴.
    current_ymd.wday = t->tm_wday;          // 무슨 요일인지 받아옴.
    current_ymd.yday = t->tm_yday;          // 1월 1일부터 며칠지났는지 받아옴.
}

void initialization()                                                                        // 화면 및 캘린더 초기화
{
    system("cls");  // 화면 초기화
    fflush(stdin); // 입력 버퍼 비우기.
    textcolor(WHITE);
    for(int y=0; y<6; y++){
        for(int x=0; x<7; x++){     // 캘린더 초기화
            calendar[y][x].day_color = WHITE;
            calendar[y][x].last_month_day =0;
            calendar[y][x].next_month_day =0;
            calendar[y][x].day =0;
        }
    }
    num_y=3;

}

int  all_leap_year(int year)                                                                 // 1년 부터 year 년 까지 윤년이 몇 번 지났는지 계산
{
    int n = 0;
    int count = 0;

    while( year > 4*n){

        if( (4*n) % 400 !=0 && (4*n) % 100 == 0 ){  // 400으로 안나누어 떨어지고 100으로 나누어떨어지는 년도는 윤년 x
            count++;
        }
        n++;
    }
    n -=count+1;  // 윤년이 해당 안된 년도 빼기

    return n;
}

int  leap_year(int year,int month,int day)                                                   // 현재 윤년이 지났는지 확인. 확인후 해당이 될 시 day +1
{

    if(month > 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))){    // 특정 날짜의 년도가 윤년일시 day ++; 해서 윤년 일수 맞추기 + 2월 일 때만 +1 일 실행.
        return Y;                                                          // 특정 날짜가 100의 배수이면서 400의 배수 일 경우 윤년이므로 day++;  특정 날짜가 400의 배수가 아니면서 100의 배수 일 경우가 있으므로 if로 걸러주기

        if(month==2&&day==29){
            return Y;
        }
    }

    return N;
}

int  plus_day_for_month(int month,int day)                                                   // 1월 부터 month -1 까지의 일수를 계산
{
    for(int i=1; i<month; i++){ // i-1월 까지 며칠이 지났는지 계산
        switch(i){
            case 1:day+=31;break;
            case 2:day+=28;break;
            case 3:day+=31;break;
            case 4:day+=30;break;
            case 5:day+=31;break;
            case 6:day+=30;break;
            case 7:day+=31;break;
            case 8:day+=31;break;
            case 9:day+=30;break;
            case 10:day+=31;break;
            case 11:day+=30;break;
            case 12:day+=31;break;
            }
    }
    return day;
}

int  last_day_calculation(int year,int month)                                                // 해당 날짜 마지막 일 계산기
{
    int day=0;

    if(month ==0){
        month = 12; // 만약 1월을 입력 받고 befor_month_day 에서 1월 전달을 출력하는 경우 1-0으로 달이 0월이 되어버리므로 12월로 uderflow 를 하기위해 if로 만듬.
    }
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    day += days_in_month[month-1];

    if(month==2)day +=leap_year(year,month,day);      // 2월 이라면 윤년 계산하여 마지막날 +1 일

    return day;
}

void print_dtw(int day)                                                                      // 특정 요일 출력
{
    switch(day){
    case 0:printf(" SUNDAY");break;
    case 1:printf(" MONDAY");break;
    case 2:printf(" TUESDAY");break;
    case 3:printf(" WEDNESDAY");break;
    case 4:printf(" THURSDAY");break;
    case 5:printf(" FRIDAY");break;
    case 6:printf(" SATURDAY");break;
    }
}

void print_color_day(int y,int x,int check)                                                  // 저장 되어 있는 컬러색깔로 달력 출력.
{
    if(calendar[y][x].day_color != WHITE){
        textcolor(calendar[y][x].day_color);
            if(calendar[y][x].day_color == GRAY && check == last){      // 저번달 일수 출력.
                if(calendar[y][x].last_month_day == 0)printf("    "); // 1년 1월일 경우 공백 출력

                else printf(" %2d ",calendar[y][x].last_month_day);
            }
            else if(calendar[y][x].day_color == GRAY && check == next){ //다음달 일수 출력.
                printf(" %2d ",calendar[y][x].next_month_day);
            }
            else printf(" %2d ",calendar[y][x].day);    // 일정이 만약 저장되어 있다면 해당 일정으로 설정해둔 색깔로 출력.

        textcolor(WHITE);
    }
    else
        printf(" %2d ",calendar[y][x].day);  // 흰색깔 출력.
}

void print_month(int month)                                                                  // 특정 월 출력
{
    switch(month){
        case 1: printf("January"); break;
        case 2: printf("February"); break;
        case 3: printf("March"); break;
        case 4: printf("April"); break;
        case 5: printf("May"); break;
        case 6: printf("June"); break;
        case 7: printf("July"); break;
        case 8: printf("August"); break;
        case 9: printf("September"); break;
        case 10: printf("October"); break;
        case 11: printf("November"); break;
        case 12: printf("December"); break;
    }
}

void print_gray_day(int day)                                                                 // 일수를 회색으로 출력
{
    textcolor(GRAY);
    printf(" %2d ",day);            // 해당 달의 일수가 다 채워지면 공백 출력
    textcolor(WHITE);
}

void print_blue_day(int day)                                                                 // 일수를 파란색으로 출력
{
    textcolor(BLUE);
    printf(" %2d ",day); // 해당 날짜의 일수를 파란색으로 강조
    textcolor(WHITE);
}

void start_ymd(int year,int month,int day,int wday)                                          // 캘린더 출력전 특정 날짜 출력
{
    printf("      ");             //줄 맞추기
    printf("%d / ", year);        //현재 년도 출력
    printf("%d / ",month);        //현재 월(숫자) 출력
    printf("%d / ", day);         // 현재 일수 출력

    print_dtw(wday);              // 요일 출력
}

int  certain_day(int year,int month,int day)                                                 // 특정 날짜에서의 요일 계산하는 알고리즘
{
    int first_day_of_year,n=0;

    first_day_of_year = (year + all_leap_year(year))%7;   // 1년 1월 1일 월요일 기준으로 특정 년도 1월 1일 요일을 계산 하는 공식 ( 년도 + 총 윤년 횟수 ) % 7 = 해당 년도 1월 1일 요일.

    day = plus_day_for_month(month,day)+leap_year(year,month,day)-1;

    day= (first_day_of_year + day)%7;  // 요일 구하는 공식 (새해 첫 요일( 0 ~ 6 , 일 : 0 , 월 :1 ~ 토 : 6 ) + 현재까지 지나간 날) => 현재 요일

    return day;
}

int hoxy_mola(int year,int month,int check)
{
    if( year ==1 && month == 1){
        return 0;
    }

    return check;
}

void made_calendar(int year,int month,int day)                                               // 6 * 7 사이즈의 캘린더를 제작 및 출력을 함.
{

    int first_day = 1;
    int next_month_day = 1;
    int first_dtw = certain_day(year,month,1);                      // 해당 날짜의 1일이 무슨 요일인지 계산
    int last_day = last_day_calculation(year,month);              // 해당 날짜의 마지막 일이 며칠인지 계산
    int last_month_day = last_day_calculation(year,month-1) - first_dtw+1;  // 해당 날짜 기준 출력되는 캘린더 중 첫째주 월요일이 며칠인지 계산

    last_month_day = hoxy_mola(year,month,last_month_day); // 1년 1월 일 경우 전 달이 없으므로 출력x

    for(int y=0; y<6; y++){
        printf("| ");
        for(int x=0; x<7; x++){
            if(y==0&&x<first_dtw){
                calendar[y][x].day_color = GRAY;
                calendar[y][x].last_month_day = last_month_day;
                print_color_day(y,x,last);   // N달의 1~마지막일수까지 다 채우고 빈칸 요일을 차례대로 저번달 일수를 회색으로 출력
                last_month_day++;
            }
            else if(first_day>last_day){
                calendar[y][x].day_color = GRAY;
                calendar[y][x].next_month_day = next_month_day;
                print_color_day(y,x,next);    // N달의 N+1 달의 처음 일수부터 차례대로 출력
                next_month_day++;
            }
            else{
                calendar[y][x].day=first_day;
                    if(calendar[y][x].day==day){
                        print_blue_day(calendar[y][x].day);     // 해당 일은 파란색으로 강조
                    }
                    else {
                        if(check_text_color_json(year,month,first_day) != error_type){  // schedule 에 저장되있는 일정이 text_color 로 지정되어 있다면 실행.
                            calendar[y][x].day_color = out_text_color_json(year,month,first_day);
                            }
                        print_color_day(y,x,this_month);     // 일수 출력
                    }
                first_day++;
            }

        }
        printf("\n");
    }
}

void print_calendar(int year,int month,int day)                                              // 특정 날짜 달력 출력
{
    printf("\n\n");
    printf("==================================\n");         // 줄 맞추는 용
    printf("\t   ");
    print_month(month);                             // 해당 날짜의 월을(영어) 표시
    printf("\n");

    printf("   SUN MON TUE WED THR FRI SAT\n");

    made_calendar(year,month,day);         // 캘린더 만들고 출력
}

int  check_day(int *year,int *month,int *day)                                                // 입력 받은 값이 년 월 일에 적합하지 않다면 N을 리턴
{

    if(*year<1);
    else if(12<*month || *month<1);
    else if(last_day_calculation(*year,*month)<*day || *day<1);
    else return Y;

    *year =0;
    *month =0;      // 오버플로우 발생 방지용 초기화.
    *day =0;

    return N;
}

int select_calendar(int year,int month,int day)                                              // 해당 날짜의 캘린더 출력
{
    initialization(); // 시작 전 초기화
    if(check_day(&year,&month,&day)==N)return N; // 날짜값이 올바른지 확인

    start_ymd(year,month,day,certain_day(year,month,day));      // 해당 날짜의 년 , 월 , 일  ,  요일 출력

    print_calendar(year,month,day); // 특정 날짜 캘린더출력

    return Y;
}

void current_calendar()                                                                      // 현재 날짜 기준으로 전반적인 달력을 출력 담당.
{

    initialization(); // 시작 전 초기화
    set_current_day();

    start_ymd(current_ymd.year,current_ymd.month,current_ymd.day,current_ymd.wday);  // 해당 날짜의 년 , 월 , 일  ,  요일 출력

    print_calendar(current_ymd.year,current_ymd.month,current_ymd.day);    // 특정 날짜 캘린더출력

}

int  check_before_day_for_current(int year,int month,int day)                                //입력 받은 값이 현재 날짜 보다 이전이면 N 값 리턴
{
    day = plus_day_for_month(month,day) + leap_year(year,month,day);  // 1월 1일 기준으로 선택한 날짜까지 총 며칠이 지났는지 계산.

    if(current_ymd.year<year)return Y; // 목표 년도가 더 높으면 Y 출력
    else if(current_ymd.yday>year)return N; // 현재 년도가 더 높으면 N 출력
    else{
        if(current_ymd.yday+1 >= day)return N; // 1월 1일 기준부터 현재까지 지난 날이 선택한 날짜랑 같거나,더 높다면 N 출력.
    }
    return Y;
}

int check_before_day_by_day(int year1,int month1,int day1,int year2,int month2,int day2)    // A 값과 B 값중 A 값이 B값보다 이전이라면 N
{
    day1 = plus_day_for_month(month1,day1) + leap_year(year1,month1,day1);  // 1월 1일 기준으로 선택한 날짜까지 총 며칠이 지났는지 계산.
    day2 = plus_day_for_month(month2,day2) + leap_year(year2,month2,day2);  // 1월 1일 기준으로 선택한 날짜까지 총 며칠이 지났는지 계산.

    if(year1<year2)return Y; // year2가 더 높으면 Y 출력
    else if(day1>year2)return N; // year 1이이 더 높으면 N 출력
    else{
        if(day1 >= day2)return N; // 1월 1일 기준부터 현재까지 지난 날이 선택한 날짜랑 같거나,더 높다면 N 출력.
    }
    return Y;
}

int check_three_start_schedule(char *date)  // 입력받은 date 가 현재 날짜보다 이전인지 , 혹은 json 데이터안에 있는 날짜보다 이전인지 체크
{
    int year[6];
    int month[6];
    int day[6];

    if(set_three_star_schedule_json() == N){
        return error_type;
    }

    sscanf(date,"%d-%d-%d",&year[5],&month[5],&day[5]);  // 입력 받은 date 값을 int 형으로 찢음

    if(check_before_day_for_current(year[5],month[5],day[5]) == Y ){  // 입력받은 날짜가 현재보다 이전인지 확인

        for(int i=0; i<json_array_get_count(three_star_array); i++){
            three_star_json = json_array_get_object(three_star_array,i);
            sscanf(json_object_get_string(three_star_json,"date"),"%d-%d-%d",&year[i],&month[i],&day[i]); // three_star_schedule 에 있는 date를 인트형으로 데이터 분리

            if(check_before_day_by_day(year[i],month[i],day[i],year[5],month[5],day[5]) == Y){  // year [5] 값이 더 크다면 Y 값 리턴.
                    rebuliding_three_star_schedule(date,i);
            }
        }
    }

   json_end();
    return N;

}