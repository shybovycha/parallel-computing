import java.rmi.RemoteException;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Client extends UnicastRemoteObject implements BaseClient, Runnable
{
    protected String name;
    protected BaseServer server;

    public Client(String name, BaseServer server) throws RemoteException
    {
        this.name = name;
        this.server = server;

        this.server.join(name, this);
    }

    public void receive(String name, String message) throws RemoteException
    {
        System.out.printf("%s: %s\n", name, message);
    }

    public String getName() throws RemoteException
    {
        return this.name;
    }

    public void run()
    {
        Scanner in = new Scanner(System.in);

        while (true)
        {
            String msg;

            try
            {
                msg = in.nextLine().trim();

                Pattern p = Pattern.compile("^@(\\w+)\\s+(.+)");
                Matcher m = p.matcher(msg);

                if (msg.equals("quit"))
                {
                    this.server.disconnect(this);
                    in.close();
                    System.exit(0);
                } else if (msg.equals("list"))
                {
                    this.server.list(this);
                } else if (m.find())
                {
                    String receiverName = m.group(1);
                    BaseClient receiver = server.lookup(receiverName);

                    if (receiver != null)
                    {
                        receiver.receive(this.name, "<private> %s".format(m.group(2)));
                    } else 
                    {
                        this.server.broadcast(this.name, m.group(2));
                    }
                } else 
                {
                    this.server.broadcast(this.name, msg);
                }
            } catch (Exception e)
            {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args)
    {
        if (args.length != 3)
        {
            System.out.printf("Usage: java Client <server IP> <server port> <username>\n");
            return;
        }

        String host = args[0], name = args[2];
        int port = Integer.parseInt(args[1]);
        
        try
        {
            Registry registry = LocateRegistry.getRegistry(host, port);
            BaseServer server = (BaseServer) registry.lookup("MooChatServer");

            Thread t = new Thread(new Client(name, server));
            t.start();
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}