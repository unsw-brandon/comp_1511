// CS Pacman!
//
// This program was written by [Brandon Chikandiwa] (z5495844)
// Started on [15 October 2023] stopped [23 October 2023]

// This is an implementation of a console version of the popular game pacman!
// The game is completed with various features that would be found in the
// original pacman game, just without the usual user interface/experience.
// The game starts of by asking you for the coordinates to place your
// pacman/player within an 8 x 10 grid. After wards you can place features
// such as bananas, apples, walls, power ups and of course ghosts!
// The game also allows you to create multiple floors! Which can be navigated,
// by both you and the enemies!

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Provided constants
#define NUM_ROWS 8
#define NUM_COLS 10
#define NUM_FLOORS 5

#define TRUE 1
#define FALSE 0

// TODO: put your constants here
#define MAX_ENEMIES 79

// Provided enums
enum entity {
    EMPTY_ENTITY,
    WALL,
    DOT,
    APPLE,
    BANANA,
    POWER_UP,
    STAIRCASE_UP,
    STAIRCASE_DOWN,

};

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    OTHER
};

// @todo: Make program efficient using enumatarated commands
enum commands {
    w,
    a,
    s,
    d,
    u,
    l,
    r,
    p,
    S,
    G,
    B,
    A,
    W,
    P
};

// Provided structs
struct enemy {
    enum direction move_direction;
    int is_present;
    int steps;
    int steps_done;
    int is_scared;
};
struct data {
    int *row;
    int *col;
    int *flo;
    int *points;
};

struct tile {
    enum entity entity;
    struct enemy enemy;
    int floor_present;
};

// TODO: Put your structs here

// @todo: Make program efficient using struct data which is common for most
// of my functions.

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your function prototypes here

// Stage 1

void prep_game(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int pacman_row, int pacman_col, int *flo_count);
void add_dots(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS]);
int is_wall_valid(int start_row, int start_col, int end_row, int end_col, struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS]);
void add_wall(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int start_row, int start_col, int end_row, int end_col, int is_wall_valid, int flo);
// Stage 2
void play_game(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman, int *flo_count, struct data prev);
void pacman_direction_command(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], enum direction command, struct data pacman, int *flo_count, struct data prev);
void perform_other_command(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], char command, struct data pacman);
enum direction parse_pacman_direction_command(char command);
void check_collisions(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman);
void check_win(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman, int *flo_count);
void apple_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman);
void banana_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman);
void dot_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman);
void append_points(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int i, int j, int pacman_flo, int *points);
void stair_up_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman);
void stair_down_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman);
// Stage 3

int has_won(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman, int *flo_count);
enum direction parse_ghost_command(char command);
void move_ghosts(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman);
void check_ghost_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int ghost_row, int ghost_col, int ghost_flo, struct data pacman, int ghost_row_new, int ghost_col_new);
enum direction parse_ghost_direction(enum direction ghost_direction);
void ghost_collision(int *points);
void ghost_collision_a(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int ghost_row, int ghost_col, int ghost_flo, struct data pacman);
void enemy_direction(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int ghost_row, int ghost_col, int ghost_flo, int *ghost_row_new, int *ghost_col_new);
void power_up_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman);
void ghost_scared_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int ghost_row, int ghost_col, int ghost_flo, struct data pacman);
void get_greatest(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                  int ghost_row, int ghost_col, int ghost_flo,
                  struct data pacman,
                  int *ghost_row_new, int *ghost_col_new);
int hits_wall(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int row, int col, int flo);
////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void initialise_map(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS]);
void print_map(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int pacman_row, int pacman_col, int pacman_flo);

