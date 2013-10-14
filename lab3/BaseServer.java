import java.rmi.Remote;
import java.rmi.RemoteException;

public interface BaseServer extends Remote
{
    void join(String name, BaseClient caller) throws RemoteException;
    void disconnect(BaseClient caller) throws RemoteException;
    void broadcast(String name, String message) throws RemoteException;
    BaseClient lookup(String name) throws RemoteException;
    void list(BaseClient caller) throws RemoteException;
}