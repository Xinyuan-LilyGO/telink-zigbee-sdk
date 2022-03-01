/********************************************************************************************************
 * @file	drv_nv.h
 *
 * @brief	This is the header file for drv_nv
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



/********************************************************************
 * @brief	Flash map usage.
 *
 * #if !defined(BOOT_LOADER_MODE) || (BOOT_LOADER_MODE == 0)
 *	 				512k							  1M
 * 		0x80000  ------------			0x100000  ------------
 *	 			|		     |					 |  MAC_Addr  |
 *	  		    |  	 NV_2 	 |			 0xFF000 |------------|
 *	 		    |		     |					 | F_CFG_Info |
 *		0x7A000 |------------|			 0xFE000 |------------|
 *	 		    | U_Cfg_Info |					 | U_Cfg_Info |
 * 		0x78000 |------------|			 0xFC000 |------------|
 *		   		| F_CFG_Info |					 |  Reserved  |
 * 		0x77000 |------------|			 0x96000 |------------|
 * 		   		|  MAC_Addr  |					 |     NV     |
 * 		0x76000 |------------|			 0x80000 |------------|
 * 		   		|		     |					 |			  |
 * 		   		|  OTA_Image |					 |			  |
 * 		   		|		     |					 |	OTA_Image |
 * 		0x40000 |------------|					 |			  |
 * 		   		|		     |					 |			  |
 * 		   		|  	 NV_1 	 |			 0x40000 |------------|
 * 		   		|		     |					 |			  |
 * 		0x34000 |------------|					 |			  |
 * 		   		|		     |					 |  Firmware  |
 * 		   		|  Firmware  |	208k			 |			  | 256k
 * 		   		|		     |					 |			  |
 * 		0x00000  ------------			 0x00000  ------------
 *
 * #else
 *	 				512k							  1M
 * 		0x80000  ------------			0x100000  ------------
 *	 			|			 |					 |  MAC_Addr  |
 *	 			|  	 NV_2 	 |			 0xFF000 |------------|
 *	 			|			 |					 | F_CFG_Info |
 *	 	0x7A000 |------------|			 0xFE000 |------------|
 *	 			| U_Cfg_Info |					 | U_Cfg_Info |
 *	 	0x78000 |------------|			 0xFC000 |------------|
 *	 			| F_CFG_Info |					 |		      |
 *	 	0x77000 |------------|					 |     NV     |
 *	 			|  MAC_Addr  |					 |		      |
 *	 	0x76000 |------------|			 0xE6000 |------------|
 *	 			|		     |					 |		      |
 *	 			|  	 NV_1	 |					 |		      |
 *	 			|		     |					 |	OTA_Image |
 *	 	0x6A000 |------------|					 |		      |
 *	 			|		     |					 |		      |
 *	 			|  OTA_Image |			 0x77000 |------------|
 *	 			|		     |					 |		      |
 *	 	0x39000 |------------|					 |		      |
 *	 			|			 |					 |  Firmware  |
 *	 			|  Firmware	 |	196k			 |		      | 444k
 *	 			|			 |					 |		      |
 *	 	0x08000 |------------|			 0x08000 |------------|
 *	 			| BootLoader |					 | BootLoader |
 *	 	0x00000  ------------			 0x00000  ------------
 *
 * #endif
 */

/* Flash Base Address define */
#if defined(MCU_CORE_826x) || defined(MCU_CORE_8258) || defined(MCU_CORE_8278)
	#define FLASH_TLNK_FLAG_OFFSET		8
#elif defined(MCU_CORE_B91)
	#define FLASH_TLNK_FLAG_OFFSET		32
#endif



/************************************************************************
 * Flash address of factory setting parameters,
 * where are stored the MAC ADDRESS and CALIBRATION information.
 */
//512k flash
#define FLASH_ADDR_OF_MAC_ADDR_512K		0x76000
#define FLASH_ADDR_OF_F_CFG_INFO_512K	0x77000
//1M flash
#define FLASH_ADDR_0F_MAC_ADDR_1M		0xFF000
#define FLASH_ADDR_OF_F_CFG_INFO_1M		0xFE000

