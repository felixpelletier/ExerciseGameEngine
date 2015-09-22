require 'rake'

class Environment

  attr_accessor :cxx_flags, :build_dir, :lib_dir, :libs, :include_dir, :src_dir, :compiler

  #init
  def initialize()
    #sensible defaults
    @cxx_flags = ["-Wall"]
    @build_dir = "build"
    @lib_dir = ["lib"]
    @libs = []
    @include_dir = ['include']
    @src_dir = ''
    @compiler = 'clang++'
  end

  # Append one or multiple flags
  def append_flag(a)
    begin
      @cxx_flags += a
    rescue
      @cxx_flags += [a]
    end
  end

  def append_lib(l)
    @libs += l
  end

  def append_libdir(a)
    @lib_dir += a
  end

  def append_include(a)
    @include_dir += a
  end

  def prepend_src(f)
    return @src_dir + '/' + f
  end

  def prepend_lib(f)
    @lib_dir[0] + '/' + f
  end

  def prepend_build(f)
    @build_dir + '/' + f
  end

  def cxx_flags
    @cxx_flags.join(' ')
  end

  def compile(src, out)
    src.each{|s| CXX.compile(prepend_src(s), prepend_build(CXX.tobj(s)), self, true)}
    src = src.map{|s| CXX.tobj(s)}
    CXX.compile(src.map{|s| prepend_build(s)}, out, self, false)
  end

  def get_includes()
    return @include_dir.map{|i| "-I#{i}"}.join(' ')
  end

  # return formated lib dir for g++
  def get_libdir()
    return @lib_dir.map{|i| "-L#{i}"}.join(' ')
  end

  # return formated libs for g++
  def get_lib()
    return @libs.map{|i| "-l#{i}"}.join(' ')
  end
end

module CXX

  def self.compile(src, target, env, object=false)
    ex = "#{env.compiler} #{env.cxx_flags} #{env.get_includes()} #{if object then "-c" end} #{sources} #{env.get_libdir} #{env.get_lib()} -o #{out}"
    puts ex
    system ex
  end

  def self.ar(src, target, env)
    sources = env.prepend_build(src)
    out = slibplatf(env.prepend_lib(target))
    ex = "ar crf #{out} #{sources}"
    puts ex
    system ex
  end

  def self.slib(src, out, env)
    cout = tobj(src[0])
    compile(src, cout, env, true)
    ar(cout, out, env)
  end

  # generals utilities
  # return a src file but terminated has a compilation object
  def self.tobj(f)
    fs = f.split('.')
    len = f.split('.').length
    ret = fs[len - 2] + '.o'
    return ret
  end

  # generate correct static lib name
  def self.slibplatf(o)
    if $PLATFORM == "unix"
      so = o.split('/')
      so[so.length - 1] = "lib" + so.last() + ".a"
      o = so.join("/")
    else
      so = o.split("/")
      so[so.length - 1] = so.last() + ".lib"
      o = so.join("/")
    end
    return o
  end
end
