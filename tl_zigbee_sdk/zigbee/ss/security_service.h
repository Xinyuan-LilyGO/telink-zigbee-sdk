/********************************************************************************************************
 * @file	security_service.h
 *
 * @brief	This is the header file for security_service
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
#ifndef SECURITY_SERVICE_H
#define SECURITY_SERVICE_H


#if SECURITY_ENABLE
	#define	SECURITY_MODE_STANDARD 			1
	#define	SECURITY_MODE_HIGH				(!SECURITY_MODE_STANDARD)
	#define	SS_UPDATE_FRAMECOUNT_THRES		1024
#endif

typedef enum{
	SS_KEYREQ_TYPE_APPLK = 0x02,
	SS_KEYREQ_TYPE_TCLK  = 0x04
}ss_keyReqType_e;

enum{
	SS_SECUR_NO_ENCR,
	SS_SECUR_NWK_ENCR,
	SS_SECUR_APS_ENCR,
	SS_SECUR_MAC_ENCR
};

/*
 * Key id - see 4.5.1.1.2
 */
enum{
	SS_SECUR_DATA_KEY,
	SS_SECUR_NWK_KEY,
	SS_SECUR_KEY_TRANSPORT_KEY,
	SS_SECUR_KEY_LOAD_KEY
};

//Key types
typedef enum{
	SS_TC_MASTER_KEY			= 0x00,	//removed from zb 3.0
	SS_STANDARD_NETWORK_KEY 	= 0x01,
	SS_APP_MASTER_KEY			= 0x02,	//removed from zb 3.0
	SS_APP_LINK_KEY				= 0x03,
	SS_TC_LINK_KEY 				= 0x04,
	SS_HIGH_SECUR_NETWORK_KEY,			//removed from zb 3.0
}ss_seKeyType_e;

typedef enum{
	SS_UNIQUE_LINK_KEY 			= 0x00,
	SS_GLOBAL_LINK_KEY 			= 0x01
}ss_linkKeytype_e;

typedef enum{
	SS_SEMODE_CENTRALIZED,
	SS_SEMODE_DISTRIBUTED
}ss_securityMode_e;

typedef enum{
	SS_PROVISIONAL_KEY,
	SS_UNVERIFIED_KEY,
	SS_VERIFIED_KEY
}ss_keyAttributes_e;

typedef struct{
	u8	key[CCM_KEY_SIZE];
	u8	keySeqNum;
	u8	keyType;
}ss_material_set_t;

typedef enum{
	SS_PRECONFIGURED_NOKEY			= 0,
	SS_PRECONFIGURED_GLOBALLINKKEY	= BIT(0),
	SS_PRECONFIGURED_UNIQUELLINKKEY = BIT(1),
	SS_PRECONFIGURED_NWKKEY			= BIT(2),
}ss_preconfiguredKey_e;

typedef struct{
	//This value set to TRUE will only allow devices know to TC join or rejoin
	bool	useWhiteList;
	// 0 ~ not support; 1 ~ support but not require; 2 ~ require the use of install code by JD, the useWhiteList would set to TRUE
	//interface need to be supported to input install code to TC
	u8		allowInstallCode;
	//Indicates whether or not devices are required to attempt to update their TCLK after joining. In centralized security network,
	//this value must be set to TRUE, the joining device must attempt TCLK update after joining the network.
	bool	updateTCLKrequired;
#if ZB_COORDINATOR_ROLE
	//This values indicates whether or not TC allow new device join to the network, set to false in centralized security NWK will
	//reject any join request
	bool	allowJoins;
	//If TC allows rejoin using well known or default keys, a setting of FALSE means rejoins are only allowed with TCLK where the
	//KeyAttributes of the apsDeviceKeyPairSet entry indicates VERIFIED_KEY. This value set to FALSE in centralized security NWK.
	bool	allowRejoins;
	//0 ~ never; 1 ~ any device may request; 2 ~ only devices in the apsDeviceKeyPaireSet.
	//Set to 0 in network with higher level protocols for establishing link keys. Set to 1/2 in centralized security networks
	u8		allowTCLKrequest;

	u8		allowAppLKrequest;
#endif
}ss_tcPolicy_t;

typedef enum{
	KEYTYPE_PRO_MASK 	  = BIT(0),
	KEYTYPE_UNVERIFY_MASK = BIT(1),
	KEYTYPE_VERIFIED_MASK = BIT(2)
}nvKeytpeMask_e;

typedef enum{
	SS_DEVKEYPAIR_SYNID_KEYATTR,
	SS_DEVKEYPAIR_SYNID_INCOMMINGFRAMECNT,
	SS_DEVKEYPAIR_SYNID_ALL
}ss_devKeyPairSyn_id;

