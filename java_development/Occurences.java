import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Occurences {
        public static void main(String[] args) {
                ArrayList<String> strs = new ArrayList<String>();
                HashMap<String, Integer> occ = new HashMap<String, Integer>();

                strs.add("foo");
                strs.add("foo");
                strs.add("foo");
                strs.add("bar");
                strs.add("baz");
                strs.add("baz");

                for (String s : strs)
                        occ.put(s, 1 + (occ.containsKey(s) ? occ.get(s) : 0));
                for (Map.Entry<String, Integer> e : occ.entrySet())
                        System.out.println(e.getKey() + ": " + e.getValue());
        }
}
