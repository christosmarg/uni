import java.io.*;
import java.util.ArrayList;

class Main {
	public static void main(String[] args) {
		ArrayList<Album> albums = new ArrayList<Album>();
		BufferedReader br;
		File f;
		String fields[];
		String str;
		String sortby;

		try {
			sortby = args[0];
			f = new File(args[1]);
			br = new BufferedReader(new FileReader(f));

			while ((str = br.readLine()) != null) {
				fields = str.split("\\;");
				albums.add(new Album(fields[0], fields[1],
				    Integer.parseInt(fields[2]),
				    Float.parseFloat(fields[3])));
			}
			br.close();
		} catch (FileNotFoundException e) {
			System.err.println("No such file");
			return;
		} catch (IOException e) {
			System.err.println("IO Exception");
			return;
		} catch (ArrayIndexOutOfBoundsException e) {
			System.err.println("Usage: java Main sortby file\n");
			System.err.println("You can sort by:\n\ttitle\n\t" +
			    "artist\n\tyear\n\tprice");
			return;
		}

		if (sortby.equals("title"))
			albums.sort((o1, o2) -> o1.get_title().compareTo(o2.get_title()));
		else if (sortby.equals("artist"))
			albums.sort((o1, o2) -> o1.get_artist().compareTo(o2.get_artist()));
		else if (sortby.equals("year"))
			albums.sort((o1, o2) -> o1.get_year().compareTo(o2.get_year()));
		else if (sortby.equals("price"))
			albums.sort((o1, o2) -> o1.get_price().compareTo(o2.get_price()));

		for (Album m : albums)
			System.out.println(m);
	}
}
