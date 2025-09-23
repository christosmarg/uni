import java.net.*;

public class UDPServer {
	public static void main(String[] args) throws Exception {
		DatagramSocket srvsock;
		DatagramPacket sendpack, recvpack;
		InetAddress addr;
		String msg;
		byte[] senddata = new byte[1024];
		byte[] recvdata = new byte[1024];
		int port = 8888, recvport;

		if (args.length == 0)
			System.out.println("usage: java UDPServer [port]");
		else
			port = Integer.parseInt(args[0]);
		System.out.println("[UDPServer] starting");
		srvsock = new DatagramSocket(port);

		while (true) {
			recvpack = new DatagramPacket(recvdata, recvdata.length);
			srvsock.receive(recvpack);
			msg = new String(recvpack.getData(), 0,
			    recvpack.getLength());
			
			System.out.println("your message: " + msg);
			addr = recvpack.getAddress();
			recvport = recvpack.getPort();
			senddata = msg.getBytes();
			sendpack = new DatagramPacket(senddata,
			    senddata.length, addr, recvport);
			srvsock.send(sendpack);
		}
	}
}
