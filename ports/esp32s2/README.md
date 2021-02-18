MicroPython port to the ESP32S2
===============================

This is a port of MicroPython to the Espressif ESP32S series of
microcontrollers. It uses the ESP-IDF framework and MicroPython runs as
a task under FreeRTOS.

Supported features include:
- REPL (Python prompt) over UART0 and USB.
- 16k stack for the MicroPython task and approximately 100k Python heap.
- Many of MicroPython's features are enabled: unicode, arbitrary-precision
  integers, single-precision floats, complex numbers, frozen bytecode, as
  well as many of the internal modules.
- Internal filesystem using the flash.
- The machine module with GPIO, UART, SPI, software I2C, ADC, DAC, PWM,
  TouchPad, WDT and Timer.
- The network module with WLAN (WiFi) support.

Setting up ESP-IDF and the build environment
--------------------------------------------

MicroPython on ESP32S2 requires the Espressif IDF version 4.2 (IoT development
framework, aka SDK). The ESP-IDF includes the libraries and RTOS needed to
manage the microcontroller, as well as a way to manage the required build
environment and toolchains needed to build the firmware.

The ESP-IDF changes quickly and MicroPython only supports certain versions.
Currently MicroPython supports only v4.2.

To install the ESP-IDF the full instructions can be found at the
[Espressif Getting Started guide](https://docs.espressif.com/projects/esp-idf/en/v4.2/get-started/index.html#installation-step-by-step).

If you are on a Windows machine then the [Windows Subsystem for
Linux](https://msdn.microsoft.com/en-au/commandline/wsl/install_guide) is the
most efficient way to install the ESP32S2 toolchain and build the project. If
you use WSL then follow the Linux instructions rather than the Windows
instructions.

The Espressif instructions will guide you through using the `install.sh`
(or `install.bat`) script to download the toolchain and set up your environment.
The steps to take are summarised below.

To check out a copy of the IDF use git clone:

```bash
$ git clone -b v4.2 --recursive https://github.com/espressif/esp-idf.git
```

(You don't need a full recursive clone; see the `ci_esp32_setup` function in
`tools/ci.sh` in this repository for more detailed set-up commands.)

After you've cloned and checked out the IDF to the correct version, run the
`install.sh` script:

```bash
$ cd esp-idf
$ ./install.sh       # (or install.bat on Windows)
$ source export.sh   # (or export.bat on Windows)
```

The `install.sh` step only needs to be done once. You will need to source
`export.sh` for every new session.

Building the firmware
---------------------

The MicroPython cross-compiler must be built to pre-compile some of the
built-in scripts to bytecode.  This can be done by (from the root of
this repository):

```bash
$ make -C mpy-cross
```

Then to build MicroPython for the ESP32S2 run:

```bash
$ cd ports/esp32s2
$ make
```

This will produce a combined `firmware.bin` image in the `build-GENERIC/`
subdirectory (this firmware image is made up of: bootloader.bin, partitions.bin
and micropython.bin).

To flash the firmware you must have your ESP32S2 in the bootloader
mode and connected to a serial port on your PC. Refer to the documentation
for your particular ESP32S2 board/module for how to do this.
You will also need to have user permissions to access the `/dev/ttyUSB0` device.
On Linux, you can enable this by adding your user to the `dialout` group, and
rebooting or logging out and in again. (Note: on some distributions this may
be the `uucp` group, run `ls -la /dev/ttyUSB0` to check.)

```bash
$ sudo adduser <username> dialout
```

If you are installing MicroPython to your module for the first time, or
after installing any other firmware, you should first erase the flash
completely:

```bash
$ make erase
```

To flash the MicroPython firmware to your ESP32S2 use:

```bash
$ make flash
```

The default ESP32S2 board build by the above commands is the `GENERIC` one, which
should work on most ESP32S2 modules. You can specify a different board by passing
`BOARD=<board>` to the make commands, for example:

```bash
$ make BOARD=GENERIC_SPIRAM
```
Note: the above "make" commands are thin wrappers for the underlying `idf.py`
build tool that is part of the ESP-IDF. You can instead use `idf.py` directly,
for example:

```bash
$ idf.py set-target esp32s2
$ idf.py build
$ idf.py -D MICROPY_BOARD=GENERIC_SPIRAM build
$ idf.py flash
```

Getting a Python prompt on the device
-------------------------------------

You can get a prompt via USB or the serial port, via UART0, which is the same UART
that is used for programming the firmware. The baudrate for the REPL is
115200 and you can use a command such as:

```bash
$ picocom -b 115200 /dev/ttyUSB0
```
or

```bash
$ miniterm.py /dev/ttyUSB0 115200
```

You can also use `idf.py monitor`.

Configuring the WiFi and using the board
----------------------------------------

The ESP32S2 port is designed to be (almost) equivalent to the ESP32 in
terms of the modules and user-facing API. There are some minor differences but
for the most part the documentation and tutorials for the ESP32 should apply
to the ESP32S2 (at least for the components that are implemented).

The following function can be used to connect to a WiFi access point (you can
either pass in your own SSID and password, or change the defaults so you can
quickly call `wlan_connect()` and it just works):

```python
def wlan_connect(ssid='MYSSID', password='MYPASS'):
    import network
    wlan = network.WLAN(network.STA_IF)
    if not wlan.active() or not wlan.isconnected():
        wlan.active(True)
        print('connecting to:', ssid)
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    print('network config:', wlan.ifconfig())
```

Defining a custom ESP32S2 board
-------------------------------

The default ESP-IDF configuration settings are provided by the `GENERIC`
board definition in the directory `boards/GENERIC`. For a custom configuration
you can define your own board directory.  Start a new board configuration by
copying an existing one (like `GENERIC`) and modifying it to suit your board.

MicroPython specific configuration values are defined in the board-specific
`mpconfigboard.h` file, which is included by `mpconfigport.h`. Additional
settings are put in `mpconfigboard.cmake`, including a list of `sdkconfig`
files that configure ESP-IDF settings. Some standard `sdkconfig` files are
provided in the `config/` directory, like `config/sdkconfig.defaults`. You can
also define custom ones in your board directory.

See existing board definitions for further examples of configuration.
