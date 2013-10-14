import java.rmi.Remote;
import java.rmi.RemoteException;

public interface BaseClient extends Remote
{
    void receive(String name, String message) throws RemoteException;
    String getName() throws RemoteException;
}