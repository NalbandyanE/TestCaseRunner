import java.io.*;
import java.util.*;

public class check {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter 'RUN' or 'SUBMIT': ");
        String button = "";
        button = scanner.nextLine().toUpperCase();
        String file_name = "";
        if(button.equals("RUN")){
            file_name = "run_cases.txt";
        } 
        if(button.equals("SUBMIT")){
            file_name = "submit_cases.txt";
        }  
        scanner.close();
        try (BufferedReader br = new BufferedReader(new FileReader(file_name));
                BufferedWriter bw = new BufferedWriter(new FileWriter("result.txt"))) {
            String line;
            List<Boolean> results = new ArrayList<>();
            int line_count = 0;
            while ((line = br.readLine()) != null) {
                ++line_count;
                String[] parts = line.split(" ");
                if (parts.length == 3) {
                    int a = Integer.parseInt(parts[0]);
                    int b = Integer.parseInt(parts[1]);
                    int c = Integer.parseInt(parts[2]);
                    int trueSum = c;
                    int yourSum = Main.solution(a, b);
                    boolean result = (yourSum == trueSum);
                    results.add(result);
                    if (!result) {
                        bw.write("Case " + line_count + " is false\n");
                        bw.write("Expected: " + trueSum + "\n");
                        bw.write("Output: " + yourSum + "\n");
                    }
                } else {
                    System.err.println("Error parsing line " + line_count);
                    System.exit(1);
                }
            }
            boolean all_results = true;
            for (boolean r : results) {
                if (!r) {
                    all_results = false;
                    break;
                }
            }
            if (all_results) {
                bw.write("Success\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}