#! /bin/bash

ServoStart()
{
    id=`ps aux | grep server_servo |  grep -v grep | awk '{ print $2 }'`;
    if [ "${id}" != "" ]
    then
          kill -9 $id
          id=
    fi

cd /home/servossl/Wrapperv1.2

file=/data/servo/SERVOWRAPPER.LOG
echo $file
(source ./server_servo.conf; source /etc/init.d/functions; daemon +10 /home/servossl/Wrapperv1.2/server_servo 2> ${file} )&

}

# 1 SIGHUP, 8  SIGFPE, 11 Invalid Memory Reference, Broken Pipe
trap ServoStart 1 8 11 13

ServoStart

if [ $? -eq 0 ]
then
  echo "$0 executed successfully, please see log in ${file}"
  exit 0 
fi
