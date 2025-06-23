import java.util.HashSet;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    public static Set<String> getWords(String text) {
        Set<String> words = new HashSet<>();
        String rex = "\\b\\w+\\b";
        Matcher matcher = Pattern.compile(rex).matcher(text);
        while (matcher.find()) {
            words.add(matcher.group());
        }
        return words;
    }

    public static void main(String[] args) {
        String std = new String(
                "PITTSBURGH (AP) — Carnegie Mellon University will hire a researcher from the Library of Congress to help it decode a collection that includes two WWII German Enigma machines."
                        +
                        "The university wants to encourage the study of 19th and 20th century computers, calculators, encryption machines and other materials related to the history of computer science."
                        +
                        "“When we look back and we see this, we see who we remember,” Andrew Moore, dean of CMU’s School of Computer Science, said, adding his students are increasingly asking for courses about the history of the field. “We see people who took technology to save lives and save the world.”"
                        +
                        "Pamela McCorduck, a prolific author on the history and future of artificial intelligence and the widow of Joseph Traub, a renowned computer scientist and the former head of CMU’s Computer Science Department, permanently loaned to the university a collection of early computers, books and letters. The collection, anchored by a three-rotor and four-rotor Enigma machine, is on display in the Fine and Rare Book Room in CMU’s Hunt Library in Oakland. The gift makes CMU one of a few institutions in the United States with Enigma machines. Even fewer display them.\r\n");
        Set<String> words = getWords(std);
        int count = 0;
        for (String word : words) {
            if (count < 6) {
                System.out.print(word + " ");
                count++;
            } else {
                System.out.println(word);
                count = 0;
            }
        }
    }
}