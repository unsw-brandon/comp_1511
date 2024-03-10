/*
 * CS Pacman
 *
 * This program was written by [Brandon Atipaishe Chikandiwa] (z5495844).
 *
 * Development Timeline:
 * - Started on [15 October 2023].
 * - Completed Stage 1 on [17 October 2023].
 * - Completed Stage 2 on [18 October 2023].
 * - Completed Stage 3 on [21 October 2023].
 * - Stage 4 is currently in progress.
 * - Commenting and efficiency improvements made on [24 October 2023].
 *
 *
 * Description:
 * CS Pacman is a console-based implementation of the popular Pac-Man game.
 * While it lacks the graphical user interface and experience of the original,
 * it replicates the core gameplay and features with a little twist.
 * The game begins by prompting the player for coordinates to place their 
 * Pac-Man character within an 8 x 10 grid. Afterward, the player can populate 
 * the grid with various elements, including bananas, apples, walls, power-ups, 
 * and ghosts. It also allows for the creation of multiple floors, although 
 * this feature is not yet implemented. Players and enemies can navigate these 
 * multiple floors as part of the gameplay. Once all dots are collected the 
 * game ends and you win,  or if Pac-man is unfortunate enough to encounter a 
 * ghost, the game will end in a loss. But don't worry you can play as many 
 * times as you like.
 */

#include <math.h>

#include <stdio.h>

#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
////////////////////////////  PROVIDED CONSANTS  //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief This holds the number of rows the map has.
 */
#define NUM_ROWS 8

/**
 * @brief This holds the number of columns the map has.
 */
#define NUM_COLS 10

/**
 * @brief This holds the maximum number of floors the map is can have.
 */
#define NUM_FLOORS 5

/**
 * @brief If something is true it has the value 1.
 */
#define TRUE 1

/**
 * @brief If something is false it has the value 0.
 */
#define FALSE 0

/**
 * @brief If something is invalid it has the value -1.
 */
#define INVALID -1
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////  CONSTANTS  //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * @brief This holds the number of steps a ghost must make while pacman has
 * consumed a power up.
 */
#define STEPS 10

/**
 * @brief This holds the max number of ghosts that can be on a map.
 */
#define MAX_ENEMIES 79

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////  PROVIDED ENUMS  ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief This holds all the entities that can be placed on a map.
 */
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

/**
 * @brief This holds the directions that pacman or an enemy can travel.
 */
enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    OTHER
};

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////  ENUMS  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief This holds possible validities of an inputted wall at given
 * coordinates.
 */
enum wall_validity {
    VALID,
    ROW_VALID,
    COL_VALID,
    IGNORE
};

///////////////////////////////////////////////////////////////////////////////
//////////////////////////// PROVIDED STRUCTS  ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief This holds all the information an enemy has at a given time, i.e the
 * direction currently being moved, the steps, the status and the presence.
 */
struct enemy {
    enum direction move_direction;
    int is_present;
    int steps;
    int steps_done;
    int is_scared;
};

/**
 * @brief This holds all the information that a tile can have at a given time,
 * i.e the entity currently on a tile or the enemy if present.
 */
struct tile {
    enum entity entity;
    struct enemy enemy;
};

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////  STRUCTS  ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief This holds pointer locations for pacman's location on the mop and
 * total number of points accumulated.
 */
struct data {
    int *row;
    int *col;
    int *points;
};

/**
 * @brief This holds the current(integer) and prospective(address) locations
 * of a ghost on a map.
 */
struct ghost_data {
    int row;
    int col;
    int *new_row;
    int *new_col;
};

///////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ///////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief This will initialise the map creating all the tiles for the map
 * and placing them inside the struct 2D array of type tile.
 * @param map This is an array of structs of type tile of the map.
 */
void initialise_map(struct tile map[NUM_ROWS][NUM_COLS]);

