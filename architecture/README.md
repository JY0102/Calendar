# Calendar Architecture Diagrams

이 디렉토리는 Calendar 콘솔 프로젝트의 주요 구조와 기능 흐름을 Mermaid 다이어그램으로 정리한 문서 모음이다.

이 프로젝트는 순수 C 언어 기반 콘솔 프로그램이며, 다음 기능을 중심으로 구성되어 있다.

- 현재 날짜 기준 달력 출력
- 날짜 이동 및 특정 날짜 조회
- 일정 추가/삭제/조회
- D-day 목표 날짜 입력 및 남은 일수 계산
- `calendar_json.json` 파일을 통한 데이터 저장
- 콘솔 좌표 출력과 색상 표시

## 문서 목록

- [전체적인 흐름도](./overall-flow.md)
- [Interface 흐름](./interface-flow.md)
- [일정 관리](./schedule-management.md)
- [목표날짜 남은일 표시 및 계산](./d-day-calculation.md)
- [달력 생성 및 UI 표시 흐름](./calendar-ui-flow.md)
- [JSON 데이터 저장 흐름](./json-data-flow.md)
- [DFD: Data Flow Diagram](./dfd.md)
- [DPD: Data Process Diagram](./dpd.md)

## DFD와 DPD 설명

### DFD란?

DFD는 Data Flow Diagram의 약자이다.

프로그램에서 데이터가 어디서 들어오고, 어떤 기능을 지나고, 어디에 저장되거나 출력되는지 보여주는 다이어그램이다.

C 언어를 처음 배우는 입장에서는 DFD를 다음처럼 보면 된다.

- 사용자가 입력한 값이 어떤 함수로 전달되는지
- 함수가 처리한 결과가 전역 변수에 저장되는지
- JSON 파일에 저장되는 데이터가 무엇인지
- 저장된 데이터가 다시 화면 출력에 어떻게 사용되는지

이 프로젝트의 DFD에서는 다음 데이터 흐름을 중심으로 정리했다.

- 사용자 입력: 메뉴 번호, 날짜, 일정 내용, 색상, D-day 이름
- 시스템 시간: 현재 연도, 월, 일, 요일, yday
- 메모리 상태: `current_ymd`, `calendar`, `d_day_value`, `se_value`
- 파일 저장소: `calendar_json.json`의 `schedule`, `d_day`

즉, DFD는 "데이터가 움직이는 길"을 보는 문서이다.

### DPD란?

DPD는 Data Process Diagram 또는 Process Decomposition 관점의 다이어그램이다.

DFD가 데이터 이동을 중심으로 본다면, DPD는 기능이 어떤 처리 단계로 나뉘고 함수들이 어떤 순서로 실행되는지 보여준다.

C 언어를 배우는 입장에서는 DPD를 함수 호출 흐름도처럼 보면 이해하기 쉽다.

- 사각형은 처리 단계 또는 함수
- 마름모는 `if`, `switch`, 메뉴 선택 같은 분기
- 화살표는 다음 실행 흐름
- 시작/종료 노드는 기능의 진입점과 종료점

이 프로젝트의 DPD에서는 다음 흐름을 중심으로 정리했다.

- `main`에서 `select_function`으로 들어가는 전체 실행 흐름
- 메인 메뉴에서 D-day 또는 일정 기능으로 이동하는 흐름
- 일정 추가/삭제 처리 단계
- D-day 목표일 입력, 계산, 저장 처리 단계
- 달력 생성과 콘솔 출력 처리 단계
- JSON 파일 읽기, 수정, 저장, 해제 처리 단계

즉, DPD는 "프로그램이 어떤 순서로 일을 처리하는지"를 보는 문서이다.

## 코드 기준 모듈

- `calendar.c`: 프로그램 진입점, 메인 메뉴 루프
- `all_function.h`: 현재 날짜 설정, 날짜 계산, 달력 생성/출력, 공통 UI 유틸
- `schedule_all_function.h`: 일정 조회, 달력 이동, 일정 추가/삭제 인터페이스
- `d_day_all_function.h`: D-day 입력, 계산, 저장/삭제 인터페이스
- `cal_json.h`: `calendar_json.json` 파일 입출력, schedule/d_day 데이터 접근
- `parson.c`, `parson.h`: JSON 파싱 라이브러리

## 읽는 순서 추천

C 언어를 배우는 중이라면 아래 순서로 보는 것이 가장 이해하기 쉽다.

1. [전체적인 흐름도](./overall-flow.md)
2. [Interface 흐름](./interface-flow.md)
3. [DPD: Data Process Diagram](./dpd.md)
4. [DFD: Data Flow Diagram](./dfd.md)
5. [달력 생성 및 UI 표시 흐름](./calendar-ui-flow.md)
6. [일정 관리](./schedule-management.md)
7. [목표날짜 남은일 표시 및 계산](./d-day-calculation.md)
8. [JSON 데이터 저장 흐름](./json-data-flow.md)

