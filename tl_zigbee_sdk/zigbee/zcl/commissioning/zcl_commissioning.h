/********************************************************************************************************
 * @file	zcl_commissioning.h
 *
 * @brief	This is the header file for zcl_commissioning
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
#ifndef ZCL_COMMISSIONING_H
#define ZCL_COMMISSIONING_H



/** @addtogroup  TELINK_ZIGBEE_STACK TELINK ZigBee Stack
 *  @{
 */

/** @addtogroup  ZCL_Module ZCL
 *  @{
 */

/** @addtogroup  ZCL_CLUSTER_COMMISSIONING COMMISSIONING Cluster
 *  @{
 */

/** @addtogroup  ZCL_COMMISSIONING_Constant COMMISSIONING Cluster Constants
 *  @{
 */

/** @addtogroup zcl_commissioning_cmdId COMMISSIONING Command Ids
 * @{
 */

// Client generated command
#define ZCL_CMD_RESTART_DEVICE                            0x00
#define ZCL_CMD_SAVE_STARTUP_PARAMETERS                   0x01
#define ZCL_CMD_RESTORE_STARTUP_PARAMETERS                0x02
#define ZCL_CMD_RESET_STARTUP_PARAMETERS                  0x03

// Server generated command
#define ZCL_CMD_RESTART_DEVICE_RSP                        0x00
#define ZCL_CMD_SAVE_STARTUP_PARAMETERS_RSP               0x01
#define ZCL_CMD_RESTORE_STARTUP_PARAMETERS_RSP            0x02
#define ZCL_CMD_RESET_STARTUP_PARAMETERS_RSP              0x03

/** @} end of group zcl_commissioning_cmdId */


/** @addtogroup zcl_commissioning_attrId COMMISSIONING Attribute Ids
 * @{
 */

/* Startup parameters */
/* Network attribute set */
#define ZCL_ATTR_SHORT_ADDRESS                          0x0000
#define ZCL_ATTR_EXTENDED_PAN_ID						0x0001
#define ZCL_ATTR_PAN_ID								  	0x0002
#define ZCL_ATTR_CHANNEL_MASK							0x0003
#define ZCL_ATTR_PROTOCOL_VERSION						0x0004
#define ZCL_ATTR_STACK_PROFILE						  	0x0005
#define ZCL_ATTR_STARTUP_CONTROL						0x0006
/* Security attribute set */
#define ZCL_ATTR_TRUST_CENTER_ADDRESS					0x0010
#define ZCL_ATTR_TRUST_CENTER_MASTER_KEY				0x0011
#define ZCL_ATTR_NETWORK_KEY							0x0012
#define ZCL_ATTR_USE_INSECURE_JOIN					  	0x0013
#define ZCL_ATTR_PRECONFIGURED_LINK_KEY				  	0x0014
#define ZCL_ATTR_NETWORK_KEY_SEQUENCE_NO				0x0015
#define ZCL_ATTR_NETWORK_KEY_TYPE						0x0016
#define ZCL_ATTR_NETWORK_MANAGER_ADDRESS				0x0017
/* Join parameters */
#define ZCL_ATTR_SCAN_ATTEMPTS						  	0x0020
#define ZCL_ATTR_TIME_BETWEEN_SCANS					  	0x0021
#define ZCL_ATTR_REJOIN_INTERVAL						0x0022
#define ZCL_ATTR_MAX_REJOIN_INTERVAL					0x0023
/* End device Parameters */
#define ZCL_ATTR_INDIRECT_POLL_RATE					  	0x0030
#define ZCL_ATTR_PARENT_RETRY_THRESHOLD				  	0x0031
/* Concentrator parameters */
#define ZCL_ATTR_CONCENTRATOR_FLAG					  	0x0040
#define ZCL_ATTR_CONCENTRATOR_RADIUS					0x0041
#define ZCL_ATTR_CONCENTRATOR_DISCOVERY_TIME			0x0042

/** @} end of group zcl_commissioning_attrId */

/** @} end of group ZCL_COMMISSIONING_Constant */



