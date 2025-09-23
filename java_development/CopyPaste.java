import java.io.*;

class CopyPaste {
	public static void main(String args[]) {
		FileInputStream fis;
		FileOutputStream fos;
		int c;

		try {
			fis = new FileInputStream(args[0]);
			fos = new FileOutputStream(args[1]);

			while ((c = fis.read()) != -1)
				fos.write(c);
			fis.close();
			fos.close();
		} catch (FileNotFoundException e) {
			System.err.println("file not found");
			return;
		} catch (IOException e) {
			System.err.println("IO Exception");
			return;
		} catch (ArrayIndexOutOfBoundsException e) {
			System.err.println("usage: java CopyPaste src dst");
			return;
		}
	}
}
