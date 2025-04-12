

# 추가한 기능 

## 1.헤더 파일 생성
---
  헤더 파일을 생성하여 헤더파일안에 있는 함수를 #include 로 가져와 코딩을 더 보기 편하게 정리 했다.
  Ex ) interface.h , all_fuction.h 

## 2. 코드 뭉치 함수화
---
나 이외에 팀원들이 "같이" 보는 코드 이기 때문에 웬만한 코드 뭉치들을 함수에 모아 보기 편하게 정리하여 필요한 코드뭉치 또는 자주쓰는 코드뭉치를 편하게 불러서 재사용을 할 수 있다.

## 3. stdio.h
---

enum열거형
```
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
  };

  BLACK == 0; 
  WHITE == 16;
```
따로 숫자를 초기화 하지 않을 경우 0부터 ~ N 까지 자동으로 순서대로 초기화 됨.

버퍼 비우기
```
  fflush(stdin);
```
남은 버퍼에 필요 없는 값이 있을 때 모든 버퍼를 초기화 할 때 사용

## 4. windows.h 
---
윈도우 헤더파일 참조.


```
    void xy_out(int x, int y)          // x , y 좌표에서부터 출력
    {
        COORD Pos;
        Pos.X = x;
        Pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    }

  xy_out(50,5);  // x 50 좌표 , y 5 좌표 출력.
```

```
    void textcolor(int colorNum)       // 텍스트 색깔 변경 
    {
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);  //특정 컬러 이름 입력시 해당 색깔로 출력
    }
    textcolor(BLUE);  // 이제부터 파란색 문자 출력
```

```
  system("cls");                       // 콘솔창 초기화
```


## 5. time.h
---
타임 헤더파일 참조

사용 전 초기화
```
    time_t timer;
    struct tm* t;

    time(&timer); // time 함수로 timer 초기화
    t = localtime(&timer); // timer를 이용해 현재 지역 시간 구조체 포인터 얻기

    if (t == NULL) {
        perror("localtime failed");
        return; // localtime 실패 시 에러 처리
    }
```

```
  printf(" Year  : %d ", t->tm_year + 1900 );    // 현재 년도 = t->tm_year + 1900
  printf(" Month : %d ",    t->tm_mon+1    );    // 현재 월 = t->tm_mon + 1   
  printf(" DAY   : %d ",    t->tm_mday     );    // 현재 일수 t->tm_mday
  print_day(t->tm_wday);

void print_day(int day){
  switch(day){       
    case 0:printf(" SUNDAY");break;        
    case 1:printf(" MONDAY");break;        
    case 2:printf(" TUESDAY");break;        // 현재 요일 출력 함수 화.
    case 3:printf(" WEDNESDAY");break;        
    case 4:printf(" THURSDAY");break;        
    case 5:printf(" FRIDAY");break;        
    case 6:printf(" SATURDAY");break;      
  }
}
```














  
