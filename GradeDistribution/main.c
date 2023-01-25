/* Eric Uehling     1.3.2023 */

#include "dist.h"

#include <stdio.h>
#include <string.h>

#define COMMAND_SIZE 50

/* Transfers the data from the input file into respective data structures. */
void load(char* filename, struct Grade_Distribution* grade_dist) {
    FILE* in = fopen(filename, "r");
    char title[COMMAND_SIZE];
    char year[COMMAND_SIZE];
    char instructor[COMMAND_SIZE];
    char subject[COMMAND_SIZE];
    int num;
    char term[COMMAND_SIZE];
    double gpa;

    while (!feof(in)) {
        fscanf(in, "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%lf,%*[^\n]\n", year, term, subject, &num, title, instructor, &gpa);

        int new_dept = 1;
        for (int i = 0; i < grade_dist->count; i++) {
            if (!strcmp(grade_dist->departments[i].name, subject)) {
                new_dept = 0;
                int new_course = 1;
                for (int j = 0; j < grade_dist->departments[i].count; j++) {
                    if (!strcmp(grade_dist->departments[i].courses[j].name, title) && grade_dist->departments[i].courses[j].num == num) {
                        new_course = 0;
                        int new_instructor = 1;
                        for (int k = 0; k < grade_dist->departments[i].courses[j].count; k++) { 
                            if (!strcmp(grade_dist->departments[i].courses[j].instructors[k].name, instructor)) {
                                new_instructor = 0;
                                grade_dist->departments[i].courses[j].instructors[k].gpa_sum += gpa;
                                grade_dist->departments[i].courses[j].instructors[k].num_classes++;
                                break;
                            }
                        }
                        if (new_instructor) {
                            struct Instructor inst;
                            init_inst(&inst);
                            update_inst(&inst, instructor, 1, gpa);
                            add_inst(&grade_dist->departments[i].courses[j], inst);
                        }
                        break;
                    }
                }
                if (new_course) {
                    struct Course course;
                    init_course(&course, 5);
                    update_course(&course, title, subject, num);
                    
                    struct Instructor inst;
                    init_inst(&inst);
                    update_inst(&inst, instructor, 1, gpa);

                    add_inst(&course, inst);
                    add_course(&grade_dist->departments[i], course);
                }
                break;
            }
        }
        if (new_dept) {
            struct Department dept;
            init_dept(&dept, 50);
            update_dept(&dept, subject);

            struct Course course;
            init_course(&course, 10);
            update_course(&course, title, subject, num);
            
            struct Instructor inst;
            init_inst(&inst);
            update_inst(&inst, instructor, 1, gpa);

            add_inst(&course, inst);
            add_course(&dept, course);
            add_dept(grade_dist, dept);
        }
    }
    fclose(in);
}

/* Eric Uehling
 * 1.3.2023
 * 
 * Usage (in terminal, in immediate directory): ./dist input.txt output.txt
 * 
 * Description: Reads input file from a list of courses to create a 
 *              plethora of dynamically scalable data structures to produce 
 *              an output file containing the average gpa of each instructor.
 */
int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	struct Grade_Distribution grade_dist;
    init_dist(&grade_dist, 200);
    load(argv[1], &grade_dist);
    
    FILE* out = fopen(argv[2], "w");
    display_dist(out, grade_dist);

    free_dist(grade_dist);
	fclose(out);
	return 0;
}
