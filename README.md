# PC Power Metrics

A simple program that displays metrics about the power consumtion of the device using Intel's RAPL technology.

## Building

### Using the Justfile

```
just setup
just build # or just run
```

#### Using Meson Directly

```
meson setup build
meson compile -C build
```
