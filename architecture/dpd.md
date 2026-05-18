# DPD: Data Process Diagram

이 문서는 Calendar 프로젝트의 처리 절차를 DPD 관점으로 정리한다.  
DFD가 데이터 이동을 중심으로 본다면, DPD는 각 기능이 어떤 프로세스 단계로 분해되는지에 초점을 둔다.

## 전체 프로세스 분해도

```mermaid
flowchart TB
    Start([프로그램 시작])
    Main[main()]
    SelectFunction[select_function()]
    DrawCurrent[current_calendar()]
    PrintDDay[print_d_day_json()]
    MainMenu[select_interface()]
    CheckInput{입력값}
    DDayFlow[D-day 프로세스]
    ScheduleFlow[일정 프로세스]
    Refresh[화면 갱신]
    End([프로그램 종료])

    Start --> Main
    Main --> SelectFunction
    SelectFunction --> DrawCurrent
    DrawCurrent --> PrintDDay
    PrintDDay --> MainMenu
    MainMenu --> CheckInput

    CheckInput -->|1| DDayFlow
    CheckInput -->|2| ScheduleFlow
    CheckInput -->|ESC| End
    CheckInput -->|그 외| Refresh

    DDayFlow --> Refresh
    ScheduleFlow --> Refresh
    Refresh --> DrawCurrent
```

## Interface 프로세스

```mermaid
flowchart TB
    Init[화면 초기화 및 현재 달력 표시]
    DDayView[저장된 D-day 표시]
    Menu[메인 메뉴 출력]
    Input[_getch로 키 입력]
    Branch{입력 분기}
    CallDDay[d_day_function 호출]
    CallSchedule[schedule_function 호출]
    ReturnEsc[ESC 반환]
    ReturnY[Y 반환 후 재표시]

    Init --> DDayView
    DDayView --> Menu
    Menu --> Input
    Input --> Branch
    Branch -->|num1| CallDDay
    Branch -->|num2| CallSchedule
    Branch -->|ESC| ReturnEsc
    Branch -->|기타 입력| ReturnY
    CallDDay --> ReturnY
    CallSchedule --> ReturnY
```

## 일정 관리 프로세스

```mermaid
flowchart TB
    Start([schedule_function])
    ShowCalendar[current_calendar]
    ScheduleMenu[schedule_interface]
    ScheduleChoice{선택}
    Browse[look_around_calendar]
    Manage[direct_schedule_interface]
    ManageChoice{추가/삭제}
    Add[add_schedule]
    Delete[delete_schedule]
    End([ESC로 뒤로가기])

    Start --> ShowCalendar
    ShowCalendar --> ScheduleMenu
    ScheduleMenu --> ScheduleChoice
    ScheduleChoice -->|1 달력 둘러보기| Browse
    ScheduleChoice -->|2 일정 관리하기| Manage
    ScheduleChoice -->|ESC| End
    Browse --> ShowCalendar
    Manage --> ManageChoice
    ManageChoice -->|1| Add
    ManageChoice -->|2| Delete
    ManageChoice -->|ESC| End
    Add --> ShowCalendar
    Delete --> ShowCalendar
```

## 일정 추가 세부 프로세스

```mermaid
flowchart TB
    Start([add_schedule])
    Draw[current_calendar]
    InputDate[날짜 입력]
    CheckDate{check_day}
    MakeDate[YYYY-MM-DD 문자열 생성]
    Exists{check_schedule_json}
    AskAppend{이미 일정 있음: 추가할지 확인}
    InputContent[get_content]
    CountCheck{content 5개 초과 여부}
    InputText[일정 내용 입력]
    InputColor[색상 선택]
    SortStar[rebuilding_star]
    SaveNew[creat_schedule_json]
    SaveAppend[plus_content_json]
    Fail[추가 취소 또는 실패]
    Success([Y 반환])

    Start --> Draw
    Draw --> InputDate
    InputDate --> CheckDate
    CheckDate -->|N| Draw
    CheckDate -->|Y| MakeDate
    MakeDate --> Exists
    Exists -->|일정 없음| InputContent
    Exists -->|일정 있음| AskAppend
    AskAppend -->|N| Fail
    AskAppend -->|Y| CountCheck
    CountCheck -->|꽉 참| Fail
    CountCheck -->|추가 가능| InputContent
    InputContent --> InputText
    InputText --> InputColor
    InputColor --> SortStar
    SortStar -->|새 일정| SaveNew
    SortStar -->|기존 일정 추가| SaveAppend
    SaveNew --> Success
    SaveAppend --> Success
```

## D-day 프로세스

