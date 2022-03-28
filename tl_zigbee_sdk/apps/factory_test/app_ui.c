/********************************************************************************************************
 * @file	app_ui.c
 *
 * @brief	This is the source file for app_ui
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
#if (__PROJECT_TL_SWITCH__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zb_api.h"
#include "zcl_include.h"
#include "sampleSwitch.h"
#include "app_ui.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * LOCAL FUNCTIONS
 */
void led_on(u32 pin)
{
	drv_gpio_write(pin, LED_ON);
}

void led_off(u32 pin)
{
	drv_gpio_write(pin, LED_OFF);
}

void light_on(void)
{
	led_on(LED1);
}

void light_off(void)
{
	led_off(LED1);
}

void light_init(void)
{
	led_off(LED1);

}

s32 zclLightTimerCb(void *arg)
{
	u32 interval = 0;

	if(g_switchAppCtx.sta == g_switchAppCtx.oriSta){
		g_switchAppCtx.times--;
		if(g_switchAppCtx.times <= 0){
			g_switchAppCtx.timerLedEvt = NULL;
			return -1;
		}
	}

	g_switchAppCtx.sta = !g_switchAppCtx.sta;
	if(g_switchAppCtx.sta){
		light_on();
		interval = g_switchAppCtx.ledOnTime;
	}else{
		light_off();
		interval = g_switchAppCtx.ledOffTime;
	}

	return interval;
}

void light_blink_start(u8 times, u16 ledOnTime, u16 ledOffTime)
{
	u32 interval = 0;
	g_switchAppCtx.times = times;

	if(!g_switchAppCtx.timerLedEvt){
		if(g_switchAppCtx.oriSta){
			light_off();
			g_switchAppCtx.sta = 0;
			interval = ledOffTime;
		}else{
			light_on();
			g_switchAppCtx.sta = 1;
			interval = ledOnTime;
		}
		g_switchAppCtx.ledOnTime = ledOnTime;
		g_switchAppCtx.ledOffTime = ledOffTime;

		g_switchAppCtx.timerLedEvt = TL_ZB_TIMER_SCHEDULE(zclLightTimerCb, NULL, interval);
	}
}

void light_blink_stop(void)
{
	if(g_switchAppCtx.timerLedEvt){
		TL_ZB_TIMER_CANCEL(&g_switchAppCtx.timerLedEvt);

		g_switchAppCtx.times = 0;
		if(g_switchAppCtx.oriSta){
			light_on();
		}else{
			light_off();
		}
	}
}

/*******************************************************************
 * @brief	Button click detect:
 * 			SW1. keep press button1 5s === factory reset
 * 			SW1. short press button1   === send level step with OnOff command (Up)
 * 			SW2. keep press button2 5s === invoke EZ-Mode
 * 			SW2. short press button2   === send level step with OnOff command (Down)
 *
 */
void buttonKeepPressed(u8 btNum){
	if(btNum == VK_SW1){
		g_switchAppCtx.state = APP_FACTORY_NEW_DOING;
		zb_factoryReset();
	}else if(btNum == VK_SW2){

	}
}

void set_detect_voltage(s32 v){
    g_switchAppCtx.Vbat = v;
}

ev_timer_event_t *brc_toggleEvt = NULL;

s32 brc_toggleCb(void *arg)
{
	epInfo_t dstEpInfo;
	TL_SETSTRUCTCONTENT(dstEpInfo, 0);

	dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
	dstEpInfo.dstEp = SAMPLE_SWITCH_ENDPOINT;
	dstEpInfo.dstAddr.shortAddr = 0xfffc;
	dstEpInfo.profileId = HA_PROFILE_ID;

	zcl_onOff_toggleCmd(SAMPLE_SWITCH_ENDPOINT, &dstEpInfo, FALSE);

	return 0;
}

void brc_toggle(void)
{
	if(!brc_toggleEvt){
		brc_toggleEvt = TL_ZB_TIMER_SCHEDULE(brc_toggleCb, NULL, 1000);
	}else{
		TL_ZB_TIMER_CANCEL(&brc_toggleEvt);
	}
}

void buttonShortPressed(u8 btNum){
	if(btNum == VK_SW1){
		if(zb_isDeviceJoinedNwk()){
#if 1
			epInfo_t dstEpInfo;
			TL_SETSTRUCTCONTENT(dstEpInfo, 0);

			dstEpInfo.profileId = HA_PROFILE_ID;
#if FIND_AND_BIND_SUPPORT
			dstEpInfo.dstAddrMode = APS_DSTADDR_EP_NOTPRESETNT;
#else
			dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
			dstEpInfo.dstEp = SAMPLE_SWITCH_ENDPOINT;
			dstEpInfo.dstAddr.shortAddr = 0xfffc;
#endif
			zcl_onOff_toggleCmd(SAMPLE_SWITCH_ENDPOINT, &dstEpInfo, FALSE);
#else
			brc_toggle();
#endif
		}
	}else if(btNum == VK_SW2){
		if(zb_isDeviceJoinedNwk()){
			static u8 lvl = 1;
			static bool dir = 1;

			epInfo_t dstEpInfo;
			TL_SETSTRUCTCONTENT(dstEpInfo, 0);

			dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
			dstEpInfo.dstEp = SAMPLE_SWITCH_ENDPOINT;
			dstEpInfo.dstAddr.shortAddr = 0xfffc;
			dstEpInfo.profileId = HA_PROFILE_ID;

			moveToLvl_t move2Level;

			move2Level.optPresent = 0;
			move2Level.transitionTime = 0x0A;
			move2Level.level = lvl;

			zcl_level_move2levelCmd(SAMPLE_SWITCH_ENDPOINT, &dstEpInfo, FALSE, &move2Level);

			if(dir){
				lvl += 50;
				if(lvl >= 250){
					dir = 0;
				}
			}else{
				lvl -= 50;
				if(lvl <= 1){
					dir = 1;
				}
			}
		}
	}
}


void keyScan_keyPressedCB(kb_data_t *kbEvt){
	//u8 toNormal = 0;
	u8 keyCode = kbEvt->keycode[0];
	//static u8 lastKeyCode = 0xff;

	buttonShortPressed(keyCode);

	if(keyCode == VK_SW1){
		g_switchAppCtx.keyPressedTime = clock_time();
		g_switchAppCtx.state = APP_FACTORY_NEW_SET_CHECK;
	}
}


void keyScan_keyReleasedCB(u8 keyCode){
	g_switchAppCtx.state = APP_STATE_NORMAL;
}

void app_key_handler(void){
	static u8 valid_keyCode = 0xff;
	if(g_switchAppCtx.state == APP_FACTORY_NEW_SET_CHECK){
		if(clock_time_exceed(g_switchAppCtx.keyPressedTime, 5*1000*1000)){
			buttonKeepPressed(VK_SW1);
		}
	}
	if(kb_scan_key(0 , 1)){
		if(kb_event.cnt){
			g_switchAppCtx.keyPressed = 1;
			keyScan_keyPressedCB(&kb_event);
			if(kb_event.cnt == 1){
				valid_keyCode = kb_event.keycode[0];
			}
		}else{
			keyScan_keyReleasedCB(valid_keyCode);
			valid_keyCode = 0xff;
			g_switchAppCtx.keyPressed = 0;
		}
	}
}

#endif  /* __PROJECT_TL_SWITCH__ */
