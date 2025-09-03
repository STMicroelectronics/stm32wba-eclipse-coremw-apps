# STM32WBA RTOS Agnostic Middleware (CoreMW) MCU Firmware Package

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/stm32wba-eclipse-coremw-apps.svg?color=brightgreen)

![freertos](https://img.shields.io/badge/freertos-v11.2.0-blue.svg) ![FileX](https://img.shields.io/badge/filex-6.4.100--beta2-blue.svg) ![LevelX](https://img.shields.io/badge/levelx-6.4.100--beta1-blue.svg) ![USBX](https://img.shields.io/badge/usbx-6.4.100--beta1-blue.svg)

## Description

**STM32Cube** is an STMicroelectronics original initiative to ease developers' life by reducing efforts, time and cost.

**RTOS Agnostic CoreMW** is a collection of middleware stacks and associated applications allowing RTOS management, File System operations and connectivity through USB. It is based on:
* Eclipse ThreadX FileX, Eclipse ThreadX LevelX and Eclipse ThreadX USBX
* FreeRTOS

#### *Note*

 * All applications are provided **only** with preconfigured projects for *EWARM* toolchain.
 * Projects in this package have not been generated with STM32CubeMX (**i.e.**, no `.ioc` files are delivered).

This package is **exclusively** published on GitHub (and is neither available in STM32CubeMX nor STM32CubeIDE available on www.st.com).
It contains the integration of the RTOS Agnostic CoreMW stacks with *STM32WBA* devices, allowing users to get quick access to pre-built projects integrating them.

#### *Note*

 * The repository containing this package has been created using the `git submodule` command. Please refer to the ["How to use"](README.md#how-to-use) section explaining how to clone this repository and how to get the latest updates.

## Release note

Details about the content of this release are available in the release note [here](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/stm32wba-eclipse-coremw-apps/blob/main/Release_Notes.html).

## List of applications

The **STM32WBA RTOS Agnostic CoreMW** package contains the following applications:

Middleware            | Application                            | Short Description
----------------------|----------------------------------------|------------------------------------------------------------------------
Eclipse ThreadX FileX | Fx_File_Edit_Standalone​                | Demonstrates how to create a FAT File system on the SD card memory using FileX running in standalone mode (without RTOS)
Eclipse ThreadX USBX  | Ux_Device_HID​                          | Shows a typical application where the STM32 MCU is enumerated as an HID device in RTOS mode
Eclipse ThreadX USBX  | Ux_Device_HID_Standalone​​              | Shows a typical application where the STM32 MCU is enumerated as an HID device in standalone mode (without RTOS)
Eclipse ThreadX USBX  | Ux_Device_CDC_ACM                      | Shows a typical application where the STM32 MCU is enumerated as a CDC device
Eclipse ThreadX USBX  | Ux_Host_HID                            | Shows how to use a USB host application based on the Human Interface Device (HID) class to connect a mouse or a keyboard in RTOS mode
Eclipse ThreadX USBX  | Ux_Host_HID_Standalone                 | Shows how to use a USB host application based on the Human Interface Device(HID) class to connect a mouse or a keyboard in standalone mode (without RTOS)


## Boards available

 * STM32WBA
   * [NUCLEO-WBA65RI](https://www.st.com/en/evaluation-tools/nucleo-wba65ri.html) RevA01

## Development Toolchains and Compilers

 * IAR Embedded Workbench for ARM (EWARM) toolchain **9.60.3** + ST-LINKV3.Patch available [here](https://github.com/STMicroelectronics/STM32CubeWBA/tree/main/Utilities/PC_Software/IDEs_Patches/EWARM)


## Dependencies

This package has been developed and tested using the list of components detailed in the table below.

Name                       |   Version
---------------------------|---------------
Cortex-M CMSIS             |   V5.9.0
STM32WBAxx CMSIS           |   V1.7.0
STM32WBAxx HAL             |   V1.7.0
BSP STM32WBAxx NUCLEO      |   V1.1.0
BSP Common                 |   V7.3.0
FreeRTOS                   |   V11.2.0
Eclipse ThreadX FileX      |   V6.4.100-beta2
Eclipse ThreadX LevelX     |   V6.4.100-beta1
Eclipse ThreadX USBX       |   V6.4.100-beta1

## How to use

This repository intrinsically contains the applications (projects and source files) located under folder `./Projects`.
It also contains the CMSIS Core files under folder `./Drivers/CMSIS/Include` for size optimization reason.
Other dependencies such as the HAL and BSP drivers, or the middleware libraries themselves are linked using the `git submodule` command.
Please check the instructions below for a proper use.

---

#### *Note*

* To clone this repository along with the linked submodules, option `--recursive` has to be specified as shown below.

```
git clone --recursive https://github.com/STMicroelectronics/stm32wba-eclipse-coremw-apps.git
```

* To get the latest updates, issue the following **two** commands (with the repository `stm32wba-eclipse-coremw-apps` as the **current working directory**).

```
git pull
git submodule update --init --recursive
```

#### *Note*

 * If GitHub "Download ZIP" option is used instead of the `git clone` command, then the required components have to be collected manually by the user.

## Known Limitations

 * None