int main(void) {
    struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS];
    initialise_map(map);

    printf("Welcome to cs_pacman!\n");
    int pacman_row, pacman_col;
    int pacman_flo = 0;
    int flo_count = 0;
    int points = 0;

    int prev_row;
    int prev_col;
    int prev_flo;
    struct data prev = {&prev_row, &prev_col, &prev_flo, &points};
    struct data pacman = {&pacman_row, &pacman_col, &pacman_flo, &points};

    printf("Enter Pacman's starting coordinates: ");
    scanf("%d %d", &pacman_row, &pacman_col);
    print_map(map, pacman_row, pacman_col, 0);

    prep_game(map, pacman_row, pacman_col, &flo_count);
    play_game(map, pacman, &flo_count, prev);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your functions here

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void initialise_map(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS]) {
    for (size_t flo = 0; flo < NUM_FLOORS; flo++) {
        for (int row = 0; row < NUM_ROWS; row++) {
            for (int col = 0; col < NUM_COLS; col++) {
                map[row][col][flo].entity = EMPTY_ENTITY;
                map[row][col][flo].enemy.move_direction = LEFT;
                map[row][col][flo].enemy.is_present = FALSE;
                map[row][col][flo].floor_present = 0;
            }
        }
    }
}

void print_map(
    struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
    int pacman_row,
    int pacman_col,
    int pacman_flo) {
    for (int i = 0; i < NUM_COLS; i++) {
        printf("----");
    }
    printf("-\n");
    for (int row = 0; row < NUM_ROWS; row++) {
        printf("|");
        for (int col = 0; col < NUM_COLS; col++) {
            if (map[row][col][pacman_flo].entity == WALL) {
                printf("|||");
            } else if (row == pacman_row && col == pacman_col) {
                printf("^_^");
            } else if (map[row][col][pacman_flo].enemy.is_present == TRUE) {
                printf("O_O");
            } else if (map[row][col][pacman_flo].entity == DOT) {
                printf(" . ");
            } else if (map[row][col][pacman_flo].entity == APPLE) {
                printf(" a ");
            } else if (map[row][col][pacman_flo].entity == BANANA) {
                printf(" b ");
            } else if (map[row][col][pacman_flo].entity == POWER_UP) {
                printf("<o>");
            } else if (map[row][col][pacman_flo].entity == STAIRCASE_UP) {
                printf("__/");
            } else if (map[row][col][pacman_flo].entity == STAIRCASE_DOWN) {
                printf("\\__");
            } else {
                printf("   ");
            }

            printf("|");
        }
        printf("\n");
        for (int i = 0; i < NUM_COLS; i++) {
            printf("----");
        }
        printf("-\n");
    }
}

void add_wall(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
              int start_row, int start_col, int end_row, int end_col,
              int flo, int is_wall_valid) {
    if (is_wall_valid == 0) {
        for (int i = start_row; i < end_row + 1; i++) {
            for (int j = start_col; j < end_col + 1; j++) {
                map[i][j][flo].entity = WALL;
            }
        }
    } else if (is_wall_valid == 1) {
        if (start_row < 0) {
            start_row = 0;
        } else if (end_row > NUM_ROWS) {
            end_row = NUM_ROWS - 1;
        }
        if (end_row < 0) {
            end_row = 0;
        } else if (start_row > NUM_ROWS) {
            start_row = NUM_ROWS - 1;
        }

        for (int i = start_row; i < NUM_ROWS; i++) {
            map[i][start_col][flo].entity = WALL;
        }
    } else if (is_wall_valid == 2) {
        if (start_col < 0) {
            start_col = 0;
        } else if (end_col > NUM_COLS) {
            end_col = NUM_COLS - 1;
        }

        if (end_col < 0) {
            end_col = 0;
        } else if (start_col > NUM_COLS) {
            start_col = NUM_COLS - 1;
        }

        for (int i = start_col; i < NUM_COLS; i++) {
            map[start_row][i][flo].entity = WALL;
        }
    } else if (is_wall_valid == 3) {

    } else {
        printf("Given wall is not horizontal or vertical!\n");
    }
}

