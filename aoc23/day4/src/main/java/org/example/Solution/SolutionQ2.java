package org.example.Solution;

import java.io.InputStream;
import java.util.Arrays;
import java.util.Objects;
import java.util.Scanner;

public class SolutionQ2 {
    int result = 0;
    public void getInput() {
        InputStream inputStream = SolutionQ1.class.getClassLoader().getResourceAsStream("input2.txt");
        final int size = 212;
        int[] copyArr = new int[size];
        int index = 1;

        if(inputStream != null) {
            try (Scanner scanner = new Scanner(inputStream)) {
                while(scanner.hasNext()) {
                    String input = scanner.nextLine();
                    int times = getWinTimes(input);
                    int end = 0;
                    if(times + index < size) {
                        end = times + index;
                    } else {
                        end = size;
                    }

                    for(int i = 0; i < copyArr[index - 1] + 1; i++) {
                        for(int j = index; j < end; j++) {
                            copyArr[j]++;
                        }
                    }
                    index++;
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }

        for(int i = 0; i < copyArr.length; i++) {
            result += copyArr[i] + 1;
        }
        System.out.println(result);
    }

    private int getWinTimes(String input) {
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
                    result++;
                    break;
                }
            }
        }

        return result;
    }
}
