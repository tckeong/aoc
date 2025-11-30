package org.example.Solution;

import java.io.InputStream;
import java.util.*;

public class SolutionQ2 {
    Long result = 0L;
    List<List<Long>> mapList;
    List<Long> seed;
    List<Long> finalList;
    public SolutionQ2 () {
        mapList = new ArrayList<>();
        seed = new ArrayList<>();
        finalList = new ArrayList<>();

        getInput("input2.txt");

        result = Collections.min(finalList);
        System.out.println(result);
    }
    public void getInput(String filePath) {
        InputStream inputStream = SolutionQ1.class.getClassLoader().getResourceAsStream(filePath);

        if(inputStream != null) {
            try (Scanner scanner = new Scanner(inputStream)) {
                seed.addAll(modifyInput(scanner.nextLine().split(":")[1]));
                while (scanner.hasNext()) {
                    String input = scanner.nextLine();
                    handleInput(input);
                }
            } catch (Exception e) {
                throw e;
            }
        }


        getSolution();
    }

    private void handleInput(String input) {
        boolean valid = true;
        for(int i = 0; i < input.length(); i++) {
            valid = (input.charAt(i) != ':') && valid;
        }

        if(valid) {
            List<Long> temp = modifyInput(input);
            if(!(temp.size() == 0 && mapList.size() == 0)) {
                mapList.add(temp);
            }
        }
    }

    private List<Long> modifyInput(String input) {
        String[] temp = input.split(" ");
        List<Long> result = new ArrayList<>();

        for(String str : temp) {
            if(!Objects.equals(str, "")) {
                result.add(Long.parseLong(str));
            }
        }

        return result;
    }

    private void getSum(List<Long> localSeed) {
        List<List<Long> > temp = new ArrayList<>();

        for(List<Long> ls : mapList) {
            if(ls.size() == 0 && temp.size() > 0) {
                for(int i = 0; i < localSeed.size(); i++) {
                    for(List<Long> j : temp) {
                        if(localSeed.get(i) >= j.get(1) && localSeed.get(i) < j.get(1) + j.get(2)) {
                            localSeed.set(i, localSeed.get(i) - j.get(1) + j.get(0));
                            break;
                        }
                    }
                }

                temp.clear();
            } else {
                temp.add(ls);
            }
        }

        for(int i = 0; i < localSeed.size(); i++) {
            for(List<Long> j : temp) {
                if(localSeed.get(i) >= j.get(1) && localSeed.get(i) < j.get(1) + j.get(2)) {
                    localSeed.set(i, localSeed.get(i) - j.get(1) + j.get(0));
                    break;
                }
            }
        }

        finalList.add(Collections.min(localSeed));
    }

    private void getSolution() {
        List<Long> tempSeed = new ArrayList<>();
        int step = 10000000;

        for(int i = 0; i < seed.size(); i += 2) {
            for(int j = 0; j < seed.get(i + 1); j += step) {
                long end = ((j+step) < seed.get(i+1)) ? j+step : seed.get(i+1);
                for(int k = j; k < end; k++) {
                    tempSeed.add(seed.get(i) + k);
                }
                getSum(tempSeed);
                tempSeed.clear();
            }
        }
    }
}
