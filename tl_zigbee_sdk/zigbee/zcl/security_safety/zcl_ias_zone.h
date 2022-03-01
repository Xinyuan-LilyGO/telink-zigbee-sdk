/********************************************************************************************************
 * @file	zcl_ias_zone.h
 *
 * @brief	This is the header file for zcl_ias_zone
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
#ifndef ZCL_IAS_ZONE_H
#define ZCL_IAS_ZONE_H


/*********************************************************************
 * CONSTANTS
 */
/**
 *  @brief  Size of ZCL zone table
 */
#ifndef ZCL_ZONE_TABLE_NUM
#define ZCL_ZONE_TABLE_NUM										5
#endif


/* Command ID */
// Client generated command
#define ZCL_CMD_ZONE_ENROLL_RSP                                	0x00
#define ZCL_CMD_INIT_NORMAL_OPERATION_MODE						0x01
#define ZCL_CMD_INIT_TEST_MODE									0x02

// Server generated command
#define ZCL_CMD_ZONE_STATUS_CHANGE_NOTIFICATION                 0x00
#define ZCL_CMD_ZONE_ENROLL_REQ                                	0x01


/* Attribute ID */
#define ZCL_ATTRID_ZONE_STATE                             		0x0000
#define ZCL_ATTRID_ZONE_TYPE                              		0x0001
#define ZCL_ATTRID_ZONE_STATUS                            		0x0002
#define ZCL_ATTRID_IAS_CIE_ADDR                           		0x0010
#define ZCL_ATTRID_ZONE_ID								  		0x0011


/* Zone States Definition */
#define ZONE_STATE_NOT_ENROLLED                           		0x00
#define ZONE_STATE_ENROLLED                               		0x01


/* Zone Types Definition */
#define ZONE_TYPE_STANDARD_CIE                            		0x0000
#define ZONE_TYPE_MOTION_SENSOR                           		0x000D
#define ZONE_TYPE_CONTACT_SWITCH                          		0x0015
#define ZONE_TYPE_DOOR_WINDOW_HANDLE							0x0016
#define ZONE_TYPE_FIRE_SENSOR                             		0x0028
#define ZONE_TYPE_WATER_SENSOR                            		0x002A
#define ZONE_TYPE_CARBON_MONOXIDE_SENSOR                        0x002B
#define ZONE_TYPE_PERSONAL_EMERGENCY_DEV                  		0x002C
#define ZONE_TYPE_VIBRATION_MOVEMENT_SENSOR                     0x002D
#define ZONE_TYPE_REMOTE_CONTROL                          		0x010F
#define ZONE_TYPE_KEY_FOB                                 		0x0115
#define ZONE_TYPE_KEY_PAD                                 		0x021D
#define ZONE_TYPE_STANDARD_WARNING_DEV                    		0x0225
#define ZONE_TYPE_GLASS_BREAK_SENSOR							0x0226
#define ZONE_TYPE_SECURITY_REPEATER								0x0229
#define ZONE_TYPE_INVALID_ZONE_TYPE                            	0xFFFF


/* Zone Status Bitmap */
#define ZONE_STATUS_BIT_ALARM1                            		0x0001
#define ZONE_STATUS_BIT_ALARM2                            		0x0002
#define ZONE_STATUS_BIT_TAMPER                            		0x0004
#define ZONE_STATUS_BIT_BATTERY                           		0x0008
#define ZONE_STATUS_BIT_SUPERVISION_NOTIFY               		0x0010
#define ZONE_STATUS_BIT_RESTORE_NOTIFY                   		0x0020
#define ZONE_STATUS_BIT_TROUBLE                           		0x0040
#define ZONE_STATUS_BIT_AC_MAINS                          		0x0080
#define ZONE_STATUS_TEST										0x0100
#define ZONE_STATUS_BATTERY_DEFECT								0x0200


/* Enroll Response Code */
#define ZONE_ENROLL_SUCC                                  		0x00
#define ZONE_ENROLL_NOT_SUPPORTED                         		0x01
#define ZONE_ENROLL_NOT_ENROLL_PERMIT                     		0x02
#define ZONE_ENROLL_TOO_MANY_ZONES                         		0x03


/**
 *  @brief  NO. of ZCL zone id (0 ~ 0xFE)
 */
#define ZCL_ZONE_MAX_ZONE_ID									0xFE
#define ZCL_ZONE_ID_INVALID										0xFF

/*********************************************************************
 * ENUMS
 */



/*********************************************************************
 * TYPES
 */
/**
 *  @brief  Structure definition for zone enroll response command
 */
typedef struct {
    u8 code;
    u8 zoneId;
} zoneEnrollRsp_t;

