import java.io.*;
import java.net.*;

class SocketUtils {
	static final int BUF_LEN = 1024;

	public static String getRequest(Socket sock) throws Exception {
		StringBuilder reqstr = new StringBuilder();
		byte[] reqbytes = new byte[BUF_LEN];
		InputStream in = sock.getInputStream();
		int n;

		while (true) {
			n = in.read(reqbytes, 0, BUF_LEN);
			if (n == -1)
				break;
			reqstr.append(new String(reqbytes, 0, n));
			if (n < BUF_LEN)
				break;
		}
		return reqstr.toString();
	}
}

public class HTTPServer {
	public static void main(String[] args) throws Exception {
		ServerSocket srvsock = new ServerSocket(8010);
		Socket sock;
		String req;
		PrintWriter pw;

		while (true) {
			System.out.println("[HTTPServer] waiting for client");
			sock = srvsock.accept();
			req = SocketUtils.getRequest(sock);
			System.out.println("[HTTPServer] obtained request:\n\n" + req);
			pw = new PrintWriter(sock.getOutputStream());

			pw.println("HTTP/1.0 200 OK");
			pw.println("Content-type: text/html");
			pw.println("Server: Java 6.1\n");

			pw.println("<html><body>Hello world</body></html>");
			pw.close();
			sock.close();
		}
	}
}
