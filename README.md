![GammaImpala Logo](images/gamma_impala_icon_64.png)
GammaImpala
===========
Change display gamma with one click
-----------------------------------

2019-2020 Gideon van der Kolf, noedigcode@gmail.com

![Screenshot](images/screenshot.png)

Due to popular demand, the most anticipated Linux utility is finally here!

GammaImpala simply displays a simple GUI with a few buttons to easily change
the gamma settings of all your displays. In addition, command-line usage is
also available so you can bind it to global hotkeys of your desktop environment
to even more instantly serve your gamma needs.

This is the biggest leap in gamma experimentation since the mysterious accidents
that led to the Incredible Hulk. While all care has been taken to provide an
error free application, I do not accept any responsibility for any accidents.
Use this at your own risk.

Usage:
------

Run with no arguments to show the GUI. The GUI displays a list of detected
screens and provides buttons to set the gamma on all screens.

Keyboard keys 7, 8, 9 and 0 or 1 can be used as shortcuts for the buttons.
Esc exits the app.

From the command-line, provide a value, e.g. 0.8, to set the gamma for all
screens without showing the GUI.

Requirements:
-------------
* Qt 5
* xrandr

The application calls the xrandr process in order to set gamma.

Building:
---------

To build from the command line, run the following:
```
qmake GammaImpala.pro
make
```
-----

If you like this and find it useful,

<a href="https://www.buymeacoffee.com/noedigcode" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: 41px !important;width: 174px !important;box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;" ></a>

