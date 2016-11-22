FROM debian
ENV SERVER_IP 192.168.1.43
COPY netburn.sh /usr/local/bin/netburn
RUN apt-get update && apt-get install -y \
    iperf \
    net-tools \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/* \
 && sed -i "s/SERVER_IP/$SERVER_IP/g" /usr/local/bin/netburn \
 && chmod +x /usr/local/bin/netburn