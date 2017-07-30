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
    if c is not 's':
        sys.stdout.write ("expected string but got type",c)
        exit(-1)
    l = sock.recv(4)
    sys.stdout.write(len(l))
    l = bytearray_to_int(l)
    return sock.recv(l).decode()

def send_int(sock, value):
    ib = int_to_bytearray(value)
    m = b'i' + ib
    sock.send(m)

def recv_int(sock):
    c = sock.recv(1).decode()
    if c is not 'i':
        sys.stdout.write ("expected int but got type",c)
        exit(-1)
    return bytearray_to_int(sock.recv(8))


def send_doubles(sock, values):
    m = b'D'
    l = len(values)
    sys.stdout.write(len(int_to_bytearray(l)))
    m = m + int_to_bytearray(l)
    for i in range(len(values)):
        m = m + double_to_bytearray(values[i])
    sock.send(m)

def recv_doubles(sock):
    c = sock.recv(1).decode()
    if c is not 'D':
        sys.stdout.write ("expected double array but got type",c)
        exit(-1)
    l = sock.recv(4)
    l = bytearray_to_int(l)
    sys.stdout.write("l",l)
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

sys.stdout.write("waiting of experiment definition")
exp = recv_string(sock)
sys.stdout.write("received: " + str(exp))

env             = gym.make(exp)
nr_of_sensors   = len(env.action_space.low)
nr_of_actuators = nr_of_sensors

sys.stdout.write("sending nr of sensors/actuators:", nr_of_sensors)
send_int(sock, nr_of_sensors)

A      = []
S      = []
reward = 0

while 1:
    s = recv_string(sock)

    if s is "QUIT":
        sys.stdout.write("received quit")
        socket.close(sock)
        exit(-1)
    elif s is "SENSORS":
        sys.stdout.write("received sensors")
        send_doubles(sock, S)
    elif s is "ACTUATORS":
        sys.stdout.write("received actuators")
        A = recv_doubles(sock)
        S, reward, done, info = env.step(action)
        env.render()
    elif s is "REWARD":
        sys.stdout.write("received reward")
        send_double(sock, reward)
    elif s is "RESET":
        sys.stdout.write("received reset")
        env.reset()
    else:
        sys.stdout.write("unknown and", s)