/**
 * @brief This will print out a 2D map-like drawing in console also setting
 * all the necessary elements for the different entities, enemies as well as
 * map borders.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman_row This is the current row of pacman on the map.
 * @param pacman_col This is the current column of pacman on the map.
 */
void print_map(struct tile map[NUM_ROWS][NUM_COLS],
               int pacman_row, int pacman_col);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION PROTOTYPES  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This adds a wall entity at specific coordinates on the map.
 * @param map This is an array of structs of type tile of the map.
 * @param start_row This is the starting row of a wall on the map.
 * @param start_col This is the starting column of a wall on the map.
 * @param end_row This is the ending row of a wall on the map.
 * @param end_col This is the ending column of a wall on the map.
 * @param wall_valid This is an integer that determines what type of a wall is
 * to be placed.
 */
void add_wall(struct tile map[NUM_ROWS][NUM_COLS],
              int start_row, int start_col,
              int end_row, int end_col, int wall_valid);

/**
 * @brief This prepares the map with the collectable, consumable, dynamic and
 * static entities that a user would want on the map.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman_row This is the starting row of pacman on the map.
 * @param pacman_col This is the starting column of pacman on the map.
 */
void prep_game(struct tile map[NUM_ROWS][NUM_COLS],
               int pacman_row, int pacman_col);

/**
 * @brief This places collectable dots on the tiles of the map that do
 * not have any entities.
 * @param map This is an array of structs of type tile of the map.
 */
void add_dots(struct tile map[NUM_ROWS][NUM_COLS]);

/**
 * @brief This will checks if a wall is valid.
 * @param map This is an array of structs of type tile of the map.
 * @param start_row This is the starting row of a wall on the map.
 * @param start_col This is the starting column of a wall on the map.
 * @param end_row This is the ending row of a wall on the map.
 * @param end_col This is the ending column of a wall on the map.
 * @return Returns an integer of what type of a wall should be placed.
 */
int wall_valid(struct tile map[NUM_ROWS][NUM_COLS],
               int start_row, int start_col,
               int end_row, int end_col);

/**
 * @brief This starts a game by continously inputing a directional or non
 * directional command until a user stops the game by either winning, losing or
 * stopping input via Ctrl+D.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void play_game(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman);

/**
 * @brief This will move a pacman in a specific direction.
 * @param map This is an array of structs of type tile of the map.
 * @param move_direction This is the direction that pacman is set to move to.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void pacman_movement(struct tile map[NUM_ROWS][NUM_COLS],
                     enum direction move_direction, struct data pacman);

/**
 * @brief This performs every other command that isn't a direction command.
 * @param map This is an array of structs of type tile of the map.
 * @param command This is a non-direction command that a user inputs.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void pacman_other_command(struct tile map[NUM_ROWS][NUM_COLS], char command,
                          struct data pacman);

/**
 * @brief This will parse the inputted char direction of pacman and return its
 * equivalent direction enumerated value.
 * @param command This is a direction command that needs to be parsed.
 * @return This returns a enum of type direction.
 */
enum direction parse_pacman_direction_command(char command);

/**
 * @brief This will parse the inputted char direction of a ghost and return its
 * equivalent direction enumerated value.
 * @param command This is a direction command that needs to be parsed.
 * @return This returns a enum of type direction.
 */
enum direction parse_ghost_direction_command(char command);

