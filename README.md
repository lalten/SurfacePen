# SurfacePen
Use the Microsoft Surface BLE Pen to do something different than opening OneNote.


## Intro ##
The purple Surface Pen button normally launches OneNote. I don't really use OneNote, but I find it interesting to control my tablet "remotely".

I used Microsoft SysInternal's [Process Monitor](https://technet.microsoft.com/sysinternals/bb896645) to find out what actually happens when you press the pen's purple button.

## How it works ##

It turns out that the Windows Registry key

```
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Authentication\LogonUI\CN
```

determines what will be executed. The default value is *C:\Program Files\Microsoft Office 15\Root\Office15\ONENOTEM.EXE*
but you can change it to anything, e.g. launch the calculator (*C:\Windows\System32\calc.exe*)

The specified executable will always be passed an command line argument:
 * Single press: */hardwareinvoke*
 * Double press: */screenclip*
 * Lockscreen press: */fromlockscreen*

I proceeded to write a simple [AutoHotkey](http://www.autohotkey.com/) script:
```AutoHotkey
if 1 = /hardwareinvoke ; single button press
    Send {Right}
else if 1 = /screenclip ; double button press
    Send {Left}
```
and compiled it to pen.exe and updated the registry key to its path (*C:\bin\pen.exe* for me)

## Files ##

**pen.exe** is the compiled version of pen.ahk

**pen.reg** contains a registry patch as per [KB310516]https://support.microsoft.com/en-us/kb/310516). It will change the value of the key given above to the value *C:\bin\pen.exe*.

**reset.reg** will reset that value to the default (*C:\Program Files\Microsoft Office 15\Root\Office15\ONENOTEM.EXE*)


## Issues ##
The double press always dims the screen shortly and then takes a screenshot before executing the program. I couldn't figure out how to suppress that. Maybe someone has an idea?

## Conclusion ##
Now I can use my Surface Pen to control presentations :)
