import java.io.*;
import java.net.*;

public class UDPClient {
	public static void main(String[] args) throws Exception {
		DatagramSocket cltsock;
		DatagramPacket sendpack, recvpack;
		InetAddress addr;
		BufferedReader input;
		String msg, srvresp;
		String hostname = "127.0.0.1";
		byte[] senddata = new byte[1024];
		byte[] recvdata = new byte[1024];
		int port = 8888;

		if (args.length == 2) {
			hostname = args[0];
			port = Integer.parseInt(args[1]);
		} else
			System.out.println("usage: java UDPClient [hostname] [port]");
		System.out.print("> ");
		input = new BufferedReader(new InputStreamReader(System.in));
		cltsock = new DatagramSocket();
		cltsock.setSoTimeout(1000);
		addr = InetAddress.getByName(hostname);
		msg = input.readLine();
		senddata = msg.getBytes();
		sendpack = new DatagramPacket(senddata, senddata.length, addr, port);
		cltsock.send(sendpack);
		recvpack = new DatagramPacket(recvdata, recvdata.length);

		try {
			cltsock.receive(recvpack);
			srvresp = new String(recvpack.getData());
			System.out.println("server response: " + srvresp);
		} catch (SocketTimeoutException e) {
			System.err.println("timeout" + e);
		}
		cltsock.close();
	}
}
