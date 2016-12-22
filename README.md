# iperf-GUI
## GUI for the network tool iperf used on a raspberry pi 3 with a 7 inch display

### Using docker to test iperf-interface

#### Set server IP address as environment variable for using netburn script inside docker container
```Bash
vim docker/iperf-interface-client/Dockerfile
```

**Replace**
```Bash
ENV SERVER_IP 192.168.1.43
```

**with you IP address**
```Bash
ENV SERVER_IP YOUR_IP_ADDRESS_HERE
```

#### Build docker image
```Bash
cd docker/iperf-interface-client && \
docker build -t iperf-interface-client .
```

#### Run iperf-interface-client docker image
```Bash
docker run -i -t -d --name iperf-interface-client iperf-interface-client
```

#### Attach to iperf-interface-client container
```Bash
docker attach iperf-interface-client
```

#### Using netburn bash script inside iperf-interface-client container
```Bash
netburn duplex
```

## Generate API documentation

To generate API documentation simply execute `doxygene` in the root folder of the application.

```Bash
doxygene
```

To install Doxygene on your OS follow the instructions on the official Website <http://www.stack.nl/~dimitri/doxygen>.
