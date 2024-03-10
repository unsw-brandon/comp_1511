/*
 * CS Climb
 *
 * This program was written by [Brandon Atipaishe Chikandiwa] (z5495844).
 *
 * Development Timeline:
 * - Started on [12 November 2023].
 * - Completed Stage 1 on [12 November 2023].
 * - Completed Stage 2 on [15 November 2023].
 * - Completed Stage 3 on [18 November 2023].
 * - Stage 4 is currently in progress.
 * - Commenting and efficiency improvements made on [18 November 2023].
 *
 *
 * CS Climb is a console-based implementation of a climb logging program. It
 * allows a user to be able to log in different routes that can be taken up,
 * additionally, each route can have varying data such as length and difficulty.
 * Routes can also have a log of it's climbers also with additional information
 * such as rating and status of the climb. The program has multiple other data
 * manipulation commands that can modify the climbing data in different ways.
 */

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

///////////////////////////////////////////////////////////////////////////////
////////////////////////////  PROVIDED CONSANTS  //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief This holds the maximum number of characters a string should have
 * throughout the program.
 */
#define MAX_STR_LEN 20

/**
 * @brief This holds the command/character used for seeking help.
 */
#define HELP_COMMAND '?'

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////  CONSTANTS  //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief TRUE which is 1.
 */
#define TRUE 1

/**
 * @brief FALSE which is 0.
 */
#define FALSE 0

/**
 * @brief This holds the command/character used for adding a route.
 */
#define ADD_ROUTE 'r'

/**
 * @brief This holds the command/character used for printing the routes in a
 * logbook.
 */
#define PRINT_ROUTES 'p'

/**
 * @brief This holds the command/character used for printing all the routes in
 * a logbook within a certain range of difficulty.
 */
#define PRINT_DIFF_ROUTE 'f'

/**
 * @brief This holds the command/character used for inserting a route at a
 * specific position in a logbook.
 */
#define INSERT_ROUTE 'i'

/**
 * @brief This holds the command/character used for changing the lengths of
 * all routes within two input routes in a logbook.
 */
#define LENGTH_CHANGE 'l'

/**
 * @brief This holds the command/character used for swapping two routes in a
 * logbook.
 */
#define SWAP_ROUTES 's'

/**
 * @brief This holds the command/character used for adding an attempt to a
 * route in a logbook.
 */
#define ADD_ATTEMPT 'a'

/**
 * @brief This holds the command/character used for printing all the contents
 * of a logbook.
 */
#define PRINT_LOGBOOK 'P'

/**
 * @brief This holds the command/character used for deleting a route from a
 * logbook.
 */
#define DELETE_ROUTE 'R'

/**
 * @brief This holds the command/character used for deleting a climber from the
 * logbook.
 */
#define DELETE_CLIMBER 'D'

/**
 * @brief This holds the command/character used for duplicating attempts.
 */
#define DUPLICATE_CLIMBER 'd'

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////  PROVIDED ENUMS  ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief All attempt_types that can be chosen.
 */
enum attempt_type {
    FIRST_GO,
    SUCCESS,
    FAIL,
    INVALID_TYPE
};

///////////////////////////////////////////////////////////////////////////////
//////////////////////////  USER DEFINED TYPES  ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////////////////////////// PROVIDED STRUCTS  ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Struct definition of an attempt contained within routes.
 */
struct attempt {
    /**
     * @brief Name of a climber who has taken an attempt.
     */
    char climber[MAX_STR_LEN];

    /**
     * @brief An enum of type attempt_type of the kind of attempt made.
     */
    enum attempt_type type;

    /**
     * @brief The rating received by a climber for an attempt
     */
    int rating;

    /**
     * @brief A pointer to the next 'struct attempt' in the route.
     */
    struct attempt *next;
};

/**
 * @brief Represents a single climbing route in the logbook.
 */
struct route {

    /**
     * @brief The name of the climbing route.
     */
    char name[MAX_STR_LEN];

    /**
     * @brief The difficulty of the route.
     */
    int difficulty;

    /**
     * @brief The length of the route in metres.
     */
    int length;

    /**
     * @brief A pointer to the next `struct route` in the logbook.
     */
    struct route *next;

    /**
     * @brief A pointer to the head `struct attempt` in the route.
     */
    struct attempt *attempts;
};

/**
 * @brief Represents the logbook that contains info on each climbing route.
 */
struct logbook {
    /**
     * @brief A pointer to the first `struct route` in the list.
     */
    struct route *routes;
};

///////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ///////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * @brief Prints the 1511 Climb usage instructions, displaying the different
 * commands and their arguments.
 */
void print_usage(void);

/**
 * @brief Prints the contents a single route in a logbook.
 * @param position Position of the route within the logbook.
 * @param route A pointer of the  `struct route` in the list.
 */
void print_one_route(int position, struct route *route);

/**
 * @brief Scans a string into the provided char array, placing a '\0' at the
 * end.
 * @param string Char array of length MAX_STR_LEN to store the string that is
 * scanned in.
 */
void scan_string(char string[MAX_STR_LEN]);

/** 
 * @brief Scans a string and converts it to an enum attempt_type.
 * @return The corresponding attempt_type, if the string was valid,
 * otherwise, returns INVALID_TYPE.
 */
enum attempt_type scan_attempt_type();

/**
 * @brief Prints a single attempt, displaying the climber name, attempt type
 * and rating.
 * @param climber Name of the climber who attempted to climb a route.
 * @param type Attempt type that was made (should be either
//                    FIRST_GO, SUCCESS, or FAIL).
 * @param rating Star rating that the climber gave the route.
 */
