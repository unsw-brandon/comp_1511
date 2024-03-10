// Program name
//
// This program was written by [Brandon Chikandiwa] (z5495844)
// on [15 October 2023]
//
// TODO: Description of program

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

/* @todo: Make program efficient using enumatarated commands */
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
    int frozen;
};

struct tile {
    enum entity entity;
    struct enemy enemy;
};

// TODO: Put your structs here

/* @todo: Make program efficient using struct data which is common for most
 * of my functions.
 */
struct data {
    struct tile map[NUM_ROWS][NUM_COLS];
    int ghost_row;
    int ghost_col;
    int *pacman_row;
    int *pacman_col;
    int *points;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your function prototypes here

// Stage 1

void prep_game(struct tile map[NUM_ROWS][NUM_COLS], int pacman_row, int pacman_col);
void add_dots(struct tile map[NUM_ROWS][NUM_COLS]);
int is_wall_valid(int start_row, int start_col, int end_row, int end_col, struct tile map[NUM_ROWS][NUM_COLS]);

// Stage 2

void play_game(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row, int *pacman_col, int *points);
void perform_direction_command(struct tile map[NUM_ROWS][NUM_COLS], enum direction command, int *pacman_row, int *pacman_col, int *points);
void perform_other_command(struct tile map[NUM_ROWS][NUM_COLS], char command, int *pacman_row, int *pacman_col, int *points);
enum direction parse_pacman_direction_command(char command);
void check_collisions(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row, int *pacman_col, int *points);
void check_win(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row, int *pacman_col, int *points);
void apple_collision(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row, int *pacman_col, int *points);
void banana_collision(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row, int *pacman_col, int *points);
void dot_collision(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row, int *pacman_col, int *points);
void append_points(struct tile map[NUM_ROWS][NUM_COLS], int i, int j, int *points);

// Stage 3

int has_won(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row, int *pacman_col, int *points);
enum direction parse_ghost_command(char command);
void move_ghosts(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row, int *pacman_col, int *points);
void check_ghost_collision(struct tile map[NUM_ROWS][NUM_COLS], int ghost_row, int ghost_col, int *pacman_row, int *pacman_col, int *points);
enum direction parse_ghost_direction(enum direction ghost_direction);
void ghost_collision(int *points);
void ghost_collision_a(struct tile map[NUM_ROWS][NUM_COLS], int ghost_row, int ghost_col, int *pacman_row, int *pacman_col, int *points);
void enemy_direction(struct tile map[NUM_ROWS][NUM_COLS], int ghost_row, int ghost_col, int *ghost_row_new, int *ghost_col_new);

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void initialise_map(struct tile map[NUM_ROWS][NUM_COLS]);
void print_map(
    struct tile map[NUM_ROWS][NUM_COLS],
    int pacman_row,
    int pacman_col);

int main(void) {
    struct tile map[NUM_ROWS][NUM_COLS];
    initialise_map(map);

    printf("Welcome to cs_pacman!\n");
    int pacman_row, pacman_col;
    int points = 0;

    printf("Enter Pacman's starting coordinates: ");
    scanf("%d %d", &pacman_row, &pacman_col);
    print_map(map, pacman_row, pacman_col);

    prep_game(map, pacman_row, pacman_col);
    play_game(map, &pacman_row, &pacman_col, &points);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your functions here

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void initialise_map(struct tile map[NUM_ROWS][NUM_COLS]) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            map[row][col].entity = EMPTY_ENTITY;
            map[row][col].enemy.move_direction = LEFT;
            map[row][col].enemy.is_present = FALSE;
        }
    }
}

