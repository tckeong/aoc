package org.example;

import java.io.*;
import java.util.Arrays;
import java.util.Scanner;

public class Solution {
    public void getInput() {
        // Use class loader to load the file from the resources folder
        InputStream inputStream = Solution.class.getClassLoader().getResourceAsStream("input.txt");
        int result = 0;

        if (inputStream != null) {
            try (Scanner scanner = new Scanner(inputStream)) {
                while (scanner.hasNextLine()) {
                    String input = scanner.nextLine();
                    result += analyseInputQ2(input);
                }
            }
        } else {
            System.out.println("File not found.");
        }

        System.out.println(result);
    }

    private int analyseInputQ1(String input) {
        String[] inputSplit = input.split(":");
        String[] colorSplit = inputSplit[1].split(";");

        for (String value : colorSplit) {
            String[] tempSplit = value.split(",");
            for (String s : tempSplit) {
                String[] finalSplit = s.split(" ");
                switch (finalSplit[2]) {
                    case "red" -> {
                        if (Integer.parseInt(finalSplit[1]) > 12) {
                            return 0;
                        }
                    }
                    case "blue" -> {
                        if (Integer.parseInt(finalSplit[1]) > 14) {
                            return 0;
                        }
                    }
                    case "green" -> {
                        if (Integer.parseInt(finalSplit[1]) > 13) {
                            return 0;
                        }
                    }
                    default -> {
                    }
                }
            }
        }

        return Integer.parseInt(inputSplit[0].split(" ")[1]);
    }

    private int analyseInputQ2(String input) {
        String[] inputSplit = input.split(":");
        String[] colorSplit = inputSplit[1].split(";");

        int red = 0;
        int blue = 0;
        int green = 0;

        for (String value : colorSplit) {
            String[] tempSplit = value.split(",");
            for (String s : tempSplit) {
                String[] finalSplit = s.split(" ");
                switch (finalSplit[2]) {
                    case "red" -> {
                        red = Math.max(red, Integer.parseInt(finalSplit[1]));
                    }
                    case "blue" -> {
                        blue = Math.max(blue, Integer.parseInt(finalSplit[1]));
                    }
                    case "green" -> {
                        green = Math.max(green, Integer.parseInt(finalSplit[1]));
                    }
                    default -> {
                    }
                }
            }
        }

        return red * blue * green;
    }
}
