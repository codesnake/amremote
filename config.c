#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "remote_config.h"

#define PRINT_CONFIG

//these string must in this order and sync with struct remote_config_t
char*  config_item[33] = {
    "factory_infcode",
    "factory_unfcode",
    "factory_code",
    "repeat_delay",
    "repeat_peroid",
    "work_mode",
    "mouse_speed",
    "repeat_enable",
    "release_delay",
    "release_fdelay",
    "release_sdelay",
    "debug_enable",
    //sw
    "bit_count",
    "tw_leader_act",
    "tw_bit0",
    "tw_bit1",
    "tw_bit2",
    "tw_bit3",
    "tw_repeat_leader",
    //reg
    "reg_base_gen",
    "reg_control",
    "reg_leader_act",
    "reg_leader_idle",
    "reg_repeat_leader",
    "reg_bit0_time",

    "fn_key_scancode",
    "left_key_scancode",
    "right_key_scancode",
    "up_key_scancode",
    "down_key_scancode",
    "ok_key_scancode",
    "pageup_key_scancode",
    "pagedown_key_scancode",
};

int remote_ioc_table[33] = {
    REMOTE_IOC_INFCODE_CONFIG,
    REMOTE_IOC_UNFCODE_CONFIG,
    REMOTE_IOC_SET_CUSTOMCODE,

    REMOTE_IOC_SET_REPEAT_DELAY,
    REMOTE_IOC_SET_REPEAT_PERIOD,
    REMOTE_IOC_SET_MODE,
    REMOTE_IOC_SET_MOUSE_SPEED,

    REMOTE_IOC_SET_REPEAT_ENABLE,
    REMOTE_IOC_SET_RELEASE_DELAY,
    REMOTE_IOC_SET_RELEASE_FDELAY,
    REMOTE_IOC_SET_RELEASE_SDELAY,
    REMOTE_IOC_SET_DEBUG_ENABLE,
    //sw
    REMOTE_IOC_SET_BIT_COUNT,
    REMOTE_IOC_SET_TW_LEADER_ACT,
    REMOTE_IOC_SET_TW_BIT0_TIME,
    REMOTE_IOC_SET_TW_BIT1_TIME,
    REMOTE_IOC_SET_TW_BIT2_TIME,
    REMOTE_IOC_SET_TW_BIT3_TIME,
    REMOTE_IOC_SET_TW_REPEATE_LEADER,
    //reg
    REMOTE_IOC_SET_REG_BASE_GEN,
    REMOTE_IOC_SET_REG_CONTROL	,
    REMOTE_IOC_SET_REG_LEADER_ACT,
    REMOTE_IOC_SET_REG_LEADER_IDLE,
    REMOTE_IOC_SET_REG_REPEAT_LEADER,
    REMOTE_IOC_SET_REG_BIT0_TIME,

    REMOTE_IOC_SET_FN_KEY_SCANCODE,
    REMOTE_IOC_SET_LEFT_KEY_SCANCODE,
    REMOTE_IOC_SET_RIGHT_KEY_SCANCODE,
    REMOTE_IOC_SET_UP_KEY_SCANCODE,
    REMOTE_IOC_SET_DOWN_KEY_SCANCODE,
    REMOTE_IOC_SET_OK_KEY_SCANCODE,
    REMOTE_IOC_SET_PAGEUP_KEY_SCANCODE,
    REMOTE_IOC_SET_PAGEDOWN_KEY_SCANCODE,
};

int set_config(remote_config_t *remote, int device_fd)
{
    unsigned int i;
    unsigned int *para = &remote->factory_infcode;

    for (i = 0; i < ARRAY_SIZE(config_item); i++) {
        if (para[i] != 0xffffffff) {
#ifdef PRINT_CONFIG
            switch (i) {
            case 2:
            case 4:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                printf("%20s = 0x%x\n", config_item[i], para[i]);
                break;
            default:
                printf("%20s = %d\n", config_item[i], para[i]);
                break;
            }
#endif
            ioctl(device_fd, remote_ioc_table[i], &para[i]);
        }
    }
    return 0;
}
