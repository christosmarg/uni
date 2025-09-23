import java.rmi.Remote;
import java.rmi.RemoteException;

public interface HRInterface extends Remote {
	String list() throws RemoteException;
	String book(String type, int num, String name) throws RemoteException;
	String guests() throws RemoteException;
	String cancel(String type, int num, String name) throws RemoteException;
	void addListSub(String name, String type) throws RemoteException;
}