void prep_game(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int pacman_row,
               int pacman_col, int *flo_count) {
    printf("Create the level: \n");

    char first_letter;
    scanf(" %c", &first_letter);

    while (first_letter == 'S') {
        if (first_letter == 'W') {
            int start_row, start_col, end_row, end_col;
            scanf("%d %d %d %d", &start_row, &start_col, &end_row, &end_col);
            int wall_valid = is_wall_valid(start_row, start_col,
                                              end_row, end_col, map);
            if (wall_valid == 0) {
                add_wall(map, start_row, start_col, end_row, end_col, *flo_count, 0);
            } else if (wall_valid == 1) {
                add_wall(map, start_row, start_col, end_row, end_col, *flo_count, 1);
            } else if (wall_valid == 2) {
                add_wall(map, start_row, start_col, end_row, end_col, *flo_count, 2);
            } else if (wall_valid == 3) {
                add_wall(map, start_row, start_col, end_row, end_col, *flo_count, 3);
            } else {
                add_wall(map, start_row, start_col, end_row, end_col, *flo_count, -1);
            }

            start_row = 0;
            start_col = 0;
            end_row = 0;
            end_col = 0;

        } else if (first_letter == 'A') {
            int apple_row, apple_col;
            scanf("%d %d", &apple_row, &apple_col);
            map[apple_row][apple_col][*flo_count].entity = APPLE;
        } else if (first_letter == 'B') {
            int banana_row, banana_col;
            scanf("%d %d", &banana_row, &banana_col);
            map[banana_row][banana_col][*flo_count].entity = BANANA;
        } else if (first_letter == 'G') {
            int ghost_row, ghost_col;
            char ghost_direction;
            scanf("%d %d %c", &ghost_row, &ghost_col, &ghost_direction);
            map[ghost_row][ghost_col][*flo_count].enemy.is_present = TRUE;
            map[ghost_row][ghost_col][*flo_count].enemy.steps = 10;
            map[ghost_row][ghost_col][*flo_count].enemy.steps_done = 10;
            map[ghost_row][ghost_col][*flo_count].enemy.is_scared = FALSE;
            map[ghost_row][ghost_col][*flo_count].enemy.move_direction =
                parse_ghost_command(ghost_direction);

        } else if (first_letter == 'P') {
            int power_up_row, power_up_col;
            scanf("%d %d", &power_up_row, &power_up_col);
            map[power_up_row][power_up_col][*flo_count].entity = POWER_UP;

        } else if (first_letter == 'F') {
            int floor_row, floor_col;
            scanf("%d %d", &floor_row, &floor_col);
            map[floor_row][floor_col][*flo_count].entity = STAIRCASE_UP;
            map[floor_row][floor_col][*flo_count].floor_present = STAIRCASE_UP;
            if (*flo_count < 5) {
                printf("FLO COUNT BEFORE: %d\n", *flo_count);
                (*flo_count)++;
                printf("FLO COUNT AFTERa: %d\n", *flo_count);
                map[floor_row][floor_col][*flo_count].entity = STAIRCASE_DOWN;
                map[floor_row][floor_col][*flo_count].floor_present = STAIRCASE_DOWN;
            }
        }

        scanf(" %c", &first_letter);
    }

    add_dots(map);
    print_map(map, pacman_row, pacman_col, 0);
}

int is_wall_valid(int start_row, int start_col, int end_row, int end_col,
                  struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS]) {

    if (start_row < 0 && end_row < 0) {
        // COL OR ROW INVALID
        return 3;
    } else if (start_col < 0 && end_col < 0) {
        return 3;
    } else if ((start_row > NUM_ROWS && end_row > NUM_ROWS) ||
               (start_col > NUM_COLS && end_col > NUM_COLS)) {
        // COL OR ROW INVALID
        return 3;
    } else if (start_row != end_row && start_col != end_col) {
        // COL OR ROW INVALID
        return -1;
    } else if (start_row < 0 || end_row > NUM_ROWS) {
        // COL VALID, ROW EXCEEDS NUM_ROWS OR ROW BELOW 0
        return 1;
    } else if (start_col < 0 || end_col > NUM_COLS) {
        // ROW VALID, COL EXCEEDS NUM_COLS OR COL BELOW 0
        return 2;
    } else {
        // ROW AND COL VALID
        return 0;
    }
}

void add_dots(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS]) {
    for (int k = 0; k < NUM_FLOORS; k++) {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (map[i][j][k].entity == EMPTY_ENTITY) {
                    map[i][j][k].entity = DOT;
                }
            }
        }
    }
}
// Stage 2

