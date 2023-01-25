Eric Uehling 
1.3.2023

Terminal Usage: 
1. make all
2. ./dist input.txt output.txt

The load function in main.c reads in the course list from input.txt and places each course in its according dynamically scalable data structure via functions from dist.c/dist.h. The main function in main.c then outputs each of the data structures into output.txt and frees the memory used to do so. To make the input file readable, CSVSorter.java was made to fix certain issues with the initial GradeDistribution.csv file. Said issues include commas in course titles and various sorting methods.