void print_one_attempt(char climber[MAX_STR_LEN],
                       enum attempt_type type,
                       int rating);

// Additional provided function prototypes
// You won't need to use these functions!
// We use them just to implement some of the provided helper functions.

/**
 * @brief Scans a single word into `buffer`, ignoring whitespace
 * @param buffer String to store the scanned word.
 * @param buffer_size Maximum size of string that can be scanned
 * (including the null terminator).
 * @return Number of chars scanned successfully.
 */
int scan_token(char *buffer, int buffer_size);

enum attempt_type string_to_type(char *type_str);

void type_to_string(char *buf, enum attempt_type type);

///////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION PROTOTYPES  //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Where the program begins looping commands until input
 * is stopped by the user.
 * @param logbook Struct containing the head of the route linked list.
 */
void start(struct logbook *logbook);

/**
 * @brief Maps all the command functions to their charater/command.
 * @param logbook Struct containing the head of the route linked list.
 * @param command Command that a user wants to perfrom.
 */
void parse_command(struct logbook *logbook, char command);
/**
 * @brief Appends a route to the logbook.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_add_route(struct logbook *logbook);

/**
 * @brief Prints all the routes in the logbook.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_print_routes(struct logbook *logbook);

/**
 * @brief Prints all the routes in a logbook that are within a certain range of
 * difficulty.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_print_difficulty_range(struct logbook *logbook);

/**
 * @brief Inserts a route before another route input by a user.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_insert_route(struct logbook *logbook);

/**
 * @brief Changes the length of all routes between two inputted routes.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_length_change(struct logbook *logbook);

/**
 * @brief Swaps the positions of two routes in a logbook.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_swap_routes(struct logbook *logbook);

/**
 * @brief Deletes a route from a logbook.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_delete_route(struct logbook *logbook);

/**
 * @brief Deletes a climber from an attempt.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_delete_climber(struct logbook *logbook);

/**
 * @brief Appends an attempt to a route in a logbook.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_add_attempt(struct logbook *logbook);

/**
 * @brief Duplicates all the attempts made by a climber for another climber.
 * @param logbook Struct containing the head of the route linked list.
 */
void command_duplicate_climber(struct logbook *logbook);

/**
 * @brief Duplicates all the attempts made by a climber for another climber.
 * @param logbook Struct containing the head of the route linked list.
 * @param route Route where the attempts are being duplicated.
 * @param attempt The attempt of the second climber who's attempt is being
 * duplicated.
 * @param climber_1 The climber who's duplicating another attempt.
 */
void duplicate_climber(struct logbook *logbook,
                       struct route *route,
                       struct attempt *attempt,
                       char climber_1[MAX_STR_LEN]);

/**
 * @brief Checks if a route that needs to be added into a logbook is valid.
 * @param logbook Struct containing the head of the route linked list.
 * @param route Route that needs to be validated.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int route_valid(struct logbook *logbook, struct route *route);

/**
 * @brief Checks if a value of difficulty lies within a certain range.
 * @param difficulty Int value of difficulty.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int diff_valid(int difficulty);

/**
 * @brief Checks if a value of length lies within a certain range.
 * @param length Int value of length.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int len_valid(int length);

/**
 * @brief Checks if a route with a certain name exists in the logbook.
 * @param logbook Struct containing the head of the route linked list.
 * @param name Name of route.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int presence_valid(struct logbook *logbook, char name[MAX_STR_LEN]);

/**
 * @brief Checks if a route that needs to be inserted into a logbook is valid.
 * @param logbook Struct containing the head of the route linked list.
 * @param route The new route.
 * @param before Name of route that the the new route will be inserted behind.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int insert_route_valid(struct logbook *logbook,
                       struct route *route,
                       char before[MAX_STR_LEN]);

/**
 * @brief Checks if the difficulty range is valid.
 * @param diff_min Minimum value of difficulty.
 * @param diff_max Maximum value of difficulty.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int diff_range_valid(int diff_min, int diff_max);

/**
 * @brief Checks if the two routes being swapped are valid or not.
 * @param logbook Struct containing the head of the route linked list.
 * @param route_1 First route to be swapped with the second route.
 * @param route_2 Second route to be swapped with the first route.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int swap_routes_valid(struct logbook *logbook,
                      char route_1[MAX_STR_LEN],
                      char route_2[MAX_STR_LEN]);
/**
 * @brief Checks if the route set can have their lengths changed.
 * @param logbook Struct containing the head of the route linked list.
 * @param route_1 Name of the first route to change.
 * @param route_2 Name of the last route to change.
 * @param change The amount to change the length by.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int length_change_valid(struct logbook *logbook,
                        char route_1[MAX_STR_LEN],
                        char route_2[MAX_STR_LEN],
                        int change);

/**
 * @brief Checks if a single route from a set can have it's length changed.
 * @param logbook Struct containing the head of the route linked list.
 * @param route_1 Name of the first route to change.
 * @param route_2 Name of the last route to change.
 * @param change The amount to change the length by.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int individual_length_change_valid(struct logbook *logbook,
                                   char route_1[MAX_STR_LEN],
                                   char route_2[MAX_STR_LEN],
                                   int change);

/**
 * @brief Checks if an attempt has valid data before its appended to a route.
 * @param logbook Struct containing the head of the route linked list.
 * @param attempt The attempt to be validated.
 * @param route The route to have the attempt be appended.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int attempt_valid(struct logbook *logbook,
                  struct attempt *attempt,
                  char route[MAX_STR_LEN]);

/**
 * @brief Checks if an attempt from a climber already exists on a route.
 * @param logbook Struct containing the head of the route linked list.
 * @param attempt The attempt to be checked.
 * @param route The route to have the attempt be checked.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int has_attempted_valid(struct logbook *logbook,
                        struct attempt *attempt,
                        char route[MAX_STR_LEN]);

/**
 * @brief Checks if a route can be deleted from a logbook.
 * @param logbook Struct containing the head of the route linked list.
 * @param route The route to be deleted.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int route_delete_valid(struct logbook *logbook, char route[MAX_STR_LEN]);

/**
 * @brief Checks if a climber is present in any route of the logbook.
 * @param logbook Struct containing the head of the route linked list.
 * @param climber Name of the climber to checked.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int attempt_presence_valid(struct logbook *logbook, char climber[MAX_STR_LEN]);

/**
 * @brief Checks if a climber is present in a specific route of the logbook.
 * @param logbook Struct containing the head of the route linked list.
 * @param climber Name of the climber to check the presence.
 * @param route Name of the route to check the presence.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int attempt_presence_route_valid(struct logbook *logbook,
                                 char climber[MAX_STR_LEN],
                                 char route[MAX_STR_LEN]);
/**
 * @brief Checks if a climber can be deleted from all routes of a logbook.
 * @param logbook Struct containing the head of the route linked list.
 * @param climber Name of the climber to be deleted.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int climber_delete_valid(struct logbook *logbook, char climber[MAX_STR_LEN]);

/**
 * @brief Checks if a climber's attempts can be duplicated for another climber.
 * @param logbook Struct containing the head of the route linked list.
 * @param climber_1 The climber to have the attempts duplicated.
 * @param climber_2 The climber who's attempts will be duplicated.
 * @return Depending on validity will either return TRUE OR FALSE.
 */