/************************************************************************/
extern u32 g_u32MacFlashAddr;
extern u32 g_u32CfgFlashAddr;

#define MAC_BASE_ADD					(g_u32MacFlashAddr)
#define FACTORY_CFG_BASE_ADD			(g_u32CfgFlashAddr)
/************************************************************************/

/**************************************************************************************
 * The following is the detailed factory configure information (F_CFG_Info).
 */
/* 8 bytes for MAC address. */
#define CFG_MAC_ADDRESS              	(MAC_BASE_ADD)

/* 2 bytes for USB ID. */
#define CFG_TELINK_USB_ID				(MAC_BASE_ADD + 0x40)

/* 1 byte for frequency offset calibration. */
#define CFG_FREQUENCY_OFFSET			(FACTORY_CFG_BASE_ADD)

/* 2 bytes for TP GAIN.
 * 0x77040(or 0xFE040) for BLE TP_GAIN_0, 0x77041(or 0xFE041) for BLE TP_GAIN_1,
 * 0x77042(or 0xFE042) for zigbee TP_GAIN_0, 0x77043(or 0xFE043) for zigbee TP_GAIN_1. */
#define CFG_TP_GAIN                  	(FACTORY_CFG_BASE_ADD + 0x42)

/* Not supported for current SDK. */
#define CFG_32K_COUNTER_CALIBRATION	 	(FACTORY_CFG_BASE_ADD + 0x80)

/* Not supported for current SDK. */
#define CFG_ADC_CALIBRATION           	(FACTORY_CFG_BASE_ADD + 0xC0)

/* Not supported for current SDK. */
#define CFG_24M_CRYSTAL_CALIBRATION     (FACTORY_CFG_BASE_ADD + 0x100)

/* Not supported for current SDK. */
#define CFG_T_SENSOR_CALIBRATION     	(FACTORY_CFG_BASE_ADD + 0x140)

/* UID-based Firmware Encryption data(16 bytes), 0x77180(or 0xFE180) ~ 0x7718F(or 0xFE18F). */
#define CFG_FIRMWARE_ENCRYPTION			(FACTORY_CFG_BASE_ADD + 0x180)

/* 2 bytes for VDD_F calibration.
 * 0x771C0(or 0xFF1C0) for DCDC trim,
 * 0x771C1(or 0xFF1C1) for LDO trim.
 */
#define CFG_VDD_F_CALIBRATION			(FACTORY_CFG_BASE_ADD + 0x1C0)


/**************************************************************************************
 * The following is the detailed user configure information (U_CFG_Info).
 */
/* 16 bytes for pre-install code. */
#if FLASH_CAP_SIZE_1M
#define CFG_PRE_INSTALL_CODE			(0xFD000)
#else
#define CFG_PRE_INSTALL_CODE			(0x78000)
#endif

/* 1 byte for factory reset.
 * If not 0xFF, means the device is doing factory reset(erase NV).
 * The device will check this byte when powered on, if it is not 0xFF,
 * it will erase NV first.
 */
#if FLASH_CAP_SIZE_1M
#define CFG_FACTORY_RST_CNT			  	(0xFC000)
#else
#define CFG_FACTORY_RST_CNT			  	(0x79000)
#endif

/**************************************************************************************
 * Flash address of NV module.
 */
#if !defined(BOOT_LOADER_MODE) || (BOOT_LOADER_MODE == 0)
#if FLASH_CAP_SIZE_1M
	#define NV_BASE_ADDRESS				(0x80000)
#else
	#define	NV_BASE_ADDRESS				(0x34000)
	#define	NV_BASE_ADDRESS2			(0x7A000)
#endif
#else
#if FLASH_CAP_SIZE_1M
	#define NV_BASE_ADDRESS				(0xE6000)
#else
	#define	NV_BASE_ADDRESS				(0x6A000)
	#define	NV_BASE_ADDRESS2			(0x7A000)
#endif
#endif