#if 0
/** @addtogroup  ZCL_COMMISSIONING_Callbacks COMMISSIONING Cluster Callbacks
 *  @{
 */

/**
 *  @brief  Definition for commissioning command callback format
 */
typedef void (*zcl_restartDeviceCb_t)( u8 options, u8 delay, u8 jitter );
typedef void (*zcl_saveStartupParamsCb_t)( u8 options, u8 index );
typedef void (*zcl_restoreStartupParamsCb_t)( u8 options, u8 index );
typedef void (*zcl_resetStartupParamsCb_t)( u8 options, u8 index );

/**
 *  @brief  Structure definition for commands callback functions in commissioning cluster
 */
typedef struct {
	zcl_restartDeviceCb_t    restartDeviceCbFunc;
	zcl_saveStartupParamsCb_t    saveStartupParamsCbFunc;
	zcl_restoreStartupParamsCb_t    restoreStartupParamsCbFunc;
	zcl_resetStartupParamsCb_t    ressetStartupParamsCbFunc;
} zcl_commissioning_AppCallbacks_t;

/** @} end of group ZCL_COMMISSIONING_Callbacks */


/** @addtogroup  ZCL_COMMISSIONING_Variables COMMISSIONING Cluster Variables
 *  @{
 */

/**
 *  @brief  External variable for commissioning Attributes
 */

/* Startup attributes set*/
	/* General startup attributes */
extern u16 zcl_attr_short_address;
extern extPANId_t zcl_attr_extended_PAN_id;
extern u16 zcl_attr_PAN_id;
extern u32 zcl_attr_channel_mask;
extern u8 zcl_attr_protocol_version;
extern u8 zcl_attr_stack_profile;
extern u8 zcl_attr_startup_control;

	/* Security attributes */
extern addrExt_t zcl_attr_trust_center_address;
extern u8 zcl_attr_trust_center_master_key[16];
extern u8 zcl_attr_network_key[16];
extern u8 zcl_attr_use_insecure_join;
extern u8 zcl_attr_preconfigured_link_key[16];
extern u8 zcl_attr_network_key_sequence_number;
extern u8 zcl_attr_network_key_type;
extern u16 zcl_attr_network_manager_address;

extern u8 zcl_attr_scan_attempts;
extern u16 zcl_attr_time_between_scans;
extern u16 zcl_attr_rejoin_interval;
extern u16 zcl_attr_max_rejoin_interval;

extern u16 indirect_poll_rate;
extern u8 zcl_attr_parent_retry_threshold;

extern u8 zcl_attr_concentrator_flag;
extern u8 zcl_attr_concentrator_radius;
extern u8 zcl_attr_concentrator_discovery_time;
/**
 *  @brief  External variable for commissioning Attribute Table
 */
extern const zclAttrInfo_t commissioning_attrTbl[];

extern const u8 zcl_commissioning_attrNum;
#endif


/**
  Macros for commissioning parse-compose
 */
#define ZCL_RESTART_OPTIONS_GET_STARTUP_MODE(options) 	(options & 7)
#define ZCL_RESTART_OPTIONS_GET_IMMEDIATE(options) 		(options & (1 << 3))

typedef struct {
	u8 options;
	u8 delay;
	u8 jitter;
} zcl_restartDevice_t;


/** @} end of group ZCL_COMMISSIONING_Variables */

/** @addtogroup  ZCL_COMMISSIONING_Fountions COMMISSIONING Cluster APIs
 *  @{
 */

/**
 * @brief       This function register COMMISSIONING cluster server to ZCL. Only after registered,
 *              commissioning attributes could be used.
 *
 * @param[in]   attrNum  - used attribute number
 * @param[in]   pAttrTbl - pointer to server side attribute table. It is implented in zcl_commissioning_attr.c
 * @param[in]   cb       - pointer to the App layer command callbacks
 *
 * @return      Status
 */
status_t zcl_commissioning_register(u8 endpoint, u8 attrNum, const zclAttrInfo_t attrTbl[], cluster_forAppCb_t cb);

void zcl_initialize_startup_attributes();


#endif	/* ZCL_COMMISSIONING_H */
