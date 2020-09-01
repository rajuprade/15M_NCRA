#! /bin/sh


while true
do

pid=`ps aux | grep tomcat | grep -v grep | awk '{ print $2}'`

if [ $? -eq 0 ]
then

File=`date +%Y%b%d_%H%M`
File=/data/hdmp/dmp${File}_${pid}.bin

jmap -dump:live,format=b,file=$File $pid
if [ $? -eq 0 ]
then
echo "`date` HEAP-PID $pid"  >> /data/hdmp/dmphistory
jmap -heap $pid >> /data/hdmp/dmphistory
echo "....................................................................." >> /data/hdmp/dmphistory
fi

fi

sleep 3600

done
