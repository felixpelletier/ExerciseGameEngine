require 'rake/clean'
require './scripts/cxx'

$TOP = `pwd`
$PLATFORM = 'UNIX'

CLEAN.include('lib/libtinyobjloader.a')
#nuke the build directory
CLOBBER.include(['build', '.tinyobj'])

directory "build/tinyobj"

task :get_tinyobj do
  unless File.directory?(".tinyobj")
    sh 'git clone https://github.com/syoyo/tinyobjloader .tinyobj'
  end
  sh "git -C .tinyobj pull"
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
  end
  sh "git -C .glm pull"
end

task :main => [:get_glm, :tinyobj] do
  env = Environment.new
  env.src_dir = 'src'
  env.build_dir = 'build'
  env.append_flag(['-O2', '-std=c++11'])
  env.append_lib(['tinyobjloader', 'glfw3', 'GLEW'])
  env.append_include(['.glm/glm', '.tinyobj'])
  Dir.chdir('src')
  src = Dir.glob('**/*.cpp')
  out = 'soul'
  Dir.chdir('..')
  unless uptodate?(env.prepend_build(out), src)
    CXX.compile(src, out, env)
  end
end
