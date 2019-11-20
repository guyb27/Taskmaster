name: nginx
cmd: "/usr/local/bin/nginx -c /etc/nginx/test.conf"
numprocs: 1
umask: 022
workingdir: /tmp
autostart: true
autorestart: unexpected
exitcodes:
-0
-2 
startretries: 3
starttime: 5
stopsignal: TERM
stoptime: 10
stdout: /tmp/nginx.stdout
stderr: /tmp/nginx.stderr
env:
_STARTED_BY: taskmaster
_ANSWER: 42

name: vogsphere
cmd: "/usr/local/bin/vogsphere-worker --no-prefork"
numprocs: 8
umask: 077
workingdir: /tmp
autostart: true
autorestart: unexpected
exitcodes: 0
startretries: 3
starttime: 5
stopsignal: USR1
stoptime: 10
stdout: /tmp/vgsworker.stdout
stderr: /tmp/vgsworker.stderr