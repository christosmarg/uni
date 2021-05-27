public class RecursiveRev {
        public static String strrev(String s) {
                if (s.isEmpty())
                        return s;
                else
                        return strrev(s.substring(1)) + s.charAt(0);
        }

        public static void main(String[] args) {
                String s = "Hello world";

                System.out.println(strrev(s));
        }
}
