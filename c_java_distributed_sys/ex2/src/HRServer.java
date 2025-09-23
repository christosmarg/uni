import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class HRServer extends HRImpl {
	public static void main(String[] args) {
		try {
			HRImpl impl = new HRImpl();
			HRInterface stub = (HRInterface)UnicastRemoteObject.exportObject(impl, 0);
			Registry reg = LocateRegistry.getRegistry();

			reg.bind("HRRegistry", stub);
			System.out.println("server ready");
		} catch (Exception e) {
			System.err.println("server exception: " + e.toString());
			e.printStackTrace();
		}
	}
}