/**
 *  @brief  Structure definition for initiate test mode command
 */
typedef struct {
    u8 testModeDuration;
    u8 currZoneSensLevel;
} zoneInitTestMode_t;

/**
 *  @brief  Structure definition for zone status change notification command
 */
typedef struct {
    u16 zoneStatus;
    u8 	extStatus;
    u8	zoneId;
    u16 delay;
} zoneStatusChangeNoti_t;

/**
 *  @brief  Structure definition for zone enroll request command
 */
typedef struct {
    u16 zoneType;
    u16 manufacturerCode;
} zoneEnrollReq_t;


/**
 *  @brief  Definition for ZCL zone table entry
 */
typedef struct {
	u8   zoneId;
    u16  zoneType;
    addrExt_t zoneAddr;
} zcl_zoneTabEntry_t;

/**
 *  @brief  Definition for ZCL zone table information
 */
typedef struct {
	u8  used;
    u8  endpoint;
    zcl_zoneTabEntry_t zone;
} zcl_zoneTable_t;

extern zcl_zoneTable_t g_zcl_zoneTab[];

#if 0
/* Command Callback Function Type */
typedef void (*zcl_enrollRspCb_t)(apsdeDataInd_t *pApsdeInd, zoneEnrollRsp_t *pZoneEnrollRsp);
typedef status_t (*zcl_initNormalOperationModeCb_t)(apsdeDataInd_t *pApsdeInd);
typedef status_t (*zcl_initTestModeCb_t)(apsdeDataInd_t *pApsdeInd, zoneInitTestMode_t *pZoneInitTestMode);
typedef void (*zcl_statusChangeNotificationCb_t)(apsdeDataInd_t *pApsdeInd, zoneStatusChangeNoti_t *pStatusChangeNoti);
typedef void (*zcl_enrollReqCb_t)(apsdeDataInd_t *pApsdeInd, zoneEnrollReq_t *pZoneEnrollReq);

/**
 *  @brief  Structure definition for commands callback functions in ias zone cluster
 */
typedef struct {
	zcl_enrollRspCb_t    				enrollRspCbFunc;
	zcl_initNormalOperationModeCb_t		initNormalOperationModeCbFunc;
	zcl_initTestModeCb_t				initTestModeCbFunc;
	zcl_statusChangeNotificationCb_t 	statusChangeNotificationCbFunc;
	zcl_enrollReqCb_t    				enrollReqCbFunc;
} zcl_iasZone_AppCallbacks_t;


/*********************************************************************
 *	External variables for zone attributes
 */
extern u8  zcl_attr_zoneState;
extern u16 zcl_attr_zoneType;
extern u16 zcl_attr_zoneStatus;
extern u8  zcl_attr_iasCieAddr[8];
extern u8  zcl_attr_zoneID;

/**
 *  @brief  External variable for IAS ZONE Attribute info table
 */
extern const zclAttrInfo_t iasZone_attrTbl[];

extern const u8 zcl_iasZone_attrNum;
#endif


status_t zcl_iasZone_register(u8 endpoint, u16 manuCode, u8 attrNum, const zclAttrInfo_t attrTbl[], cluster_forAppCb_t cb);


status_t zcl_iasZone_enrollReq(u8 srcEp, epInfo_t *pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, zoneEnrollReq_t *pEnrollReq);
#define zcl_iasZone_enrollReqCmd(a,b,c,d)	(zcl_iasZone_enrollReq((a), (b), (c), ZCL_SEQ_NUM, (d)))

status_t zcl_iasZone_initNormalOperationMode(u8 srcEp, epInfo_t *pDstEpInfo, u8 disableDefaultRsp, u8 seqNo);
#define zcl_iasZone_initNormalOperationModeCmd(a,b,c)	(zcl_iasZone_initNormalOperationMode((a), (b), (c), ZCL_SEQ_NUM))

status_t zcl_iasZone_initTestMode(u8 srcEp, epInfo_t *pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, zoneInitTestMode_t *pInitTestMode);
#define zcl_iasZone_initTestModeCmd(a,b,c,d)	(zcl_iasZone_initTestMode((a), (b), (c), ZCL_SEQ_NUM, (d)))

status_t zcl_iasZone_statusChangeNotification(u8 srcEp, epInfo_t *pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, zoneStatusChangeNoti_t *pStatusChangeNoti);
#define zcl_iasZone_statusChangeNotificationCmd(a,b,c,d)	(zcl_iasZone_statusChangeNotification((a), (b), (c), ZCL_SEQ_NUM, (d)))


extern zcl_zoneTable_t *zcl_findZoneEntry(u8 endpoint, u8 zoneId);

#endif	/* ZCL_IAS_ZONE_H */
