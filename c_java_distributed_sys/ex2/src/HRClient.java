import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.util.Scanner;

public class HRClient {
	public static void usage() {
		System.err.println("usage: java HRClient list <hostname>");
		System.err.println("       java HRClient book <type> <number> <name> <hostname>");
		System.err.println("       java HRClient guests <hostname>");
		System.err.println("       java HRClient cancel <type> <number> <name> <hostname>");
		System.exit(1);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String str = "";

		try {
			if (args.length != 2 && args.length != 5)
				usage();
			String host = args[args.length-1];
			HRInterface stub = (HRInterface)Naming.lookup(host);

			if (args[0].equals("list") && args.length == 2)
				str = stub.list();
			else if (args[0].equals("book") && args.length == 5) {
				str = stub.book(args[1], Integer.parseInt(args[2]), args[3]);
				if (str.equals("fail: no rooms available")) {
					System.out.println("the room is currently unavailable");
					System.out.print("do you want to be notified (y/n)? ");
					if (sc.next().equals("y")) {
						stub.addListSub(args[3], args[1]);
						System.out.println("thank you");
						return;
					}
				}
			} else if (args[0].equals("guests") && args.length == 2)
				str = stub.guests();
			else if (args[0].equals("cancel") && args.length == 5)
				str = stub.cancel(args[1], Integer.parseInt(args[2]), args[3]);
			else
				usage();
		} catch (RemoteException e) {
			System.err.println("RemoteException: " + e.toString());
		} catch (NotBoundException e) {
			System.err.println("NotBoundException: " + e.toString());
		} catch (IndexOutOfBoundsException e) {
			usage();
		} catch (Exception e) {
			System.err.println("Exception: " + e.toString());
		}

		System.out.println(str);
	}
}
