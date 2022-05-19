Cypherbridge Systems LLC
Demo Kit README
STM32H735G-DK Platform
Project QiSpace SDK

www.cypherbridge.com
support@cypherbridge.com
+1 760.814.1575


================
NOTICE TO USER
================

This project is delivered under Design Services Agreement 
and subject to its SOW scope, pricing, milestones and deliverables.

The Demo Kit project content includes SDK components that are 
Proprietary code and subject to the terms and conditions
defined in the SDK LICENSE.

Demo Kit README Copyright (c) 2022 Cypherbridge Systems LLC.


====================================
REFERENCES AND DOCUMENTATION
====================================

[1] UM2679 STM32H735G Discovery Kit User Guide, STMicroelectronics, Rev 5 September 2021

[2] UM2609 STM32CubeIDE User Guide, STMicroelectronics, Rev 5 November 2021

[3] STM32 ST-LINK utility for Windows 10, STMicroelectronics
https://www.st.com/en/development-tools/stsw-link004.html


====================================
DOCUMENT REVISION HISTORY
====================================
220513B - This document created  
Added QiSpace project import step-by-step


===========================
OVERVIEW
===========================

The Demo runs out of box to demonstrate QiSpace SDK features 
and operations, including cross-platform portability extending 
to IoT platforms.

This Demo Kit is integrated and tested with STM32H735G-DK 
and built on the following toolchains:

1. STMicro STM32CubeIDE 1.9.0 Ubuntu 20.04 LTS

2. ARM Keil uVision toolchain MDK v.7.15.0 Windows 10


===========================
SYSTEM CONFIGURATION
===========================

Development machine PC Ubuntu 20.04 LTS
STM32H735G-DK 
STLink cable USB Host A to MicroB
/dev/ttyACM0 USB serial debug port 115.2K/N/8/1


===========================
STM32CUBEIDE SYSTEM SETUP
===========================

# install STMicro CubeIDE
# https://www.st.com/en/development-tools/stm32cubeide.html
# Getlatest STM32CubeIDE Debian Linux Installer 1.9.0
# save to Downloads
# toolchain install point is /opt/st

unzip en.st-stm32cubeide_1.9.0_12015_20220302_0855_amd64.deb_bundle.sh.zip

sudo ./st-stm32cubeide_1.9.0_12015_20220302_0855_amd64.deb_bundle.sh

# install putty
# installs to /usr/bin/putty
sudo apt install putty


===========================
STM32H735G-DK SETUP
===========================

Refer to Ref[1] for STM32H735G-DK out of box setup

Connect MicroUSB serial cable from STM32H735G-DK STLK CN15 to 
  Ubuntu development machine USB host port
This enumerates devices including /dev/ttyACM0 along STLink debug device
confirm correct enumeration with with dmesg; ls /dev/ttyACM0
optional use dbus or sudo chmod /dev/ttyACM0 666

Open Putty terminal
# at ubuntu bash window
putty &
open Serial line /dev/ttyACM0 Speed 115200


===============================
DEMO KIT INSTALL BUILD AND TEST 
===============================

Install QiSpace Demo Kit to STM32CubeIDE default workspace
home directory ~/STM32CubeIDE/workspace_1.9.0/QiSpace

tar xvjf demokit_workspace_1.9.0-220513A.tar.bz2

........................
Launch STM32Cube IDE
........................

Use keyboard Windows hot key, or Gnome desktop Activties, search STM
Click open STM32CubeIDE icon

Open the default workspace as shown in the step above.  
~/STM32CubeIDE/workspace_1.9.0

Use IDE toolbar button icons or menus to execute the following steps

1. Project clean and build
2. Project debug to download demo kit image to STM33H735G-DK
3. Run demo kit 

After demo kit program is downloaded and tested, 
the IDE debug session can be closed.
The demo can repeat by clicking STM32H735G-DK Black RST button

On Windows machine The demo can be run using Teraterm
USB serial port.  Connect STM32

......................
Note on Project Import
......................

STM32CubeIDE Eclipse based toolchain may not correctly open QiSpace project.
If unable to open and build QiSpace project, then use following steps.

From bash shell, copy the QiSpace project to temporary directory

cp -r QiSpace /tmp

In STM32CubeIDE, right click QiSpace project, Delete.  Check delete from file system.
This will remove the QiSpace project from the workspace.

Next Import the QiSpace project.
In STM32CubeIDe, menu File, Import, Existing Projects Into Workspace
Browse to /tmp
Select QiSpace 
CHECK Copy Projects into Workspace (must use COPY not linked project)
Finish

QiSpace project will now appear in workspace and ready to build and test
using the steps above.


===========================
DEMO KIT OPERATION
===========================

Demo kit initializes the target system, then executes QiSpace 
demo kit functions.  These functions perform internal self-test 
and cryptographic operations.  The results are output to the 
Putty terminal window as shown in this example:

DEMO KIT 0.1.0 START
q_self_test START
q_self_test END
demo_qeep START
Demo QiSpace QEEP operation...


===========================
WINDOWS PC OPERATION
===========================

After Install Build and Test is complete, then
the demo can be run from Windows PC using Teraterm
USB serial port.  Connect STM32H735G-DK to Windows PC
STLink cable USB Host A to MicroB

If needed install Reference [3] STLink Utility for Windows
to install STLink Windows drivers

====================================
RELEASE NOTES AND REVISION HISTORY
====================================

....................................
220512A
QiSpace Demo Kit for Linux
First internal distribution 
....................................

Known Issues and Limitations
1. Hard fault exception in QSC_qeep_key_load()


