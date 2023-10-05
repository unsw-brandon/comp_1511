// Written
// By ....
//
// Interactive program to scan in and display the details of students in a
// class.

#include <stdio.h>

// TODO use these enums and #defines to clean up the code
#define MAX_CLASS_SIZE 20
#define MAX_EXAM_MARK 40
#define MAX_ASSIGMENTS_MARK 60
#define NOT_FOUND -1

enum loop_sentinal { STOP_LOOPING,
                     KEEP_LOOPING };
enum command { HELP,
               PRINT_STUDENT,
               PRINT_CLASS,
               QUIT,
               INVALID_COMMAND };
enum degree_type { UGRD,
                   PGRD,
                   INVALID_DEGREE };
enum major {
    COMPA1,
    COMPD1,
    COMPE1,
    COMPI1,
    COMPJ1,
    COMPN1,
    COMPS1,
    COMPY1,
    NONE
};

struct student {
    int z_id;
    int major;
    int degree_type;
    double assignments_mark;
    double exam_mark;
    double course_grade;
};

/*
 * This function scans in the major of the student and returns an integer value
 * between 0 and 8.
 */
int get_major(int degree_type) {

    int major = COMPA1;
    if (degree_type == UGRD) {
        // Print Major Prompt
        printf("Select Major: \n");

        while (major <= NONE) {
            printf("%d: ", major);

            // print major text
            if (major == COMPA1) {
                printf("Computer Science\n");
            } else if (major == COMPD1) {
                printf("Database Systems\n");
            } else if (major == COMPE1) {
                printf("eCommerce Systems\n");
            } else if (major == COMPI1) {
                printf("Artificial Intelligence\n");
            } else if (major == COMPJ1) {
                printf("Programming Languages\n");
            } else if (major == COMPN1) {
                printf("Computer Networks\n");
            } else if (major == COMPS1) {
                printf("Embedded Systems\n");
            } else if (major == COMPY1) {
                printf("Security Engineering\n");
            } else {
                printf("None\n");
            }

            major++;
        }

        // scanning in the major
        int scanned_major;
        scanf("%d", &scanned_major);
        major = NONE;
        if (scanned_major >= COMPA1 && scanned_major < NONE) {
            major = scanned_major;
        }
        major = scanned_major;
    }
    return major;
}

/*
 * This function scans in the type of degree the student is undertaking and returns
 * an integer value between 0 and 2.
 */
int get_degree_type() {
    // Printing the Degree type prompt
    printf("Select Degree Type: \n");
    printf("0: Undergraduate\n");
    printf("1: Postgraduate\n");

    // scanning the degree type
    int scanned_degree_type;
    scanf("%d", &scanned_degree_type);
    int degree_type = INVALID_DEGREE;
    if (scanned_degree_type == UGRD || scanned_degree_type == PGRD) {
        degree_type = scanned_degree_type;
    }
    return degree_type;
}

/*
 * This function scans in the assignment mark of the student and returns a double
 * value of the mark.
 */
double get_assignments_mark() {
    printf("Enter Assignments mark (out of %d): ", MAX_ASSIGMENTS_MARK);
    double assignments_mark;
    scanf("%lf", &assignments_mark);

    if (assignments_mark > MAX_ASSIGMENTS_MARK) {
        assignments_mark = MAX_ASSIGMENTS_MARK;
    } else if (assignments_mark < 0) {
        assignments_mark = 0;
    }
    return assignments_mark;
}

/*
 * This function scans in the exam mark of the student and returns a double
 * value of the mark.
 */
double get_exam_mark() {
    printf("Enter exam mark (out of %d): ", MAX_EXAM_MARK);
    double exam_mark;
    scanf("%lf", &exam_mark);

    if (exam_mark > MAX_EXAM_MARK) {
        exam_mark = MAX_EXAM_MARK;
    } else if (exam_mark < 0) {
        exam_mark = 0;
    }

    return exam_mark;
}

/*
 * This procedure will print out the available commands that can be chosen.
 */
void help() {
    printf("Enter a number corresponding to one of the following commands: \n");
    printf("0 (Help): Display program instructions\n");
    printf("1 (Display Student): Print the details of a specific student\n");
    printf("2 (Display Class): Print the details of all students in a class\n");
    printf("3 (Quit): Exit the program\n");
}

/*
 * This procedure will output the details of a student. The procedure will take
 * in a student struct as a parameter.
 */
