echo WScript.sleep 500 >sss.vbs

start Serverdb.bat
sss.vbs
start ServerGate.bat
sss.vbs
start ServerLogin.bat