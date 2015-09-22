require 'rake/clean'
require './scripts/cxx'

$TOP = `pwd`
if ENV['OS'] == "Windows_NT"
  $PLATFORM = 'win32'
  puts "Platform is Windows NT."
else
  $PLATFORM = 'unix'
  puts "Platform is Linux."
end

CLEAN.include([CXX.slibplatf('lib/tinyobjloader'), 'build/soul', 'build/soul.exe', 'build/tinyobj/tiny_obj_loader.o'])
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
  unless uptodate?(CXX.slibplatf('lib/tinyobjloader'), src)
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

  #def src
  Dir.chdir('src')
  src = Dir.glob('**/*.cpp')
  Dir.chdir('..')

  #def out
  if $PLATFORM == "win32"
    out = 'soul.exe'
  else
    out = 'soul'
  end
  out = env.prepend_build(out)

  env.src_dir = 'src'
  env.build_dir = 'build'
  env.append_flag(['-O2', '-std=c++11'])
  if ENV['debug']
    env.append.flag(['--verbose', 'Wl,-v', '-g'])
  end
  env.append_lib(['tinyobjloader'])
  env.append_include(['.glm', '.tinyobj'])
  if $PLATFORM == 'win32'
    env.append_include(['"./include/lua"'])
    #env.append_libdir(['""', '"C:\tools\mingw64\lib\gcc\x86_64-w64-mingw32\lib"'])
    env.append_lib(['glfw3', 'lua53', 'opengl32', 'gdi32', 'glew32'])
    ex = "cp ./lib/lua53.dll ./lib/glew32.dll ./build"
    puts ex
    system ex
  else # linux env
    env.append_lib(['glfw', 'rt', 'm', 'dl', 'lua', 'GL', 'GLEW'])
  end
  env.compile(src, out)
end

task :run => :main do
  if $PLATFORM == 'win32'
    exe = './build/soul.exe'
  else
    exe = './build/soul'
  end
  puts exe
  system exe
end

task :default => :main
