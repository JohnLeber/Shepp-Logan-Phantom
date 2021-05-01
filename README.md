# Shepp-Logan Phantom Generator

This repository provides a single stand-alone portable C++ header file ([SheppLoganPhantom.h](https://github.com/JohnLeber/Shepp-Logan-Phantom/blob/master/SheppLoganPhantom.h)) that can be used to generate 2D [Shepp-Logan phantom](https://en.wikipedia.org/wiki/Shepp%E2%80%93Logan_phantom) images and write them to a block of memory. The code is hosted in a Visual Studio 2019 MFC project that demonstrates how to use the code to render an image. The code has the following features:
1) Care has been taken to keep the code in [SheppLoganPhantom.h](https://github.com/JohnLeber/Shepp-Logan-Phantom/blob/master/SheppLoganPhantom.h) portable across different platforms/compilers. 
2) The code deliberately avoids anti-aliasing so that every pixel contained in the phantom image corresponds to one of the specified grey-level intensities.
3) The shape, position, intensity and orientation of the ellipses can be customized via an input array.

![alt text](https://github.com/JohnLeber/Shepp-Logan-Phantom/blob/master/PhantomImage.jpg)

 
The original paper can be found [here](https://web.archive.org/web/20160304035526/http://stat.wharton.upenn.edu/~shepp/publications/33.pdf)