typedef struct{
	addrExt_t			device_address;

	u8					linkKey[CCM_KEY_SIZE];		/* The actual value of the link key. */

	ss_keyAttributes_e 	keyAttr;
	ss_linkKeytype_e 	apsLinkKeyType;
	u8					used;
	u8					rsv;//used as mapping index to stack item

	u32					outgoingFrameCounter;
	u32					incomingFrameCounter;
}ss_dev_pair_set_t;

typedef struct{
	u32						ssTimeoutPeriod;
	u32						outgoingFrameCounter;
	u32						prevOutgoingFrameCounter;
	ss_dev_pair_set_t		*keyPairSetNew;								//16
	ss_material_set_t		nwkSecurMaterialSet[SECUR_N_SECUR_MATERIAL];//36
	u16						devKeyPairNum;
	addrExt_t				trust_center_address;						//10
	u8						securityLevel:3;
	u8						secureAllFresh:1;
	u8						activeSecureMaterialIndex:2;
	u8						reserved:2;
	u8						activeKeySeqNum;
	ss_preconfiguredKey_e	preConfiguredKeyType;//pre-configured type, should be set during init state which used for ZDO auth
	ss_tcPolicy_t			tcPolicy;									//10
	u8						*touchLinkKey;
	u8						*distibuteLinkKey;
	u8						tcLinkKeyType;
	u8						*tcLinkKey;									//13
}ss_info_base_t;


//Parameters for APSME-TRANSPORT-KEY.request primitive
typedef struct{
	/* The dstAddr is all zeros, means broadcast, for SS_STANDARD_NETWORK_KEY.
	 */
	addrExt_t	dstAddr;
	u8			keyType;
	u8			key[CCM_KEY_SIZE];
	u8			relayByParent;
	u8			keySeqNum;
	addrExt_t	partnerAddr;  //for application key
	u8			initatorFlag;
	u8 			nwkSecurity;
}ss_apsmeTransportKeyReq_t;

//Parameters for APSME-TRANSPORT-KEY.indication primitive
typedef struct{
	addrExt_t		srcAddr;
	u8				keyType;
	u8				key[CCM_KEY_SIZE];
	union{
		u8			keySeqNum;
		addrExt_t	partnerAddr;
	};
}ss_apsmeTransportKeyInd_t;

//Parameters for APSME-UPDATE-DEVICE.request primitive
typedef struct{
	//The extended 64-bit address of the device
	//that shall be sent the update information.
	addrExt_t 	dstAddr;
	/*The extended 64-bit address of the device
	whose status is being updated.*/
	addrExt_t 	devAddr;
	u16    		devShortAddr;
	u8     		status;
}ss_apsmeUpdateDeviceReq_t;

typedef enum{
	SS_STANDARD_DEV_SECURED_REJOIN 	= 0,
	SS_STANDARD_DEV_UNSECURED_JOIN 	= 1,
	SS_DEV_LEFT 					= 2,
	SS_STANDARD_DEV_TC_REJOIN 		= 3
}ss_apsmeUpdateDevStatus_e;

//Parameters for APSME-UPDATE-DEVICE.indication primitive
typedef struct{
	/*The extended 64-bit address of the
	device originating the update-device
	command.*/
	addrExt_t 						srcAddr;
	/*The extended 64-bit address of the device
	whose status is being updated.*/
	addrExt_t 						devAddr;
	u16								devShortAddr;
	ss_apsmeUpdateDevStatus_e		status;
}ss_apsmeUpdateDeviceInd_t;

//Parameters for APSME-REMOVE-DEVICE.request primitive
typedef struct{
	/*The extended 64-bit address of the device
	that is the parent of the child device that is
	requested to be removed, or the router
	device that is requested to be removed.*/
	addrExt_t	parentAddr;
	/*The extended 64-bit address of the target
	device that is requested to be removed. If a
	router device is requested to be removed,
	then the ParentAddress shall be the same
	as the TargetAddress.*/
	addrExt_t	targetExtAddr;
}ss_apsmeRemoveDeviceReq_t;

//Parameters for APSME-REMOVE-DEVICE.indication primitive
typedef struct{
	/*The extended 64-bit address of the device
	 requesting that a child device be removed.*/
	addrExt_t	tcAddr;
	/*The extended 64-bit address of the child
	device that is requested to be removed*/
	addrExt_t	childExtAddr;
}ss_apsmeRemoveDeviceInd_t;

//Parameters for APSME-REQUEST-KEY.request primitive
typedef struct{
	/* The address of the device which the request-key command should be sent. */
	tl_zb_addr_t 	dstAddr;
	/* If the key type is SS_KEYREQ_TYPE_APPLK, this parameter shall indicate an
	 * extend 64-bit address of a device that shall receive the same key as the
	 * device requesting the key.
	 */
	addrExt_t		partnerAddr;
	/* ZB_ADDR_16BIT_DEV_OR_BROADCAST or ZB_ADDR_64BIT_DEV. */
	u8				dstAddrMode;//zb_addr_mode_t
	/* the type of key being requested. */
	ss_keyReqType_e	keyType;
}ss_apsmeRequestKeyReq_t;

