#include"all_function.h"

//d_day 에서만 쓰는 함수들 모음집


void d_day_calculation()                                                                     // 현재일부터 목표일 까지 총 며칠이 지났는지 계산
{
    int day= se_value.g_day;

    if(se_value.g_year != current_ymd.year){    // 만약 년도가 다를때 목표일까지 남은 날 구하기.

        se_value.g_day = plus_day_for_month(se_value.g_month,se_value.g_day) + leap_year(se_value.g_year,se_value.g_month,se_value.g_day);  // 1월 1일 부터 목표 날 까지 요일 수.

        se_value.g_day += (se_value.g_year - current_ymd.year-1)*365;  // 현재년도와 목포년도 사이에 있던 N년 차이 만큼 N*365일 더하기

        for(int i=current_ymd.year; i<se_value.g_year; i++){ // 현재년도와 목표년도 사이에 윤년이 있을 때 마다  +1을 하는 함수
            se_value.g_day += leap_year(i,3,1);
        }
        d_day_value.day = se_value.g_day + 364 - current_ymd.yday;     // 현재 년도가 다음년도까지 남은 일수 + 위에 일수 총합 -> 목표일까지 남은 날
    }
    else{
        se_value.g_day = plus_day_for_month(se_value.g_month,se_value.g_day) + leap_year(se_value.g_year,se_value.g_month,day);  // 1월 1일 부터 현재 날 까지 요일 수.
        d_day_value.day= se_value.g_day - current_ymd.yday - 1;
    }
}

void real_delete_d_day()                                                                     //d_day 값 모드 초기화
{
    d_day_value.check =N;
    d_day_value.day =0;
    for(int i=0; i<10; i++)d_day_value.name[i]='\0';
    delete_d_day_json();
}

int  question_delete_d_day()                                                                 // d_day 삭제하는지 물어보기.
{

    if(check_d_day_json() == N)return N;

    current_calendar(); //화면 초기화.

    fflush(stdin); // 입력 버퍼 비우기.

    xy_out(50,8); printf(" 정말로 삭제하시겠습니까? Y/N:"); scanf("%c",&Y_N);

    switch(switching_y_n()){
        case N: return Y;
        case Y: real_delete_d_day();
    }
    return Y;
}

int  name_retouch()                                                                          // 만약에 d-day 수정이 필요하면 수정을 하게 해줌
{
    num_y+=4;

    fflush(stdin); // 입력 버퍼 비우기.

    xy_out(50,num_y++); printf("수정하시겠습니까? Y / N :"); scanf("%c",&Y_N);

    while(((Y_N=='Y'&&Y_N!='N')||(Y_N!='Y'&&Y_N=='N'))!=1){        // Y 또는 N 이라는 값을 받을 때 까지 반복문
        fflush(stdin); // 입력 버퍼 비우기.

        xy_out(50,num_y++); printf(" 다시 입력해주세요 :"); scanf("%c",&Y_N);
    }
    return switching_y_n();
}

void scan_goal_day()                                                                         // 종료일 값을 받아서 현재와 며칠 차이가 나는지 계산
{
    num_y = 6;
    xy_out(50,3); printf("목표일을 써주세요 , 잘못된 값 입력시 다시 시작합니다.");

    xy_out(50,4); printf("EX - 목표일 2004년 3월 5일=> 목표일:2004 3 5");

    xy_out(50,num_y++); printf("목표일:"); scanf("%d %d %d",&se_value.g_year,&se_value.g_month,&se_value.g_day);

    while((check_day(&se_value.g_year,&se_value.g_month,&se_value.g_day)&&check_before_day_for_current(se_value.g_year,se_value.g_month,se_value.g_day))!= Y)  // 스캔 받은 값이 올바르지 않다면 실행.
    {
        fflush(stdin); // 입력 버퍼 비우기.

        xy_out(50,num_y++); printf(" 잘못된 날짜를 입력하셨습니다.");

        xy_out(50,num_y++); printf("목표일:"); scanf("%d %d %d",&se_value.g_year,&se_value.g_month,&se_value.g_day);
    }
    num_y++;

    d_day_calculation();      //day_value.day 에 현재일부터 목표일 까지 계산하여 남은 일수를 할당함.
}

void scan_d_day_name()                                                                       // D-day 의 이름 값을 입력을 받음.
{
    char *name= (char*)malloc(32 *sizeof(char));


    xy_out(50,num_y++); printf(" D-DAY의 이름을 설정해주세요 ");
    xy_out(50,num_y++); printf("( 단 ,16글자까지지");
    xy_out(50,num_y++); printf(" Ex : [brith day] D - %d",d_day_value.day);   // 예시 출력.

    fflush(stdin);
    xy_out(50,num_y++); printf("이름:");
    fgets(name, 16, stdin);

    name[strcspn(name, "\n")] = '\0';

    while(strlen(name)>16){      // 16글자가 넘으면 다시 실행 되는 반복문
        fflush(stdin); // 입력 버퍼 비우기.

        xy_out(50,num_y++); printf(" 초과된 단어를 사용하셨습니다.");

        xy_out(50,num_y++); printf("이름:");
        fgets(name, 16, stdin);
        name[strcspn(name, "\n")] = '\0';
    }

    strcpy(d_day_value.name , name);   // 구조체 배열에 문자열 복사 후 저장.
}

int  scan_d_day()                                                                             // d_day 설정을 받아옴.
{
    while(1){

    current_calendar(); // 화면 초기화.
    scan_goal_day();    // 목표일 입력 받기.
    scan_d_day_name();  // 목표일 이름 입력 받기.

    xy_out(50,num_y+2); printf("출력 예시 : [%s] D - %d",d_day_value.name,d_day_value.day);

    if(name_retouch() == N)break;    // 수정하시겠습니까? 대답이 N 이라면 반복문 종료.
    }

    d_day_value.check=Y; // d_day_value 안에 값이 들어가있는 것을 check
    change_d_day_json(d_day_value.name,d_day_value.day);
    return Y;
}

int  d_day_interface()                                                                       // D_day 관련 인터페이스 입력 받음
{
    char check;
    int f;

    xy_out(50,6); printf(" [1] : D - day 추가/편집하기");
    xy_out(50,9); printf(" [2] : D - day 지우기");


    while(1){
        check = _getch();

        if(check == num1 || check == num2 || check == ESC )
                switch(check){                  // check 값에 따라 해당하는 기능 함수를 실행
                    case num1:return scan_d_day();
                    case num2:return question_delete_d_day();
                    case ESC:return ESC;  // 뒤로가기
       }
    }
    return Y;
}

void d_day_function()                                                                        // 시작 날짜 부터 종료 날짜까지 총 며칠이 남았는지 계산하는 담당
{
    char name[16];

    current_calendar(); //화면 초기화
    print_d_day_json();

    while (d_day_interface()==N)   // 만약 올바른 값이 안나왔다면 재시작.
    {
        current_calendar();        //화면 초기화 및 전반적인 현재 일 기준 달력 출력

        xy_out(50,10); printf("** D_day 가 비어있습니다.**");
    }

}