int duplicate_valid(struct logbook *logbook,
                    char climber_1[MAX_STR_LEN],
                    char climber_2[MAX_STR_LEN]);

/**
 * @brief Gets a route with a given name.
 * @param logbook Struct containing the head of the route linked list.
 * @param name Name of route to find.
 * @return returns a struct route with the name provided or NULL.
 */
struct route *get_route(struct logbook *logbook, char name[MAX_STR_LEN]);

/**
 * @brief Creates a new attempt linked list of in reverse of the one provided.
 * @param head Struct containing the head of the attempt linked list.
 * @return A reversed link list.
 */
struct attempt *reverse(struct attempt *head);

/**
 * @brief Calculates an average rating of all the attempt ratings in a route.
 * @param current Struct of a route in a logbook.
 * @return A double value of the average.
 */
double get_average_rating(struct route *current);

/**
 * @brief Free's all remaining memory that isn't used after the program is
 * ended
 * @param logbook Struct containing the head of the route linked list.
 */
void free_all(struct logbook *logbook);

/**
 * @brief Free's all the remaining memory after an attempt is duplicated.
 * @param head A pointer of 'struct attempt' that is the first element of an
 * attempt linked list.
 */
void free_list(struct attempt *head);
/**
 * @brief Creates a 'struct logbook'.
 * @return A pointer to this logbook.
 */
struct logbook *create_logbook();

/**
 * @brief Creates a route given all the route's information.
 * @param name Name of route.
 * @param diffuculty Difficulty of route.
 * @param length Length of route.
 * @return A pointer to the route that has been created.
 */
struct route *create_route(char name[MAX_STR_LEN], int difficulty, int length);

/**
 * @brief Creates an attempt given all the attempt's information.
 * @param climber Name of climber of attempt.
 * @param type Type of attempt made.
 * @param rating Rating of attempt.
 * @return A pointer to the attempt that has been created.
 */
struct attempt *create_attempt(char climber[MAX_STR_LEN],
                               enum attempt_type type,
                               int rating);

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Allocate memory for a new struct logbook and return a pointer to it
//
// Parameters:
//      None
//
// Returns:
//      new_logbook - a pointer to the newly created struct logbook
struct logbook *create_logbook() {
    struct logbook *new_logbook = malloc(sizeof(struct logbook));
    new_logbook->routes = NULL;
    return new_logbook;
}

struct route *create_route(char name[MAX_STR_LEN], int difficulty, int length) {
    struct route *route = malloc(sizeof(struct route));
    (*route).difficulty = difficulty;
    (*route).length = length;
    (*route).next = NULL;
    (*route).attempts = NULL;
    strcpy((*route).name, name);
    return route;
}

struct attempt *create_attempt(char climber[MAX_STR_LEN],
                               enum attempt_type type,
                               int rating) {
    struct attempt *my_attempt = malloc(sizeof(struct attempt));
    strcpy((*my_attempt).climber, climber);
    (*my_attempt).rating = rating;
    (*my_attempt).type = type;
    (*my_attempt).next = NULL;

    return my_attempt;
}

