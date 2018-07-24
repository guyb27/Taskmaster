# Geo easyparsing file format
#
# stopsignal: 0-31

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
starttime: 3
stopsignal: 4
stoptime: 10
stdout: /tmp/my_ls.stdout
stderr: /tmp/my_ls.stderr
env:
_STARTED_BY: taskmaster
_ANSWER: 42

name: fucked
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
_STARTED_BY: taskmaster
_ANSWER: 42

name: loop
cmd: /Users/gbarnay/Documents/cursus/taskmaster/last/loop
numprocs: 3
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
_STARTED_BY: taskmaster
_ANSWER: 42