void play_game(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman, int *flo_count, struct data prev) {

    char command;
    printf("Enter command: ");
    int result_code = scanf(" %c", &command);

    while (result_code == 1) {

        enum direction parsed_command = parse_pacman_direction_command(command);

        if (parsed_command == OTHER) {
            perform_other_command(map, command, pacman);
        } else {
            pacman_direction_command(map, parsed_command, pacman, flo_count, prev);
        }

        printf("Enter command: ");
        result_code = scanf(" %c", &command);
    }
}

enum direction parse_pacman_direction_command(char command) {
    if (command == 'w') {
        return UP;
    } else if (command == 's') {
        return DOWN;
    } else if (command == 'a') {
        return LEFT;
    } else if (command == 'd') {
        return RIGHT;
    } else {
        return OTHER;
    }
}

void pacman_direction_command(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                              enum direction command, struct data pacman, int *flo_count, struct data prev) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *pacman_flo = pacman.flo;

    if (map[*pacman_row][*pacman_col][*pacman_flo].floor_present > 0) {
        map[*(prev.row)][*(prev.col)][*(prev.flo)].entity = map[*pacman_row][*pacman_col][*pacman_flo].floor_present;
    }

    if (command == UP) {
        if (*pacman_row - 1 < 0) {
            if (map[NUM_ROWS - 1][*pacman_col][*pacman_flo].entity != WALL) {
                *pacman_row = NUM_ROWS - 1;
            }
        } else {
            if (map[(*pacman_row) - 1][*pacman_col][*pacman_flo].entity != WALL) {
                (*pacman_row)--;
            }
        }
    } else if (command == DOWN) {
        if (*pacman_row + 1 > NUM_ROWS - 1) {
            if (map[0][*pacman_col][*pacman_flo].entity != WALL) {
                *pacman_row = 0;
            }
        } else {
            if (map[(*pacman_row) + 1][*pacman_col][*pacman_flo].entity != WALL) {
                (*pacman_row)++;
            }
        }
    } else if (command == LEFT) {
        if (*pacman_col - 1 < 0) {
            if (map[*pacman_row][NUM_COLS - 1][*pacman_flo].entity != WALL) {
                *pacman_col = NUM_COLS - 1;
            }
        } else {
            if (map[*pacman_row][(*pacman_col) - 1][*pacman_flo].entity != WALL) {
                (*pacman_col)--;
            }
        }
    } else if (command == RIGHT) {
        if (*pacman_col + 1 > NUM_COLS - 1) {

            if (map[*pacman_row][0][*pacman_flo].entity != WALL) {
                *pacman_col = 0;
            }
        } else {
            if (map[*pacman_row][(*pacman_col) + 1][*pacman_flo].entity != WALL) {
                (*pacman_col)++;
            }
        }
    }

    *prev.row = *pacman_row;
    *prev.col = *pacman_col;
    *prev.flo = *pacman_flo;

    check_collisions(map, pacman);
    check_win(map, pacman, flo_count);
    move_ghosts(map, pacman);

    print_map(map, *pacman_row, *pacman_col, *pacman_flo);
}

void check_win(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
               struct data pacman, int *flo_count) {
    int *points = pacman.points;

    if (has_won(map, pacman, flo_count) == 1) {
        printf("Game won! You got %d points.\n", *points);
        exit(0);
    }
}
void check_collisions(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                      struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *pacman_flo = pacman.flo;
    int *points = pacman.points;

    enum entity prev_entity = map[*pacman_row][*pacman_col][*pacman_flo].entity;

    if (prev_entity == APPLE) {
        apple_collision(map, pacman);

    } else if (prev_entity == BANANA) {
        banana_collision(map, pacman);

    } else if (prev_entity == DOT) {
        dot_collision(map, pacman);

    } else if (prev_entity == POWER_UP) {
        power_up_collision(map, pacman);

    } else if (prev_entity == STAIRCASE_UP) {
        stair_up_collision(map, pacman);

    } else if (prev_entity == STAIRCASE_DOWN) {
        stair_down_collision(map, pacman);
    }

    if (map[*pacman_row][*pacman_col][*pacman_flo].enemy.is_present == 1 &&
        map[*pacman_row][*pacman_col][*pacman_flo].enemy.is_scared > 0) {
        append_points(map, *pacman_row, *pacman_col, *pacman_flo, points);

    } else if (map[*pacman_row][*pacman_col][*pacman_flo].enemy.is_present == 1) {
        append_points(map, *pacman_row, *pacman_col, *pacman_flo, points);
        ghost_collision(points);
    }
}
void stair_up_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                        struct data pacman) {

    int *pacman_flo = pacman.flo;

    (*pacman_flo)++;
}

