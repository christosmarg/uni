public class Main {
        public static void main(String[] args) {
                Point pt = new Point(50.55, 23.11);
                Pixel px = new Pixel(pt, 0xffaaee);
                Rectangle rect = new Rectangle();

                System.out.println(pt.toString());
                System.out.println(px.toString());
                rect.print();
                rect.info();
        }
}
