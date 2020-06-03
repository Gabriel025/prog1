package prog1.welch;

import java.util.Random;

public class polar {
    Random rand;
    boolean hasStoredValue;
    double storedValue;

    public polar() {
        rand = new Random();
        hasStoredValue = false;
    }

    public polar(long seed) {
        rand = new Random(seed);
        hasStoredValue = false;
    }

    double next() {
        if(hasStoredValue) {
            hasStoredValue = false;
            return storedValue;
        }

        double v1, v2, w;

        do {
            v1 = rand.nextDouble() * 2 - 1;
            v2 = rand.nextDouble() * 2 - 1;
            w = v1 * v1 + v2 * v2;
        } while(w > 1);

        double r = Math.sqrt(-2.0 * Math.log(w) / w);

        hasStoredValue = true;
        storedValue = r * v2;

        return r * v1;
    }

    public static void main(String args[]) {
        polar p = new polar();
        for(int i = 0; i < 10; i++) {
            System.out.println(p.next());
        }
    }
}