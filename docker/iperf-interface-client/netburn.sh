#!/bin/bash

case "$1" in
  "duplex")
  echo "Duplex mode"
  iperf -c SERVER_IP -u -P 1 -i 1 -p 5001 -f m -b 10.0M -t 30 -d -L 5001 -T 1
  ;;
  "simplex")
  echo "Simplex mode"
  iperf -c SERVER_IP -u -P 1 -i 1 -p 5001 -f m -b 10.0M -t 30 -T 1
  ;;
  "server")
  echo "Server mode"
  iperf -s -u -p 5001
  ;;
  *)
  echo "Usage: $0 [duplex, simplex, server]"
  ;;
esac