void stair_down_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                          struct data pacman) {

    int *pacman_flo = pacman.flo;

    (*pacman_flo)--;
}

void perform_other_command(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                           char command, struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *pacman_flo = pacman.flo;
    int *points = pacman.points;

    if (command == 'p') {
        printf("You have %d points!\n", *points);
    }

    print_map(map, *pacman_row, *pacman_col, *pacman_flo);
}

void apple_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                     struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *pacman_flo = pacman.flo;
    int *points = pacman.points;

    int start_row = (*pacman_row) - 2;
    int end_row = (*pacman_row) + 3;
    int start_col = (*pacman_col) - 2;
    int end_col = (*pacman_col) + 3;

    if (start_row < 0) {
        start_row = 0;
    }

    if (end_row > NUM_ROWS - 1) {
        end_row = NUM_ROWS;
    }

    if (start_col < 0) {
        start_col = 0;
    }

    if (end_col > NUM_COLS - 1) {
        end_col = NUM_COLS;
    }

    for (int i = start_row; i < end_row; i++) {
        for (int j = start_col; j < end_col; j++) {
            append_points(map, i, j, *pacman_flo, points);
        }
    }
}

void banana_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                      struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *pacman_flo = pacman.flo;
    int *points = pacman.points;

    int start_row = 0;
    int end_row = NUM_ROWS;
    int start_col = 0;
    int end_col = NUM_COLS;

    for (int i = start_row; i < end_row; i++) {
        if (map[i][*pacman_col][*pacman_flo].entity == WALL && (*pacman_row) < i) {
            end_row = i - 1;
        } else if (map[i][*pacman_col][*pacman_flo].entity == WALL && (*pacman_row) > i) {
            start_row = i + 1;
        }
    }

    for (int i = start_col; i < end_col; i++) {
        if (map[*pacman_row][i][*pacman_flo].entity == WALL && (*pacman_col) < i) {
            end_col = i - 1;
        } else if (map[*pacman_row][i][*pacman_flo].entity == WALL && (*pacman_col) > i) {
            start_col = i + 1;
        }
    }

    for (int i = start_row; i < end_row; i++) {
        append_points(map, i, *pacman_col, *pacman_flo, points);
    }

    for (int i = start_col; i < end_col; i++) {
        append_points(map, *pacman_row, i, *pacman_flo, points);
    }
}

void dot_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                   struct data pacman) {
    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *pacman_flo = pacman.flo;
    int *points = pacman.points;
    append_points(map, *pacman_row, *pacman_col, *pacman_flo, points);
}

void ghost_collision(int *points) {

    printf("Game over! You got %d points.\n", *points);
    exit(0);
}

void power_up_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                        struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *pacman_flo = pacman.flo;
    int *points = pacman.points;

    append_points(map, *pacman_row, *pacman_col, *pacman_flo, points);

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (map[i][j][*pacman_flo].enemy.is_present == TRUE) {
                map[i][j][*pacman_flo].enemy.is_scared += 10;
            }
        }
    }
}

void append_points(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                   int i, int j, int pacman_flo, int *points) {

    if (map[i][j][pacman_flo].enemy.is_present == TRUE && map[i][j][pacman_flo].enemy.is_scared > FALSE) {
        *points += 100;
        map[i][j][pacman_flo].enemy.is_present = FALSE;
    }
    if (map[i][j][pacman_flo].entity == DOT) {
        *points += 10;
    } else if (map[i][j][pacman_flo].entity == APPLE) {
        *points += 20;
    } else if (map[i][j][pacman_flo].entity == BANANA) {
        *points += 20;
    } else if (map[i][j][pacman_flo].entity == POWER_UP) {
        *points += 50;
    }

    map[i][j][pacman_flo].entity = EMPTY_ENTITY;
}

