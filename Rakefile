require 'rake/clean'
require './scripts/cxx'

$TOP = `pwd`
if ENV['OS'] == "Windows_NT"
  $PLATFORM = 'win32'
else
  $PLATFORM = 'unix'
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
  src = ['tiny_obj_loader.cc', 'test.cc']
  unless uptodate?(CXX.slibplatf('build/lib/tinyobjloader'), src)
    tiny_env = Environment.new
    tiny_env.build_dir = 'build/tinyobj'
    tiny_env.src_dir = '.tinyobj'
    CXX.slib(src, 'tinyobjloader', tiny_env)
  end
end

task :get_glm do
  unless File.directory?(".glm")
    sh "git clone https://github.com/g-truc/glm.git .glm"
    sh "git -C .glm checkout 8f39bb8730d4"
  end
end

task :main => [:get_glm] do
  env = Environment.new
  env.src_dir = 'src'
  env.build_dir = 'build'
  env.append_flag(['-O2', '-std=c++11'])
  env.append_lib(['tinyobjloader', 'glfw', 'rt', 'm', 'dl', 'GLEW', 'GLEWmx', 'GL', 'lua'])
  env.append_include(['.glm', '.tinyobj'])
  #env.append_libdir(['/usr/lib'])
  if $PLATFORM == 'win32'
    env.append_include(['"C:\Program Files (x86)\Lua\5.1\include"'])
  end
  Dir.chdir('src')
  src = Dir.glob('**/*.cpp')
  out = 'soul'
  Dir.chdir('..')
  unless uptodate?(env.prepend_build(out), src)
    CXX.compile(src, out, env)
  end
end

task :default => :main
