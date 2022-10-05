#!/bin/sh

prefix="prefix = "
my_path="$(pwd)"
build_path="$prefix""$my_path""/sdl/build"
sed -i .bak "7s,.*,$build_path," ./sdl/build/Makefile
