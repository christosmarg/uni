package population;

import java.io.*;
import java.util.ArrayList;

public class Main {
	public static void main(String[] args) throws Exception {
		ExcelParser ep;
		ArrayList<Country> countries;
		String path = "";
		
		try {
			path = args[0];
			ep = new ExcelParser(path);
			countries = ep.get_countries();
		} catch (FileNotFoundException e) {
			System.err.println(path + ": no such file");
			return;
		} catch (IndexOutOfBoundsException e) {
			System.err.println("usage: population xlsx_file");
			return;
		} catch (IOException e) {
			System.err.println(path + ": io error");
			return;
		}
	}
}