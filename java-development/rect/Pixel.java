class Pixel extends Point {
        int color;
        static int n = 0;

        Pixel() {
                super(0.0, 0.0f);
                this.color = 0x000000;
                n++;
        }

        Pixel(double x, double y, int color) {
                super(x, y);
                this.color = color;
                n++;
        }

        Pixel(Point p, int color) {
                super(p);
                this.color = color;
                n++;
        }

        public String toString() {
                return "x: " + x + "\ty: " + y + "\tcolor: " +
                    String.format("0x%06X", color);
        }
}
