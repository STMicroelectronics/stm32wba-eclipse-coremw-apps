
## <b>Ux_Host_HID Application Description</b>

This application provides an example of Eclipse USBX stack usage .
It shows how to develop USB Host Human Interface "HID" able to enumerate and communicates with a mouse or a keyboard.

The application is designed to behave as a USB HID Host, the code provides required requests to properly enumerate
HID devices , HID Class APIs to decode HID reports received from a mouse or a keyboard and display data on UART HyperTerminal.

The application creates 3 threads:

  - app_ux_host_thread_entry:  used to start the host.
  - hid_mouse_thread_entry:    used to decode HID reports received from a mouse.
  - hid_keyboard_thread_entry: used to decode HID reports received from a keyboard.

#### <b>Expected success behavior</b>

When a HID device is plugged to NUCLEO-WBA65RI board, a message will be displayed on the UART HyperTerminal showing
the Vendor ID and Product ID of the attached device.
After enumeration phase, a message will indicate that the device is ready for use.
The host must be able to properly decode HID reports sent by the corresponding device and display those information on the HyperTerminal.

The received HID reports are used by host to identify:

In case of a mouse:

   - (x,y) mouse position
   - Wheel position
   - Pressed mouse buttons

In case of a keyboard:

   - Pressed key

#### <b>Error behaviors</b>

Errors are detected such as (Unsupported device, Enumeration Fail) and the corresponding message is displayed on the HyperTerminal.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" Specification and HID class Specification.

#### <b>Known limitations</b>

None

### <b>Notes</b>

None

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

Connectivity, USBX Host, FreeRTOS, USB_OTG, HID, Mouse, Keyboard, UART, USART,


### <b>Hardware and Software environment</b>

  - This application runs on STM32WBAxx devices
  - This application has been tested with STMicroelectronics NUCLEO-WBA65RI boards revision MB2130-WBA65RI-A01
    and can be easily tailored to any other supported device and development board.

- NUCLEO-WBA65RI Set-up
    - Plug the USB HID device into the NUCLEO-WBA65RI board through 'Type C  to A-Female' cable to the connector:
      - CN9 : to use USB High Speed OTG IP
    - Connect ST-Link cable to the PC USB port to display data on the HyperTerminal.

    A virtual COM port will then appear in the HyperTerminal:

     - Hyperterminal configuration
       - Data Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - Flow control: None

<b>Note</b>
It is mandatory to check that the Jumpers below are fitted:
    JP1 :   5V_USB Jumper is fitted in order to provide Vbus 5V.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open EWARM project
 - Rebuild all files and load your image into target memory
 - Run the application

<b>Note</b>

The user has to check the list of the COM ports in Device Manager to find out the number of the COM ports that have been assigned (by OS) to the Stlink VCP.
The application uses the HSE clock as USB source clock.