/************************************************************************
 * Flash address of APP firmware.
 */
#define FLASH_ADDR_OF_APP_FW			APP_IMAGE_ADDR


/************************************************************************
 * Flash address of OTA image.
 */
#if !defined(BOOT_LOADER_MODE) || (BOOT_LOADER_MODE == 0)
#if FLASH_CAP_SIZE_1M
	//max size = (0x80000 - 0) / 2 = 256k
	#define FLASH_OTA_IMAGE_MAX_SIZE	((NV_BASE_ADDRESS - FLASH_ADDR_OF_APP_FW) / 2)
#else
	//max size = (0x34000 - 0) = 208k
	#define FLASH_OTA_IMAGE_MAX_SIZE	(NV_BASE_ADDRESS - FLASH_ADDR_OF_APP_FW)
#endif
	//unchangeable address
	#define FLASH_ADDR_OF_OTA_IMAGE		(0x40000)
#else
	//1M   Flash: max size = (0xE6000 - 0x8000) / 2 = 444k
	//512k Flash: max size = (0x6A000 - 0x8000) / 2 = 196k
	#define FLASH_OTA_IMAGE_MAX_SIZE	((NV_BASE_ADDRESS - FLASH_ADDR_OF_APP_FW) / 2)
	//1M   Flash: ota addr = 0x8000 + 444k = 0x77000
	//512k Flash: ota addr = 0x8000 + 196k = 0x39000
	#define FLASH_ADDR_OF_OTA_IMAGE		(FLASH_ADDR_OF_APP_FW + FLASH_OTA_IMAGE_MAX_SIZE)
#endif

/******************************************* DUAL_MODE ********************************************************/
/* Don't care, will be delete. */
#if DUAL_MODE
//NOTE: firmware must less then 192K if UDAL_MODE used
typedef enum{
	TYPE_TLK_MESH  						= 0x000000A3,// don't change, must same with telink mesh SDK
	TYPE_SIG_MESH  						= 0x0000003A,// don't change, must same with telink mesh SDK
	TYPE_TLK_BLE_SDK 					= 0x000000C3,// don't change, must same with telink mesh SDK
	TYPE_TLK_ZIGBEE  					= 0x0000003C,// don't change, must same with telink mesh SDK
	TYPE_DUAL_MODE_STANDBY				= 0x00000065,// dual mode state was standby to be selected
	TYPE_DUAL_MODE_RECOVER 				= 0x00000056,// don't change, must same with telink mesh SDK, recover for mesh
}telink_sdk_type_t;

#define CFG_TELINK_SDK_TYPE				(0x73000)
#define CFG_TELINK_SIG_MESH_CRC			(0x73040)
#define CFG_TELINK_SIG_MESH_CODE_4K		(0x75000)
#define CFG_TELINK_DUAL_MODE_ENABLE		(0x76080)
#endif	/* DUAL_MODE */
/******************************************** END ***********************************************************/






/* sector info(4Bytes) + index info(8Bytes) + index info(8Bytes) + ... */
typedef struct{
	u16 usedFlag;
	u8  idName;
	u8  opSect;
}nv_sect_info_t;

typedef struct{
	u32 offset;
	u16 size;
	u8  itemId;
	u8  usedState;
}nv_info_idx_t;

/* item:  item_hdr(8Bytes) + payload*/
typedef struct{
	u32 checkSum;
	u16 size;
	u8  itemId;
	u8  used;
}itemHdr_t;

typedef struct{
	u16 opIndex;
	u8 	opSect;
}itemIfno_t;

