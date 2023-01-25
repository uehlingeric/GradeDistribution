/* Eric Uehling     1.3.2023 */

#ifndef DIST_H
#define DIST_H

#include <stdlib.h>
#include <stdio.h>

struct Instructor
{
	char* name;
	int num_classes;
	double gpa_sum;
};

struct Course
{
	struct Instructor* instructors;
	int num;
	char* name;
	char* dept;
	int size;
	int count;
};

struct Department
{
	struct Course* courses;
	char* name;
	int size;
	int count;
};

struct Grade_Distribution
{
	struct Department* departments;
	int size;
	int count;
};

// instructor functions
void init_inst(struct Instructor* inst);
void update_inst(struct Instructor* inst, char* name, int num_Classes, double gpa_sum);
void display_inst(FILE* out, struct Instructor inst);
void free_inst(struct Instructor inst);

// course functions
void init_course(struct Course* course, int size);
void update_course(struct Course* course, char* name, char* dept, int num);
void add_inst(struct Course* course, struct Instructor instructor);
void display_course(FILE* out, struct Course course);
void free_course(struct Course course);

// department functions
void init_dept(struct Department* depart, int size);
void update_dept(struct Department* depart, char* name);
void add_course(struct Department* depart, struct Course course);
void display_dept(FILE* out, struct Department depart);
void free_dept(struct Department depart);

// grade_distribution functions
void init_dist(struct Grade_Distribution* grade_dist, int size);
void add_dept(struct Grade_Distribution* grade_dist, struct Department depart);
void display_dist(FILE* out, struct Grade_Distribution grade_dist);
void free_dist(struct Grade_Distribution grade_dist);

#endif