void print_map(
    struct tile map[NUM_ROWS][NUM_COLS],
    int pacman_row,
    int pacman_col) {
    for (int i = 0; i < NUM_COLS; i++) {
        printf("----");
    }
    printf("-\n");
    for (int row = 0; row < NUM_ROWS; row++) {
        printf("|");
        for (int col = 0; col < NUM_COLS; col++) {
            if (map[row][col].entity == WALL) {
                printf("|||");
            } else if (row == pacman_row && col == pacman_col) {
                printf("^_^");
            } else if (map[row][col].enemy.is_present == TRUE) {
                printf("O_O");
            } else if (map[row][col].entity == DOT) {
                printf(" . ");
            } else if (map[row][col].entity == APPLE) {
                printf(" a ");
            } else if (map[row][col].entity == BANANA) {
                printf(" b ");
            } else if (map[row][col].entity == POWER_UP) {
                printf("<o>");
            } else if (map[row][col].entity == STAIRCASE_UP) {
                printf("__/");
            } else if (map[row][col].entity == STAIRCASE_DOWN) {
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

void add_wall(int start_row, int start_col, int end_row,
              int end_col, struct tile map[NUM_ROWS][NUM_COLS], int wall_valid) {
    if (wall_valid == 0) {
        for (int i = start_row; i < end_row + 1; i++) {
            for (int j = start_col; j < end_col + 1; j++) {
                map[i][j].entity = WALL;
            }
        }
    } else if (wall_valid == 1) {
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
            map[i][start_col].entity = WALL;
        }
    } else if (wall_valid == 2) {
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
            map[start_row][i].entity = WALL;
        }
    } else if (wall_valid == 3) {

    } else {
        printf("Given wall is not horizontal or vertical!\n");
    }
}

void prep_game(struct tile map[NUM_ROWS][NUM_COLS], int pacman_row,
               int pacman_col) {
    printf("Create the level: \n");

    char first_letter;
    scanf(" %c", &first_letter);

    while (first_letter) {
        if (first_letter == 'S') {
            break;
        } else if (first_letter == 'W') {
            int start_row, start_col, end_row, end_col;
            scanf("%d %d %d %d", &start_row, &start_col, &end_row, &end_col);
            int is_wall_valid = is_wall_valid(start_row, start_col,
                                           end_row, end_col, map);
            if (is_wall_valid == 0) {
                add_wall(start_row, start_col, end_row, end_col, map, 0);
            } else if (is_wall_valid == 1) {
                add_wall(start_row, start_col, end_row, end_col, map, 1);
            } else if (is_wall_valid == 2) {
                add_wall(start_row, start_col, end_row, end_col, map, 2);
            } else if (is_wall_valid == 3) {
                add_wall(start_row, start_col, end_row, end_col, map, 3);
            } else {
                add_wall(start_row, start_col, end_row, end_col, map, -1);
            }

            start_row = 0;
            start_col = 0;
            end_row = 0;
            end_col = 0;
        } else if (first_letter == 'A') {
            int apple_row, apple_col;
            scanf("%d %d", &apple_row, &apple_col);
            map[apple_row][apple_col].entity = APPLE;
        } else if (first_letter == 'B') {
            int banana_row, banana_col;
            scanf("%d %d", &banana_row, &banana_col);
            map[banana_row][banana_col].entity = BANANA;
        } else if (first_letter == 'G') {
            int ghost_row, ghost_col;
            char ghost_direction;
            scanf("%d %d %c", &ghost_row, &ghost_col, &ghost_direction);
            map[ghost_row][ghost_col].enemy.is_present = TRUE;
            map[ghost_row][ghost_col].enemy.steps = 10;
            map[ghost_row][ghost_col].enemy.steps_done = 10;
            map[ghost_row][ghost_col].enemy.frozen = FALSE;
            map[ghost_row][ghost_col].enemy.move_direction =
                parse_ghost_command(ghost_direction);
        } else {
            int power_up_row, power_up_col;
            scanf("%d %d", &power_up_row, &power_up_col);
            map[power_up_row][power_up_col].entity = POWER_UP;
        }

        scanf(" %c", &first_letter);
    }

    add_dots(map);
    print_map(map, pacman_row, pacman_col);
}

int is_wall_valid(int start_row, int start_col, int end_row, int end_col,
               struct tile map[NUM_ROWS][NUM_COLS]) {

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

void add_dots(struct tile map[NUM_ROWS][NUM_COLS]) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {

            if (map[i][j].entity == EMPTY_ENTITY) {
                map[i][j].entity = DOT;
            }
        }
    }
}

// Stage 2

void play_game(struct tile map[NUM_ROWS][NUM_COLS], int *pacman_row,
               int *pacman_col, int *points) {
    char command;
    printf("Enter command: ");
    int result_code = scanf(" %c", &command);

    while (result_code == 1) {
        enum direction parsed_command = parse_pacman_direction_command(command);
        if (parsed_command == OTHER) {
            perform_other_command(map, command, pacman_row, pacman_col, points);
        } else {
            perform_direction_command(map, parsed_command, pacman_row,
                                      pacman_col, points);
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

void pacman_movement(struct tile map[NUM_ROWS][NUM_COLS],
                               enum direction command, struct data pacman) {

    if (command == UP) {
        if (*pacman_row - 1 < 0) {
            if (map[NUM_ROWS - 1][*pacman_col].entity != WALL) {
                *pacman_row = NUM_ROWS - 1;
            }
        } else {
            if (map[(*pacman_row) - 1][*pacman_col].entity != WALL) {
                (*pacman_row)--;
            }
        }
    } else if (command == DOWN) {
        if (*pacman_row + 1 > NUM_ROWS - 1) {
            if (map[0][*pacman_col].entity != WALL) {
                *pacman_row = 0;
            }
        } else {
            if (map[(*pacman_row) + 1][*pacman_col].entity != WALL) {
                (*pacman_row)++;
            }
        }
    } else if (command == LEFT) {
        if (*pacman_col - 1 < 0) {
            if (map[*pacman_row][NUM_COLS - 1].entity != WALL) {
                *pacman_col = NUM_COLS - 1;
            }
        } else {
            if (map[*pacman_row][(*pacman_col) - 1].entity != WALL) {
                (*pacman_col)--;
            }
        }
    } else if (command == RIGHT) {
        if (*pacman_col + 1 > NUM_COLS - 1) {

            if (map[*pacman_row][0].entity != WALL) {
                *pacman_col = 0;
            }
        } else {
            if (map[*pacman_row][(*pacman_col) + 1].entity != WALL) {
                (*pacman_col)++;
            }
        }
    }

    check_collisions(map, pacman_row, pacman_col, points);
    check_win(map, pacman_row, pacman_col, points);
    move_ghosts(map, pacman_row, pacman_col, points);
    print_map(map, *pacman_row, *pacman_col);
}

void check_win(struct tile map[NUM_ROWS][NUM_COLS],
               int *pacman_row, int *pacman_col, int *points) {
    if (has_won(map, pacman_row, pacman_col, points) == 1) {
        printf("Game won! You got %d points.\n", *points);
        exit(0);
    }
}
void check_collisions(struct tile map[NUM_ROWS][NUM_COLS],
                      int *pacman_row, int *pacman_col, int *points) {
    enum entity prev_entity = map[*pacman_row][*pacman_col].entity;

    if (prev_entity == APPLE) {
        apple_collision(map, pacman_row, pacman_col, points);
    } else if (prev_entity == BANANA) {
        banana_collision(map, pacman_row, pacman_col, points);
    } else if (prev_entity == DOT) {
        if (map[*pacman_row][*pacman_col].enemy.is_present == 1) {
            append_points(map, *pacman_row, *pacman_col, points);
            ghost_collision(points);
        } else {
            dot_collision(map, pacman_row, pacman_col, points);
        }
    }
}

void perform_other_command(struct tile map[NUM_ROWS][NUM_COLS],
                           char command, int *pacman_row, int *pacman_col,
                           int *points) {
    if (command == 'p') {
        printf("You have %d points!\n", *points);
    }

    print_map(map, *pacman_row, *pacman_col);
}

void apple_collision(struct tile map[NUM_ROWS][NUM_COLS],
                     int *pacman_row, int *pacman_col, int *points) {
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
            append_points(map, i, j, points);
        }
    }
}

void banana_collision(struct tile map[NUM_ROWS][NUM_COLS],
                      int *pacman_row, int *pacman_col, int *points) {
    int start_row = 0;
    int end_row = NUM_ROWS;
    int start_col = 0;
    int end_col = NUM_COLS;

    for (int i = start_row; i < end_row; i++) {
        if (map[i][*pacman_col].entity == WALL && (*pacman_row) < i) {
            end_row = i - 1;
        } else if (map[i][*pacman_col].entity == WALL && (*pacman_row) > i) {
            start_row = i + 1;
        }
    }

    for (int i = start_col; i < end_col; i++) {
        if (map[*pacman_row][i].entity == WALL && (*pacman_col) < i) {
            end_col = i - 1;
        } else if (map[*pacman_row][i].entity == WALL && (*pacman_col) > i) {
            start_col = i + 1;
        }
    }

    for (int i = start_row; i < end_row; i++) {
        append_points(map, i, *pacman_col, points);
    }

    for (int i = start_col; i < end_col; i++) {
        append_points(map, *pacman_row, i, points);
    }
}

void dot_collision(struct tile map[NUM_ROWS][NUM_COLS],
                   int *pacman_row, int *pacman_col, int *points) {
    append_points(map, *pacman_row, *pacman_col, points);
}

void ghost_collision(int *points) {
    printf("Game over! You got %d points.\n", *points);
    exit(0);
}

void append_points(struct tile map[NUM_ROWS][NUM_COLS],
                   int i, int j, int *points) {
    if (map[i][j].entity == DOT) {
        *points += 10;
    } else if (map[i][j].entity == APPLE) {
        *points += 20;
    } else if (map[i][j].entity == BANANA) {
        *points += 20;
    }

    map[i][j].entity = EMPTY_ENTITY;
}

// Stage 3

int has_won(struct tile map[NUM_ROWS][NUM_COLS],
            int *pacman_row, int *pacman_col, int *points) {

    int has_won = 1;

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (map[i][j].entity == DOT) {
                return 0;
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

void move_ghost(struct tile map[NUM_ROWS][NUM_COLS],
                int ghost_row, int ghost_col,
                int *pacman_row, int *pacman_col, int *points) {

    ghost_collision_a(map, ghost_row, ghost_col, pacman_row, pacman_col, points);
}

void move_ghosts(struct tile map[NUM_ROWS][NUM_COLS],
                 int *pacman_row, int *pacman_col, int *points) {

    int enemies_count = 0;
    int enemies[MAX_ENEMIES][2];

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (map[i][j].enemy.is_present == TRUE) {
                enemies[enemies_count][0] = i;
                enemies[enemies_count][1] = j;
                enemies_count++;
            }
        }
    }

    for (int i = 0; i < enemies_count; i++) {
        move_ghost(map, enemies[i][0], enemies[i][1], pacman_row, pacman_col,
                   points);
    }
}

void check_ghost_collision(struct tile map[NUM_ROWS][NUM_COLS],
                           int ghost_row, int ghost_col,
                           int *pacman_row, int *pacman_col, int *points) {

    if (ghost_row == *pacman_row && ghost_col == *pacman_col) {
        append_points(map, *pacman_row, *pacman_col, points);
        ghost_collision(points);
    }
}
void ghost_collision_a(struct tile map[NUM_ROWS][NUM_COLS],
                       int ghost_row, int ghost_col,
                       int *pacman_row, int *pacman_col, int *points) {

    int ghost_row_new = ghost_row;
    int ghost_col_new = ghost_col;

    if (map[ghost_row][ghost_col].enemy.steps_done <= 0) {
        if (map[ghost_row][ghost_col].enemy.steps <= 2) {
            map[ghost_row][ghost_col].enemy.steps = 10;
        } else {
            map[ghost_row][ghost_col].enemy.steps -= 2;
        }
        map[ghost_row][ghost_col].enemy.steps_done =
            map[ghost_row][ghost_col].enemy.steps - 1;
        map[ghost_row][ghost_col].enemy.move_direction =
            parse_ghost_direction(map[ghost_row][ghost_col].enemy.move_direction);
    } else {
        map[ghost_row][ghost_col].enemy.steps_done -= 1;
    }

    enemy_direction(map, ghost_row, ghost_col, &ghost_row_new, &ghost_col_new);

    if (map[ghost_row_new][ghost_col_new].entity == WALL || map[ghost_row_new][ghost_col_new].enemy.is_present == TRUE) {
        map[ghost_row][ghost_col].enemy.steps -= 2;
        map[ghost_row][ghost_col].enemy.steps_done = map[ghost_row][ghost_col].enemy.steps;
        map[ghost_row][ghost_col].enemy.move_direction = parse_ghost_direction(map[ghost_row][ghost_col].enemy.move_direction);
    } else {
        struct enemy temp = map[ghost_row][ghost_col].enemy;
        map[ghost_row][ghost_col].enemy.is_present = FALSE;
        check_ghost_collision(map, ghost_row_new, ghost_col_new, pacman_row, pacman_col, points);
        map[ghost_row_new][ghost_col_new].enemy = temp;
    }
}

void enemy_direction(struct tile map[NUM_ROWS][NUM_COLS], int ghost_row, int ghost_col, int *ghost_row_new, int *ghost_col_new) {
    if (map[ghost_row][ghost_col].enemy.move_direction == UP) {
        (*ghost_row_new)--;

        if (*ghost_row_new < 0) {
            *ghost_row_new = NUM_ROWS - 1;
        } else if (*ghost_row_new > NUM_ROWS - 1) {
            *ghost_row_new = 0;
        }
    } else if (map[ghost_row][ghost_col].enemy.move_direction == DOWN) {
        (*ghost_row_new)++;

        if (*ghost_row_new < 0) {
            *ghost_row_new = NUM_ROWS - 1;
        } else if (*ghost_row_new > NUM_ROWS - 1) {
            *ghost_row_new = 0;
        }
    } else if (map[ghost_row][ghost_col].enemy.move_direction == LEFT) {
        (*ghost_col_new)--;

        if (*ghost_col_new < 0) {
            *ghost_col_new = NUM_COLS - 1;
        } else if (*ghost_col_new > NUM_COLS - 1) {
            *ghost_col_new = 0;
        }
    } else if (map[ghost_row][ghost_col].enemy.move_direction == RIGHT) {
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