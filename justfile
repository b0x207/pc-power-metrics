default:
    @just --list

run: build set-suid
    exec build/pc-power-metrics

build:
    meson compile -C build

setup:
    meson setup build --wipe

set-suid:
    sudo chmod u+s build/pc-power-metrics
    sudo chown root build/pc-power-metrics
