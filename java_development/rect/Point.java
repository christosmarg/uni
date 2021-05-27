class Point {
        double x;
        double y;

        Point() {
                this.x = 0.0;
                this.y = 0.0;
        }

        Point(double x, double y) {
                this.x = x;
                this.y = y;
        }
        
        Point(Point p) {
                this.x = p.x;
                this.y = p.y;
        }

        public String toString() {
                return "(" + x + ", " + y + ")";
        }
}
