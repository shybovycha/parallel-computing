import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Map;
import java.util.HashMap;

public class Server implements BaseServer
{
    protected Map<String, BaseClient> clients;

    public Server() throws RemoteException
    {
        this.clients = new HashMap<String, BaseClient>();
    }

    public void join(String name, BaseClient sender) throws RemoteException
    {
        this.broadcast(name, "<joined>");
        this.clients.put(name, sender);

        System.out.printf("%s joined\n", name);
    }

    public void disconnect(BaseClient sender) throws RemoteException
    {
        this.clients.remove(sender.getName());
        this.broadcast(sender.getName(), "<left>");

        System.out.printf("%s left\n", sender.getName());
    }

    public void broadcast(String name, String message) throws RemoteException
    {
        for (BaseClient c : this.clients.values()) 
        {
            c.receive(name, message);
        }

        System.out.printf("%s: %s\n", name, message);
    }

    public BaseClient lookup(String name) throws RemoteException
    {
        return (BaseClient) this.clients.get(name);
    }

    public void list(BaseClient sender) throws RemoteException
    {
        for (String clientName : this.clients.keySet())
        {
            if (clientName.equals(sender.getName()))
                continue;

            sender.receive("<server>", "%s".format(clientName));
        }
    }

    public static void main(String[] args)
    {
        if (args.length != 1)
        {
            System.out.printf("Usage: java Server <port>\n");
            return;
        }

        int port = Integer.parseInt(args[0]);

        try
        {
            Server srv = new Server();
            LocateRegistry.getRegistry(port).bind("MooChatServer", UnicastRemoteObject.exportObject(srv, 0));
            System.out.printf("Server started on %d port\n", port);
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}