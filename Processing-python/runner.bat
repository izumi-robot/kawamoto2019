@echo off
cd /d %~dp0
set PATH=C:\Users\robo\Documents\processing.py-3017-windows64\jre\bin
set jarfile=C:\Users\robo\Documents\processing.py-3017-windows64\processing-py.jar
java -jar %jarfile% %1
exit 0