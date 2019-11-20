#!/usr/bin/python
# coding: utf-8

from Tkinter import *
import tkMessageBox
import os
from functools import partial
import time
import socket
import sys
import fcntl, os
import json

win = Tk()
win.title("Taskmaster GUI")
win.geometry('+1000+500')
win.wm_attributes("-topmost", 1)

################################################################################
port = 2022
host = '127.0.0.1'

if (len(sys.argv) == 1):
    print("Listening " + host + " on port: " + str(port))
if (len(sys.argv) > 1):
    host = sys.argv[1]
if (len(sys.argv) > 2):
    port = int(sys.argv[2])

def restart_program():
    """Im using this because of a macos bug that prevent the askretrycancel
       messagebox to quit...
    """
    python = sys.executable
    os.execl(python, python, *sys.argv)

try: 
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
except socket.error as err: 
    print("socket creation failed with error %s" %(err))
try: 
    host_ip = socket.gethostbyname(host) 
except socket.gaierror:
    print("there was an error resolving the host")
    sys.exit()

try:
    sock.connect((host_ip, port))
except Exception as e:
    print(e)
    if not tkMessageBox.askretrycancel(e, "Erreur de connection, voulez-vous retenter ?"):
        win.destroy()
        sys.exit()
    restart_program()
    sys.exit()

fcntl.fcntl(sock, fcntl.F_SETFL, os.O_NONBLOCK)

def receive():
    BUFF_SIZE = 4096
    data = b''
    while True:
        part = sock.recv(BUFF_SIZE)
        data += part
        if len(part) < BUFF_SIZE:
            break
    return data

def countStrings(strings):
    count = 0
    i = 0
    while True:
        if (i >= len(strings)):
            return (count)
        if strings[i] == chr(0):
            count += 1
        if (count == 2):
            return count
        i += 1

def readString(strings):
    chars = []
    i = 0
    while True:
        if (i >= len(strings)):
            return "".join(chars)
        c = strings[i]
        i += 1
        if c == chr(0):
            return "".join(chars)
        chars.append(c)

################################################################################
def start(name):
    print("starting " + name)
    sock.send("start " + name)
    win.after(500, client_loop, 0, False)

def stop(name):
    print("stopping " + name)
    sock.send("stop " + name)
    win.after(500, client_loop, 0, False)

def restart(name):
    print("restarting " + name)
    sock.send("restart " + name)
    win.after(500, client_loop, 0, False)

def stop_all():
    print("stopping all !")
    sock.send("stop all")
    win.after(500, client_loop, 0, False)

def restart_all():
    print("restarting all !")
    sock.send("restart all")
    win.after(500, client_loop, 0, False)

def refresh_all(status):
    curr_row = 2
    for process in status:
        if (process["status"] == "1"): 
            bg_row = "pale green"
        elif (process["status"] == "2"): 
            bg_row = "light sky blue"
        elif (process["status"] == "4"): 
            bg_row = "indian red"
        else:
            bg_row = "grey"
        if (process["status"] == "1"):
            str_status = "running"
        elif (process["status"] == "2"):
            str_status = "starting"
        elif (process["status"] == "3"):
            str_status = "paused"
        elif (process["status"] == "4"):
            str_status = "error"
        else:
            str_status = "stopped"
        Label(win, text='', borderwidth=1, bg=bg_row, font='Helvetica 21 bold').grid(row=curr_row, column=1, columnspan=6, sticky="ew")
        Label(win, text=process["name"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=1, sticky="w")
        Label(win, text=str_status, borderwidth=1, bg=bg_row).grid(row=curr_row, column=2, sticky="W")
        Label(win, text=process["retries"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=3, sticky="W")
        if (process["timetype"] == "starttime"):
            Label(win, text=process["pid"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=4, sticky="W")
        else:
            Label(win, text="N/A", borderwidth=1, bg=bg_row).grid(row=curr_row, column=4, sticky="W")
        Label(win, text=process["timetype"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=5, sticky="W")
        Label(win, text=time.strftime('%H:%M:%S', time.gmtime(float(process["elapsed"]))), borderwidth=1, bg=bg_row).grid(row=curr_row, column=6, sticky="W")
        if (process["status"] == "1" or process["status"] == "2"):
            Button(win, text='Stop ', command=partial(stop, process["name"]), borderwidth=0, bg="grey").grid(row=curr_row, column=7, sticky="w")
        else:
            Button(win, text='Start', command=partial(start, process["name"]), borderwidth=1, bg="indian red").grid(row=curr_row, column=7, sticky="w")
        curr_row += 1
    Button(win, text='start/restart all', command=partial(restart_all), borderwidth=1, bg="red").grid(row=curr_row, column=1, sticky="w")
    Button(win, text='stop all', command=partial(stop_all), borderwidth=1, bg="red").grid(row=curr_row, column=2, sticky="w")
    win.update()
################################################################################

def init_table_header():
    Label(win, text='Name:',    borderwidth=1, width=15, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=1, sticky="W")
    Label(win, text='Status:',  borderwidth=1, width=10, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=2, sticky="W")
    Label(win, text='Retries:', borderwidth=1, width=10, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=3, sticky="W")
    Label(win, text='Pid:',     borderwidth=1, width=10, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=4, sticky="W")
    Label(win, text='Elapsed time:', borderwidth=1, width=25, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=5, columnspan=2, sticky="W")
    Label(win, text='Start/Stop:', borderwidth=1, width=10, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=7, sticky="W")
    win.update()

def client_loop(cnt, loop):
    status = ""
    if (cnt < 2):
        receive() #for prompt
    sock.send("json status")
    while len(status) == 0:
        try:
            status = receive()
        except socket.error as ex:
            if str(ex) == "[Errno 35] Resource temporarily unavailable":
                time.sleep(0)
                continue
            raise ex
    if (status[0] == '['):
        refresh_all(json.loads(readString(status)))
    cnt = countStrings(status)
    if (loop):
        win.after(2000, client_loop, cnt, True)

def on_closing():
    sock.shutdown(socket.SHUT_RDWR)
    sock.close()
    win.destroy()

win.protocol("WM_DELETE_WINDOW", on_closing)
init_table_header()
client_loop(0, True)
################################################################################

win.mainloop()
