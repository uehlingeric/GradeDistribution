/* Eric Uehling     11.3.2022 */

package GradeDistribution.CSVSorter;
import java.io.*;
import java.util.*;

/* Eric Uehling
 * 1.3.2023
 * 
 * Usage (in terminal, in immediate directory): java CSVSorter.java
 * 
 * Description: Reads in csv file to remove commas from course names 
 *              and sort into lexicographical order and outputs as txt file.
 */
public class CSVSorter {
    private static final String IN = "C:\\Users\\Eric\\Desktop\\CS\\Personal Projects\\GradeDistribution\\CSVSorter\\GradeDistribution.csv";
    private static final String OUT = "C:\\Users\\Eric\\Desktop\\CS\\Personal Projects\\GradeDistribution\\CSVSorter\\input.txt";

    private ArrayList<String> list;
    
    /* Creates a CSVSorter object with an updated list of each course. */
    public CSVSorter() {
        list = new ArrayList<>();
        try {
            File file = new File(IN);
            Scanner in = new Scanner(file);
            while (in.hasNextLine()) {
                list.add(in.nextLine());
            }
            in.close();
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    /* Converts the ArrayList of courses into a String[][] while removing the commas from course titles. */
    private String[][] splitList() {
        String[][] newArr = new String[list.size()][23];

        for (int i = 0; i < list.size(); i++) {
            String[] course = list.get(i).split(",");
            while (course.length > 23) {
                String line = String.join(",", course);

                int count = 0;
                for (int j = 0; j < line.length(); j++) {
                    if (line.substring(j, j + 1).equals(",")) count++;
                    if (count == 5) {
                        line = line.substring(0, j) + line.substring(j + 1);
                        break;
                    }
                }

                course = line.split(",");
            }
            newArr[i] = course;
        }

        return newArr;
    }

    /* Reads two String[] objects (courses) and returns the compared value. */
    private static Comparator<String[]> comparator = new Comparator<String[]>() {
        @Override
        public int compare(String[] x, String[] y) {
            int xx = Integer.parseInt(x[3]);
            int yy = Integer.parseInt(y[3]);

            if (x[2].compareTo(y[2]) < 0) {
                return -1;
            }
            else if (x[2].compareTo(y[2]) > 0) {
                return 1;
            }
            else if (xx < yy) {
                return -1;
            }
            else if (xx > yy) {
                return 1;
            }
            else if (x[5].compareTo(y[5]) < 0) {
                return -1;
            }
            else if (x[5].compareTo(y[5]) > 0) {
                return 1;
            }
            return 0;
        }
    }; 

    /* Creates and writes the updated (readable) input file for dist.exe. */
    public void writeFile() {
        try {
            FileWriter fWriter = new FileWriter(OUT);
            String[][] arr = splitList();
            Arrays.sort(arr, comparator);

            for (int i = 0; i < arr.length; i++) {
                String line = String.join(",", arr[i]);
                fWriter.write(line);
                fWriter.write("\n");
            }
            fWriter.close();
        }
        catch (Exception e) {
            System.out.println("Error");
        }
    }

    public static void main(String[] args) {  
        CSVSorter sort = new CSVSorter();
        sort.writeFile();
    }
}