/**
 * @brief This checks what type of collision pacman had with other entities
 * and (or) enemies.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void check_pacman_collisions(struct tile map[NUM_ROWS][NUM_COLS],
                             struct data pacman);

/**
 * @brief This will perform the action of moving a single ghost in its correct
 * direction.
 * @param map This is an array of structs of type tile of the map.
 * @param ghost This is a struct containing a ghost's information,
 * i.e old and new locations.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void move_single_ghost(struct tile map[NUM_ROWS][NUM_COLS],
                       struct ghost_data ghost, struct data pacman);

/**
 * @brief This will check if the conditions necessary for pacman to win the game
 * have been reached, the points of pacman and a display message are output and
 * the program is exited otherwise no other actions are performed.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void check_win(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman);

/**
 * @brief This will check if pacman collided with an apple entity and perform
 * the necessary actions that must be done when pacman collides with an apple
 * entity.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void apple_collision(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman);

/**
 * @brief This will check if pacman collided with a banana entity and perform
 * the necessary actions that must be done when pacman collides with a banana
 * entity.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void banana_collision(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman);

/**
 * @brief This will check if pacman collided with a dot entity and perform
 * the necessary actions that must be done when pacman collides with a dot
 * entity.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void dot_collision(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman);

/**
 * @brief This will check if pacman collided with a power up entity and perform
 * the necessary actions that must be done when pacman collides with a power up
 * entity.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void power_up_collision(struct tile map[NUM_ROWS][NUM_COLS],
                        struct data pacman);

/**
 * @brief This will check if the conditions necessary for pacman to lose the
 * game have been reached, the points of pacman and a display message are output
 * and the program is exited otherwise no other actions are performed.
 * @param points This is an array of structs of type tile of the map.
 */
void ghost_collision(int *points);

/**
 * @brief This will append the total number of points that pacman has depending
 * on what entities pacman collides with after each given movement.
 * @param map This is an array of structs of type tile of the map.
 * @param row This is the row on the map of the entity that pacman will be
 * colliding with.
 * @param col This is the column on the map of the entity that pacman will be
 * colliding with.
 * @param points This points to the address location of the points that pacman
 * currently has.
 */
void append_points(struct tile map[NUM_ROWS][NUM_COLS],
                   int row, int col, int *points);

/**
 * @brief This checks if all the dots on the map have been consumed by pacman.
 * And returns the appropriate value.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 * @return Either a TRUE(1) or FALSE(0) value.
 */
int has_won(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman);

/**
 * @brief This will loop through every single tile in on the map, checking if
 * there is a ghost on that tile and if there is it will do the action of
 * moving it
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void move_all_ghosts(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman);

/**
 * @brief This will check what all collisions the ghost has made are, and if
 * certains collisions are made the necessary actions will be done.
 * @param map This is an array of structs of type tile of the map.
 * @param ghost This is a struct containing a ghost's information,
 * i.e old and new locations.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void check_ghost_collision(struct tile map[NUM_ROWS][NUM_COLS],
                           struct ghost_data ghost, struct data pacman);

/**
 * @brief This will parse the next direction a ghost is supposed to move.
 * @param ghost_direction This is the current direction a ghost is set to move.
 * @returns This will return the next direction for the ghost to move.
 */
enum direction parse_ghost_direction(enum direction ghost_direction);

/**
 * @brief This will calculate the direction for a ghost to move next.
 * @param map This is an array of structs of type tile of the map.
 * @param ghost This is a struct containing a ghost's information,
 * i.e old and new locations.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void single_ghost_movement(struct tile map[NUM_ROWS][NUM_COLS],
                           struct ghost_data ghost, struct data pacman);

/**
 * @brief This will calculate the direction for a ghost to move when pacman has
 * eaten a power up.
 * @param map This is an array of structs of type tile of the map.
 * @param ghost This is a struct containing a ghost's information,
 * i.e old and new locations.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void single_ghost_movement_scared(struct tile map[NUM_ROWS][NUM_COLS],
                                  struct ghost_data ghost, struct data pacman);

/**
 * @brief This will move a ghost in a specific location given the direction.
 * @param map This is an array of structs of type tile of the map.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 * @param direction
 */
void single_ghost_actual_movement(struct tile map[NUM_ROWS][NUM_COLS],
                                  struct ghost_data ghost,
                                  enum direction move_direction);

/**
 * @brief This will calcualate and determine the best movement for a ghost,
 * which would keep it as furthest away from the pacman as possible, when it is
 * scared.
 * @param map This is an array of structs of type tile of the map.
 * @param ghost This is a struct containing a ghost's information,
 * i.e old and new locations.
 * @param pacman This is a struct containing pacman's information,
 * i.e points and location.
 */
