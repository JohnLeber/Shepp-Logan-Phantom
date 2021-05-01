# Shepp-Logon Phantom Generator

This project provides a single stand-alone portable C++ header file (SheppLogonPhantom.h) that can be used to generate [Shepp-Logon phantom](https://en.wikipedia.org/wiki/Shepp%E2%80%93Logan_phantom) images and write them to a block of memory. The code is hosted in a Visual Studio 2019 MFC project that demonstrates how to use the code to render an image. Care has been taken, however, to keep the code in SheppLogonPhantom.h portable across different platforms/compilers. The code deliberately avoids anti-aliasing so that every pixel contained in the phantom image corresponds to one of the specified grey-level intensities.

![alt text](https://github.com/nodecomplete/SheppLogon/blob/master/SheppLogon/PhantomImage.jpg)

 
