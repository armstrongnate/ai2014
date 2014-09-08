This directory is for housing and building third party libraries that
are used by the ai system.

BOOST:
  - Windows users, you need to run boost_1_44_setup.exe with an 
    internet connection.

  - select multithreaded with and without debugging.
  - Only the boost-serialization packages are required.  Others
    are up to you.
  - Move the "boost" header directory to ai/include
  - Move the lib contents to ai/lib

GETOPT:
  - copy getopt.h to ai/include
  
