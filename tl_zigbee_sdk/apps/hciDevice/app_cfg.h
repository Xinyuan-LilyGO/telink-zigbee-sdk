/********************************************************************************************************
 * @file	app_cfg.h
 *
 * @brief	This is the header file for app_cfg
 *
 * @author	Zigbee Group
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions
 *              in binary form must reproduce the above copyright notice, this list of
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *
 *              3. Neither the name of TELINK, nor the names of its contributors may be
 *              used to endorse or promote products derived from this software without
 *              specific prior written permission.
 *
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or
 *              relating to such deletion(s), modification(s) or alteration(s).
 *
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************************************/
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif


/**********************************************************************
 * Version configuration
 */
#include "version_cfg.h"

/**********************************************************************
 * Product Information
 */
/* PA */
#define PA_ENABLE						0

/* Debug mode */
#define	UART_PRINTF_MODE				1
#define USB_PRINTF_MODE         		0

/* HCI interface */
#define	ZBHCI_UART						1
#define ZBHCI_USB_CDC					0
#define ZBHCI_USB_HID					0

/* BDB */
#define TOUCHLINK_SUPPORT				1
#define FIND_AND_BIND_SUPPORT			0

/* Board ID */
#define BOARD_826x_EVK					0
#define BOARD_826x_DONGLE				1
#define BOARD_826x_DONGLE_PA			2
#define BOARD_8258_EVK					3
#define BOARD_8258_EVK_V1P2				4//C1T139A30_V1.2
#define BOARD_8258_DONGLE				5
#define BOARD_8278_EVK					6
#define BOARD_8278_DONGLE				7
#define BOARD_9518_EVK					8
#define BOARD_9518_DONGLE				9
#define BOARD_8258                      10

/* Board define */
#if defined(MCU_CORE_826x)
#if !PA_ENABLE
	#define BOARD						BOARD_826x_DONGLE
#else
	#define BOARD						BOARD_826x_DONGLE_PA
#endif
	#define CLOCK_SYS_CLOCK_HZ  		32000000
#elif defined(MCU_CORE_8258)
#if (CHIP_TYPE == TLSR_8258_1M)
	#define FLASH_CAP_SIZE_1M			1
#endif
	#define BOARD						BOARD_8258
	#define CLOCK_SYS_CLOCK_HZ  		48000000
#elif defined(MCU_CORE_8278)
	#define FLASH_CAP_SIZE_1M			1
	#define BOARD						BOARD_8278_DONGLE//BOARD_8278_EVK
	#define CLOCK_SYS_CLOCK_HZ  		48000000
#elif defined(MCU_CORE_B91)
	#define FLASH_CAP_SIZE_1M			1
	#define BOARD						BOARD_9518_DONGLE//BOARD_9518_EVK
	#define CLOCK_SYS_CLOCK_HZ  		48000000
#else
	#error "MCU is undefined!"
#endif

/* Board include */
#if (BOARD == BOARD_826x_EVK)
	#include "board_826x_evk.h"
#elif (BOARD == BOARD_826x_DONGLE)
	#include "board_826x_dongle.h"
#elif (BOARD == BOARD_826x_DONGLE_PA)
	#include "board_826x_dongle_pa.h"
#elif (BOARD == BOARD_8258_DONGLE)
	#include "board_8258_dongle.h"
#elif (BOARD == BOARD_8258_EVK)
	#include "board_8258_evk.h"
#elif (BOARD == BOARD_8258_EVK_V1P2)
	#include "board_8258_evk_v1p2.h"
#elif (BOARD == BOARD_8258)
	#include "board_8258.h"
#elif (BOARD == BOARD_8278_EVK)
	#include "board_8278_evk.h"
#elif (BOARD == BOARD_8278_DONGLE)
	#include "board_8278_dongle.h"
#elif (BOARD == BOARD_9518_EVK)
	#include "board_9518_evk.h"
#elif (BOARD == BOARD_9518_DONGLE)
	#include "board_9518_dongle.h"
#endif


/* Voltage detect module */
#define VOLTAGE_DETECT_ENABLE						1

/* Watch dog module */
#define MODULE_WATCHDOG_ENABLE						0

/* UART module */
#if ZBHCI_UART
#define	MODULE_UART_ENABLE							1
#endif

/* USB module */
#if (ZBHCI_USB_CDC || ZBHCI_USB_HID)
#define MODULE_USB_ENABLE							1
#if ZBHCI_USB_CDC
	#define USB_CDC_ENABLE							1
	#define USB_VENDOR_ENABLE						0
#elif ZBHCI_USB_HID
	#define USB_CDC_ENABLE							0
	#define USB_VENDOR_ENABLE						1
#endif
#endif

#if (ZBHCI_USB_PRINT || ZBHCI_USB_CDC || ZBHCI_USB_HID || ZBHCI_UART)
	#define ZBHCI_EN								1
#endif


/**********************************************************************
 * ZCL cluster support setting
 */
#define ZCL_ON_OFF_SUPPORT							1
#define ZCL_LEVEL_CTRL_SUPPORT						1
#define ZCL_LIGHT_COLOR_CONTROL_SUPPORT				1
#define ZCL_DOOR_LOCK_SUPPORT						1
#define ZCL_TEMPERATURE_MEASUREMENT_SUPPORT			1
#define ZCL_IAS_ZONE_SUPPORT						1
#define ZCL_POLL_CTRL_SUPPORT						1
#define ZCL_GROUP_SUPPORT							1
#define ZCL_SCENE_SUPPORT							1
#define ZCL_ON_OFF_SUPPORT                          1
#define ZCL_LEVEL_CTRL_SUPPORT                      1
#define ZCL_LIGHT_COLOR_CONTROL_SUPPORT             1
#define ZCL_OTA_SUPPORT								1

#define AF_TEST_ENABLE								0


/**********************************************************************
 * Stack configuration
 */
#include "stack_cfg.h"


/**********************************************************************
 * EV configuration
 */
typedef enum{
	EV_POLL_ED_DETECT,
	EV_POLL_HCI,
    EV_POLL_IDLE,
	EV_POLL_MAX,
}ev_poll_e;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
