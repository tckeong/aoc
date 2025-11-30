package org.example;

import java.io.InputStream;
import java.util.*;

public class SolutionQ2 {
    HashMap<Integer, List<List<Integer> > > intMap = new HashMap<>();
    List<List<Integer> > symbolPos = new ArrayList<>();
    int result = 0;

    public void getInput() {
        InputStream inputStream = SolutionQ1.class.getClassLoader().getResourceAsStream("input1.txt");
        int index = 0;

        if(inputStream != null) {
            try (Scanner scanner = new Scanner(inputStream)) {
                while (scanner.hasNext()) {
                    String input = scanner.nextLine();
                    intMap.put(index, getNum(input));
                    symbolPos.addAll(getSymbolPos(input, index));
                    index++;
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }

        for (List<Integer> symPos : symbolPos) {
            if(check(symPos)) {
                int result1 = getSum(intMap.get(symPos.get(0)), symPos.get(1), true, true);
                if (result1 != -1) {
                    result += result1;
                } else {
                    result1 = getSum(intMap.get(symPos.get(0) - 1), symPos.get(1), false, false);
                    int result2 = getSum(intMap.get(symPos.get(0)), symPos.get(1), true, false);
                    int result3 = getSum(intMap.get(symPos.get(0) + 1), symPos.get(1), false, false);

                    result += result1 * result2 * result3;
                }
            }
        }

        System.out.println(result);
    }

    private List<List<Integer> > getNum(String input) {
        List<List<Integer> > result = new ArrayList<>();
        for(int i = 0; i < input.length(); i++) {
            if(Character.isDigit(input.charAt(i))) {
                StringBuilder tempStr = new StringBuilder();
                int tempStart = i;
                for(int j = i; j < input.length() && Character.isDigit(input.charAt(j)); j++) {
                    tempStr.append(input.charAt(j));
                    i = j;
                }
                result.add(List.of(tempStart, i, Integer.parseInt(String.valueOf(tempStr))));
            }
        }

        return result;
    }

    private List<List<Integer> > getSymbolPos(String input, int index) {
        List<List<Integer> > result = new ArrayList<>();

        for(int i = 0; i < input.length(); i++) {
            if(input.charAt(i) == '*') {
                result.add(List.of(index, i));
            }
        }

        return  result;
    }

    private int getSum(List<List<Integer> > intList,int end, boolean sameRow, boolean exact) {
        if(exact) {
            return (intList.size() == 2) ? intList.get(0).get(2) * intList.get(1).get(2) : -1;
        } else {
            int result = 1;
            int len = intList.size();

            for (List<Integer> curList : intList) {

                if (!sameRow && (Math.abs(curList.get(0) - end) <= 1 || Math.abs(curList.get(1) - end) <= 1)) {
                    result *= curList.get(2);
                } else if (sameRow && (curList.get(0) == end + 1 || curList.get(1) == end - 1)) {
                    result *= curList.get(2);
                }

            }

            return result;
        }
    }

    private boolean check(List<Integer> symPos) {
        int row = symPos.get(0);
        int col = symPos.get(1);

        int valid = 0;

        List<List<Integer> > iList = intMap.get(row);
        for (List<Integer> curList : iList) {
            if((Math.abs(curList.get(0) - col) <= 1 || Math.abs(curList.get(1) - col) <= 1)) {
                valid++;
            }
        }

        if(row - 1 >= 0) {
            iList = intMap.get(row - 1);
            for (List<Integer> curList : iList) {
                if((Math.abs(curList.get(0) - col) <= 1 || Math.abs(curList.get(1) - col) <= 1)) {
                    valid++;
                }
            }
        }

        if(row + 1 < intMap.size()) {
            iList = intMap.get(row + 1);
            for (List<Integer> curList : iList) {
                if((Math.abs(curList.get(0) - col) <= 1 || Math.abs(curList.get(1) - col) <= 1)) {
                    valid++;
                }
            }
        }

        return valid == 2;
    }
}

