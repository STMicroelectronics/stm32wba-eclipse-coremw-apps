/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_usbx_host.c
  * @brief   USBX host applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_usbx_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define APP_DEFAULT_STACK_SIZE    (configMINIMAL_STACK_SIZE * 8)
#define APP_DEFAULT_PRIORITY      (configMAX_PRIORITIES / 2U)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TaskHandle_t ux_host_app_thread_handle;
TaskHandle_t hid_keyboard_thread_handle;
TaskHandle_t hid_mouse_thread_handle;

UX_HOST_CLASS_HID          *hid_instance;
UX_HOST_CLASS_HID_MOUSE    *mouse;
UX_HOST_CLASS_HID_KEYBOARD *keyboard;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static VOID app_ux_host_thread_entry(void *args);
static UINT ux_host_event_callback(ULONG event, UX_HOST_CLASS *current_class, VOID *current_instance);
static VOID ux_host_error_callback(UINT system_level, UINT system_context, UINT error_code);
/* USER CODE BEGIN PFP */
extern HCD_HandleTypeDef hhcd_USB_OTG_HS;
/* USER CODE END PFP */

/**
  * @brief  Application USBX Host Initialization.
  * @param  none
  * @retval status
  */
UINT MX_USBX_Host_Init(VOID)
{
  UINT ret = UX_SUCCESS;

  /* Initialize the USBX Host stack */
  if (MX_USBX_Host_Stack_Init() != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  /* Create the USBX Host thread entry */
  if (xTaskCreate(app_ux_host_thread_entry, "host thread entry",
                       APP_DEFAULT_STACK_SIZE, NULL,
                       APP_DEFAULT_PRIORITY, &ux_host_app_thread_handle) != pdPASS)
  {
    return UX_ERROR;
  }

  /* Create the HID mouse thread */
  if (xTaskCreate(hid_mouse_thread_entry, "hid mouse thread entry",
                       APP_DEFAULT_STACK_SIZE, NULL,
                       APP_DEFAULT_PRIORITY, &hid_mouse_thread_handle) != pdPASS)
  {
    return UX_ERROR;
  }

  /* Create the HID keyboard thread */
  if (xTaskCreate(hid_keyboard_thread_entry, "hid keyboard thread entry",
                       APP_DEFAULT_STACK_SIZE, NULL,
                       APP_DEFAULT_PRIORITY, &hid_keyboard_thread_handle) != pdPASS)
  {
    return UX_ERROR;
  }

  return ret;
}


/**
  * @brief  Function implementing app_ux_host_thread_entry.
  * @param  args: Not used
  * @retval none
  */
static VOID app_ux_host_thread_entry(void *args)
{
  /* USER CODE BEGIN app_ux_host_thread_entry */

  /* Initialization of USB host */
  USBX_APP_Host_Init();
  vTaskDelete(ux_host_app_thread_handle);
}
/**
  * @brief  ux_host_event_callback
  *         This callback is invoked to notify application of instance changes.
  * @param  event: event code.
  * @param  current_class: Pointer to class.
  * @param  current_instance: Pointer to class instance.
  * @retval status
  */
UINT ux_host_event_callback(ULONG event, UX_HOST_CLASS *current_class, VOID *current_instance)
{
  UINT status = UX_SUCCESS;

  UX_HOST_CLASS_HID_CLIENT *client  = (UX_HOST_CLASS_HID_CLIENT *)current_instance;

  switch (event)
  {
    case UX_DEVICE_INSERTION:
      if (current_class->ux_host_class_entry_function == ux_host_class_hid_entry)
      {
        if (hid_instance == NULL)
        {
          hid_instance = (UX_HOST_CLASS_HID *)current_instance;
        }
      }
      break;

    case UX_DEVICE_REMOVAL:
      if ((void*)hid_instance == current_instance)
      {
        hid_instance = NULL;
      }
      break;

    case UX_HID_CLIENT_INSERTION:
      USBH_UsrLog("\nHID Client Plugged");

      if (client->ux_host_class_hid_client_handler == ux_host_class_hid_keyboard_entry)
      {
        if (keyboard == NULL)
        {
          keyboard = client->ux_host_class_hid_client_local_instance;

          USBH_UsrLog("HID_Keyboard_Device");
          USBH_UsrLog("PID: %#x ", (UINT)keyboard->ux_host_class_hid_keyboard_hid->ux_host_class_hid_device->ux_device_descriptor.idProduct);
          USBH_UsrLog("VID: %#x ", (UINT)keyboard->ux_host_class_hid_keyboard_hid->ux_host_class_hid_device->ux_device_descriptor.idVendor);
          USBH_UsrLog("USB HID Host Keyboard App...");
          USBH_UsrLog("keyboard is ready...\n");
        }
      }

      if (client->ux_host_class_hid_client_handler == ux_host_class_hid_mouse_entry)
      {
        if (mouse == NULL)
        {
          mouse = client->ux_host_class_hid_client_local_instance;

          USBH_UsrLog("HID_Mouse_Device");
          USBH_UsrLog("PID: %#x ", (UINT)mouse->ux_host_class_hid_mouse_hid->ux_host_class_hid_device->ux_device_descriptor.idProduct);
          USBH_UsrLog("VID: %#x ", (UINT)mouse->ux_host_class_hid_mouse_hid->ux_host_class_hid_device->ux_device_descriptor.idVendor);
          USBH_UsrLog("USB HID Host Mouse App...");
          USBH_UsrLog("Mouse is ready...\n");
        }
      }
      break;

    case UX_HID_CLIENT_REMOVAL:
      if ((void*)keyboard == client->ux_host_class_hid_client_local_instance)
      {
        keyboard = NULL;
        USBH_UsrLog("\nHID Client Keyboard Unplugged");
      }

      if ((void*)mouse == client->ux_host_class_hid_client_local_instance)
      {
        mouse = NULL;
        USBH_UsrLog("\nHID Client Mouse Unplugged");
      }
      break;

    default:
      break;
  }

  return status;
}


/**
  * @brief  ux_host_error_callback
  *         This callback is invoked to notify application of error changes.
  * @param  system_level: system level parameter.
  * @param  system_context: system context code.
  * @param  error_code: error event code.
  * @retval none
  */
VOID ux_host_error_callback(UINT system_level, UINT system_context, UINT error_code)
{
  switch (error_code)
  {
    case UX_DEVICE_ENUMERATION_FAILURE:
      USBH_UsrLog("USB Device Enumeration Failure");
      break;

    case UX_NO_DEVICE_CONNECTED:
      USBH_UsrLog("USB Device disconnected");
      break;

    default:
      break;
  }
}


/**
  * @brief MX_USBX_Host_Stack_Init
  *        Initialization of USB host stack.
  *        Init USB Host stack, add register the host class stack
  * @retval ret
  */
UINT MX_USBX_Host_Stack_Init(VOID)
{
  UINT ret = UX_SUCCESS;

  if (ux_host_stack_initialize(ux_host_event_callback) != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  ux_utility_error_callback_register(&ux_host_error_callback);

  if (ux_host_stack_class_register(_ux_system_host_class_hid_name, ux_host_class_hid_entry) != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  if (ux_host_class_hid_client_register(_ux_system_host_class_hid_client_mouse_name, ux_host_class_hid_mouse_entry) != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  if (ux_host_class_hid_client_register(_ux_system_host_class_hid_client_keyboard_name, ux_host_class_hid_keyboard_entry) != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  ux_host_stack_hcd_register(_ux_system_host_hcd_stm32_name, _ux_hcd_stm32_initialize,
                             USB_OTG_HS_BASE, (ULONG)&hhcd_USB_OTG_HS);

  return ret;
}


/**
  * @brief  MX_USBX_Host_Stack_DeInit
  *         Uninitialize the host stack, unregister of host class stack and
  *         unregister of the usb host controllers
  * @retval ret
  */
UINT MX_USBX_Host_Stack_DeInit(VOID)
{
  UINT ret = UX_SUCCESS;

  ux_host_stack_hcd_unregister(_ux_system_host_hcd_stm32_name, USB_OTG_HS_BASE, (ULONG)&hhcd_USB_OTG_HS);

  if (ux_host_stack_class_unregister(ux_host_class_hid_entry) != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  if (ux_host_stack_uninitialize() != UX_SUCCESS)
  {
    return UX_ERROR;
  }

  return ret;
}
/* USER CODE BEGIN 1 */
/**
  * @brief  USBX_APP_Host_Init
  *         Initialization of USB host.
  * @param  none
  * @retval none
  */
void USBX_APP_Host_Init(void)
{
  HAL_HCD_Start(&hhcd_USB_OTG_HS);

  USBH_UsrLog("**** USB OTG HS in HID Host **** \n");
  USBH_UsrLog("USB Host library started.\n");
  USBH_UsrLog("Starting HID Application");
  USBH_UsrLog("Connect your HID Device");
}

/**
  * @brief  USB utility interrupt disable.
  * @retval interrupt_save
  */
ALIGN_TYPE _ux_utility_interrupt_disable(VOID)
{
  UINT interrupt_save;

  interrupt_save = __get_PRIMASK();
  __disable_irq();

  return interrupt_save;
}

/**
  * @brief  USB utility interrupt restore.
  * @retval none
  */
VOID _ux_utility_interrupt_restore(ALIGN_TYPE flags)
{
  __set_PRIMASK(flags);
}

/**
  * @brief  Get Time Tick for host timing.
  * @retval time tick
  */
ULONG _ux_utility_time_get(VOID)
{
  return HAL_GetTick();
}

/* USER CODE END 1 */
