from os import mkdir,system
from os.path import exists, isdir
from shutil import copy2,copytree,rmtree

# Cleaning folders
if exists("dist") and isdir("dist"):
  rmtree("dist")

if exists("build") and isdir("build"):
  rmtree("build")

# Creating folders
mkdir("dist")
mkdir("build")

# Populating dist
copytree("src/icons/","dist/icons")

# Populating build
copytree("src/libs","build/libs")
copy2("src/CMakeLists.txt", "build")
copy2("src/bindings.cpp", "build")
copy2("src/index.html", "build")

# Build wasm
system("cd build && emcmake cmake . -DCMAKE_BUILD_TYPE=Release && cmake --build .")

# Minify html
system("html-minifier --collapse-whitespace --remove-comments --remove-optional-tags --remove-redundant-attributes --remove-script-type-attributes --remove-tag-whitespace --use-short-doctype --minify-css true --minify-js true src/index.html -o dist/index.html")
system("html-minifier --collapse-whitespace --remove-comments --remove-optional-tags --remove-redundant-attributes --remove-script-type-attributes --remove-tag-whitespace --use-short-doctype --minify-css true --minify-js true src/manifest.webmanifest -o dist/manifest.webmanifest")
