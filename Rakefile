require 'rake/clean'
require './scripts/cxx'

$TOP = `pwd`
if ENV['OS'] == "Windows_NT"
  $PLATFORM = 'win32'
  puts "Platform is Windows NT"
else
  $PLATFORM = 'unix'
  puts "Platform is Unix like"
end

CLEAN.include(CXX.slibplatf('lib/tinyobjloader'))
#nuke the build directory
CLOBBER.include(['build', '.tinyobj', '.glm'])

directory "build/tinyobj"

task :get_tinyobj do
  unless File.directory?(".tinyobj")
    sh 'git clone https://github.com/syoyo/tinyobjloader .tinyobj'
    sh 'git -C .tinyobj checkout 475bc83ef319'
  end
end

task :tinyobj => [:get_tinyobj, "build/tinyobj"] do
  src = ['tiny_obj_loader.cc']
  unless uptodate?(CXX.slibplatf('build/lib/tinyobjloader'), src)
    tiny_env = Environment.new
    tiny_env.build_dir = 'build/tinyobj'
    tiny_env.src_dir = '.tinyobj'
    tiny_env.cxx_flags = []
    tiny_env.include_dir = []
    CXX.slib(src, 'tinyobjloader', tiny_env)
  end
end

task :get_glm do
  unless File.directory?(".glm")
    sh "git clone https://github.com/g-truc/glm.git .glm"
    sh "git -C .glm checkout 8f39bb8730d4"
  end
end

task :main => [:get_glm, :tinyobj] do
  env = Environment.new
  env.src_dir = 'src'
  env.build_dir = 'build'
  env.append_flag(['-O2', '-std=c++11', '--verbose', '-Wl,--verbose'])
  env.append_lib(['tinyobjloader', 'GLEW', 'GLEWmx'])
  env.append_include(['.glm', '.tinyobj'])
  if $PLATFORM == 'win32'
    env.append_include(['"C:\Program Files (x86)\Lua\5.1\include"'])
    env.append_libdir(['"C:\Program Files (x86)\Lua\5.1"', '"C:\tools\mingw64\lib\gcc\x86_64-w64-mingw32\lib"'])
    env.append_lib(['glfw3', 'lua51', 'opengl32', 'gdi32', 'glew32', 'glew32mx'])
  else
    env.append_lib(['glfw', 'rt', 'm', 'dl', 'lua', 'GL', 'GLEW', 'GLEWmx'])
  end
  Dir.chdir('src')
  src = Dir.glob('**/*.cpp')
  out = 'soul'
  Dir.chdir('..')
  unless uptodate?(env.prepend_build(out), src)
    CXX.compile(src, out, env)
  end
end

task :run => :main do
  sh "./build/soul"
end

task :default => :main