//Parameters for APSME-REQUEST-KEY.indication primitive
typedef struct{
	/* The address of the device that sent the request-key command. */
	tl_zb_addr_t 	srcAddr;
	/* If the key type is SS_KEYREQ_TYPE_APPLK, this parameter shall indicate an
	 * extend 64-bit address of a device that shall receive the same key as the
	 * device requesting the key.
	 */
	addrExt_t		partnerAddr;
	/* ZB_ADDR_16BIT_DEV_OR_BROADCAST or ZB_ADDR_64BIT_DEV. */
	u8				dstAddrMode;//zb_addr_mode_t
	/* the type of key being requested. */
	ss_keyReqType_e	keyType;
}ss_apsmeRequestKeyInd_t;

//Parameters for APSME-SWITCH-KEY.request primitive
typedef struct{
	/* The extended 64-bit address of the device to which the switch-key command is sent.
	 * This may be the broadcast address 0xFFFFFFFFFFFFFFFF.
	 */
	addrExt_t	dstAddr;
	/* A sequence number assigned to a network key by the TC
	 * and used to distinguish network keys.
	 */
	u8			keySeqNum;
}ss_apsmeSwitchKeyReq_t;

//Parameters for APSME-SWITCH-KEY.indication primitive
typedef struct{
	addrExt_t	srcAddr;
	u8			keySeqNum;
}ss_apsmeSwitchKeyInd_t;

//Parameters for APSME-VERIFY-KEY.request primitive
typedef struct{
	addrExt_t	dstAddr;
	u8			keyType;
}ss_apsmeVerifyKeyReq_t;

//Parameters for APSME-VERIFY-KEY.indication primitive
typedef struct{
	addrExt_t	srcAddr;
	u8			hashVal[16];
	u8			keyType;
}ss_apsmeVerifyKeyInd_t;

//Parameters for APSME-CONFIRM-KEY.request primitive
typedef struct{
	addrExt_t	dstAddr;
	u8			keyType;
	u8			status;
}ss_apsmeConfirmKeyReq_t;

//Parameters for APSME-CONFIRM-KEY.indication primitive
typedef struct{
	addrExt_t	srcAddr;
	u8			keyType;
	u8			status;
}ss_apsmeConfirmKeyInd_t;

typedef struct{
	addrExt_t	dstAddr;
	u8			key[CCM_KEY_SIZE];
}ss_tcUpdateNwkKey_t;


extern ss_info_base_t ss_ib;

#define SS_IB()	ss_ib


void ss_mmoHash(u8 *data, u8 len, u8 *result);
u8 aes_ccmAuthTran(u8 M, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *result);
u8 aes_ccmEncTran(u8 M, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *result);
u8 aes_ccmDecTran(u8 micLen, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *mic);
u8 aes_ccmDecAuthTran(u8 micLen, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *mic);


u16 ss_devKeyPairInfoGet(void);
u8 ss_devKeyPairFind(addrExt_t extAddr, ss_dev_pair_set_t *keyPair);
u8 ss_devKeyPairDelete(addrExt_t extAddr);
void ss_devKeyPairSave(ss_dev_pair_set_t *keyPair);


u32 ss_outgoingFrameCntGet(void);

/*
 * @brief 	get the MAC address form key pair table so as to get the information of the node which have joined the network
 *
 * @param	start_idx  			the index of the key pair table
 *
 * @param	num		   			the count of the node want to be read out
 *
 * @param   *validNum			the valid count will be read out
 *
 * @param   nodeMacAddrList		the node MAC address list
 *
 * */
u16 ss_nodeMacAddrFromdevKeyPair(u16 start_idx, u8 num, u8 *validNum, addrExt_t *nodeMacAddrList);

/*
 * @brief 	save ssib to flash
 *
 * */
void zdo_ssInfoSaveToFlash(void);

/*
 * @brief 	get ssib from flash
 *
 * */
u8 zdo_ssInfoInit(void);

/*
 * @brief 	update ssib to flash
 *
 * */
void zdo_ssInfoUpdate(void);

/*
 * @brief 	get network key index from flash
 *
 * */
u8 zdo_ssInfoKeyGet(void);


/* generate network key, and then store it in the ib table */
void ss_nwkKeyGenerate(u8 *nwkKey);

/* store network key in ib table */
void ss_nwkKeyStore(u8 *nwkKey);

/*
 * @brief	security configuration
 *
 * @param	enSecurity  security enable
 *
 * */
void ss_zdoInit(bool enSecurity);

/*
 * @brief	security configuration
 *
 * @param	m  security mode, distribute network or central network
 *
 * */
void ss_securityModeSet(ss_securityMode_e m);

/*
 * @brief	judge if it's a distribute security mode
 *
 * */
bool ss_securityModeIsDistributed(void);

bool ss_keyPreconfigured(void);

#endif	/* SECURITY_SERVICE_H */
