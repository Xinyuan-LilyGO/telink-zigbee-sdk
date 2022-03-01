/********************************************************************************************************
 * @file	nwk_ctx.h
 *
 * @brief	This is the header file for nwk_ctx
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
#ifndef NWK_CTX_H
#define NWK_CTX_H


/**
 * Startup control attribute
 */
typedef enum
{
    STARTUP_CONTROL_PART_OF_NETWORK,
    STARTUP_CONTROL_FORM_A_NETWORK,
    STARTUP_CONTROL_REJOIN_NETWORK,
    STARTUP_CONTROL_START_FROM_SCRATCH
}StartupControl_attr_t;

/**
   Network layer running state
*/
typedef enum
{
	NLME_STATE_IDLE,
	NLME_STATE_DISC,
	NLME_STATE_FORMATION_ED_SCAN,
	NLME_STATE_FORMATION_ACTIVE_SCAN,
	NLME_STATE_FORMATION,
	NLME_STATE_ROUTER,
	NLME_STATE_ED_SCAN,
	NLME_STATE_REJOIN,
	NLME_STATE_ORPHAN_SCAN,
	NLME_STATE_RESET,
	NLME_STATE_PANID_CONFLICT_RESOLUTION,
	NLME_STATE_ADDR_CONFLICT_RESOLUTION,
	NLME_STATE_ZLL_COMMISSION
}nlme_state_t;

typedef enum
{
	NLME_IDLE,
	NLME_PERMIT_JOIN_REQ,
	NLME_SEND_DEV_ANN,
	NLME_LEAVING,
}user_state_t;

typedef struct
{
	u16	nwkFwdDstAddr;
	u16 nwkFwdSrcAddr;
	u16	senderAddr;
	u16 lastSendFailAddr;
}manyToOne_repair_t;

typedef struct
{
	u16	nwkFwdDstAddr;
	u16 nwkFwdSrcAddr;
}srcRoute_repair_t;

typedef void (*nwkDiscoveryUserCb_t)(void);

/**
   Place to store values between multiply operations
*/
typedef struct
{
	nwkForTouchlinkCb_t	touchLinkCb;
	/* For coordinator to store formation information */
	struct{
		u8 energy_detect[TL_ZB_MAC_CHANNEL_NUM];
		u8 channel_pan_count[TL_ZB_MAC_CHANNEL_NUM];
	}formationInfo;
	/* End [32 bytes] */

	/* For router and end device  to store assocJoin/rejoin information */
	union{
		struct{
			tl_zb_addition_neighbor_entry_t	*pParent;
		}assocJoin;
		struct{
			tl_zb_addition_neighbor_entry_t	*pParent;
		}rejoin;
	}join;
	u8 *joinCandidateList;
	/* End [8 bytes]*/

	/* For coordinator or router store current joining device info */
	ev_timer_event_t *curJoiningDevTimerEvt;

	nwkDiscoveryUserCb_t nwkDiscConf;

    u32	scanChannels;

    u8	scanDuration;
	u8  is_factory_new:1;	/*!< Device is factory new */
	u8  permit_join:1; 		/*!< True if permit join is in progress */
	u8  joined:1;      		/*!< Non-zero if we are joined into the network *///10
	u8  router_started:1; 	/*!< not used */
	u8  is_tc:1;            /*!< True if we are Trust Center */
	u8  joined_pro:1;
	u8	panIdConflict:1;	/*!< if we find panID conflict */
	u8	joinAccept:1;
	u8	known_panids_cnt:4;
	u8	discoverRoute:1;	/*!< Always TRUE for NLDE data request! see 2.2.4.1.1.3 */
	u8  panidUpdateRecv:1;	/*receive network update for panid conflict*/
	u8  resv:1;
	u8	parentIsChanged:1;	/*!< A flag indicates that the device's parent is changed through rejoin */
	u8 	user_state:4;		/*!< Current network user_state_t */
	u8 	state:4; 			/*!< Current network subsystem state nlme_state_t */

	u8 	parent; 			/*!< parent address (valid if we are not ZC and joined) */
	u8 	leaveRejoin;		/*!< if we need rejoin after leave */
	u16 new_panid;

	/* For PANID conflict resolution */
	u16 known_panids[PANID_TABLE_SIZE];

	manyToOne_repair_t	manyToOneRepair; /* saved for check nlde-data.confirm status when unicast data frame using many-to-one */
	srcRoute_repair_t 	srcRouteRepair;
}nwk_ctx_t;

extern nwk_ctx_t g_zbNwkCtx;


#define ZB_SET_DISCOVER_ROUTE(v)		(g_zbNwkCtx.discoverRoute = v)
#define ZB_GET_DISCOVER_ROUTE			(g_zbNwkCtx.discoverRoute)

#define ZB_SET_USER_STATE(v)			(g_zbNwkCtx.user_state = v)
#define ZB_GET_USER_STATE				(g_zbNwkCtx.user_state)

#endif /* NWK_CTX_H */
