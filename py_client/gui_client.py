# coding: utf-8
from Tkinter import *
import os
from functools import partial
import time
#import threading
#import ttk

win = Tk()
win.title("Taskmaster GUI")
win.geometry('+1000+500')
win.wm_attributes("-topmost", 1)

################################################################################
def start(name):
    print "starting " + name

def stop(name):
    print "stopping " + name

def restart(name):
    print "restarting " + name

def stop_all():
    print "stopping all !"

def restart_all():
    print "restarting all !"

def refresh_all(status):
    curr_row = 2
    for process in status:
        if (process["status"] == "running"):
            bg_row = "pale green"
        elif (process["status"] == "error"):
            bg_row = "indian red"
        elif (process["status"] == "paused"):
            bg_row = "orange"
        else:
            bg_row = "grey"
        Label(win, text='', borderwidth=1, bg=bg_row, font='Helvetica 21 bold').grid(row=curr_row, column=1, columnspan=6, sticky="ew")
        Label(win, text=process["name"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=1, sticky="w")
        Label(win, text=process["status"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=2, sticky="W")
        Label(win, text=process["retries"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=3, sticky="W")
        Label(win, text=process["pid"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=4, sticky="W")
        Label(win, text=process["timetype"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=5, sticky="W")
        Label(win, text=process["elapsed"], borderwidth=1, bg=bg_row).grid(row=curr_row, column=6, sticky="W")
        if (process["status"] == "running"):
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
    #Label(win, text='',         borderwidth=1, width=10, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=5, sticky="W")
    #Label(win, text='Elapsed time:', borderwidth=1, width=15, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=6, sticky="W")
    Label(win, text='Elapsed time:', borderwidth=1, width=25, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=5, columnspan=2, sticky="W")
    Label(win, text='Start/Stop:', borderwidth=1, width=10, fg="midnight blue", font='Helvetica 13 bold', anchor="w").grid(row=1, column=7, sticky="W")
    win.update()
init_table_header()


status = [
    {
        "name": "ls",
        "status": "running",
        "retries": "2",
        "pid": "N/A",
        "timetype": "starttime",
        "elapsed": "0"
    },
    {
        "name": "segfault",
        "status": "error",
        "retries": "2",
        "pid": "N/A",
        "timetype": "downtime",
        "elapsed": "0"
    },
    {
        "name": "test",
        "status": "stopped",
        "retries": "2",
        "pid": "N/A",
        "timetype": "downtime",
        "elapsed": "0"
    },
    {
        "name": "segfault",
        "status": "running",
        "retries": "2",
        "pid": "N/A",
        "timetype": "downtime",
        "elapsed": "0"
    }
]

refresh_all(status)

time.sleep(2)
status = [
    {
        "name": "ls",
        "status": "stopped",
        "retries": "2",
        "pid": "N/A",
        "timetype": "downtime",
        "elapsed": "0"
    },
    {
        "name": "segfault",
        "status": "error",
        "retries": "2",
        "pid": "N/A",
        "timetype": "downtime",
        "elapsed": "0"
    },
    {
        "name": "test",
        "status": "running",
        "retries": "2",
        "pid": "N/A",
        "timetype": "downtime",
        "elapsed": "0"
    },
    {
        "name": "segfault",
        "status": "paused",
        "retries": "2",
        "pid": "N/A",
        "timetype": "downtime",
        "elapsed": "0"
    }
]

refresh_all(status)


win.mainloop()