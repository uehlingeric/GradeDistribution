/* Eric Uehling     1.3.2023 */

#include "dist.h"

#include <stdio.h>
#include <string.h>

/* Initializes an Instructor struct. */
void init_inst(struct Instructor* inst) {
    inst->gpa_sum = 0;
    inst->num_classes = 0;
    inst->name = NULL;
}

/* Creates memory and sets values for Instructor struct. */
void update_inst(struct Instructor* inst, char* name, int num_classes, double gpa_sum) {
    if (inst->name != NULL) free_inst(*inst);
    inst->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(inst->name, name);
    inst->num_classes = num_classes;
    inst->gpa_sum = gpa_sum;
}

/* Displays Instructor struct. */
void display_inst(FILE* out, struct Instructor inst) {
    double gpa = inst.gpa_sum / inst.num_classes;
    fprintf(out, "\t\tIntstructor: %s, Average GPA: %f, Number of Classes: %d\n", inst.name, gpa, inst.num_classes);
}

/* Frees memory of Instructor struct. */
void free_inst(struct Instructor inst) {
    free(inst.name);
}

/* Initializes an Course struct. */
void init_course(struct Course* course, int size) {
    course->instructors = calloc(size, sizeof(struct Instructor) + 1);
    course->num = 0;
    course->name = NULL;
    course->dept = NULL;
    course->count = 0;
    course->size = size;
}

/* Creates memory and sets values for Course struct. */
void update_course(struct Course* course, char* name, char* dept, int num) {
    if (course->name != NULL || course->dept != NULL) free_course(*course);
    course->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(course->name, name);
    course->dept = calloc(strlen(dept) + 1, sizeof(char));
    strcpy(course->dept, dept);
    course->num = num;
}

/* Dynamically adds an Instructor struct to a Course struct.*/
void add_inst(struct Course* course, struct Instructor instructor) {
    if (course->count == course->size) {
        course->size *= 2;
        course->instructors = realloc(course->instructors, course->size * sizeof(struct Instructor) + 1);
    }
    course->instructors[course->count] = instructor;
    course->count++;
}

/* Displays Course struct. */
void display_course(FILE* out, struct Course course) {
    fprintf(out, "\tCourse: %s %d - %s\n", course.dept, course.num, course.name);
    for (int i = 0; i < course.count; i++) {
        display_inst(out, course.instructors[i]);
    }
}

/* Frees memory of Course struct. */
void free_course(struct Course course) {
    for (int i = 0; i < course.count; i++) {
        free_inst(course.instructors[i]);
    }
    free(course.instructors);
    free(course.name);
}

/* Initializes an Department struct. */
void init_dept(struct Department* depart, int size) {
    depart->courses = calloc(size, sizeof(struct Course) + 1);
    depart->count = 0;
    depart->name = NULL;
    depart->size = size;
}

/* Creates memory and sets values for Department struct. */
void update_dept(struct Department* depart, char* name) {
    if (depart->name != NULL) free_dept(*depart);
    depart->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(depart->name, name);
}

/* Dynamically adds an Course struct to a Department struct.*/
void add_course(struct Department* depart, struct Course course) {
    if (depart->count == depart->size) {
        depart->size *= 2;
        depart->courses = realloc(depart->courses, depart->size * sizeof(struct Course) + 1);
    }
    depart->courses[depart->count] = course;
    depart->count++;
}

/* Displays Department struct. */
void display_dept(FILE* out, struct Department depart) {
    fprintf(out, "Department: %s\n", depart.name);
    for (int i = 0; i < depart.count; i++) {
        display_course(out, depart.courses[i]);
    }
}

/* Frees memory of Department struct. */
void free_dept(struct Department depart) {
    for (int i = 0; i < depart.count; i++) {
        free_course(depart.courses[i]);
    }
    free(depart.courses);
    free(depart.name);
}

/* Initializes an Grade_Distribution struct. */
void init_dist(struct Grade_Distribution* grade_dist, int size) {
    grade_dist->departments = calloc(size, sizeof(struct Department) + 1);
    grade_dist->count = 0;
    grade_dist->size = size;
}

/* Dynamically adds an Department struct to a Grade_Distribution struct.*/
void add_dept(struct Grade_Distribution* grade_dist, struct Department depart) {
    if (grade_dist->count == grade_dist->size) {
        grade_dist->size *= 2;
        grade_dist->departments = realloc(grade_dist->departments, grade_dist->size * sizeof(struct Department) + 1);
    }
    grade_dist->departments[grade_dist->count] = depart;
    grade_dist->count++;
}

/* Displays Grade_Distribution struct. */
void display_dist(FILE* out, struct Grade_Distribution grade_dist) {
    fprintf(out, "Grade Distribution: 2018 Fall - 2023 Fall\n\n");
    for (int i = 0; i < grade_dist.count; i++) {
        display_dept(out, grade_dist.departments[i]);
    }
}

/* Frees memory of Grade_Distribution struct. */
void free_dist(struct Grade_Distribution grade_dist) {
    for (int i = 0; i < grade_dist.count; i++) {
        free_dept(grade_dist.departments[i]);
    }
    free(grade_dist.departments);
}