void scared_ghost_best_movement(struct tile map[NUM_ROWS][NUM_COLS],
                                struct ghost_data ghost, struct data pacman);

/**
 * @brief This will check if a ghost has collided with a barrier such as a wall
 * or another ghost
 * @param map This is an array of structs of type tile of the map.
 * @param row This is the prospective row of the ghost on the map.
 * @param col This is the prospective column of the ghost on the map.
 */
int hits_wall(struct tile map[NUM_ROWS][NUM_COLS], int row, int col);

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

void print_map(struct tile map[NUM_ROWS][NUM_COLS],
               int pacman_row, int pacman_col) {
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

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////  MY FUNCTIONS ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
////////////////////////  INITIALISATION FUNCTIONS  ///////////////////////////
///////////////////////////////////////////////////////////////////////////////

void prep_game(struct tile map[NUM_ROWS][NUM_COLS],
               int pacman_row, int pacman_col) {
    printf("Create the level: \n");

    char first_letter;
    scanf(" %c", &first_letter);

    while (first_letter != 'S') {
        if (first_letter == 'W') {
            int start_row, start_col, end_row, end_col;
            scanf("%d %d %d %d", &start_row, &start_col, &end_row, &end_col);
            int is_wall_valid =
                wall_valid(map, start_row, start_col, end_row, end_col);
            add_wall(map, start_row, start_col, end_row, end_col,
                     is_wall_valid);
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
            map[ghost_row][ghost_col].enemy.steps = STEPS;
            map[ghost_row][ghost_col].enemy.steps_done = STEPS;
            map[ghost_row][ghost_col].enemy.is_scared = FALSE;
            map[ghost_row][ghost_col].enemy.move_direction =
                parse_ghost_direction_command(ghost_direction);
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

///////////////////////////////////////////////////////////////////////////////
///////////////////////////  ACTION FUNCTIONS  ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void add_wall(struct tile map[NUM_ROWS][NUM_COLS],
              int start_row, int start_col,
              int end_row, int end_col,
              int wall_valid) {
    if (wall_valid == 0) {
        for (int i = start_row; i < end_row + 1; i++) {
            for (int j = start_col; j < end_col + 1; j++) {
                map[i][j].entity = WALL;
            }
        }
    } else if (wall_valid == 1) {
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
    } else if (wall_valid == 2) {
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
    } else if (wall_valid == 3) {
        
    } else {
        printf("Given wall is not horizontal or vertical!\n");
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

void play_game(struct tile map[NUM_ROWS][NUM_COLS],
               struct data pacman) {

    char command;
    printf("Enter command: ");
    int result_code = scanf(" %c", &command);

    while (result_code == 1) {

        enum direction parsed_command = parse_pacman_direction_command(command);

        if (parsed_command == OTHER) {
            pacman_other_command(map, command, pacman);
        } else {
            pacman_movement(map, parsed_command, pacman);
        }

        printf("Enter command: ");
        result_code = scanf(" %c", &command);
    }
}

void pacman_movement(struct tile map[NUM_ROWS][NUM_COLS],
                     enum direction move_direction, struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;

    if (move_direction == UP) {
        if (*pacman_row - 1 < 0) {
            if (map[NUM_ROWS - 1][*pacman_col].entity != WALL) {
                *pacman_row = NUM_ROWS - 1;
            }
        } else {
            if (map[(*pacman_row) - 1][*pacman_col].entity != WALL) {
                (*pacman_row)--;
            }
        }
    } else if (move_direction == DOWN) {
        if (*pacman_row + 1 > NUM_ROWS - 1) {
            if (map[0] [*pacman_col].entity != WALL) {
                *pacman_row = 0;
            }
        } else {
            if (map[(*pacman_row) + 1][*pacman_col].entity != WALL) {
                (*pacman_row)++;
            }
        }
    } else if (move_direction == LEFT) {
        if (*pacman_col - 1 < 0) {
            if (map[*pacman_row][NUM_COLS - 1].entity != WALL) {
                *pacman_col = NUM_COLS - 1;
            }
        } else {
            if (map[*pacman_row][(*pacman_col) - 1].entity != WALL) {
                (*pacman_col)--;
            }
        }
    } else if (move_direction == RIGHT) {
        if (*pacman_col + 1 > NUM_COLS - 1) {

            if (map [*pacman_row][0].entity != WALL) {
                *pacman_col = 0;
            }
        } else {
            if (map[*pacman_row][(*pacman_col) + 1].entity != WALL) {
                (*pacman_col)++;
            }
        }
    }

    check_pacman_collisions(map, pacman);
    check_win(map, pacman);
    move_all_ghosts(map, pacman);
    print_map(map, *pacman_row, *pacman_col);
}

void pacman_other_command(struct tile map[NUM_ROWS][NUM_COLS], char command,
                          struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *points = pacman.points;

    if (command == 'p') {
        printf("You have %d points!\n", *points);
    }

    print_map(map, *pacman_row, *pacman_col);
}

void apple_collision(struct tile map[NUM_ROWS][NUM_COLS],
                     struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
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
            append_points(map, i, j, points);
        }
    }
}

void banana_collision(struct tile map[NUM_ROWS][NUM_COLS],
                      struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *points = pacman.points;

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
                   struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *points = pacman.points;

    append_points(map, *pacman_row, *pacman_col, points);
}

void power_up_collision(struct tile map[NUM_ROWS][NUM_COLS],
                        struct data pacman) {

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *points = pacman.points;

    append_points(map, *pacman_row, *pacman_col, points);

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (map[i][j].enemy.is_present == TRUE) {
                map[i][j].enemy.is_scared += STEPS;
            }
        }
    }
}

void ghost_collision(int *points) {
    printf("Game over! You got %d points.\n", *points);
    exit(0);
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////  UTILITY FUNCTIONS  ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void append_points(struct tile map[NUM_ROWS][NUM_COLS],
                   int row, int col, int *points) {

    if (map[row][col].enemy.is_present ==
            TRUE &&
        map[row][col].enemy.is_scared > FALSE) {
        *points += 100;
        map[row][col].enemy.is_present = FALSE;
    }
    if (map[row][col].entity == DOT) {
        *points += 10;
    } else if (map[row][col].entity == APPLE ||
               map[row][col].entity == BANANA) {
        *points += 20;
    } else if (map[row][col].entity == POWER_UP) {
        *points += 50;
    }

    map[row][col].entity = EMPTY_ENTITY;
}

void check_pacman_collisions(struct tile map[NUM_ROWS][NUM_COLS],
                             struct data pacman) {
    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *points = pacman.points;

    enum entity prev_entity = map[*pacman_row][*pacman_col].entity;

    if (prev_entity == APPLE) {
        apple_collision(map, pacman);
    } else if (prev_entity == BANANA) {
        banana_collision(map, pacman);
    } else if (prev_entity == DOT) {
        dot_collision(map, pacman);
    } else if (prev_entity == POWER_UP) {
        power_up_collision(map, pacman);
    }

    if (map[*pacman_row][*pacman_col].enemy.is_present == 1 &&
        map[*pacman_row][*pacman_col].enemy.is_scared > 0) {
        append_points(map, *pacman_row, *pacman_col, points);
    } else if (map[*pacman_row][*pacman_col].enemy.is_present == 1) {
        append_points(map, *pacman_row, *pacman_col, points);
        ghost_collision(points);
    }
}

void move_all_ghosts(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman) {
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
        struct ghost_data ghost = {
            enemies[i][0],
            enemies[i][1],
            &(enemies[i][0]),
            &(enemies[i][1])
        };

        move_single_ghost(map, ghost, pacman);
    }
}

