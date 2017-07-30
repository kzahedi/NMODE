#!/usr/bin/env python3
import gym
import socket
import struct
import time
import sys

def connect(host, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    return s

def server(port):
    host = "127.0.0.1"
    p = port
    s = socket.socket()
    connected = False
    while connected is False:
        try:
            s.bind((host,p))
            connected = True
        except:
            p = p + 1
    sys.stdout.write("  --> port " + str(p) + " opened")
    sys.stdout.flush()
    s.listen(1)
    conn, addr = s.accept()
    return conn



def double_to_bytearray(values):
    return bytearray(struct.pack("d", values))

def bytearray_to_double(_bytes):
    return struct.unpack('d', _bytes)[0]

def int_to_bytearray(value):
    return bytearray(struct.pack("i", value))

def bytearray_to_int(_bytes):
    return struct.unpack('i', _bytes)[0]



def send_string(sock, msg):
    m = b's'
    l = len(msg)
    ib = int_to_bytearray(l)
    m = m + ib
    m = m + msg.encode()
    sock.send(m)

def recv_string(sock):
    c = sock.recv(1).decode()
    # sys.stdout.write("found: " + c + "\n")
    # sys.stdout.flush()
    if c is not 's':
        sys.stdout.write("expected string but got type " + str(c) + "\n")
        sys.stdout.flush()
        exit(-1)
    l = sock.recv(4)
    l = bytearray_to_int(l)
    return sock.recv(l).decode()

def send_int(sock, value):
    ib = int_to_bytearray(value)
    m = b'i' + ib
    sock.send(m)

def recv_int(sock):
    c = sock.recv(1).decode()
    if c is not 'i':
        sys.stdout.write("expected int but got type " + str(c))
        sys.stdout.write()
        exit(-1)
    return bytearray_to_int(sock.recv(8))

def send_double(sock, value):
    ib = double_to_bytearray(value)
    m = b'd' + ib
    sock.send(m)

def recv_double(sock):
    c = sock.recv(1).decode()
    if c is not 'd':
        sys.stdout.write("expected int but got type " + str(c))
        sys.stdout.write()
        exit(-1)
    return bytearray_to_double(sock.recv(8))

def send_doubles(sock, values):
    m = b'D'
    l = len(values)
    m = m + int_to_bytearray(l)
    for i in range(len(values)):
        m = m + double_to_bytearray(values[i])
    sock.send(m)

def recv_doubles(sock):
    c = sock.recv(1).decode()
    if c is not 'D':
        sys.stdout.write("expected double array but got type " + str(c))
        exit(-1)
    l = sock.recv(4)
    l = bytearray_to_int(l)
    values = []
    for i in range(l):
        d = sock.recv(8)
        values.append(bytearray_to_double(d))
    return values


# time.sleep(5)


env             = None
nr_of_sensors   = -1
nr_of_actuators = -1

sock = server(4500)

# sys.stdout.write("waiting of experiment definition\n")
exp = recv_string(sock)
# sys.stdout.write("received: " + str(exp) + "\n")

env             = gym.make(str(exp).rstrip().lstrip())
env.reset()
nr_of_sensors   = len(env.action_space.low)
nr_of_actuators = nr_of_sensors

sys.stdout.write("sending nr of sensors/actuators: " + str(nr_of_sensors))
sys.stdout.flush()
send_int(sock, nr_of_sensors)

A      = []
S      = []
reward = 0

while 1:
    # sys.stdout.write("\n\nwaiting for new command\n")
    # sys.stdout.flush()
    s = recv_string(sock)
    # sys.stdout.write("received command " + str(s) + "\n")
    # sys.stdout.flush()

    if s == "QUIT":
        # sys.stdout.write("received quit")
        # sys.stdout.flush()
        socket.close(sock)
        exit(-1)
    elif s == "SENSORS":
        # sys.stdout.write("received sensors")
        # sys.stdout.flush()
        send_doubles(sock, S[0:nr_of_sensors])
    elif s == "ACTUATORS":
        # sys.stdout.write("received actuators")
        # sys.stdout.flush()
        A = recv_doubles(sock)
        S, reward, done, info = env.step(A)
        env.render()
    elif s == "REWARD":
        # sys.stdout.write("received reward")
        # sys.stdout.flush()
        send_double(sock, reward)
    elif s == "RESET":
        # sys.stdout.write("received reset")
        # sys.stdout.flush()
        env.reset()
    else:
        sys.stdout.write("unknown command " + str(s))
        sys.stdout.flush()
