# Geo easyparsing file format
#
# stopsignal: 0-31

name: segfault
cmd: /Users/gbarnay/Documents/projects/taskmaster/segfault
numprocs: 1
umask: 022
workingdir: .
autostart: 1
autorestart: 2
exitcodes:
-7
-90
startretries: 2
starttime: 3
stopsignal: 10
stoptime: 10
stdout: /dev/ttys005
stderr: /dev/ttys005
env:
_FUCKER: jack
_ANSWER: 42
