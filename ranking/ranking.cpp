#include "ranking.h"

using namespace std;

// 성적 구조체
typedef struct __User {
    char name[32 + 1];
    int score;
} Data;
// 구조체 우선순위 큐 비교 함수
struct greater_Data {
    bool operator()(const Data &d1, const Data &d2) {
        return d1.score < d2.score;
    }
};

void init_test_data();
void draw_ranking();
char *get_ranking(int place);

void init_priority_queue() {
    /* init_test_data();
    // 임시로 10개의 더미 데이터 추가
*/
    draw_ranking();
}

// 임시로 10개의 더미 데이터 추가
void init_test_data() {
    int fd;

    // 파일 열기
    if ((fd = open("./ranking_board.dat", O_CREAT | O_WRONLY, S_IRWXU)) == -1) {
        // file Open error!
        exit(1);
    }
    Data *tempData = (Data *)malloc(sizeof(Data));
    char *temp = (char *)malloc(sizeof(char) * 2);

    // 10개의 임시데이터 추가
    for (int i = 1; i <= 10; i++) {
        memset(tempData->name, '\0', 33);
        strcat(tempData->name, "test");
        sprintf(temp, "%d", i);
        strcat(tempData->name, temp);
        tempData->score = i;
        write(fd, (Data *)tempData, sizeof(Data));
    }
}

// 핵심 구현 함수
void draw_ranking() {
    const int startpoint_x = 17;
    const int startpoint_y = 3;
    const int scoreprint_x = 9;
    int fd, rsize;
    int count = 0;
    int place = 1;

    priority_queue<Data, vector<Data>, greater_Data> pq; // 우선순위 큐 선언
    endwin();

    // 화면 설정
    WINDOW *score = newwin(31, 80, 0, 0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    wbkgd(score, COLOR_PAIR(1));
    wborder(score, '|', '|', '-', '-', '+', '+', '+', '+');

    // 로고 그리기
    mvwprintw(score, startpoint_y, startpoint_x,
              "###     #    #   #  #   #  ###  #   #   ### ");
    mvwprintw(score, startpoint_y + 1, startpoint_x,
              "#  #   # #   ##  #  #  #    #   ##  #  #    ");
    mvwprintw(score, startpoint_y + 2, startpoint_x,
              "###   #####  # # #  ###     #   # # #  # ###");
    mvwprintw(score, startpoint_y + 3, startpoint_x,
              "#  #  #   #  #  ##  #  #    #   #  ##  #   #");
    mvwprintw(score, startpoint_y + 4, startpoint_x,
              "#  #  #   #  #   #  #   #  ###  #   #   ### ");
    mvwprintw(score, startpoint_y + 7, 1,
              "----------------------------------------------------------------"
              "--------------");

    Data *readBuffer =
        (Data *)malloc(sizeof(Data)); // 파일에서 데이터를 읽을 버퍼
    // 버퍼 초기화
    memset(readBuffer->name, '\0', 33);
    readBuffer->score = 0;

    // 파일 열기
    fd = open("./ranking_board.dat", O_RDONLY, 0644);

    // 파일에서 읽고 우선순위큐에 삽입
    while ((rsize = read(fd, (Data *)readBuffer, sizeof(Data))) > 0) {
        pq.push(*readBuffer);
    }

    // 우선순위큐에서 하나씩 꺼내서 읽어 다음을 수행
    while (!pq.empty()) {
        const char *pop_name = pq.top().name; // 이름 꺼내기
        int pop_score = pq.top().score;       // 점수 거내기
        pq.pop();
        char *rank = get_ranking(place); // 순위 문자열 받아오기

        switch (place) { // 순위에 따라 다르게 출력 (1, 2, 3 위는 상단
                         // 4 ~ 8 위는 아래)
        // 1위
        case 1:
            mvwprintw(score, 12, 38, "%s", pop_name);
            mvwprintw(score, 13, 38, "%d", pop_score);
            mvwprintw(score, 15, 35, "*** %s ***", rank);
            break;
        // 2위
        case 2:
            mvwprintw(score, 15, 15, "%s", pop_name);
            mvwprintw(score, 16, 15, "%d", pop_score);
            mvwprintw(score, 18, 12, "** %s **", rank);
            break;
        // 3위
        case 3:
            mvwprintw(score, 15, 62, "%s", pop_name);
            mvwprintw(score, 16, 62, "%d", pop_score);
            mvwprintw(score, 18, 60, "* %s *", rank);
            break;
        // 4~8위
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            mvwprintw(score, 23, scoreprint_x + (place - 4) * 14, "%s",
                      pop_name);
            mvwprintw(score, 24, scoreprint_x + (place - 4) * 14, "%d",
                      pop_score);
            mvwprintw(score, 26, scoreprint_x + (place - 4) * 14, "%s", rank);
            break;
        // 그 외는 출력하지 않음.
        default:
            break;
        }
        place++;
        count++;
    }
    // 파일에 저장되어있는 모든 점수의 개수
    mvwprintw(score, 29, 60, "Records count: %d", count);
    mvwprintw(score, 29, 2, "Press any key to exit");

    wrefresh(score);
}

// 등수 (1st, 2nd, 3rd, 4th...)
char *get_ranking(int place) {
    char *ranking = (char *)malloc(sizeof(char) * 4);
    memset(ranking, '\0', sizeof(ranking));
    sprintf(ranking, "%d", place);
    switch (place) {
    case 1:
        strcat(ranking, "st");
        break;
    case 2:
        strcat(ranking, "nd");
        break;
    case 3:
        strcat(ranking, "rd");
        break;
    default:
        strcat(ranking, "th");
    }
    return ranking;
}

/* 랭킹 파일에 이름과 점수를 추가하는 함수 */
void append_ranking(char *name, int score) {
    int fd;

    // 파일 열기
    if ((fd = open("./ranking_board.dat", O_CREAT | O_WRONLY | O_APPEND,
                   S_IRWXU)) == -1) {
        // file Open error!
        exit(1);
    }
    Data *tempData = (Data *)malloc(sizeof(Data));

    memset(tempData->name, '\0', 33);
    strcat(tempData->name, name);
    tempData->score = score;
    write(fd, (Data *)tempData, sizeof(Data));
}

/* 파일로부터 최고점수를 반환하는 함수 */
int get_best_score() {
    int fd, rsize;
    int best_score = 0;

    Data *readBuffer =
        (Data *)malloc(sizeof(Data)); // 파일에서 데이터를 읽을 버퍼
    // 버퍼 초기화
    memset(readBuffer->name, '\0', 33);
    readBuffer->score = 0;

    // 파일 열기
    fd = open("./ranking_board.dat", O_RDONLY, 0644);

    // 파일에서 가장 큰 score를 받는다
    while ((rsize = read(fd, (Data *)readBuffer, sizeof(Data))) > 0) {
        if (readBuffer->score > best_score)
            best_score = readBuffer->score;
    }

    return best_score;
}
