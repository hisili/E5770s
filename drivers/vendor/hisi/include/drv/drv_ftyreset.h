/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 *
 * mobile@huawei.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __DRV_FTYRESET_H__
#define __DRV_FTYRESET_H__

#include "drv_comm.h"

#include "product_config.h"

typedef enum
{
    APP_START_INVALID = 0,/*SDK???������㨹*/
    APP_START_READY = 1,  /*SDK???��ok*/
    APP_RESTORE_OK = 2, /*SDK???��3?3��OK*/
    APP_RESTORE_PROCESSING = 3 /*SDK???��3?3��?D*/
}NODE_STATE_TYPE;

typedef int (*FtyresetNotifyAppHandle)(void);
extern NODE_STATE_TYPE drv_get_ftyreset_node_state(void);

/*************************CHG?��?�� END*********************************/
#endif

