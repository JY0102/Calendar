# DFD: Data Flow Diagram

Calendar project data flow diagrams.

## Level 0: Context Diagram

```mermaid
flowchart LR
    User["User"]
    Time["System Time"]
    App(("Calendar Console App"))
    Json[("calendar_json.json")]

    User -->|"menu key, date, schedule, color, dday name"| App
    Time -->|"current year, month, day, weekday, yday"| App
    App -->|"calendar screen, schedule list, dday, error message"| User
    App <-->|"read and write schedule, d_day"| Json
```

## Level 1: Overall Data Flow

```mermaid
flowchart TB
    User["User"]
    Time["System Time"]
    Console["P1 Console Interface"]
    Calendar["P2 Calendar Render"]
    Schedule["P3 Schedule Management"]
    DDay["P4 D-day Management"]
    JsonRepo["P5 JSON Repository"]
    Memory[("Global Memory State")]
    JsonFile[("calendar_json.json")]

    User -->|"getch and scanf input"| Console
    Console -->|"menu value 1, 2, ESC"| Schedule
    Console -->|"menu value 1, 2, ESC"| DDay
    Console -->|"screen refresh request"| Calendar

    Time -->|"time and localtime"| Calendar
    Calendar -->|"set current_ymd"| Memory
    Calendar -->|"set calendar cells"| Memory
    Calendar -->|"request schedule color by date"| JsonRepo
    JsonRepo -->|"text color id"| Calendar
    Calendar -->|"calendar UI data"| User

    Schedule -->|"date, content, text_color"| JsonRepo
    Schedule -->|"query selected date schedule"| JsonRepo
    JsonRepo -->|"exists flag, content list, color"| Schedule
    Schedule -->|"schedule result screen"| User

    DDay -->|"goal date and name"| Memory
    DDay -->|"request date calculation"| Calendar
    Calendar -->|"date validation and calculation data"| DDay
    DDay -->|"name, remaining day, check_value"| JsonRepo
    JsonRepo -->|"saved dday data"| DDay
    DDay -->|"dday result screen"| User

    JsonRepo <-->|"parse and serialize"| JsonFile
    JsonRepo -->|"root value, arrays, objects"| Memory
```

## Level 2: Schedule Data Flow

```mermaid
flowchart TB
    User["User"]
    ScheduleUI["P3.1 Schedule Menu"]
    DateCheck["P3.2 Date Validation"]
    ContentInput["P3.3 Content Input"]
    PrioritySort["P3.4 Priority Sort"]
    ScheduleStore["P3.5 Schedule Save or Delete"]
    CalendarCore["P2 Calendar and Date Core"]
    JsonRepo["P5 JSON Repository"]
    JsonFile[("calendar_json.json")]

    User -->|"select schedule management"| ScheduleUI
    ScheduleUI -->|"add or delete prompt"| User
    User -->|"year month day"| DateCheck
    DateCheck -->|"check_day request"| CalendarCore
    CalendarCore -->|"Y or N"| DateCheck

    DateCheck -->|"valid date string"| JsonRepo
    JsonRepo -->|"schedule exists flag"| ScheduleUI

    User -->|"content input, N to stop"| ContentInput
    User -->|"text color number"| ContentInput
    ContentInput -->|"content candidates"| PrioritySort
    PrioritySort -->|"sorted content by star priority"| ScheduleStore
    ScheduleStore -->|"create or append schedule"| JsonRepo
    ScheduleStore -->|"delete schedule"| JsonRepo
    JsonRepo <-->|"update schedule array"| JsonFile
    JsonRepo -->|"operation result"| ScheduleUI
    ScheduleUI -->|"success or failure message"| User
```

## Level 2: D-day Data Flow

```mermaid
flowchart TB
    User["User"]
    DDayUI["P4.1 D-day Menu"]
    GoalInput["P4.2 Goal Date Input"]
    GoalCheck["P4.3 Goal Date Validation"]
    DDayCalc["P4.4 Remaining Day Calculation"]
    NameInput["P4.5 D-day Name Input"]
    DDayStore["P4.6 D-day Save or Delete"]
    CalendarCore["P2 Calendar and Date Core"]
    Memory[("current_ymd, se_value, d_day_value")]
    JsonRepo["P5 JSON Repository"]
    JsonFile[("calendar_json.json")]

    User -->|"select add or delete dday"| DDayUI
    DDayUI -->|"add or edit"| GoalInput
    User -->|"goal year month day"| GoalInput
    GoalInput -->|"goal date"| GoalCheck
    GoalCheck -->|"check_day and check_before_day_for_current"| CalendarCore
    CalendarCore -->|"Y or N"| GoalCheck
    GoalCheck -->|"valid goal date"| DDayCalc
    DDayCalc <-->|"current date and goal date"| Memory
    DDayCalc -->|"remaining day"| Memory

    DDayCalc -->|"remaining day value"| NameInput
    User -->|"dday name"| NameInput
    NameInput -->|"name and day"| DDayStore
    DDayStore -->|"change dday json"| JsonRepo
    DDayUI -->|"delete confirm Y"| DDayStore
    DDayStore -->|"delete dday json"| JsonRepo
    JsonRepo <-->|"update d_day item"| JsonFile
```

## Level 2: Calendar Render Data Flow

```mermaid
flowchart TB
    Time["System Time"]
    Request["Screen Refresh Request"]
    Init["P2.1 Clear Screen and Array"]
    Current["P2.2 Set Current Date"]
    DateCalc["P2.3 Date Calculation"]
    CalendarBuild["P2.4 Build Calendar Cells"]
    ColorLookup["P2.5 Schedule Color Lookup"]
    Render["P2.6 Console Render"]
    JsonRepo["P5 JSON Repository"]
    Memory[("current_ymd and calendar cells")]
    JsonFile[("calendar_json.json")]
    User["User"]

    Request --> Init
    Init -->|"initialized cells"| Memory
    Time --> Current
    Current -->|"current_ymd"| Memory
    Memory --> DateCalc
    DateCalc -->|"first weekday, last day, previous month day"| CalendarBuild
    CalendarBuild -->|"date for each cell"| ColorLookup
    ColorLookup -->|"check text color json"| JsonRepo
    JsonRepo <-->|"query schedule"| JsonFile
    JsonRepo -->|"text color or none"| ColorLookup
    ColorLookup -->|"day color"| CalendarBuild
    CalendarBuild -->|"completed calendar cells"| Memory
    Memory --> Render
    Render -->|"calendar UI"| User
```

