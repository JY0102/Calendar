# Calendar Architecture Diagrams

이 디렉토리는 Calendar 콘솔 프로젝트의 주요 기능 흐름을 Mermaid 다이어그램으로 정리한다.

## 문서 목록

- [전체적인 흐름도](./overall-flow.md)
- [Interface 흐름](./interface-flow.md)
- [일정 관리](./schedule-management.md)
- [목표날짜 남은일 표시 및 계산](./d-day-calculation.md)
- [달력 생성 및 UI 표시 흐름](./calendar-ui-flow.md)
- [JSON 데이터 저장 흐름](./json-data-flow.md)

## 코드 기준 모듈

- `calendar.c`: 프로그램 진입점, 메인 메뉴 루프
- `all_function.h`: 현재 날짜 설정, 날짜 계산, 달력 생성/출력, 공통 UI 유틸
- `schedule_all_function.h`: 일정 조회, 달력 이동, 일정 추가/삭제 인터페이스
- `d_day_all_function.h`: D-day 입력, 계산, 저장/삭제 인터페이스
- `cal_json.h`: `calendar_json.json` 파일 입출력, schedule/d_day 데이터 접근
- `parson.c`, `parson.h`: JSON 파싱 라이브러리

