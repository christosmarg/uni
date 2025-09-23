import java.io.*;

class ReadLines {
	public static void main(String args[]) {
		BufferedReader br;
		File f;
		String str;
		int ln = 0;

		try {
			f = new File(args[0]);
			br = new BufferedReader(new FileReader(f));

			while ((str = br.readLine()) != null) {
				System.out.println(str);
				ln++;
			}
			br.close();
		} catch (FileNotFoundException e) {
			System.err.println("file not found");
			return;
		} catch (IOException e) {
			System.err.println("IO Exception");
			return;
		} catch (ArrayIndexOutOfBoundsException e) {
			System.err.println("usage: java ReadLines file");
			return;
		}

		System.out.println("Lines read: " + ln);
	}
}
