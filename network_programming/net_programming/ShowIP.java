import java.net.*;

public class ShowIP {
	public static void main(String[] args) throws Exception {
		InetAddress[] addr;
		String hostname = "";

		try {
			hostname = args[0];
			addr = InetAddress.getAllByName(hostname);

			for (int i = 0; i < addr.length; i++)
				System.out.println(i + "\t" + hostname + ": " +
				    addr[i].toString());
		} catch (ArrayIndexOutOfBoundsException e) {
			System.err.println("usage: java ShowIP <hostname>");
			System.exit(1);
		} catch (UnknownHostException e) {
			System.err.println("unknown host: " + hostname);
			System.exit(1);
		}
	}
}