// Stage 3

int has_won(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], struct data pacman, int *flo_count) {

    int has_won = 1;

    for (int k = 0; k < *flo_count; k++) {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (map[i][j][k].entity == DOT) {
                    return 0;
                }
            }
        }
    }

    return has_won;
}

enum direction parse_ghost_command(char command) {
    if (command == 'u') {
        return UP;
    } else if (command == 'd') {
        return DOWN;
    } else if (command == 'l') {
        return LEFT;
    } else if (command == 'r') {
        return RIGHT;
    } else {
        return OTHER;
    }
}

void move_ghost(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                int ghost_row, int ghost_col, int ghost_flo,
                struct data pacman) {

    if (map[ghost_row][ghost_col][ghost_flo].enemy.is_scared > 0) {
        map[ghost_row][ghost_col][ghost_flo].enemy.is_scared -= 1;
        ghost_scared_collision(map, ghost_row, ghost_col, ghost_flo,
                               pacman);
    } else {

        ghost_collision_a(map, ghost_row, ghost_col, ghost_flo,
                          pacman);
    }
}

void move_ghosts(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                 struct data pacman) {

    int enemies_count = 0;
    int enemies[MAX_ENEMIES][3];

    for (int k = 0; k < NUM_FLOORS; k++) {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (map[i][j][k].enemy.is_present == TRUE) {
                    enemies[enemies_count][0] = i;
                    enemies[enemies_count][1] = j;
                    enemies[enemies_count][2] = k;
                    enemies_count++;
                }
            }
        }
    }

    for (int i = 0; i < enemies_count; i++) {
        move_ghost(map, enemies[i][0], enemies[i][1], enemies[i][2],
                   pacman);
    }
}

void check_ghost_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                           int ghost_row, int ghost_col, int ghost_flo,
                           struct data pacman,
                           int ghost_row_new, int ghost_col_new) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *pacman_flo = pacman.flo;
    int *points = pacman.points;

    if (map[ghost_row][ghost_col][ghost_flo].enemy.is_scared == 0) {
        if (ghost_row_new == *pacman_row && ghost_col_new == *pacman_col) {
            append_points(map, *pacman_row, *pacman_col, *pacman_flo, points);
            ghost_collision(points);
        } else {
            append_points(map, *pacman_row, *pacman_col, *pacman_flo, points);
        }
    } else {
        append_points(map, *pacman_row, *pacman_col, *pacman_flo, points);
    }
}

void ghost_collision_a(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                       int ghost_row, int ghost_col, int ghost_flo,
                       struct data pacman) {

    int ghost_row_new = ghost_row;
    int ghost_col_new = ghost_col;

    if (map[ghost_row][ghost_col][ghost_flo].enemy.steps_done <= 0) {
        if (map[ghost_row][ghost_col][ghost_flo].enemy.steps <= 2) {
            map[ghost_row][ghost_col][ghost_flo].enemy.steps = 10;
        } else {
            map[ghost_row][ghost_col][ghost_flo].enemy.steps -= 2;
        }
        map[ghost_row][ghost_col][ghost_flo].enemy.steps_done =
            map[ghost_row][ghost_col][ghost_flo].enemy.steps - 1;
        map[ghost_row][ghost_col][ghost_flo].enemy.move_direction =
            parse_ghost_direction(map[ghost_row][ghost_col][ghost_flo]
                                      .enemy.move_direction);
    } else {
        map[ghost_row][ghost_col][ghost_flo].enemy.steps_done -= 1;
    }

    enemy_direction(map, ghost_row, ghost_col, ghost_flo, &ghost_row_new, &ghost_col_new);

    if (map[ghost_row_new][ghost_col_new][ghost_flo].entity == WALL ||
        map[ghost_row_new][ghost_col_new][ghost_flo].enemy.is_present == TRUE) {
        map[ghost_row][ghost_col][ghost_flo].enemy.steps -= 2;
        map[ghost_row][ghost_col][ghost_flo].enemy.steps_done =
            map[ghost_row][ghost_col][ghost_flo].enemy.steps;
        map[ghost_row][ghost_col][ghost_flo].enemy.move_direction =
            parse_ghost_direction(map[ghost_row][ghost_col][ghost_flo]
                                      .enemy.move_direction);
    } else {
        struct enemy temp = map[ghost_row][ghost_col][ghost_flo].enemy;
        map[ghost_row][ghost_col][ghost_flo].enemy.is_present = FALSE;
        check_ghost_collision(map, ghost_row, ghost_col, ghost_flo,
                              pacman, ghost_row_new, ghost_col_new);
        map[ghost_row_new][ghost_col_new][ghost_flo].enemy = temp;
    }
}

