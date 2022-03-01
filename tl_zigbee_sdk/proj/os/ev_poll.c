/********************************************************************************************************
 * @file	ev_poll.c
 *
 * @brief	This is the source file for ev_poll
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
#include "../tl_common.h"
#include "ev_poll.h"


ev_poll_t ev_poll[EV_POLL_MAX];


/**
 * @brief       Schedule a new priority task
 *
 * @param[in]   e   - Specified poll event ID
 * @param[in]   cb  - Pointer for the poll callback function
 *
 * @return      None
 */
void ev_on_poll(ev_poll_e e, ev_poll_callback_t cb)
{
	ev_poll[e].cb = cb;
	ev_poll[e].valid = 1;
}

/**
 * @brief       Enable the specified poll event
 *
 * @param[in]   e - Specified poll event ID
 *
 * @return      None
 */
void ev_enable_poll(ev_poll_e e)
{
	ev_poll[e].valid = 1;
}

/**
 * @brief       Schedule a LOW Medium task
 *
 * @param[in]   e - Specified poll event ID
 *
 * @return      None
 */
void ev_disable_poll(ev_poll_e e)
{
	ev_poll[e].valid = 0;
}

/**
 * @brief       Process poll events
 *
 * @param[in]   None
 *
 * @return      None
 */
void ev_poll_process(void){
    for(u8 i = 0; i < EV_POLL_MAX; i++){
        if(ev_poll[i].valid){
        	ev_poll[i].cb();
        }
    }
}