void print_usage(void) {
    printf(
        "=====================[     1511 Climb     ]=====================\n"
        "      ===============[     Usage Info     ]===============      \n"
        "  r [name] [difficulty] [length]                                \n"
        "    Append a climbing route to the end of the logbook           \n"
        "  p                                                             \n"
        "    Print out all the climbing routes in the logbook            \n"
        "                                                                \n"
        "  f [difficulty_min] [difficulty_max]                           \n"
        "    Filter routes by difficulty                                 \n"
        "  i [name] [difficulty] [length] [route_to_insert_before]       \n"
        "    Insert a climbing route into the logbook before             \n"
        "    `route_to_insert_before`                                    \n"
        "  l [route_1] [route_2] [length_change]                         \n"
        "    Change length of all routes between `route_1` and `route_2` \n"
        "  s [route_1] [route_2]                                         \n"
        "    Swap 2 routes                                               \n"
        "                                                                \n"
        "  a [climber] [attempt_type] [rating] [route]                   \n"
        "    Add an attempt of `route` by `climber`                      \n"
        "  P                                                             \n"
        "    Print out all the routes and attempts in the logbook        \n"
        "  R [route]                                                     \n"
        "    Remove a route and all associated attempts                  \n"
        "  D [climber]                                                   \n"
        "    Delete all attempts by `climber`                            \n"
        "  d [climber_1] [climber_2]                                     \n"
        "    Duplicate all of `climber_2`s attempts for `climber_1`      \n"
        "                                                                \n"
        "  c [route_1] [route_2]                                         \n"
        "    Combine 2 routes                                            \n"
        "  L [route]                                                     \n"
        "    Print the climber leaderboard for `route`                   \n"
        "                                                                \n"
        "  ?                                                             \n"
        "    Show help                                                   \n"
        "================================================================\n");
}

// Prints a single route, displaying its position in the logbook, name, grade
// and length.
//
// Parameters:
//      position    - The position of the route in the logbook (the first
//                        route will be route_number 1, second will be 2, etc)
//      route       - A pointer to the struct route to be printed
//
// Returns:
//      None
void print_one_route(int position, struct route *route) {
    int line_length = MAX_STR_LEN + 2;
    printf("/--------- \\/ ---------\\\n");

    char position_str[MAX_STR_LEN];
    sprintf(position_str, "Route #%d", position);
    int padding = line_length - strlen(position_str);
    printf("|%*s%s%*s|\n", padding / 2, "", position_str, (padding + 1) / 2,
           "");

    padding = line_length - strlen(route->name);
    printf("|%*s%s%*s|\n", padding / 2, "", route->name, (padding + 1) / 2, "");

    printf("|    Difficulty: %2d    |\n", route->difficulty);
    printf("|    Length (m): %2d    |\n", route->length);
    printf("\\--------- || ---------/\n");
}

void scan_string(char string[MAX_STR_LEN]) {
    scan_token(string, MAX_STR_LEN);
}

enum attempt_type scan_attempt_type() {
    char type[MAX_STR_LEN];
    scan_token(type, MAX_STR_LEN);
    return string_to_type(type);
}

void print_one_attempt(char climber[MAX_STR_LEN],
                       enum attempt_type type,
                       int rating) {
    char type_string[MAX_STR_LEN];
    type_to_string(type_string, type);
    printf("        --> %s\n", type_string);
    printf("            Climber: %s\n", climber);
    printf("            Rating:  ");
    for (int i = 0; i < rating; i++) {
        printf("*");
    }
    printf("\n\n");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////// ADDITIONAL PROVIDED FUNCTIONS ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == FALSE) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    // Consume all leading whitespace
    scanf(" ");

    // Scan in characters until whitespace
    while (i < buffer_size - 1 && (num_scanned = scanf("%c", &c)) == TRUE &&
           !isspace(c)) {
        buffer[i++] = c;
    }

    if (i > 0) {
        buffer[i] = '\0';
    }

    return num_scanned;
}

// Converts a string to the corresponding enum attempt_type
//
// Parameters:
//      type_str    - The string to be converted
//
// Returns:
//      The matching enum attempt_type, or `INVALID_TYPE` if `type_str` matches
//      no valid attempt type
enum attempt_type string_to_type(char *type_str) {
    int len = MAX_STR_LEN;

    if (strncasecmp(type_str, "first_go", len) == FALSE) {
        return FIRST_GO;
    }
    if (strncasecmp(type_str, "success", len) == FALSE) {
        return SUCCESS;
    }
    if (strncasecmp(type_str, "fail", len) == FALSE) {
        return FAIL;
    }

    return INVALID_TYPE;
}