void enemy_direction(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                     int ghost_row, int ghost_col, int ghost_flo,
                     int *ghost_row_new, int *ghost_col_new) {
    if (map[ghost_row][ghost_col][ghost_flo].enemy.move_direction == UP) {
        (*ghost_row_new)--;

        if (*ghost_row_new < 0) {
            *ghost_row_new = NUM_ROWS - 1;
        } else if (*ghost_row_new > NUM_ROWS - 1) {
            *ghost_row_new = 0;
        }
    } else if (map[ghost_row][ghost_col][ghost_flo].enemy.move_direction == DOWN) {
        (*ghost_row_new)++;

        if (*ghost_row_new < 0) {
            *ghost_row_new = NUM_ROWS - 1;
        } else if (*ghost_row_new > NUM_ROWS - 1) {
            *ghost_row_new = 0;
        }
    } else if (map[ghost_row][ghost_col][ghost_flo].enemy.move_direction == LEFT) {
        (*ghost_col_new)--;

        if (*ghost_col_new < 0) {
            *ghost_col_new = NUM_COLS - 1;
        } else if (*ghost_col_new > NUM_COLS - 1) {
            *ghost_col_new = 0;
        }
    } else if (map[ghost_row][ghost_col][ghost_flo].enemy.move_direction == RIGHT) {
        (*ghost_col_new)++;

        if (*ghost_col_new < 0) {
            *ghost_col_new = NUM_COLS - 1;
        } else if (*ghost_col_new > NUM_COLS - 1) {
            *ghost_col_new = 0;
        }
    }
}

void enemy_scared_direction(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                            int ghost_row, int ghost_col,
                            int *ghost_row_new, int *ghost_col_new,
                            enum direction move_direction) {
    if (move_direction == UP) {
        (*ghost_row_new)--;

        if (*ghost_row_new < 0) {
            *ghost_row_new = NUM_ROWS - 1;
        } else if (*ghost_row_new > NUM_ROWS - 1) {
            *ghost_row_new = 0;
        }
    } else if (move_direction == DOWN) {
        (*ghost_row_new)++;

        if (*ghost_row_new < 0) {
            *ghost_row_new = NUM_ROWS - 1;
        } else if (*ghost_row_new > NUM_ROWS - 1) {
            *ghost_row_new = 0;
        }
    } else if (move_direction == LEFT) {
        (*ghost_col_new)--;

        if (*ghost_col_new < 0) {
            *ghost_col_new = NUM_COLS - 1;
        } else if (*ghost_col_new > NUM_COLS - 1) {
            *ghost_col_new = 0;
        }
    } else if (move_direction == RIGHT) {
        (*ghost_col_new)++;

        if (*ghost_col_new < 0) {
            *ghost_col_new = NUM_COLS - 1;
        } else if (*ghost_col_new > NUM_COLS - 1) {
            *ghost_col_new = 0;
        }
    }
}

enum direction parse_ghost_direction(enum direction ghost_direction) {
    if (ghost_direction == UP) {
        return LEFT;
    } else if (ghost_direction == LEFT) {
        return DOWN;
    } else if (ghost_direction == DOWN) {
        return RIGHT;
    } else if (ghost_direction == RIGHT) {
        return UP;
    } else {
        return OTHER;
    }
}

