#Readme

This document explains how to install and run the MediaTek USB serial port driver on your MacOS X 10.10 and 10.11.

##Install MediaTek USB serial port driver
	
	1. Open install package (Ex. "BMCDCACM_Driver_Vxxx.xx.x.mpkg") and follow the instruction to install it.
	2. Wait until the driver is installed successfully and reboot your MacOS.
	
	Now, the MediaTek USB serial port driver installation is completed.


##Uninstall driver
	1 Open the Terminal
	2 Run command as follow:
		"sudo rm -rf /System/Library/Extensions/BMUSBCDC.kext"
		"sudo touch /System/Library/Extensions/"
		"sudo sync"
	3 Reboot MacOS
	

##Version History

Package : <<MTK_MacOS_COM_Driver_For_Bootrom_v115.44.0>>
Date    : <<2015/10/28>>
-------------------------------------------------------------------------------------
1. Modify driver compatibility¡Asupport to MacOS 10.11


Package : <<MTK_MacOS_COM_Driver_For_6280_Bootrom_v115.04.0>>
Date    : <<2015/01/19>>
-------------------------------------------------------------------------------------
1. Support LinkItONE Bootrom usb serial port on MacOS 10.10