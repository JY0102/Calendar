#include"d_day_all_function.h"
#include"schedule_all_function.h"

int select_interface()                                                          // 달력 옆에 인터페이스 생성
{
    int f;
    char check;

    xy_out(50,6);  printf(" [1] : D - day 설정하기");
    xy_out(50,9);  printf(" [2] : SCHEDULE 설정보기");
    xy_out(50,15); printf("필요하신 기능이 있으면 번호를 입력 해주시면 감사하겠습니다.");



    check = _getch();

    if(check == num1 || check == num2 || check == ESC )
        switch(check){                  // check 값에 따라 해당하는 기능 함수를 실행
            case num1:d_day_function();break;
            case num2:schedule_function();break;
            case ESC:return ESC;  // 프로그램 종료.
        }
    return Y;
}

void select_function()
{
    current_calendar();         //화면 초기화 및 전반적인 현재 일 기준 출력
    print_d_day_json();            // 만약에 d_day 에 값이 들어 있다면 출력.

    while(select_interface() != ESC){         //f 값으로 어떤 기능을 사용할지 받음.

        current_calendar();         //화면 초기화 및 전반적인 현재 일 기준 출력
        print_d_day_json();            // 만약에 d_day 에 값이 들어 있다면 출력.

    }
}

int main(){

    select_function();

    return 0;
}


