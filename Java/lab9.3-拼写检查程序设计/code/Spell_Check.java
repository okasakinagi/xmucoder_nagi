import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Spell_Check {
    private Set<String> dictionary;
    private String cur_check;

    Spell_Check(String dictionary) {
        this.dictionary = new HashSet<String>(Arrays.asList(dictionary.split(" ")));
    }

    public String check(String word) {
        this.cur_check = word;
        if (dictionary.contains(word)) {
            return word;
        } else {
            Set<String> choice = new HashSet<String>();
            choice.addAll(generate_double());
            choice.addAll(generate_swap());
            choice.addAll(generate_keyboard());
            for (String i : choice) {
                if (dictionary.contains(i)) {
                    return i;
                }
            }
        }
        return null;
    }

    private Set<String> generate_double() {
        Set<String> result = new HashSet<String>();
        for (int i = 0; i < cur_check.length() - 2; i++) {
            if (cur_check.charAt(i) == cur_check.charAt(i + 1)) {
                result.add(cur_check.substring(0, i) + cur_check.substring(i + 1));
            }
        }
        return result;
    }

    private Set<String> generate_swap() {
        Set<String> result = new HashSet<String>();
        for (int i = 0; i < cur_check.length() - 3; i++) {
            result.add(cur_check.substring(0, i) + cur_check.substring(i + 1, i + 2) + cur_check.substring(i, i + 1)
                    + cur_check.substring(i + 2));
        }
        return result;
    }

    private Set<String> generate_keyboard() {
        ArrayList<Character> up = new ArrayList<>(Arrays.asList('q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'));
        ArrayList<Character> mid = new ArrayList<>(Arrays.asList('a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'));
        ArrayList<Character> down = new ArrayList<>(Arrays.asList('z', 'x', 'c', 'v', 'b', 'n', 'm'));
        Set<String> result = new HashSet<String>();
        int idx;
        for (int i = 0; i < cur_check.length(); i++) {
            char cur = cur_check.charAt(i);
            if ((idx = up.indexOf(cur)) != -1) {
                if (idx > 0) {
                    result.add(cur_check.substring(0, i) + up.get(idx - 1) + cur_check.substring(i + 1));
                    result.add(cur_check.substring(0, i) + mid.get(idx - 1) + cur_check.substring(i + 1));

                }
                if (idx < 9) {
                    result.add(cur_check.substring(0, i) + up.get(idx + 1) + cur_check.substring(i + 1));
                    result.add(cur_check.substring(0, i) + mid.get(idx) + cur_check.substring(i + 1));
                }
            } else if ((idx = mid.indexOf(cur)) != -1) {
                result.add(cur_check.substring(0, i) + up.get(idx + 1) + cur_check.substring(i + 1));
                result.add(cur_check.substring(0, i) + up.get(idx) + cur_check.substring(i + 1));
                if (idx > 0) {
                    result.add(cur_check.substring(0, i) + mid.get(idx - 1) + cur_check.substring(i + 1));
                    if (idx < 8)
                        result.add(cur_check.substring(0, i) + down.get(idx - 1) + cur_check.substring(i + 1));
                }
                if (idx < 8)
                    result.add(cur_check.substring(0, i) + mid.get(idx + 1) + cur_check.substring(i + 1));

                if (idx < 7)
                    result.add(cur_check.substring(0, i) + down.get(idx) + cur_check.substring(i + 1));
            } else if ((idx = down.indexOf(cur)) != -1) {
                result.add(cur_check.substring(0, i) + up.get(idx + 1) + cur_check.substring(i + 1));
                result.add(cur_check.substring(0, i) + up.get(idx) + cur_check.substring(i + 1));
                if (idx > 0)
                    result.add(cur_check.substring(0, i) + down.get(idx - 1) + cur_check.substring(i + 1));
                if (idx < 6)
                    result.add(cur_check.substring(0, i) + down.get(idx) + cur_check.substring(i + 1));
            } else
                throw new IllegalArgumentException("Check keyboard array");
        }
        return result;
    }
}
