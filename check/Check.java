import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class Check {
    public static void main(String[] args) {
        File ref = new File("../data/dat" + args[0] + "_ref");
        File out = new File("../out/dat" + args[0] + "_out");

        String co = null;
        try {
            co = new BufferedReader(new FileReader(ref)).readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        String ch = null;
        try {
            ch = new BufferedReader(new FileReader(out)).readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }

        char[] sco = co != null ? co.toCharArray() : new char[0];
        char[] sch = ch != null ? ch.toCharArray() : new char[0];

        int sum = 0;
        for (int i = 0; i < sco.length; i++) {
            if (sco[i] == sch[i]) sum++;
        }
        System.out.println(args[0] + ": " + (sum / (double) sco.length * 100.0) + "%");
    }
}