//If OTA enabled, the maximum space used for nv module t is 56K, thus the item num cannot over 14
/*****************************************************************************************************************************
 * Store zigbee information in flash.
 * 		Module ID				|			512K Flash				|			1M Flash				|
 * -----------------------------|-----------------------------------|-----------------------------------|
 * NV_MODULE_ZB_INFO			|		0x34000 - 0x36000			|		0x80000 - 0x82000			|
 * NV_MODULE_ADDRESS_TABLE		|		0x36000 - 0x38000			|		0x82000 - 0x84000			|
 * NV_MODULE_APS				|		0x38000 - 0x3a000			|		0x84000 - 0x86000			|
 * NV_MODULE_ZCL				|		0x3a000 - 0x3c000			|		0x86000 - 0x88000			|
 * NV_MODULE_NWK_FRAME_COUNT	|		0x3c000 - 0x3e000			|		0x88000 - 0x8a000			|
 * NV_MODULE_OTA				|		0x3e000 - 0x40000			|		0x8a000 - 0x8c000			|
 * NV_MODULE_APP				|		0x7a000 - 0x7c000			|		0x8c000 - 0x8e000			|
 * NV_MODULE_KEYPAIR			|		0x7c000 - 0x80000			|		0x8e000 - 0x96000			|
 * 								|	*16K - can store 127 nodes		|	*32K - can store 302 nodes		|
 * NV_MAX_MODULS
 */
typedef enum{
	NV_MODULE_ZB_INFO 				= 0,
	NV_MODULE_ADDRESS_TABLE 		= 1,
    NV_MODULE_APS 					= 2,
    NV_MODULE_ZCL 					= 3,
	NV_MODULE_NWK_FRAME_COUNT 		= 4,
	NV_MODULE_OTA 					= 5,
	NV_MODULE_APP 					= 6,
	NV_MODULE_KEYPAIR 				= 7,
    NV_MAX_MODULS
}nv_module_t;

typedef enum{
	NV_ITEM_ID_INVALID				= 0,/* Item id 0 should not be used. */

	NV_ITEM_ZB_INFO 				= 1,
	NV_ITEM_ADDRESS_FOR_NEIGHBOR,
	NV_ITEM_ADDRESS_FOR_BIND,
	NV_ITEM_APS_SSIB,
	NV_ITEM_APS_GROUP_TABLE,
	NV_ITEM_APS_BINDING_TABLE,

	NV_ITEM_NWK_FRAME_COUNT,

	NV_ITEM_SS_KEY_PAIR,

	NV_ITEM_OTA_HDR_SERVERINFO,
	NV_ITEM_OTA_CODE,

	NV_ITEM_ZCL_REPORT 				= 0x20,
	NV_ITEM_ZCL_ON_OFF,
	NV_ITEM_ZCL_LEVEL,
	NV_ITEM_ZCL_COLOR_CTRL,
	NV_ITEM_ZCL_SCENE_TABLE,
	NV_ITEM_ZCL_GP_PROXY_TABLE,
	NV_ITEM_ZCL_GP_SINK_TABLE,
	NV_ITEM_ZCL_WWAH_APS_AUTH_INFO,
	NV_ITEM_ZCL_WWAH_APS_ACKS_INFO,
	NV_ITEM_ZCL_WWAH_USE_TC_CLUSTER_INFO,

	NV_ITEM_APP_SIMPLE_DESC,
	NV_ITEM_APP_POWER_CNT,

	NV_ITEM_ID_MAX					= 0xFF,/* Item id 0xFF should not be used. */
}nv_item_t;

typedef enum{
	NV_SUCC,
    NV_INVALID_MODULS 				= 1,
    NV_INVALID_ID ,
    NV_ITEM_NOT_FOUND,
    NV_NOT_ENOUGH_SAPCE,
    NV_ITEM_LEN_NOT_MATCH,
    NV_CHECK_SUM_ERROR,
    NV_ENABLE_PROTECT_ERROR,
    NV_NO_MEDIA
} nv_sts_t;


#define FLASH_PAGE_SIZE							256
#define	FLASH_SECTOR_SIZE						4096//4K

#define NV_SECTOR_VALID							0x5A5A
#define NV_SECTOR_INVALID						0x5050
#define NV_SECTOR_IDLE							0xFFFF

#define ITEM_FIELD_VALID						0x5A
#define ITEM_FIELD_INVALID						0x50
#define ITEM_FIELD_OPERATION					0xFA
#define ITEM_FIELD_IDLE							0xFF


