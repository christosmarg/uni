class Rectangle {
        private Point pts[];

        Rectangle() {
                pts = new Point[4];
                for (int i = 0; i < pts.length; i++)
                        pts[i] = new Point(0.0, 0.0);
        }

        Rectangle(Point[] p) {
                pts = p;
        }

        public Point[] getpoints() {
                return pts;
        }

        public double width() {
                return Math.abs(pts[1].x - pts[0].x);
        }

        public double height() {
                return Math.abs(pts[2].y - pts[1].y);
        }

        public void info() {
                System.out.println("Top:    " + pts[0]);
                System.out.println("Width:  " + width());
                System.out.println("Height: " + height());
        }

        public void print() {
                for (Point p : pts)
                        System.out.print(p.toString() + " ");
                System.out.println();
        }
}
