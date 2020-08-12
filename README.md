# QT_C++_Linuxcnc_interface_gui
Linuxcnc interface gui based on halcommands and emc-nml messages, can read and visualise gcode
For information only. Not ready to use in real time applications!

Example :
![alt text](https://raw.githubusercontent.com/grotius-cnc/QT_C-_Linuxcnc_interface_gui/master/github_screenshot.png)

To use :

1. clone and download linuxcnc. install as rip. how to install, follow this guide :
    https://forum.linuxcnc.org/27-driver-boards/35591-beckhoff-ethercat-64-with-bit-linuxcnc-how-to-install#121471
    
2. Start linuxcnc as rip. and select config axis_mm. select => create destop icon.
3. Copy the compiled qt executable file into the linux bin folder "../linuxcnc/bin/" or make a symbolic link.

4. Modify the axis_mm.ini file "../inuxcnc/configs/sim/axis/axis_mm.ini and replace in the file :

# Name of display program, e.g., axis
#DISPLAY = axis
DISPLAY = QT_Lcnc_interface

# Axes sections ---------------
[AXIS_X]
MIN_LIMIT = -10000
MAX_LIMIT = 10000

# Joints sections -------------
[JOINT_0]
MIN_LIMIT = -10000
MAX_LIMIT = 10000

5. modify in the file ../QT_Lcnc_interface/display/variable.cpp 

std::string nmlfile="/home/user/linuxcnc/configs/common/linuxcnc.nml";

To your path :

std::string nmlfile="/yourdirecory/linuxcnc/configs/common/linuxcnc.nml";

6. start linuxcnc axis_mm config and start the qt application. 

Comments :
  1. The program read's gcode with "G0" for reading "g0" you have to expand or modity ./QT_Lcnc_interface/gcode/parse_gcode.h
  2. Some gui commands are emc-nml commands. It looks like linuxcnc has a overflow after some time trough the emc-nml calls. Solution may be free memory, 
  deallocation etc.
  3. Replacing emc-nml commands with halui read and write operations that are available, will solve this problem at tab 2 quickly, is what i suspect.
  4. Have fun with playing around with the program !!
  


