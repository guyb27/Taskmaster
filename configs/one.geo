# Geo easyparsing file format
# #
# # stopsignal: 0-31

name: ls
cmd: /bin/ls -laR /
numprocs: 3
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
