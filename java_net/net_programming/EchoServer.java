import java.net.*;
import java.io.*;

public class EchoServer {
	public static void main(String[] args) throws IOException {
		ServerSocket srvsock;
		Socket cltsock;
		BufferedReader in;
		PrintWriter out;
		String line;
		int port = 7777;

		if (args.length == 0)
			System.err.println("usage: java EchoServer [port]");
		else
			port = Integer.parseInt(args[0]);
		System.out.println("[EchoServer] starting");
		try {
			srvsock = new ServerSocket(port);
			while (true) {
				cltsock = srvsock.accept();
				out = new PrintWriter(
				    cltsock.getOutputStream(), true);
				in = new BufferedReader(new InputStreamReader(
				    cltsock.getInputStream()));
				while ((line = in.readLine()) != null) {
					if (line.equals("exit"))
						break;
					out.println(line);
				}
			}
		} catch (IOException e) {
			System.err.println("[EchoServer] exception on port " + port);
			System.err.println(e.getMessage());
		}
	}
}