void move_single_ghost(struct tile map[NUM_ROWS][NUM_COLS],
                       struct ghost_data ghost, struct data pacman) {

    int ghost_row = ghost.row;
    int ghost_col = ghost.col;

    if (map[ghost_row][ghost_col].enemy.is_scared > 0) {
        map[ghost_row][ghost_col].enemy.is_scared -= 1;
        single_ghost_movement_scared(map, ghost, pacman);
    } else {
        single_ghost_movement(map, ghost, pacman);
    }
}

void single_ghost_movement(struct tile map[NUM_ROWS][NUM_COLS],
                           struct ghost_data ghost, struct data pacman) {

    int ghost_row = ghost.row;
    int ghost_col = ghost.col;
    int *ghost_row_new = ghost.new_row;
    int *ghost_col_new = ghost.new_col;

    if (map[ghost_row][ghost_col].enemy.steps_done <= 0) {
        if (map[ghost_row][ghost_col].enemy.steps <= 2) {
            map[ghost_row][ghost_col].enemy.steps = STEPS;
        } else {
            map[ghost_row][ghost_col].enemy.steps -= 2;
        }
        map[ghost_row][ghost_col].enemy.steps_done =
            map[ghost_row][ghost_col].enemy.steps - 1;
        map[ghost_row][ghost_col].enemy.move_direction =
            parse_ghost_direction(map[ghost_row][ghost_col]
                                      .enemy.move_direction);
    } else {
        map[ghost_row][ghost_col].enemy.steps_done -= 1;
    }
    enum direction move_direction =
        map[ghost_row][ghost_col].enemy.move_direction;
    single_ghost_actual_movement(map, ghost, move_direction);

    if (map[*ghost_row_new][*ghost_col_new].entity == WALL ||
        map[*ghost_row_new][*ghost_col_new].enemy.is_present == TRUE) {
        map[ghost_row][ghost_col].enemy.steps -= 2;
        map[ghost_row][ghost_col].enemy.steps_done =
            map[ghost_row][ghost_col].enemy.steps;
        map[ghost_row][ghost_col].enemy.move_direction =
            parse_ghost_direction(map[ghost_row][ghost_col]
                                      .enemy.move_direction);
    } else {
        struct enemy temp = map[ghost_row][ghost_col].enemy;
        map[ghost_row][ghost_col].enemy.is_present = FALSE;
        check_ghost_collision(map, ghost, pacman);
        map[*ghost_row_new][*ghost_col_new].enemy = temp;
    }
}

