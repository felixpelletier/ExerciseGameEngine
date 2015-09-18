require 'rake/clean'
require './scripts/cxx'

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
    tiny_env.append_include('.tinyobj/')
    tiny_env.src_dir = '.tinyobj'
    CXX.slib(src, 'tinyobjloader', tiny_env)
  end
end
