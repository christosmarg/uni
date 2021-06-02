package population;

public class Main {
	public static void main(String[] args) {
		ExcelParser ep;
		
		try {
			ep = new ExcelParser(args[0]);
		} catch (IndexOutOfBoundsException e) {
			System.err.println("usage: population xlsx_file");
		} catch (Exception e) {
			System.err.println(e);
		}
	}
}