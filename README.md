# Task Allocation Monitor

## Setup

The setup requires the package manager Conan to be installed and set up for use with the bincrafters repository.
Please refer to Conan's [installation page](https://docs.conan.io/en/1.7/installation.html), as well as the setup page for [bincrafters](https://bintray.com/bincrafters/public-conan) for questions on the installation.
Once conan is set up properly, the Cmake build will set up the project properly.

### Debugging

On some machines, conan might not configure its settings correctly.
In such cases, it is required to manually fill profile information as follows:
```shell script
conan profile new default --detect
conan profile update settings.compiler=gcc default
conan profile update settings.compiler.version=<installed version of gcc> default
conan profile update settings.compiler.libcxx=libstc++11 default
```