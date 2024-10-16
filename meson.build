project(
  'test',
  'cpp',
  version : '0.1',
  default_options :
    ['warning_level=3', 'cpp_std=c++17']
)

compiler = meson.get_compiler('cpp')
all_deps = [
    compiler.find_library('sfml-graphics', dirs: '/home/linuxbrew/.linuxbrew/opt/sfml/lib/ '),
    compiler.find_library('sfml-window', dirs: '/home/linuxbrew/.linuxbrew/opt/sfml/lib/ '),
    compiler.find_library('sfml-system', dirs: '/home/linuxbrew/.linuxbrew/opt/sfml/lib/ '),
    compiler.find_library('GL', dirs: '/home/linuxbrew/.linuxbrew/opt/sfml/lib/ '),
    compiler.find_library('glut', dirs: '/home/linuxbrew/.linuxbrew/opt/sfml/lib/ '),
]
all_includes = [
]

source_files = []

subdir('src')