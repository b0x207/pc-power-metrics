default:
    @just --list

run: build
    exec build/pc-power-metrics

build:
    meson compile -C build

setup:
    meson setup build
