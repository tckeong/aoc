package org.example;

import java.util.Scanner;

public class Solution {
    public Solution() {
        Scanner scanner = new Scanner(System.in);

        String input = "";
        int result = 0;

        while(!input.equals("end")) {
            input = scanner.nextLine();
            result += getNumber(input);
        }

        System.out.println(result);
    }

    private int getNumber(String input) {
        int a = -1;
        int b = -1;

        for(int i = 0; i < input.length(); i++) {
            int tempNum = parseNumber((input.substring(i)));
            if(Character.isDigit(input.charAt(i)) || tempNum != 0) {
                if(a == -1) {
                    a = (tempNum != 0) ? tempNum : input.charAt(i) - '0';
                }
                b = (tempNum != 0) ? tempNum : input.charAt(i) - '0';
            }
        }

        if(a == -1 && b == -1) {
            return 0;
        } else if(a != -1 && b == -1) {
            return a * 10 + a;
        } else {
            return a * 10 + b;
        }
    }

    private int parseNumber(String input) {
        int result = 0;
        try {
            for(int i = 0; i < 10; i++) {
                if (input.startsWith("one")) {
                    result = 1;
                } else if (input.startsWith("two")) {
                    result = 2;
                } else if (input.startsWith("three")) {
                    result = 3;
                } else if (input.startsWith("four")) {
                    result = 4;
                } else if (input.startsWith("five")) {
                    result = 5;
                } else if (input.startsWith("six")) {
                    result = 6;
                } else if (input.startsWith("seven")) {
                    result = 7;
                } else if (input.startsWith("eight")) {
                    result = 8;
                } else if (input.startsWith("nine")) {
                    result = 9;
                }
            }
        } catch(Exception e) {
            result = 0;
        }
        return result;
    }
}