#if FLASH_CAP_SIZE_1M
#define MODULES_START_ADDR(id)					(NV_BASE_ADDRESS + FLASH_SECTOR_SIZE * (2 * id))
#define NV_SECTOR_SIZE(id)						((id == NV_MODULE_KEYPAIR) ? (4 * FLASH_SECTOR_SIZE) : FLASH_SECTOR_SIZE)
#define MODULE_INFO_SIZE(id)					((id == NV_MODULE_OTA || id == NV_MODULE_KEYPAIR || id == NV_MODULE_ADDRESS_TABLE) ? ((id == NV_MODULE_KEYPAIR) ? (12*FLASH_PAGE_SIZE) : (4*FLASH_PAGE_SIZE)) : (2*FLASH_PAGE_SIZE))
#else
#define MODULES_START_ADDR(id)					((id < 6) ? (NV_BASE_ADDRESS + FLASH_SECTOR_SIZE * (2 * id)) : (NV_BASE_ADDRESS2 + FLASH_SECTOR_SIZE * (2 * (id-6))))
#define NV_SECTOR_SIZE(id)						((id == NV_MODULE_KEYPAIR) ?  (2 * FLASH_SECTOR_SIZE) : FLASH_SECTOR_SIZE)
#define MODULE_INFO_SIZE(id)					((id == NV_MODULE_OTA || id == NV_MODULE_KEYPAIR || id == NV_MODULE_ADDRESS_TABLE) ? (4*FLASH_PAGE_SIZE) : (2*FLASH_PAGE_SIZE))
#endif

#define MODULE_SECTOR_NUM						(2)

#define MODULE_IDX_SIZE(id)						(MODULE_INFO_SIZE(id) - sizeof(nv_sect_info_t))
#define MODULE_SECT_START(id, sectNo)   		(MODULES_START_ADDR(id) + sectNo * (NV_SECTOR_SIZE(id)))
#define MODULE_SECT_END(id, sectNo)     		(MODULES_START_ADDR(id) + (sectNo + 1) * (NV_SECTOR_SIZE(id)))
#define MODULE_IDX_START(id, sectNo)    		(MODULE_SECT_START(id, sectNo) + sizeof(nv_sect_info_t))
#define MODULE_IDX_NUM(id)    					(MODULE_IDX_SIZE(id) / (sizeof(nv_info_idx_t)))
#define MODULE_CONTEXT_START(id, sectNo, len)  	(MODULE_SECT_START(id, sectNo) + MODULE_INFO_SIZE(id))
#define ITEM_TOTAL_LEN(len)						(len + sizeof(itemHdr_t))
#define FRAMECOUNT_PAYLOAD_START(opSect)		(((MODULE_SECT_START(NV_MODULE_NWK_FRAME_COUNT, opSect) + sizeof(nv_sect_info_t)) + 0x03) & (~0x03))
#define FRAMECOUNT_NUM_PER_SECT()				((((FLASH_SECTOR_SIZE - sizeof(nv_sect_info_t)) & (~0x03))) / 4)




nv_sts_t nv_resetAll(void);
nv_sts_t nv_resetModule(u8 modules);
nv_sts_t nv_flashWriteNew(u8 single, u16 id, u8 itemId, u16 len, u8 *buf);
nv_sts_t nv_flashReadNew(u8 single, u8 id, u8 itemId, u16 len, u8 *buf);
nv_sts_t nv_itemDeleteByIndex(u8 id, u8 itemId, u8 opSect, u16 opIdx);
nv_sts_t nv_flashReadByIndex(u8 id, u8 itemId, u8 opSect, u16 opIdx, u16 len, u8 *buf);
nv_sts_t nv_resetToFactoryNew(void);
bool nv_facrotyNewRstFlagCheck(void);
void nv_facrotyNewRstFlagSet(void);
void nv_facrotyNewRstFlagClear(void);
nv_sts_t nv_nwkFrameCountSaveToFlash(u32 frameCount);
nv_sts_t nv_nwkFrameCountFromFlash(u32 *frameCount);

