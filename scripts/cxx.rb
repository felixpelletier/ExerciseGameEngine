class Environment

  attr_accessor :cxx_flags, :build_dir, :lib_dir, :libs, :include_dir, :src_dir

  #init
  def initialize()
    #sensible defaults
    @cxx_flags = ["-Wall"]
    @build_dir = "build"
    @lib_dir = ["lib"]
    @libs = []
    @include_dir = []
    @src_dir = ''
  end

  # Append one or multiple flags
  def append_flag(a)
    begin
      @cxx_flags += a
    rescue
      @cxx_flags += [a]
    end
  end

  def append_libdir(a)
    begin
      @lib_dir += a
    rescue
      @lib_dir += [a]
    end
  end

  def append_include(a)
    begin
      @include_dir += a
    rescue
      @include_dir += [a]
    end
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

  require 'rake'

  def self.compile(src, target, env)
    sources = src.map{|i| env.prepend_src(i)}.join(' ')
    out = env.prepend_build(target)
    system "g++ #{env.cxx_flags} #{sources} #{env.get_includes()} #{env.get_libdir} #{env.get_lib()} -o #{out}"
  end

  def self.ar(src, target, env)
    sources = env.prepend_build(src)
    out = slibplatf(env.prepend_lib(target))
    system "ar crf #{out} #{sources}"
  end

  def self.slib(src, out, env)
    cout = tobj(src[0])
    compile(src, cout, env)
    ar(cout, out, env)
  end

  # generals utilities
  # change to windows compliant path
  def self.pathplatf(p)
    if $PLATFORM == "UNIX"
      pass
    else
      ps = p.split("/")
      p = ps.join("\\")
    end
    return p
  end

  # return a src file but terminated has a compilation object
  def self.tobj(f)
    fs = f.split('.')
    len = f.split('.').length
    ret = fs[len - 2] + '.o'
    return ret
  end

  # generate correct static lib name
  def self.slibplatf(o)
    if $PLATFORM == "UNIX"
      so = o.split('/')
      so[so.length - 1] = "lib" + so.last() + ".a"
      o = so.join("/")
    else
      so = o.split("/")
      so.last += ".lib"
      o = so.join("/")
    end
    return o
  end
end