void single_ghost_actual_movement(struct tile map[NUM_ROWS][NUM_COLS],
                                  struct ghost_data ghost,
                                  enum direction move_direction) {

    int *ghost_row_new = ghost.new_row;
    int *ghost_col_new = ghost.new_col;

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

void single_ghost_movement_scared(struct tile map[NUM_ROWS][NUM_COLS],
                                  struct ghost_data ghost, struct data pacman) {

    int ghost_row = ghost.row;
    int ghost_col = ghost.col;
    int *ghost_row_new = ghost.new_row;
    int *ghost_col_new = ghost.new_col;

    scared_ghost_best_movement(map, ghost, pacman);

    struct enemy temp = map[ghost_row][ghost_col].enemy;
    map[ghost_row][ghost_col].enemy.is_present = FALSE;
    check_ghost_collision(map, ghost, pacman);
    map[*ghost_row_new][*ghost_col_new].enemy = temp;
}

void check_ghost_collision(struct tile map[NUM_ROWS][NUM_COLS],
                           struct ghost_data ghost, struct data pacman) {

    int ghost_row = ghost.row;
    int ghost_col = ghost.col;
    int *ghost_row_new = ghost.new_row;
    int *ghost_col_new = ghost.new_col;

    int *pacman_row = pacman.row;
    int *pacman_col = pacman.col;
    int *points = pacman.points;

    if (map[ghost_row][ghost_col].enemy.is_scared == 0) {
        if (*ghost_row_new == *pacman_row && *ghost_col_new == *pacman_col) {
            append_points(map, *pacman_row, *pacman_col, points);
            ghost_collision(points);
        } else {
            append_points(map, *pacman_row, *pacman_col, points);
        }
    } else {
        append_points(map, *pacman_row, *pacman_col, points);
    }
}

void scared_ghost_best_movement(struct tile map[NUM_ROWS][NUM_COLS],
                                struct ghost_data ghost, struct data pacman) {

    int ghost_row = ghost.row;
    int ghost_col = ghost.col;
    int *ghost_row_new = ghost.new_row;
    int *ghost_col_new = ghost.new_col;

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

    if (hits_wall(map, d1_r, d1_c) == FALSE) {
        if (dist_1 > d_big || (dist_1 == d_big && fake_direction > UP)) {
            d_big = dist_1;
            d_r_big = d1_r;
            d_c_big = d1_c;
            fake_direction = UP;
        }
    }

    if (hits_wall(map, d2_r, d2_c) == FALSE) {
        if (dist_2 > d_big || (dist_2 == d_big && fake_direction > LEFT)) {
            d_big = dist_2;
            d_r_big = d2_r;
            d_c_big = d2_c;
            fake_direction = LEFT;
        }
    }

    if (hits_wall(map, d3_r, d3_c) == FALSE) {
        if (dist_3 > d_big || (dist_3 == d_big && fake_direction > RIGHT)) {
            d_big = dist_3;
            d_r_big = d3_r;
            d_c_big = d3_c;
            fake_direction = RIGHT;
        }
    }

    if (hits_wall(map, d4_r, d4_c) == FALSE) {
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

///////////////////////////////////////////////////////////////////////////////
///////////////////////////  CONTROL FUNCTIONS  ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void check_win(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman) {

    int *points = pacman.points;

    if (has_won(map, pacman) == 1) {
        printf("Game won! You got %d points.\n", *points);
        exit(0);
    }
}

int wall_valid(struct tile map[NUM_ROWS][NUM_COLS],
               int start_row, int start_col, int end_row, int end_col) {

    if (start_row != end_row && start_col != end_col) {
        // INVALID
        return -1;
    } else if ((start_row < 0 && end_row < 0) ||
               (start_col < 0 && end_col < 0) ||
               ((start_row > NUM_ROWS && end_row > NUM_ROWS) ||
                (start_col > NUM_COLS && end_col > NUM_COLS))) {
        // IGNORE
        return IGNORE;
    } else if (
        start_row < 0 || end_row > NUM_ROWS) {
        // COL VALID, ROW EXCEEDS NUM_ROWS OR ROW BELOW 0
        return COL_VALID;
    } else if (start_col < 0 || end_col > NUM_COLS) {
        // ROW VALID, COL EXCEEDS NUM_COLS OR COL BELOW 0
        return ROW_VALID;
    } else {
        // ROW AND COL VALID
        return VALID;
    }
}

int has_won(struct tile map[NUM_ROWS][NUM_COLS], struct data pacman) {

    int has_won = TRUE;

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (map[i][j].entity == DOT) {
                return FALSE;
            }
        }
    }

    return has_won;
}

int hits_wall(struct tile map[NUM_ROWS][NUM_COLS], int row, int col) {
    if (map[row][col].entity == WALL)
        return TRUE;
    else if (map[row][col].enemy.is_present == TRUE)
        return TRUE;
    else
        return FALSE;
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

enum direction parse_ghost_direction_command(char command) {
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

/**
 * @brief Main method where the program starts.
 */
int main(void) {
    struct tile map[NUM_ROWS][NUM_COLS];
    initialise_map(map);

    printf("Welcome to cs_pacman!\n");
    int pacman_row, pacman_col;
    int points = 0;

    struct data pacman = {
        &pacman_row,
        &pacman_col,
        &points
    };

    printf("Enter Pacman's starting coordinates: ");
    scanf("%d %d", &pacman_row, &pacman_col);
    print_map(map, pacman_row, pacman_col);

    prep_game(map, pacman_row, pacman_col);
    play_game(map, pacman);
    return 0;
}