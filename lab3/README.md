# Java RMI based Chat

## Compiling

    javac Client.java
    javac Server.java

## Running server

    rmiregistry 20001
    java -Djava.rmi.server.hostname=<YOUR_IP> -Djava.security.policy=chat.policy Server 20001

## Running client

    java -Djava.security.policy=chat.policy Client <YOUR_SERVER_IP> 20001 <YOUR_CHAT_USERNAME>

## Available client commands

`list` - shows all the chatters online
`quit` - disconnect
`@<USERNAME>` - private message to `<USERNAME>`. E.g.: `@moo how are you?` will send the `how are you?` message to user with username `moo`
