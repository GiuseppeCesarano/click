from os import mkdir, system
from os.path import exists, isdir
from shutil import copy2, copytree, rmtree

if not (exists("dist") and isdir("dist")):
    mkdir("dist")

if not(exists("build") and isdir("build")):
    mkdir("build")

if not(exists("dist/icons/") and isdir("dist/icons/")):
    copytree("src/icons/", "dist/icons")

copy2("src/index.html", "dist")

# Populating build

if exists("build/libs/") and isdir("build/libs/"):
    rmtree("build/libs")
copytree("src/libs", "build/libs")

copy2("src/CMakeLists.txt", "build")
copy2("src/bindings.cpp", "build")

grinder_list = []
with open("grinders.txt") as grinders_file:
    lines = grinders_file.readlines()
    for line in lines:
        l = line[:-1].split(',')
        grinder_list.append(l)

init_list = []
map = []

for grinder in grinder_list:
    if len(grinder) > 2:
        vals = ','.join(grinder[2:])
        init_list.append("constexpr std::initializer_list<int> {NAME} {{{VAL}}};\n".format(
            NAME=grinder[0].replace('-', '_'), VAL=vals))
        map.append('{{"{NAME}"sv, grinder{{{H_CLICK}, {INIT_LIST}}}}}'.format(
            NAME=grinder[0], H_CLICK=grinder[1], INIT_LIST=grinder[0].replace('-', '_')))
    else:
        map.append('{{"{NAME}"sv, grinder{{{H_CLICK}}}}}'.format(
            NAME=grinder[0], H_CLICK=grinder[1]))

initializer_list = ''.join(init_list)
constexpr_map = ','.join(map)

with open("build/libs/grinders/grinders.hpp", "r+") as hpp:
    hpp_text = hpp.read()
    hpp_text = hpp_text.replace("PYTHON_INITIALIZER", initializer_list).replace(
        "PYTHON_SIZE", str(len(grinder_list))).replace("PYTHON_MAP", constexpr_map)
    hpp.seek(0)
    hpp.write(hpp_text)

with open("dist/index.html", "r+") as index:
    options = []
    index_text = index.read()
    for grinder in grinder_list:
        options.append('<option>{NAME}</option>'.format(NAME=grinder[0]))
    index_text = index_text.replace("<PYTHON_OPTIONS>", ''.join(options))
    index.seek(0)
    index.write(index_text)

# Build wasm
system("cd build && emcmake cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=Yes && cmake --build .")

# Minify html
MINIFY_CMD = "html-minifier --collapse-whitespace --remove-comments --remove-optional-tags --remove-redundant-attributes --remove-script-type-attributes --remove-tag-whitespace --use-short-doctype --minify-css true --minify-js true --minifyURLs true {} -o {}"

system(MINIFY_CMD.format("dist/index.html", "dist/index.html"))
system(MINIFY_CMD.format("src/manifest.webmanifest", "dist/manifest.webmanifest"))
system(MINIFY_CMD.format("src/sw.js", "dist/sw.js"))
