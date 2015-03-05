import os

## Default flag of scons
#SetOption('implicit_cache', 1)
# use --implicit-deps-changed to force a rebuild of deps


## The environment var
# NOTE: the PATH var has a default value and is not equal to a user PATH
#path = [ '/usr/bin'
#        ,'/usr/local/bin']

platform = ARGUMENTS.get('OS', Platform())
include = "#./include:."
lib = "#./lib:/usr/lib:/usr/lib/mesa"
bin = "#./bin"

default_flags = ['-std=c++11']
env_flags = [ '-O1'] + default_flags
debug_flags = [ '-Wall'
               ,'-g'] + default_flags

# semi deployment (dev)
env = Environment( BINDIR = bin
                  ,INCDIR = include
                  ,LIBDIR = lib
                  ,CPPPATH = include
                  ,LIBPATH = [lib]) 
# full debug env
debug = env.Clone()
env.Append(CCFLAGS = env_flags)
debug.Append(CCFLAGS = debug_flags)
# an environment holds a set of vars and rules to build a specific project, for our needs, env is the default environment
# use Environment(ENV = {'PATH' : path}) to change PATH

Export('env debug') # white space are illegal var name in python, this is auto split


# actual building
tiny_build = './.build/tinyobj'
soul_build = './.build/soul'
SConscript('./scripts/.tinyobj/SConscript', variant_dir=tiny_build) 
SConscript('./src/SConscript', variant_dir=soul_build) # duplicate source code


## Various useful command
# Ignore(target, './file.h') ignore for a given target some implicit deps
# Depends(target, './file.h') for an explicit deps
# env.Copy(options) return a copy plus the new options of an environement
# COMMAND_LINE_TARGETS -> iterator that contain args
#   if bar in COMMAND_LINE_TARGETS: something
# see env.InstallAs if multiple bin need to be installed in the same dir under differents name
# env.Precious(targets) -> scons won't delete precious target, unless -c (clean) flag is up
# hierarchical build: http://www.scons.org/doc/0.96.1/HTML/scons-user/c1736.html
# we can collect compile obj from sconscript with the Return('obj') pattern
