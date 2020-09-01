echo "Executing cms shutdown script";
sleep 10
sh /apache-tomcat-6.0.24/bin/catalina.sh stop 15 -force
sh /apache-activemq-5.4.2/bin/activemq stop


