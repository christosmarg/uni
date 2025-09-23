import java.io.*;

class Prime {
	public static void main(String[] args) {
		try {
			FileOutputStream fos = new FileOutputStream(args[0]);
			BufferedOutputStream bos = new BufferedOutputStream(fos);
			DataOutputStream dos = new DataOutputStream(bos);
			int i = 0;
			int n = 2;

			while (i < 100) {
				if (is_prime(n)) {
					dos.writeInt(n);
					i++;
				}
				n++;
			}
			dos.close();
			fos.close();
		} catch (FileNotFoundException e) {
			System.err.println("File not found");
			return;
		} catch (IOException e) {
			System.err.println("IO Exception");
			return;
		}
	}

	private static boolean is_prime(int n) {
		for (int i = 2; i < n; i++)
			if (n % i == 0)
				return false;
		return true;
	}
}
