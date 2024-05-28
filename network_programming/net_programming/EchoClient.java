import java.net.*;
import java.io.*;

public class EchoClient {
	public static void main(String[] args) throws IOException {
		Socket echosock;
		PrintWriter out;
		BufferedReader in, stdin;
		String input;
		String hostname = "127.0.0.1";
		int port = 7777;

		if (args.length == 2) {
			hostname = args[0];
			port = Integer.parseInt(args[1]);
		} else
			System.err.println("usage: java EchoClient [hostname] [port]");
		try {
			echosock = new Socket(hostname, port);
			out = new PrintWriter(echosock.getOutputStream(), true);
			in = new BufferedReader(new InputStreamReader(
			    echosock.getInputStream()));
			stdin = new BufferedReader(new InputStreamReader(System.in));
			
			System.out.print("> ");
			while ((input = stdin.readLine()) != null) {
				out.println(input);
				System.out.println("echo: " + in.readLine());
				System.out.print("> ");
			}
		} catch (UnknownHostException e) {
			System.err.println("unknown host: " + hostname);
		} catch (IOException e) {
			System.err.println("io exception: " + e.getMessage());
		}
	}
}
