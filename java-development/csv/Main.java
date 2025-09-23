import java.io.*;
import java.util.ArrayList;

class Main {
	public static void main(String[] args) {
		ArrayList<Movie> movies = new ArrayList<Movie>();
		BufferedReader br;
		File f;
		String fields[] = new String[3];
		String str;
		String sortby;

		try {
			sortby = args[0];
			f = new File(args[1]);
			br = new BufferedReader(new FileReader(f));

			while ((str = br.readLine()) != null) {
				fields = str.split("\\|");
				movies.add(new Movie(fields[0],
				    Integer.parseInt(fields[1]),
				    Float.parseFloat(fields[2])));
			}
			br.close();
		} catch (FileNotFoundException e) {
			System.err.println("file not found");
			return;
		} catch (IOException e) {
			System.err.println("IO Excetion");
			return;
		} catch (ArrayIndexOutOfBoundsException e) {
			System.err.println("usage: java Main sortby file\n");
			System.err.println("You can sort by:\n\ttitle\n\tyear\n\tprice");
			return;
		}

		if (sortby.equals("title"))
			movies.sort((o1, o2) -> o1.get_title().compareTo(o2.get_title()));
		else if (sortby.equals("year"))
			movies.sort((o1, o2) -> o1.get_year().compareTo(o2.get_year()));
		else if (sortby.equals("price"))
			movies.sort((o1, o2) -> o1.get_price().compareTo(o2.get_price()));

		for (Movie m : movies)
			System.out.println(m);
	}
}