// Converts an enum attempt_type to a string
//
// Parameters:
//      buf         - The string to store the attempt type
//      type        - The enum attempt_type to be converted
//
// Returns:
//      None
void type_to_string(char *buf, enum attempt_type type) {
    if (type == FIRST_GO) {
        strcpy(buf, "FIRST GO");
    } else if (type == SUCCESS) {
        strcpy(buf, "SUCCESS");
    } else if (type == FAIL) {
        strcpy(buf, "FAIL");
    } else {
        strcpy(buf, "INVALID");
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////  MY FUNCTIONS ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
////////////////////////  INITIALISATION FUNCTIONS  ///////////////////////////
///////////////////////////////////////////////////////////////////////////////

void start(struct logbook *logbook) {
    char command;
    printf("Enter command: ");
    int result_code = scanf(" %c", &command);

    while (result_code == TRUE) {
        parse_command(logbook, command);

        printf("Enter command: ");
        result_code = scanf(" %c", &command);
    }

    free_all(logbook);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////  ACTION FUNCTIONS  ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void delete_climber(struct route *route,
                    char climber[MAX_STR_LEN],
                    int *removed) {
    struct attempt *current = (*route).attempts;
    struct attempt *prev = NULL;

    while (current != NULL) {
        if (strcmp((*current).climber, climber) == FALSE) {
            if (prev == NULL) {
                (*route).attempts = (*current).next;
            } else {
                (*prev).next = (*current).next;
            }

            struct attempt *temp_current = current;
            current = (*current).next;
            free(temp_current);
            (*removed)++;
        } else {
            prev = current;
            current = (*current).next;
        }
    }
}

void add_attempt(struct logbook *logbook,
                 struct attempt *attempt,
                 char route[MAX_STR_LEN]) {
    struct route *current = get_route(logbook, route);

    struct attempt *first = (*current).attempts;
    struct attempt *prev = NULL;

    if (first == NULL) {
        (*current).attempts = attempt;
    } else {
        while (first != NULL &&
               (strcmp((*attempt).climber, (*first).climber) > 0)) {
            prev = first;
            first = (*first).next;
        }

        if (prev == NULL) {
            struct attempt *temp = (*current).attempts;
            (*current).attempts = attempt;
            (*attempt).next = temp;
        } else {
            struct attempt *temp = (*prev).next;
            (*prev).next = attempt;
            (*attempt).next = temp;
        }
    }
}

void command_add_route(struct logbook *logbook) {
    char name[MAX_STR_LEN];
    int difficulty, length;
    scan_string(name);
    scanf("%d %d", &difficulty, &length);

    struct route *route = (*logbook).routes;

    while (route != NULL) {
        route = (*route).next;
    }

    struct route *new_route = create_route(name, difficulty, length);

    if (route_valid(logbook, new_route) == FALSE)
        return;

    if ((*logbook).routes == NULL) {
        (*logbook).routes = new_route;
    } else {
        route = (*logbook).routes;

        while ((*route).next != NULL) {
            route = (*route).next;
        }

        (*route).next = new_route;
    }

    printf("Route '%s' added successfully!\n", name);
}

void command_print_routes(struct logbook *logbook) {
    struct route *route = (*logbook).routes;
    int count = 1;

    if (route == NULL) {
        printf("There are no routes in this logbook!\n");
        return;
    }

    while (route != NULL) {
        print_one_route(count, route);
        route = (*route).next;
        count++;
    }
}

void command_print_difficulty_range(struct logbook *logbook) {
    int diff_min, diff_max;
    scanf("%d %d", &diff_min, &diff_max);

    struct route *route = (*logbook).routes;

    if (diff_range_valid(diff_min, diff_max) == FALSE) {
        printf("ERROR: Difficulty range invalid!\n");
        return;
    }

    printf("Routes between difficulty %d and %d:\n", diff_min, diff_max);

    int count = 1;

    while (route != NULL) {
        if ((*route).difficulty >= diff_min &&
            (*route).difficulty <= diff_max) {
            print_one_route(count, route);
        }

        route = (*route).next;
        count++;
    }
}

void command_insert_route(struct logbook *logbook) {
    char name[MAX_STR_LEN], before[MAX_STR_LEN];
    int difficulty, length;
    scan_string(name);
    scanf("%d %d", &difficulty, &length);
    scan_string(before);

    struct route *route = (*logbook).routes;
    struct route *prev = NULL;
    struct route *new_route = create_route(name, difficulty, length);

    if (insert_route_valid(logbook, new_route, before) == FALSE) {
        return;
    }

    while (route != NULL && strcmp((*route).name, before) != 0) {
        prev = route;
        route = (*route).next;
    }

    if (prev == NULL) {
        struct route *temp = route;
        (*logbook).routes = new_route;
        (*new_route).next = temp;
    } else {
        (*prev).next = new_route;
        (*new_route).next = route;
    }

    printf("Route '%s' inserted successfully!\n", name);
}
void command_length_change(struct logbook *logbook) {
    char route_1[MAX_STR_LEN], route_2[MAX_STR_LEN];
    int change;

    scan_string(route_1);
    scan_string(route_2);
    scanf("%d", &change);

    if (length_change_valid(logbook, route_1, route_2, change) == FALSE) {
        return;
    }

    struct route *current = (*logbook).routes;
    struct route *start = NULL;
    struct route *end = NULL;
    int count = 0;
    int start_position = 0;
    int end_position = 0;

    while (current != NULL) {
        if (strcmp((*current).name, route_1) == FALSE) {
            start_position = count;
            start = current;
        }

        if (strcmp((*current).name, route_2) == FALSE) {
            end_position = count;
            end = current;
        }

        count++;
        current = (*current).next;
    }

    if (start_position > end_position) {
        struct route *holder = end;
        for (int i = 0; i < start_position - end_position + 1; i++) {
            (*holder).length += change;
            printf("Length of '%s' updated from %dm to %dm\n", (*holder).name,
                   (*holder).length - change, (*holder).length);
            holder = (*holder).next;
        }
    } else {
        struct route *holder = start;
        for (int i = 0; i < end_position - start_position + 1; i++) {
            (*holder).length += change;
            printf("Length of '%s' updated from %dm to %dm\n", (*holder).name,
                   (*holder).length - change, (*holder).length);
            holder = (*holder).next;
        }
    }
}

void command_swap_routes(struct logbook *logbook) {
    char route_1[MAX_STR_LEN], route_2[MAX_STR_LEN];
    scan_string(route_1);
    scan_string(route_2);

    if (swap_routes_valid(logbook, route_1, route_2) == FALSE) {
        return;
    }

    struct route *current = (*logbook).routes;
    int route_1_position = 0;
    int route_2_position = 0;
    struct route *r_1 = NULL;
    struct route *r_2 = NULL;
    int count = 0;

    while (current != NULL) {
        if (strcmp((*current).name, route_1) == FALSE) {
            route_1_position = count;
            r_1 = current;
        }

        if (strcmp((*current).name, route_2) == FALSE) {
            route_2_position = count;
            r_2 = current;
        }

        count++;
        current = (*current).next;
    }

    if (route_1_position > route_2_position) {
        char temp_str[MAX_STR_LEN];

        int temp_diff = (*r_2).difficulty;
        int temp_len = (*r_2).length;
        strcpy(temp_str, (*r_2).name);

        (*r_2).difficulty = (*r_1).difficulty;
        (*r_2).length = (*r_1).length;
        strcpy((*r_2).name, (*r_1).name);

        (*r_1).difficulty = temp_diff;
        (*r_1).length = temp_len;
        strcpy((*r_1).name, temp_str);

    } else {
        char temp_str[MAX_STR_LEN];

        int temp_diff = (*r_1).difficulty;
        int temp_len = (*r_1).length;
        strcpy(temp_str, (*r_1).name);

        (*r_1).difficulty = (*r_2).difficulty;
        (*r_1).length = (*r_2).length;
        strcpy((*r_1).name, (*r_2).name);

        (*r_2).difficulty = temp_diff;
        (*r_2).length = temp_len;
        strcpy((*r_2).name, temp_str);
    }

    printf("'%s' swapped positions with '%s'!\n", route_1, route_2);
}

void command_add_attempt(struct logbook *logbook) {
    char climber[MAX_STR_LEN], route[MAX_STR_LEN];
    enum attempt_type type;
    int rating;

    scan_string(climber);
    type = scan_attempt_type();

    scanf("%d", &rating);

    scan_string(route);

    struct attempt *attempt = create_attempt(climber, type, rating);

    if (attempt_valid(logbook, attempt, route) == FALSE) {
        return;
    }

    add_attempt(logbook, attempt, route);
    printf("Logged attempt of '%s' by %s\n", route, (*attempt).climber);
}

void command_print_logbook(struct logbook *logbook) {
    if (logbook == NULL || (*logbook).routes == NULL) {
        printf("There are no routes in this logbook!\n");
        return;
    }

    struct route *current = (*logbook).routes;
    int count = 1;

    while (current != NULL) {
        printf("Route #%d: %s\n", count, (*current).name);
        printf("Difficulty: %d | ", (*current).difficulty);
        printf("Length: %dm | ", (*current).length);
        printf("Avg rating: %.1lf/3.0\n", get_average_rating(current));

        struct attempt *first = (*current).attempts;

        while (first != NULL) {
            print_one_attempt((*first).climber, (*first).type, (*first).rating);
            first = (*first).next;
        }

        count++;
        current = (*current).next;
    }
}

void command_delete_route(struct logbook *logbook) {
    char route[MAX_STR_LEN];
    scan_string(route);

    if (route_delete_valid(logbook, route) == FALSE) {
        return;
    }

    struct route *current = (*logbook).routes;
    struct route *prev = NULL;

    while (current != NULL) {
        if (strcmp((*current).name, route) == FALSE) {
            break;
        }

        prev = current;
        current = (*current).next;
    }

    struct attempt *first = (*current).attempts;

    while (first != NULL) {
        struct attempt *temp = first;
        first = (*first).next;
        free(temp);
    }

    if (prev == NULL) {
        (*logbook).routes = (*current).next;
    } else {
        (*prev).next = (*current).next;
    }

    free(current);
    printf("Removed route '%s' from logbook\n", route);
}

void command_delete_climber(struct logbook *logbook) {
    char climber[MAX_STR_LEN];
    scan_string(climber);

    if (climber_delete_valid(logbook, climber) == FALSE) {
        return;
    }

    int removed = 0;

    struct route *route = (*logbook).routes;

    while (route != NULL) {
        delete_climber(route, climber, &removed);
        route = (*route).next;
    }
    printf("Deleted %d attempt(s) logged by %s\n", removed, climber);
}

void command_duplicate_climber(struct logbook *logbook) {
    char climber_1[MAX_STR_LEN], climber_2[MAX_STR_LEN];
    scan_string(climber_1);
    scan_string(climber_2);

    if (duplicate_valid(logbook, climber_1, climber_2) == FALSE) {
        return;
    }

    struct route *route = (*logbook).routes;

    while (route != NULL) {
        struct attempt *attempt = reverse((*route).attempts);
        struct attempt *attempt_temp = attempt;
        while (attempt != NULL) {
            if (strcmp((*attempt).climber, climber_2) == FALSE) {
                duplicate_climber(logbook, route, attempt, climber_1);
            }

            attempt = (*attempt).next;
        }
        free_list(attempt_temp);
        route = (*route).next;
    }
}

void duplicate_climber(struct logbook *logbook,
                       struct route *route,
                       struct attempt *attempt,
                       char climber_1[MAX_STR_LEN]) {

    struct attempt *new_attempt = create_attempt(climber_1, (*attempt).type,
                                                 (*attempt).rating);

    if ((*attempt).type == FIRST_GO &&
        attempt_presence_route_valid(logbook, climber_1,
                                     (*route).name) == FALSE) {
        (*new_attempt).type = SUCCESS;
    }

    add_attempt(logbook, new_attempt, (*route).name);
    printf("Logged attempt of '%s' by %s\n", (*route).name, climber_1);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////  CONTROL FUNCTIONS  ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void parse_command(struct logbook *logbook, char command) {
    if (command == HELP_COMMAND) {
        print_usage();
    } else if (command == ADD_ROUTE) {
        command_add_route(logbook);
    } else if (command == PRINT_ROUTES) {
        command_print_routes(logbook);
    } else if (command == PRINT_DIFF_ROUTE) {
        command_print_difficulty_range(logbook);
    } else if (command == INSERT_ROUTE) {
        command_insert_route(logbook);
    } else if (command == LENGTH_CHANGE) {
        command_length_change(logbook);
    } else if (command == SWAP_ROUTES) {
        command_swap_routes(logbook);
    } else if (command == ADD_ATTEMPT) {
        command_add_attempt(logbook);
    } else if (command == PRINT_LOGBOOK) {
        command_print_logbook(logbook);
    } else if (command == DELETE_ROUTE) {
        command_delete_route(logbook);
    } else if (command == DELETE_CLIMBER) {
        command_delete_climber(logbook);
    } else if (command == DUPLICATE_CLIMBER) {
        command_duplicate_climber(logbook);
    }
}

int route_valid(struct logbook *logbook, struct route *route) {
    if (diff_valid((*route).difficulty) == FALSE) {
        printf("ERROR: Route difficulty must be between 1 and 39\n");
        return 0;
    } else if (len_valid((*route).length) == FALSE) {
        printf("ERROR: Route length must be between 1m and 60m\n");
        return 0;
    } else if (presence_valid(logbook, (*route).name) == FALSE) {
        printf("ERROR: A route with the name ");
        printf("'%s' already exists in this logbook\n", (*route).name);
        return 0;
    } else
        return 1;
}

int insert_route_valid(struct logbook *logbook,
                       struct route *route,
                       char before[MAX_STR_LEN]) {
    if (diff_valid((*route).difficulty) == FALSE) {
        printf("ERROR: Route difficulty must be between 1 and 39\n");
        return 0;
    } else if (len_valid((*route).length) == FALSE) {
        printf("ERROR: Route length must be between 1m and 60m\n");
        return 0;
    } else if (presence_valid(logbook, (*route).name) == FALSE) {
        printf("ERROR: A route with the name ");
        printf("'%s' already exists in this logbook\n", (*route).name);
        return 0;
    } else if ((*logbook).routes == NULL) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n",
               before);
        return 0;
    } else if (presence_valid(logbook, before) == TRUE) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n",
               before);
        return 0;
    } else
        return 1;
}

