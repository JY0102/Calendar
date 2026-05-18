# DPD: Data Process Diagram

Calendar project process decomposition diagrams.

## Overall Process

```mermaid
flowchart TB
    Start(["Program Start"])
    Main["main"]
    SelectFunction["select_function"]
    DrawCurrent["current_calendar"]
    PrintDDay["print_d_day_json"]
    MainMenu["select_interface"]
    CheckInput{"Input Value"}
    DDayFlow["D-day Process"]
    ScheduleFlow["Schedule Process"]
    Refresh["Refresh Screen"]
    End(["Program End"])

    Start --> Main
    Main --> SelectFunction
    SelectFunction --> DrawCurrent
    DrawCurrent --> PrintDDay
    PrintDDay --> MainMenu
    MainMenu --> CheckInput

    CheckInput -->|"1"| DDayFlow
    CheckInput -->|"2"| ScheduleFlow
    CheckInput -->|"ESC"| End
    CheckInput -->|"Other"| Refresh

    DDayFlow --> Refresh
    ScheduleFlow --> Refresh
    Refresh --> DrawCurrent
```

## Interface Process

```mermaid
flowchart TB
    Init["Clear screen and show current calendar"]
    DDayView["Show saved D-day"]
    Menu["Show main menu"]
    Input["Read key by getch"]
    Branch{"Input Branch"}
    CallDDay["Call d_day_function"]
    CallSchedule["Call schedule_function"]
    ReturnEsc["Return ESC"]
    ReturnY["Return Y and redraw"]

    Init --> DDayView
    DDayView --> Menu
    Menu --> Input
    Input --> Branch
    Branch -->|"num1"| CallDDay
    Branch -->|"num2"| CallSchedule
    Branch -->|"ESC"| ReturnEsc
    Branch -->|"Other"| ReturnY
    CallDDay --> ReturnY
    CallSchedule --> ReturnY
```

## Schedule Management Process

```mermaid
flowchart TB
    Start(["schedule_function"])
    ShowCalendar["current_calendar"]
    ScheduleMenu["schedule_interface"]
    ScheduleChoice{"Choice"}
    Browse["look_around_calendar"]
    Manage["direct_schedule_interface"]
    ManageChoice{"Add or Delete"}
    Add["add_schedule"]
    Delete["delete_schedule"]
    End(["Back by ESC"])

    Start --> ShowCalendar
    ShowCalendar --> ScheduleMenu
    ScheduleMenu --> ScheduleChoice
    ScheduleChoice -->|"1 Browse Calendar"| Browse
    ScheduleChoice -->|"2 Manage Schedule"| Manage
    ScheduleChoice -->|"ESC"| End
    Browse --> ShowCalendar
    Manage --> ManageChoice
    ManageChoice -->|"1"| Add
    ManageChoice -->|"2"| Delete
    ManageChoice -->|"ESC"| End
    Add --> ShowCalendar
    Delete --> ShowCalendar
```

## Schedule Add Detail Process

```mermaid
flowchart TB
    Start(["add_schedule"])
    Draw["current_calendar"]
    InputDate["Input Date"]
    CheckDate{"check_day"}
    MakeDate["Create YYYY-MM-DD String"]
    Exists{"check_schedule_json"}
    AskAppend{"Schedule Exists: Append?"}
    InputContent["get_content"]
    CountCheck{"Content Limit Check"}
    InputText["Input Schedule Content"]
    InputColor["Select Text Color"]
    SortStar["rebuilding_star"]
    SaveNew["creat_schedule_json"]
    SaveAppend["plus_content_json"]
    Fail["Cancel or Fail"]
    Success(["Return Y"])

    Start --> Draw
    Draw --> InputDate
    InputDate --> CheckDate
    CheckDate -->|"N"| Draw
    CheckDate -->|"Y"| MakeDate
    MakeDate --> Exists
    Exists -->|"Not Exists"| InputContent
    Exists -->|"Exists"| AskAppend
    AskAppend -->|"N"| Fail
    AskAppend -->|"Y"| CountCheck
    CountCheck -->|"Full"| Fail
    CountCheck -->|"Available"| InputContent
    InputContent --> InputText
    InputText --> InputColor
    InputColor --> SortStar
    SortStar -->|"New Schedule"| SaveNew
    SortStar -->|"Append Schedule"| SaveAppend
    SaveNew --> Success
    SaveAppend --> Success
```

## D-day Process

