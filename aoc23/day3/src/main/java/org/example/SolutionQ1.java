package org.example;

import java.io.InputStream;
import java.util.*;

public class SolutionQ1 {
    HashMap<Integer, List<List<Integer> > > intMap = new HashMap<>();
    List<List<Integer> > symbolPos = new ArrayList<>();
    public void getInput() {
        InputStream inputStream = SolutionQ1.class.getClassLoader().getResourceAsStream("input1.txt");
        int index = 0;
        int result = 0;

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
            if(symPos.get(0) - 1 >= 0) {
                result += getSum(intMap.get(symPos.get(0) - 1), symPos.get(0) - 1, symPos.get(1), false);
            }
            result += getSum(intMap.get(symPos.get(0)), symPos.get(0), symPos.get(1), true);
            if(symPos.get(0) + 1 <= intMap.size()) {
                result += getSum(intMap.get(symPos.get(0) + 1), symPos.get(0) + 1, symPos.get(1), false);
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
            if(!Character.isDigit(input.charAt(i)) && !(input.charAt(i) == '.')) {
                result.add(List.of(index, i));
            }
        }

        return  result;
    }

    private int getSum(List<List<Integer> > intList, int start, int end, boolean sameRow) {
        int result = 0;
        List<List<Integer> > rmList = new ArrayList<>();
        int len = intList.size();

        for (List<Integer> curList : intList) {

            if (!sameRow && (Math.abs(curList.get(0) - end) <= 1 || Math.abs(curList.get(1) - end) <= 1)) {
                result += curList.get(2);
                rmList.add(curList);
            } else if (sameRow && (curList.get(0) == end + 1 || curList.get(1) == end - 1)) {
                result += curList.get(2);
                rmList.add(curList);
            }

        }

        for (List<Integer> i : rmList) {
            intMap.remove(i);
        }

        intMap.remove(start);
        intMap.put(start, intList);

        return result;
    }
}

