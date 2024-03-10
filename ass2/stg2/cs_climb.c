/*
 * CS Climb
 *
 * This program was written by [Brandon Atipaishe Chikandiwa] (z5495844).
 *
 * Development Timeline:
 * - Started on [12 November 2023].
 * - Completed Stage 1 on [12 November 2023].
 * - Completed Stage 2 on [15 November 2023]. 
 * - Completed Stage 3 on [21 November 2023]. TODO: Add Stage 3 End Date
 * - Completed Stage 4 on [21 November 2023]. TODO: Add Stage 4 End Date
 * - Commenting and efficiency improvements made on [24 November 2023]. TODO: Add Eff Imps End Date
 *
 *
 * Description: TODO: complete description below
 * CS Climb is a console-based implementation of
 */

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

////////////////////////////////////////////////////////////////////////////////
///////////////////////////      Constants       ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define MAX_STR_LEN 20
#define HELP_COMMAND '?'
#define TRUE = 1
#define FALSE = 0

// Provided enums
// This enum only has to be used in Stage 3.1 onwards
enum attempt_type { FIRST_GO,
                    SUCCESS,
                    FAIL,
                    INVALID_TYPE };

// TODO: Your #defines/enums can go here:

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Any additional structs you want to add can go here:

// Provided structs

// Represents a single climbing route in the logbook
struct route {
    // The name of the climbing route
    char name[MAX_STR_LEN];
    // The difficulty of the route
    int difficulty;
    // The length of the route in metres
    int length;
    // A pointer to the next `struct route` in the logbook
    struct route *next;
};

// Represents the logbook that contains info on each climbing route
struct logbook {
    // A pointer to the first `struct route` in the list
    struct route *routes;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void print_usage(void);
void print_one_route(int position, struct route *route);
void scan_string(char string[MAX_STR_LEN]);
enum attempt_type scan_attempt_type();
void print_one_attempt(
    char climber[MAX_STR_LEN],
    enum attempt_type type,
    int rating);

// Additional provided function prototypes
// You won't need to use these functions!
// We use them just to implement some of the provided helper functions.
int scan_token(char *buffer, int buffer_size);
enum attempt_type string_to_type(char *type_str);
void type_to_string(char *buf, enum attempt_type type);

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void start(struct logbook *logbook);
void parse_command(char command, struct logbook *logbook);
void command_add_route(struct logbook *logbook);
void command_print_routes(struct logbook *logbook);
int route_valid(struct logbook *logbook, struct route *route);
void command_print_difficulty_range(struct logbook *logbook);
int diff_valid(int difficulty);
int len_valid(int length);
int presence_valid(struct logbook *logbook, char name[MAX_STR_LEN]);
void command_insert_route(struct logbook *logbook);
int insert_route_valid(struct logbook *logbook, struct route *route, char before[MAX_STR_LEN]);
void command_length_change(struct logbook *logbook);
int length_change_valid(struct logbook *logbook, char route_1[MAX_STR_LEN], char route_2[MAX_STR_LEN], int change);
int individual_length_change_valid(struct logbook *logbook, char route_1[MAX_STR_LEN], char route_2[MAX_STR_LEN], int change);
void command_swap_routes(struct logbook *logbook);

struct logbook *create_logbook();
struct route *create_route(
    char name[MAX_STR_LEN],
    int difficulty,
    int length);

///////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION PROTOTYPES  //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    printf("Welcome to 1511 Climb! \n");
    printf("Log all of your climbing adventures here! \n");

    struct logbook *logbook = create_logbook();

    // STAGE 1.2
    // TODO: Write your command loop
    start(logbook);
    printf("\nGoodbye\n");

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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

struct route *create_route(
    char name[MAX_STR_LEN],
    int difficulty,
    int length) {

    struct route *created_route = malloc(sizeof(struct route));
    (*created_route).difficulty = difficulty;
    (*created_route).length = length;
    (*created_route).next = NULL;
    strcpy((*created_route).name, name);
    return created_route;
}

// TODO: Put your functions here

////////////////////////////////////////////////////////////////////////////////
///////////////////////////  PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Prints the 1511 Climb usage instructions,
// displaying the different commands and their arguments.
//
// Parameters:
//      None
//
// Returns:
//      None
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
    printf(
        "|%*s%s%*s|\n", padding / 2, "", position_str, (padding + 1) / 2, "");

    padding = line_length - strlen(route->name);
    printf("|%*s%s%*s|\n", padding / 2, "", route->name, (padding + 1) / 2, "");

    printf("|    Difficulty: %2d    |\n", route->difficulty);
    printf("|    Length (m): %2d    |\n", route->length);
    printf("\\--------- || ---------/\n");
}

