package org.example.Solution;

import java.io.InputStream;
import java.util.Arrays;
import java.util.Objects;
import java.util.Scanner;

public class SolutionQ1 {
    int result = 0;
    public void getInput() {
        InputStream inputStream = SolutionQ1.class.getClassLoader().getResourceAsStream("input2.txt");

        if(inputStream != null) {
            try (Scanner scanner = new Scanner(inputStream)) {
                while(scanner.hasNext()) {
                    String input = scanner.nextLine();
                    result += getNum(input);
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }

        System.out.println(result);
    }

    private int getNum(String input) {
        int result = 0;
        String[] inputSplit = input.split("\\|");

        String[] winningNumbers = Arrays.stream(inputSplit[0].split(" "))
                                         .filter(i -> !Objects.equals(i, ""))
                                         .toArray(String[]::new);

        String[] mine = Arrays.stream(inputSplit[1].split(" "))
                              .filter(i -> !Objects.equals(i, ""))
                              .toArray(String[]::new);

        for(int i = 2; i < winningNumbers.length; i++) {
            for(int j = 0; j < mine.length; j++) {
                if(Integer.parseInt(winningNumbers[i]) == Integer.parseInt(mine[j])) {
                    result = (result == 0) ? 1 : result * 2;
                    break;
                }
            }
        }


        return result;
    }
}
