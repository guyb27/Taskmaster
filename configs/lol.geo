# Geo easyparsing file format
# #
# # stopsignal: 0-31

name: ls
cmd: /bin/ls -laR /
numprocs: 1
umask: 022
workingdir: .
autostart: 0
autorestart: 1
exitcodes:
-0
-2 
startretries: 3
starttime: 300
stopsignal: 4
stoptime: 10
stdout: /dev/ttys001
stderr: /tmp/my_ls.stderr
env:
_STARTED_BY: taskmaster
_ANSWER: 42

name: unknown
cmd: lol
numprocs: 1
umask: 022
workingdir: .
autostart: 0
autorestart: 1
exitcodes:
-0
-2
startretries: 3
starttime: 3
stopsignal: 4
stoptime: 10
stdout: /tmp/my_ls.stdout
stderr: /tmp/my_ls.stderr
env:
_FUCKER: jack
_ANSWER: 492

name: segfault
cmd: /Users/gbarnay/Documents/projects/taskmaster/segfault
numprocs: 1
umask: 022
workingdir: .
autostart: 1
autorestart: 2
exitcodes:
-0
-2
startretries: 10
starttime: 3
stopsignal: 2
stoptime: 10
stdout: /tmp/my_ls.stdout
stderr: /tmp/my_ls.stderr
env:
_FUCKER: jack
_ANSWER: 42

name: loop
cmd: ./loop
numprocs: 2
umask: 022
workingdir: .
autostart: 1
autorestart: 1
exitcodes:
-0
-2 
startretries: 3
starttime: 6
stopsignal: 2
stoptime: 10
stdout: /tmp/nginx.stdout
stderr: /tmp/nginx.stderr
env:
_STARTED_BY: ls
_ANSWER: 42