// Scans a string into the provided char array, placing a '\0' at the end
//
// Parameters:
//      string      - a char array of length MAX_STR_LEN to store the string
//                    that is scanned in
//
// Returns:
//      None
//
// Usage:
// ```
//      char string[MAX_STR_LEN];
//      scan_string(string);
// ```
void scan_string(char string[MAX_STR_LEN]) {
    scan_token(string, MAX_STR_LEN);
}

// Scans a string and converts it to an enum attempt_type.
//
// Parameters:
//      None
//
// Returns:
//      The corresponding attempt_type, if the string was valid,
//      Otherwise, returns INVALID_TYPE.
//
// Usage:
// ```
//      enum attempt_type type = scan_attempt_type();
// ```
enum attempt_type scan_attempt_type(void) {
    char type[MAX_STR_LEN];
    scan_token(type, MAX_STR_LEN);
    return string_to_type(type);
}

// Prints a single attempt, displaying the climber name, attempt type and rating
//
// Parameters:
//      climber     - The name of the climber who attempted to climb a route
//      type        - The attempt type that was made (should be either
//                    FIRST_GO, SUCCESS, or FAIL)
//      rating      - The star rating that the climber gave the route
//
// Returns:
//      None
void print_one_attempt(
    char climber[MAX_STR_LEN],
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

// Scans a single word into `buffer`, ignoring whitespace
//
// Parameters:
//      buffer      - the string to store the scanned word
//      buffer_size - the maximum size of string that can be scanned (including
//                    the null terminator)
// Returns:
//      The number of chars scanned successfully
int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    // Consume all leading whitespace
    scanf(" ");

    // Scan in characters until whitespace
    while (i < buffer_size - 1 && (num_scanned = scanf("%c", &c)) == 1 && !isspace(c)) {
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

    if (strncasecmp(type_str, "first_go", len) == 0) {
        return FIRST_GO;
    }
    if (strncasecmp(type_str, "success", len) == 0) {
        return SUCCESS;
    }
    if (strncasecmp(type_str, "fail", len) == 0) {
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

void start(struct logbook *logbook) {
    char command;
    printf("Enter command: ");
    int result_code = scanf(" %c", &command);

    while (result_code == 1) {

        parse_command(command, logbook);

        printf("Enter command: ");
        result_code = scanf(" %c", &command);
    }
}

void parse_command(char command, struct logbook *logbook) {
    if (command == HELP_COMMAND) {
        print_usage();
    } else if (command == 'r') {
        command_add_route(logbook);
    } else if (command == 'p') {
        command_print_routes(logbook);
    } else if (command == 'f') {
        command_print_difficulty_range(logbook);
    } else if (command == 'i') {
        command_insert_route(logbook);
    } else if (command == 'l') {
        command_length_change(logbook);
    } else if (command == 's') {
        command_swap_routes(logbook);
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

    if (route_valid(logbook, new_route) == 0)
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

int route_valid(struct logbook *logbook, struct route *route) {
    if (diff_valid((*route).difficulty) == 0) {
        printf("ERROR: Route difficulty must be between 1 and 39\n");
        return 0;
    } else if (len_valid((*route).length) == 0) {
        printf("ERROR: Route length must be between 1m and 60m\n");
        return 0;
    } else if (presence_valid(logbook, (*route).name) == 0) {
        printf("ERROR: A route with the name '%s' already exists in this logbook\n", (*route).name);
        return 0;
    } else
        return 1;
}

// Order of checking
// Diff -> Length -> Presence of New -> Presence of Existing || Null list
int insert_route_valid(struct logbook *logbook, struct route *route, char before[MAX_STR_LEN]) {
    if (diff_valid((*route).difficulty) == 0) {
        printf("ERROR: Route difficulty must be between 1 and 39\n");
        return 0;
    } else if (len_valid((*route).length) == 0) {
        printf("ERROR: Route length must be between 1m and 60m\n");
        return 0;
    } else if (presence_valid(logbook, (*route).name) == 0) {
        printf("ERROR: A route with the name '%s' already exists in this logbook\n", (*route).name);
        return 0;
    } else if ((*logbook).routes == NULL) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n", before);
        return 0;
    } else if (presence_valid(logbook, before) == 1) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n", before);
        return 0;
    } else
        return 1;
}

int presence_valid(struct logbook *logbook, char name[MAX_STR_LEN]) {
    struct route *route = (*logbook).routes;

    if (route != NULL) {
        while (route != NULL) {
            if (strcmp((*route).name, name) == 0) {
                return 0;
            }
            route = (*route).next;
        }
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

int diff_range_valid(int diff_min, int diff_max) {
    if (diff_valid(diff_min) == 0) {
        return 0;
    } else if (diff_valid(diff_max) == 0) {
        return 0;
    } else if (diff_min > diff_max) {

        return 0;
    } else
        return 1;
}

void command_print_difficulty_range(struct logbook *logbook) {
    int diff_min, diff_max;
    scanf("%d %d", &diff_min, &diff_max);

    struct route *route = (*logbook).routes;

    if (diff_range_valid(diff_min, diff_max) == 0) {
        printf("ERROR: Difficulty range invalid!\n");
        return;
    }

    printf("Routes between difficulty %d and %d:\n", diff_min, diff_max);

    int count = 1;

    while (route != NULL) {
        if ((*route).difficulty >= diff_min && (*route).difficulty <= diff_max) {
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

    if (insert_route_valid(logbook, new_route, before) == 0) {
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

int length_change_valid(struct logbook *logbook, char route_1[MAX_STR_LEN], char route_2[MAX_STR_LEN], int change) {
    if (presence_valid(logbook, route_2) == 1) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n", route_2);
        return 0;
    } else if (individual_length_change_valid(logbook, route_1, route_2, change) == 0) {
        printf("ERROR: Invalid length change! No route lengths have been changed\n");
        return 0;
    } else if (presence_valid(logbook, route_1) == 1) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n", route_1);
        return 0;
    } else
        return 1;
}

int individual_length_change_valid(struct logbook *logbook, char route_1[MAX_STR_LEN], char route_2[MAX_STR_LEN], int change) {
    struct route *current = (*logbook).routes;
    struct route *start = NULL;
    struct route *end = NULL;
    int count = 0;
    int start_position = 0;
    int end_position = 0;

    while (current != NULL) {
        if (strcmp((*current).name, route_1) == 0) {
            start = current;
            start_position = count;
        }
        if (strcmp((*current).name, route_2) == 0) {
            end = current;
            end_position = count;
        }

        count++;
        current = (*current).next;
    }

    if (start_position > end_position) {
        struct route *holder = end;
        for (int i = 0; i < start_position - end_position + 1; i++) {
            if (len_valid((*holder).length + change) == 0) {
                return 0;
            }

            holder = (*holder).next;
        }
    } else {
        struct route *holder = start;
        for (int i = 0; i < end_position - start_position + 1; i++) {
            if (len_valid((*holder).length + change) == 0) {
                return 0;
            }

            holder = (*holder).next;
        }
    }
    return 1;
}

void command_length_change(struct logbook *logbook) {
    char route_1[MAX_STR_LEN], route_2[MAX_STR_LEN];
    int change;

    scan_string(route_1);
    scan_string(route_2);
    scanf("%d", &change);

    if (length_change_valid(logbook, route_1, route_2, change) == 0) {
        return;
    }

    struct route *current = (*logbook).routes;
    struct route *start = NULL;
    struct route *end = NULL;
    int count = 0;
    int start_position = 0;
    int end_position = 0;

    while (current != NULL) {
        if (strcmp((*current).name, route_1) == 0) {
            start_position = count;
            start = current;
        }

        if (strcmp((*current).name, route_2) == 0) {
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
            printf("Length of '%s' updated from %dm to %dm\n", (*holder).name, (*holder).length - change, (*holder).length);
            holder = (*holder).next;
        }
    } else {
        struct route *holder = start;
        for (int i = 0; i < end_position - start_position + 1; i++) {
            (*holder).length += change;
            printf("Length of '%s' updated from %dm to %dm\n", (*holder).name, (*holder).length - change, (*holder).length);
            holder = (*holder).next;
        }
    }
}

int swap_routes_valid(struct logbook *logbook, char route_1[MAX_STR_LEN], char route_2[MAX_STR_LEN]) {
    if (presence_valid(logbook, route_1) == 1) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n", route_1);
        return 0;
    } else if (presence_valid(logbook, route_2) == 1) {
        printf("ERROR: No route with the name '%s' exists in this logbook\n", route_2);
        return 0;
    } else if (strcmp(route_1, route_2) == 0) {
        printf("ERROR: Cannot swap '%s' with itself\n", route_1);
        return 0;
    } else
        return 1;
}

void command_swap_routes(struct logbook *logbook) {
    char route_1[MAX_STR_LEN], route_2[MAX_STR_LEN];
    scan_string(route_1);
    scan_string(route_2);

    if (swap_routes_valid(logbook, route_1, route_2) == 0) {
        return;
    }

    struct route *current = (*logbook).routes;
    int route_1_position = 0;
    int route_2_position = 0;
    struct route *r_1 = NULL;
    struct route *r_2 = NULL;
    int count = 0;

    while (current != NULL) {
        if (strcmp((*current).name, route_1) == 0) {
            route_1_position = count;
            r_1 = current;
        }

        if (strcmp((*current).name, route_2) == 0) {
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