int presence_valid(struct logbook *logbook, char name[MAX_STR_LEN]) {
    struct route *route = (*logbook).routes;

    while (route != NULL) {
        if (strcmp((*route).name, name) == FALSE) {
            return 0;
        }
        route = (*route).next;
    }

    return 1;
}

int attempt_presence_valid(struct logbook *logbook, char climber[MAX_STR_LEN]) {
    struct route *route = (*logbook).routes;

    while (route != NULL) {
        struct attempt *attempt = (*route).attempts;

        while (attempt != NULL) {
            if (strcmp((*attempt).climber, climber) == FALSE) {
                return 0;
            }

            attempt = (*attempt).next;
        }
        route = (*route).next;
    }

    return 1;
}

int diff_valid(int difficulty) {
    if (difficulty <= 0 || difficulty > 39)
        return 0;
    else
        return 1;
}

int len_valid(int length) {
    if (length <= 0 || length > 60)
        return 0;
    else
        return 1;
}

int rating_valid(int rating) {
    if (rating < 0 || rating > 3) {
        return 0;
    } else
        return 1;
}

int type_valid(enum attempt_type type) {
    if (type == INVALID_TYPE) {
        return 0;
    } else
        return 1;
}

int diff_range_valid(int diff_min, int diff_max) {
    if (diff_valid(diff_min) == FALSE) {
        return 0;
    } else if (diff_valid(diff_max) == FALSE) {
        return 0;
    } else if (diff_min > diff_max) {
        return 0;
    } else
        return 1;
}

