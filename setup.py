#python setup.py build
#python setup.py install

from distutils.core import setup, Extension

skcmodule = Extension('skc',
                      depends = ['controller.h'],
                      extra_objects = ['/Users/sameriksson/store/xcode/PySamKeyCapture/libSamKeyCapture.a'],
                      #extra_link_args=['-static'],
                      #include_dirs = ['/Users/sameriksson/store/xcode/PySamsScreenCapture'],
                      #libraries = ['libSamScreenCapture'],
                      #library_dirs = ['/Users/sameriksson/store/xcode/PySamsScreenCapture'],
                      sources = ['samskeycapture.c'])

setup (name = 'skc',
       version = '1.0',
       description = 'Sams Key Capture',
       ext_modules = [skcmodule])