void print_student_details(struct student student) {
    printf("z%07d: {\n", student.z_id);
    // Print student Details
    printf("\tDegree Type: ");
    if (student.degree_type == UGRD) {
        printf("Undergraduate\n");
    } else if (student.degree_type == PGRD) {
        printf("Postgraduate\n");
    } else {
        printf("INVALID\n");
    }

    if (student.degree_type == UGRD) {
        printf("\tMajor: ");
        if (student.major == COMPA1) {
            printf("Computer Science\n");
        } else if (student.major == COMPD1) {
            printf("Database Systems\n");
        } else if (student.major == COMPE1) {
            printf("eCommerce Systems\n");
        } else if (student.major == COMPI1) {
            printf("Artificial Intelligence\n");
        } else if (student.major == COMPJ1) {
            printf("Programming Languages\n");
        } else if (student.major == COMPN1) {
            printf("Computer Networks\n");
        } else if (student.major == COMPS1) {
            printf("Embedded Systems\n");
        } else if (student.major == COMPY1) {
            printf("Security Engineering\n");
        } else {
            printf("None\n");
        }
    }

    printf("\tAssignments Mark: %3.02lf/%d\n", student.assignments_mark, MAX_ASSIGMENTS_MARK);
    printf("\tExam Mark: %3.02lf/%d\n", student.exam_mark, MAX_EXAM_MARK);
    printf("\tCourse Grade: %3.02lf/%d\n", student.course_grade, MAX_ASSIGMENTS_MARK + MAX_EXAM_MARK);
    printf("}\n");
}

/* This function will scan in a zId and return it.*/
int get_z_id() {
    int z_id;
    scanf("%d", &z_id);
    return z_id;
}

/*
 * This function will scan in a zId and do a linear search through the array of class structs,
 * it will try to find a match for the zId scanned in. Once found it will return the position/index
 * of the class struct in the array.
 */
int get_student_index(int i, int class_size, struct student class[MAX_CLASS_SIZE]) {
    printf("Enter Student zID: ");
    int z_id = get_z_id();

    i = 0;
    while (i < class_size) {
        if (class[i].z_id == z_id) {
            return i;
        }
        i++;
    }
    return NOT_FOUND;
}

/*
 * This procedure will output an error message if an invalid zId is scanned in.
 */
void student_id_not_found() {
    printf("No student with that zID exists\n");
}

/*
 * This procedure will output an error message when an invalid command is chosen.
 */
void invalid() {
    printf("Invalid Command\n");
}

/*
 * The function will scan in a command and will correctly map the scanned in command
 * to the action it is supposed to perform. Returns a value of whether or not to keep
 * looping.
 */
int perform_command(int i, int class_size, struct student class[MAX_CLASS_SIZE]) {
    printf("Enter Command Number (0 for Help): ");
    int scanned_command;
    scanf("%d", &scanned_command);
    int command = 4;
    if (scanned_command >= 0 && scanned_command <= 3) {
        command = scanned_command;
    }

    if (command == HELP) {
        help();
    } else if (command == PRINT_STUDENT) {
        int student_index = get_student_index(i, class_size, class);
        printf("STUDENT ID: %d\n", student_index);
        if (student_index == NOT_FOUND) {
            student_id_not_found();
        } else {
            print_student_details(class[student_index]);
        }
    } else if (command == PRINT_CLASS) {
        printf("Students: \n");
        i = 0;
        while (i < class_size) {
            struct student student = class[i];
            print_student_details(student);
            i++;
        }
    } else if (command == QUIT) {
        return STOP_LOOPING;
    } else {
        invalid();
    }

    return KEEP_LOOPING;
}

int main(void) {
    int class_size;
    printf("Enter Class Size: ");
    scanf("%d", &class_size);

    if (class_size <= 0 || class_size > MAX_CLASS_SIZE) {
        printf("Class Size must be between 1 and %d\n", MAX_CLASS_SIZE);
        return 0;
    }

    struct student class[MAX_CLASS_SIZE];

    int i = 0;
    while (i < class_size) {
        struct student new_student;
        printf("Student %d: \n", i + 1);
        printf("Enter Student zID: ");
        new_student.z_id = get_z_id();
        new_student.degree_type = get_degree_type();
        new_student.major = get_major(new_student.degree_type);
        new_student.assignments_mark = get_assignments_mark();
        new_student.exam_mark = get_exam_mark();
        new_student.course_grade = new_student.exam_mark + new_student.assignments_mark;

        class[i] = new_student;
        i++;
    }

    int is_looping = KEEP_LOOPING;
    while (is_looping) {
        is_looping = perform_command(i, class_size, class);
    }

    printf("Exiting Program\n");

    return 0;
}