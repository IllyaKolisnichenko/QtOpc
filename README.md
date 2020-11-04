# QtOpc
 [GitHub Qt OPC UA](https://github.com/qt/qtopcua )


Must be installed:

1.  [Qt](https://www.qt.io)
2. [Perl](https://www.perl.org/get.html)

## Compiling on Windows

```
"c:\Program Files (x86)\Microsoft Visual Studio\2017\WDExpress\VC\Auxiliary\Build\vcvarsx86_amd64.bat"
git clone https://code.qt.io/qt/qtopcua.git
cd qtopcua
git checkout 5.12
mkdir build
cd build
qmake ..
nmake
nmake install
```

## Compiling on Linux

```
git clone https://code.qt.io/qt/qtopcua.git
cd qtopcua
git checkout 5.12
mkdir build && cd build
~/Qt/5.12.0/gcc_64/bin/qmake ..
make
sudo make install # sudo is not required if Qt 5.12 has been installed to a directory owned by the user
```