void ghost_scared_collision(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                            int ghost_row, int ghost_col, int ghost_flo,
                            struct data pacman) {

    int ghost_row_new = ghost_row;
    int ghost_col_new = ghost_col;

    get_greatest(map, ghost_row, ghost_col, ghost_flo, pacman, &ghost_row_new, &ghost_col_new);

    struct enemy temp = map[ghost_row][ghost_col][ghost_flo].enemy;
    map[ghost_row][ghost_col][ghost_flo].enemy.is_present = FALSE;
    check_ghost_collision(map, ghost_row, ghost_col, ghost_flo, pacman, ghost_row_new, ghost_col_new);
    map[ghost_row_new][ghost_col_new][ghost_flo].enemy = temp;
}

void get_greatest(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS],
                  int ghost_row, int ghost_col, int ghost_flo,
                  struct data pacman,
                  int *ghost_row_new, int *ghost_col_new) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;

    int d1_r = ghost_row - 1;

    if (d1_r < 0) {
        d1_r = NUM_ROWS - 1;
    }

    int d1_c = ghost_col;
    int d2_r = ghost_row;
    int d2_c = ghost_col - 1;

    if (d2_c < 0) {
        d2_c = NUM_COLS - 1;
    }

    int d3_r = ghost_row;
    int d3_c = ghost_col + 1;

    if (d3_c > NUM_COLS - 1) {
        d3_c = 0;
    }

    int d4_r = ghost_row + 1;

    if (d4_r > NUM_ROWS - 1) {
        d4_r = 0;
    }

    int d4_c = ghost_col;

    double dist_1 = sqrt(pow((*pacman_row - d1_r), 2) +
                         pow((*pacman_col - d1_c), 2));
    double dist_2 = sqrt(pow((*pacman_row - d2_r), 2) +
                         pow((*pacman_col - d2_c), 2));
    double dist_3 = sqrt(pow((*pacman_row - d3_r), 2) +
                         pow((*pacman_col - d3_c), 2));
    double dist_4 = sqrt(pow((*pacman_row - d4_r), 2) +
                         pow((*pacman_col - d4_c), 2));

    double d_big = 0.0;
    int d_r_big = 0;
    int d_c_big = 0;

    enum direction fake_direction = OTHER;

    if (hits_wall(map, d1_r, d1_c, ghost_flo) == FALSE) {
        if (dist_1 > d_big || (dist_1 == d_big && fake_direction > UP)) {
            d_big = dist_1;
            d_r_big = d1_r;
            d_c_big = d1_c;
            fake_direction = UP;
        }
    }

    if (hits_wall(map, d2_r, d2_c, ghost_flo) == FALSE) {
        if (dist_2 > d_big || (dist_2 == d_big && fake_direction > LEFT)) {
            d_big = dist_2;
            d_r_big = d2_r;
            d_c_big = d2_c;
            fake_direction = LEFT;
        }
    }

    if (hits_wall(map, d3_r, d3_c, ghost_flo) == FALSE) {
        if (dist_3 > d_big || (dist_3 == d_big && fake_direction > RIGHT)) {
            d_big = dist_3;
            d_r_big = d3_r;
            d_c_big = d3_c;
            fake_direction = RIGHT;
        }
    }

    if (hits_wall(map, d4_r, d4_c, ghost_flo) == FALSE) {
        if (dist_4 > d_big || (dist_4 == d_big && fake_direction > DOWN)) {
            d_big = dist_4;
            d_r_big = d4_r;
            d_c_big = d4_c;
            fake_direction = DOWN;
        }
    }

    *ghost_row_new = d_r_big;
    *ghost_col_new = d_c_big;
}

int hits_wall(struct tile map[NUM_ROWS][NUM_COLS][NUM_FLOORS], int row, int col, int flo) {
    if (map[row][col][flo].entity == WALL)
        return TRUE;
    else if (map[row][col][flo].enemy.is_present == TRUE)
        return TRUE;
    else
        return FALSE;
}