int length_change_valid(struct logbook *logbook,
                        char route_1[MAX_STR_LEN],
                        char route_2[MAX_STR_LEN],
                        int change) {
    if (presence_valid(logbook, route_2) == TRUE) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n",
               route_2);
        return 0;
    } else if (individual_length_change_valid(logbook, route_1, route_2,
                                              change) == FALSE) {
        printf("ERROR: Invalid length change!");
        printf(" No route lengths have been changed\n");
        return 0;
    } else if (presence_valid(logbook, route_1) == TRUE) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n",
               route_1);
        return 0;
    } else
        return 1;
}

int individual_length_change_valid(struct logbook *logbook,
                                   char route_1[MAX_STR_LEN],
                                   char route_2[MAX_STR_LEN],
                                   int change) {
    struct route *current = (*logbook).routes;
    struct route *start = NULL;
    struct route *end = NULL;
    int count = 0;
    int start_position = 0;
    int end_position = 0;

    while (current != NULL) {
        if (strcmp((*current).name, route_1) == FALSE) {
            start = current;
            start_position = count;
        }
        if (strcmp((*current).name, route_2) == FALSE) {
            end = current;
            end_position = count;
        }

        count++;
        current = (*current).next;
    }

    if (start_position > end_position) {
        struct route *holder = end;
        for (int i = 0; i < start_position - end_position + 1; i++) {
            if (len_valid((*holder).length + change) == FALSE) {
                return 0;
            }

            holder = (*holder).next;
        }
    } else {
        struct route *holder = start;
        for (int i = 0; i < end_position - start_position + 1; i++) {
            if (len_valid((*holder).length + change) == FALSE) {
                return 0;
            }

            holder = (*holder).next;
        }
    }
    return 1;
}

