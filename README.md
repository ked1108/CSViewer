# CSViewer
I was dealing with a lot of csv files on linux and I didn't have any program to view csv files in a gui.  
Hence I took it upon myself to create one. That resulted in the inception of CSViewer

## Installation
It's a qt5 based project and hence you need to have qt5 libaries on your system installed to run this  
on fedora you need to install `qt5-qtbase-devel` package 
```bash
sudo dnf install qt5-qtbase-devel
```
Idk about other systems go figure it out yourself  

After that you need to simple run 
```bash
mkdir build && cd build
cmake ..
make 
```
That should do the trick, if it doesn't then you either dont have cmake, or qt5 installed  
Go install it and try this again.