# Scripts


I've put scripts in here to build clang and gcc in comfortably out-of-the-way directories
in /usr/local to avoid interfering with system operations. You may need to use
LD\_LIBRARY\_PATH to point your system at dynamic libraries built by these compilers
if you don't want to adjust your system libdirs. Adjusting your system libdirs would
kind of defeat the purpose of building these compilers out of the way, I think.


Check the scripts for directories and stuff prior to building them. They don't check the
sources out for you -- you need to do that separately.


## Building gcc


 * Clone the gcc source repo down from the git mirror or download it from a gnu.org mirror.
 * make a build directory in the top level source directory
 * run the buildgcc.sh script in this directory from that build directory.
 
 
Please verify the configure flags being passed are what you want for your system
prior to building. There's not a whole lot in there, but you may want to add or remove
some flags. You may also want to adjust the number of processes make uses. 


This is a pretty big build, so expect it to take potentially upward of an hour depending
on your system config and number of processes you allocate to it.


## Building Clang

 * Requires ninja. If you want to use modules anywhere, you'll need to install ninja or something else that supports modules anyway.
 * Clone the Bloomberg p2996 for somewhere and point the CLANG_SOURCE variable in the script
   to that directory.
 * The buildclang script will build the compiler in /tmp/build. You can run "sudo ninja install" from that directory when the build completes.