```mermaid
flowchart TB
    Start(["d_day_function"])
    Draw["current_calendar"]
    Print["print_d_day_json"]
    Menu["d_day_interface"]
    Choice{"Choice"}
    Scan["scan_d_day"]
    DeleteQuestion["question_delete_d_day"]
    Empty{"D-day Exists?"}
    RealDelete["real_delete_d_day"]
    Back(["Back by ESC"])

    Start --> Draw
    Draw --> Print
    Print --> Menu
    Menu --> Choice
    Choice -->|"1 Add or Edit"| Scan
    Choice -->|"2 Delete"| DeleteQuestion
    Choice -->|"ESC"| Back
    DeleteQuestion --> Empty
    Empty -->|"No"| Menu
    Empty -->|"Yes and Confirmed"| RealDelete
    RealDelete --> Menu
    Scan --> Menu
```

## D-day Calculation Detail Process

```mermaid
flowchart TB
    Start(["scan_d_day"])
    Draw["current_calendar"]
    GoalInput["scan_goal_day"]
    DateCheck{"Valid Future Date?"}
    Calc["d_day_calculation"]
    SameYear{"Same Year?"}
    SameYearCalc["goal yday minus current yday minus 1"]
    DiffYearCalc["goal days plus middle years plus leap correction"]
    NameInput["scan_d_day_name"]
    Preview["Show Preview"]
    Retouch{"name_retouch"}
    Save["change_d_day_json"]
    End(["Return Y"])

    Start --> Draw
    Draw --> GoalInput
    GoalInput --> DateCheck
    DateCheck -->|"N"| GoalInput
    DateCheck -->|"Y"| Calc
    Calc --> SameYear
    SameYear -->|"Y"| SameYearCalc
    SameYear -->|"N"| DiffYearCalc
    SameYearCalc --> NameInput
    DiffYearCalc --> NameInput
    NameInput --> Preview
    Preview --> Retouch
    Retouch -->|"Y Edit"| Draw
    Retouch -->|"N Confirm"| Save
    Save --> End
```

## Calendar Build Process

```mermaid
flowchart TB
    Start(["current_calendar or select_calendar"])
    Init["initialization"]
    Mode{"Caller Type"}
    SetCurrent["set_current_day"]
    CheckInputDate["check_day"]
    Header["start_ymd"]
    PrintCalendar["print_calendar"]
    CalcFirst["certain_day for first weekday"]
    CalcLast["last_day_calculation"]
    BuildLoop["Loop 6 by 7 cells"]
    CellType{"Cell Type"}
    LastMonth["Previous Month Cell"]
    NextMonth["Next Month Cell"]
    Today["Selected Date Cell"]
    ScheduleColor["Schedule Color Lookup"]
    Normal["Normal Date Cell"]
    Render["print_color_day or print_blue_day"]
    End(["Render Done"])

    Start --> Init
    Init --> Mode
    Mode -->|"current_calendar"| SetCurrent
    Mode -->|"select_calendar"| CheckInputDate
    SetCurrent --> Header
    CheckInputDate -->|"Y"| Header
    CheckInputDate -->|"N"| End
    Header --> PrintCalendar
    PrintCalendar --> CalcFirst
    CalcFirst --> CalcLast
    CalcLast --> BuildLoop
    BuildLoop --> CellType
    CellType -->|"Previous Month Area"| LastMonth
    CellType -->|"Next Month Area"| NextMonth
    CellType -->|"Selected Date"| Today
    CellType -->|"Current Month Date"| ScheduleColor
    ScheduleColor -->|"Has Schedule"| Render
    ScheduleColor -->|"No Schedule"| Normal
    LastMonth --> Render
    NextMonth --> Render
    Today --> Render
    Normal --> Render
    Render --> BuildLoop
    BuildLoop --> End
```

## JSON Process

```mermaid
flowchart TB
    Start(["JSON Function Call"])
    Parse["json_parse_file"]
    Root["json_value_get_object"]
    SelectArray{"Target Array"}
    ScheduleArray["schedule array"]
    DDayArray["d_day array"]
    Operation{"Operation Type"}
    Read["Read: check, print, call"]
    Create["Create: creat_schedule_json"]
    Update["Update: plus_content_json or change_d_day_json"]
    Delete["Delete: delete_schedule_json or delete_d_day_json"]
    Serialize["json_serialize_to_file_pretty"]
    Free["json_value_free"]
    End(["Return"])

    Start --> Parse
    Parse --> Root
    Root --> SelectArray
    SelectArray -->|"schedule"| ScheduleArray
    SelectArray -->|"d_day"| DDayArray
    ScheduleArray --> Operation
    DDayArray --> Operation
    Operation -->|"Read"| Read
    Operation -->|"Create"| Create
    Operation -->|"Update"| Update
    Operation -->|"Delete"| Delete
    Read --> Free
    Create --> Serialize
    Update --> Serialize
    Delete --> Serialize
    Serialize --> Free
    Free --> End
```