```mermaid
flowchart TB
    Start([d_day_function])
    Draw[current_calendar]
    Print[print_d_day_json]
    Menu[d_day_interface]
    Choice{선택}
    Scan[scan_d_day]
    DeleteQuestion[question_delete_d_day]
    Empty{D-day 존재 여부}
    RealDelete[real_delete_d_day]
    Back([ESC로 뒤로가기])

    Start --> Draw
    Draw --> Print
    Print --> Menu
    Menu --> Choice
    Choice -->|1 추가/편집| Scan
    Choice -->|2 삭제| DeleteQuestion
    Choice -->|ESC| Back
    DeleteQuestion --> Empty
    Empty -->|없음| Menu
    Empty -->|있음, Y 확인| RealDelete
    RealDelete --> Menu
    Scan --> Menu
```

## D-day 계산 세부 프로세스

```mermaid
flowchart TB
    Start([scan_d_day])
    Draw[current_calendar]
    GoalInput[scan_goal_day]
    DateCheck{날짜 유효성 및 현재 이후 여부}
    Calc[d_day_calculation]
    SameYear{현재 연도와 목표 연도 동일?}
    SameYearCalc[목표 yday - 현재 yday - 1]
    DiffYearCalc[목표일까지 일수 + 중간 연도 일수 + 윤년 보정]
    NameInput[scan_d_day_name]
    Preview[출력 예시 표시]
    Retouch{name_retouch}
    Save[change_d_day_json]
    End([Y 반환])

    Start --> Draw
    Draw --> GoalInput
    GoalInput --> DateCheck
    DateCheck -->|N| GoalInput
    DateCheck -->|Y| Calc
    Calc --> SameYear
    SameYear -->|Y| SameYearCalc
    SameYear -->|N| DiffYearCalc
    SameYearCalc --> NameInput
    DiffYearCalc --> NameInput
    NameInput --> Preview
    Preview --> Retouch
    Retouch -->|Y 수정| Draw
    Retouch -->|N 확정| Save
    Save --> End
```

## 달력 생성 프로세스

```mermaid
flowchart TB
    Start([current_calendar 또는 select_calendar])
    Init[initialization]
    Mode{호출 함수}
    SetCurrent[set_current_day]
    CheckInputDate[check_day]
    Header[start_ymd]
    PrintCalendar[print_calendar]
    CalcFirst[certain_day: 해당 월 1일 요일]
    CalcLast[last_day_calculation: 말일]
    BuildLoop[6 x 7 셀 반복]
    CellType{셀 종류}
    LastMonth[이전 달 날짜 GRAY]
    NextMonth[다음 달 날짜 GRAY]
    Today[선택 날짜 BLUE]
    ScheduleColor[일정 색상 조회]
    Normal[일반 날짜 WHITE]
    Render[print_color_day 또는 print_blue_day]
    End([화면 출력 완료])

    Start --> Init
    Init --> Mode
    Mode -->|current_calendar| SetCurrent
    Mode -->|select_calendar| CheckInputDate
    SetCurrent --> Header
    CheckInputDate -->|Y| Header
    CheckInputDate -->|N| End
    Header --> PrintCalendar
    PrintCalendar --> CalcFirst
    CalcFirst --> CalcLast
    CalcLast --> BuildLoop
    BuildLoop --> CellType
    CellType -->|첫 주 이전 달 영역| LastMonth
    CellType -->|말일 이후 다음 달 영역| NextMonth
    CellType -->|선택 날짜| Today
    CellType -->|현재 달 일반 날짜| ScheduleColor
    ScheduleColor -->|일정 있음| Render
    ScheduleColor -->|일정 없음| Normal
    LastMonth --> Render
    NextMonth --> Render
    Today --> Render
    Normal --> Render
    Render --> BuildLoop
    BuildLoop --> End
```

## JSON 처리 프로세스

```mermaid
flowchart TB
    Start([JSON 함수 호출])
    Parse[json_parse_file]
    Root[json_value_get_object]
    SelectArray{대상 배열}
    ScheduleArray[schedule 배열]
    DDayArray[d_day 배열]
    Operation{작업 종류}
    Read[조회: check/print/call]
    Create[생성: creat_schedule_json]
    Update[수정: plus_content_json/change_d_day_json]
    Delete[삭제: delete_schedule_json/delete_d_day_json]
    Serialize[json_serialize_to_file_pretty]
    Free[json_value_free]
    End([반환])

    Start --> Parse
    Parse --> Root
    Root --> SelectArray
    SelectArray -->|schedule| ScheduleArray
    SelectArray -->|d_day| DDayArray
    ScheduleArray --> Operation
    DDayArray --> Operation
    Operation -->|조회| Read
    Operation -->|생성| Create
    Operation -->|수정| Update
    Operation -->|삭제| Delete
    Read --> Free
    Create --> Serialize
    Update --> Serialize
    Delete --> Serialize
    Serialize --> Free
    Free --> End
```