int swap_routes_valid(struct logbook *logbook,
                      char route_1[MAX_STR_LEN],
                      char route_2[MAX_STR_LEN]) {
    if (presence_valid(logbook, route_1) == TRUE) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n",
               route_1);
        return 0;
    } else if (presence_valid(logbook, route_2) == TRUE) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n",
               route_2);
        return 0;
    } else if (strcmp(route_1, route_2) == FALSE) {
        printf("ERROR: Cannot swap '%s' with itself\n", route_1);
        return 0;
    } else
        return 1;
}

int attempt_valid(struct logbook *logbook,
                  struct attempt *attempt,
                  char route[MAX_STR_LEN]) {
    if (type_valid((*attempt).type) == FALSE) {
        printf("ERROR: Attempt type invalid\n");
        return 0;
    } else if (rating_valid(((*attempt).rating)) == FALSE) {
        printf("ERROR: Rating must be between 0 and 3\n");
        return 0;
    } else if (presence_valid(logbook, route) == TRUE) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n",
               route);
        return 0;
    } else if (has_attempted_valid(logbook, attempt, route) == FALSE) {
        printf(
            "ERROR: %s has already attempted '%s' - they can't get it on their "
            "first go!\n",
            (*attempt).climber, route);
        return 0;
    } else
        return 1;
}

int has_attempted_valid(struct logbook *logbook,
                        struct attempt *attempt,
                        char route[MAX_STR_LEN]) {
    struct attempt *first = (*get_route(logbook, route)).attempts;

    if (attempt == NULL) {
        return 1;
    } else {
        while (first != NULL) {
            if (strcmp((*attempt).climber, (*first).climber) == FALSE &&
                (*attempt).type == FIRST_GO) {
                return 0;
            }

            first = (*first).next;
        }
    }

    return 1;
}

int route_delete_valid(struct logbook *logbook, char route[MAX_STR_LEN]) {
    if (presence_valid(logbook, route) == TRUE) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n",
               route);
        return 0;
    } else
        return 1;
}

int climber_delete_valid(struct logbook *logbook, char climber[MAX_STR_LEN]) {
    if (attempt_presence_valid(logbook, climber) == TRUE) {
        printf("ERROR: %s has not logged any attempts\n", climber);
        return 0;
    } else
        return 1;
}

int duplicate_valid(struct logbook *logbook,
                    char climber_1[MAX_STR_LEN],
                    char climber_2[MAX_STR_LEN]) {
    if (attempt_presence_valid(logbook, climber_2) == TRUE) {
        printf("ERROR: %s has not logged any attempts\n", climber_2);
        return 0;
    } else if (strcmp(climber_1, climber_2) == FALSE) {
        printf("ERROR: Cannot duplicate attempts made by the same climber\n");
        return 0;
    } else
        return 1;
}

int attempt_presence_route_valid(struct logbook *logbook,
                                 char climber[MAX_STR_LEN],
                                 char route[MAX_STR_LEN]) {
    struct attempt *first = (*get_route(logbook, route)).attempts;

    if (first == NULL) {
        return 1;
    } else {
        while (first != NULL) {
            if (strcmp(climber, (*first).climber) == FALSE) {
                return 0;
            }

            first = (*first).next;
        }
    }

    return 1;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////  CONVERSION FUNCTIONS  //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct attempt *reverse(struct attempt *head) {
    struct attempt *attempt_reverse = NULL;

    while (head != NULL) {
        struct attempt *new_node = malloc(sizeof(struct attempt));

        strcpy((*new_node).climber, (*head).climber);
        (*new_node).rating = (*head).rating;
        (*new_node).type = (*head).type;
        (*new_node).next = attempt_reverse;

        attempt_reverse = new_node;

        head = (*head).next;
    }

    return attempt_reverse;
}

struct route *get_route(struct logbook *logbook, char name[MAX_STR_LEN]) {
    struct route *route = (*logbook).routes;

    while (route != NULL) {
        if (strcmp((*route).name, name) == FALSE) {
            return route;
        }

        route = (*route).next;
    }

    return NULL;
}

double get_average_rating(struct route *current) {
    double total = 0;
    int count = 0;

    struct attempt *first = (*current).attempts;

    if (first == NULL) {
        return 0.0;
    }

    while (first != NULL) {
        total += (*first).rating;
        count++;
        first = (*first).next;
    }

    if (count == FALSE)
        return 0.0;
    else
        return total / count;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////  MEMORY MGMNT FUNCTIONS  ////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void free_all(struct logbook *logbook) {
    if (logbook == NULL) {
        return;
    } else {
        struct route *route = (*logbook).routes;
        while (route != NULL) {
            struct route *temp_route = route;
            struct attempt *attempt = (*route).attempts;
            while (attempt != NULL) {
                struct attempt *temp_attempt = attempt;
                attempt = (*attempt).next;
                free(temp_attempt);
            }
            route = (*route).next;
            free(temp_route);
        }
    }
    free(logbook);
}

void free_list(struct attempt *head) {
    struct attempt *current = head;
    struct attempt *next;

    while (current != NULL) {
        next = (*current).next;
        free(current);
        current = next;
    }
}

/**
 * @brief Main method where the program starts.
 */
int main(void) {
    printf("Welcome to 1511 Climb! \n");
    printf("Log all of your climbing adventures here! \n");

    struct logbook *logbook = create_logbook();

    start(logbook);
    printf("\nGoodbye\n");

    return 0;
}