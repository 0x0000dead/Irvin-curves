### Plotting Irving Curves for semiconductor of n type.
**TODO:**

- [x] Build and run project 
- [ ] Thoroughly discover `examples` folder to find some feautures which can be helpful for us. 
- [ ] Catch the physical basics
- [ ] Build the window prototype with buttons and trackbars (the info about modified param required)
- [ ] Implement physics part
- [ ] Plot the curves

### Build and install to MSCV 2019
This guide is expanded version of [original instruction guide.](https://qwt.sourceforge.io/qwtinstall.html)

**How to build?**
1. In this project we will use `Qt 5.15.0`. You can [download from here.](https://www.qt.io/download)  
2. Download `qwt-6.2.0` [from here](https://sourceforge.net/projects/qwt/files/qwt/6.2.0/qwt-6.2.0.zip/download) to `C:/` folder.  
3. In `Command Prompt` run `cd C:\qwt-6.2.0\` and then `qmake qwt.pro`. Make sure that `Path` variables already has `qmake.exe` path. If not then just run:  
```"C:\PATH_TO_QT\5.15.0\msvc2019_64\bin\qmake.exe" qwt.pro```
It will create `Makefile`.  
4. In the `Command Prompt` run `nmake`. It will build the src. If you have fatall erorr then before `nmake` run:  
```C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat```  
5. Then `nmake install`.  
6. Now you have `lib` and `dll` files. And you can run examples.  

**Result**
![Image of Yaktocat](/PBM/Images/example.png)
