#ifndef  _REMOTE_CONFIG_H
#define  _REMOTE_CONFIG_H

#include <asm/ioctl.h>
#include <stdint.h>

#define REMOTE_IOC_UNFCODE_CONFIG            _IOW('I', 12, uint32_t)
#define REMOTE_IOC_INFCODE_CONFIG            _IOW('I', 13, uint32_t)
#define REMOTE_IOC_RESET_KEY_MAPPING         _IOW('I', 3, uint32_t)
#define REMOTE_IOC_SET_KEY_MAPPING           _IOW('I', 4, uint32_t)
#define REMOTE_IOC_SET_MOUSE_MAPPING         _IOW('I', 5, uint32_t)
#define REMOTE_IOC_SET_REPEAT_DELAY          _IOW('I', 6, uint32_t)
#define REMOTE_IOC_SET_REPEAT_PERIOD         _IOW('I', 7, uint32_t)

#define REMOTE_IOC_SET_REPEAT_ENABLE         _IOW('I', 8, uint32_t)
#define REMOTE_IOC_SET_DEBUG_ENABLE          _IOW('I', 9, uint32_t) 
#define REMOTE_IOC_SET_MODE                  _IOW('I', 10, uint32_t) 
#define REMOTE_IOC_SET_MOUSE_SPEED           _IOW('I', 11, uint32_t)

#define REMOTE_IOC_SET_REPEAT_KEY_MAPPING    _IOW('I', 20, uint32_t)
#define REMOTE_IOC_SET_RELEASE_FDELAY        _IOW('I', 97, uint32_t)
#define REMOTE_IOC_SET_RELEASE_SDELAY        _IOW('I', 98, uint32_t)
#define REMOTE_IOC_SET_RELEASE_DELAY         _IOW('I', 99, uint32_t)
#define REMOTE_IOC_SET_CUSTOMCODE            _IOW('I', 100, uint32_t)
//reg
#define REMOTE_IOC_SET_REG_BASE_GEN          _IOW('I', 101, uint32_t)
#define REMOTE_IOC_SET_REG_CONTROL           _IOW('I', 102, uint32_t)
#define REMOTE_IOC_SET_REG_LEADER_ACT        _IOW('I', 103, uint32_t)
#define REMOTE_IOC_SET_REG_LEADER_IDLE       _IOW('I', 104, uint32_t)
#define REMOTE_IOC_SET_REG_REPEAT_LEADER     _IOW('I', 105, uint32_t)
#define REMOTE_IOC_SET_REG_BIT0_TIME         _IOW('I', 106, uint32_t)

//sw
#define REMOTE_IOC_SET_BIT_COUNT             _IOW('I', 107, uint32_t)
#define REMOTE_IOC_SET_TW_LEADER_ACT         _IOW('I', 108, uint32_t)
#define REMOTE_IOC_SET_TW_BIT0_TIME          _IOW('I', 109, uint32_t)
#define REMOTE_IOC_SET_TW_BIT1_TIME          _IOW('I', 110, uint32_t)
#define REMOTE_IOC_SET_TW_REPEATE_LEADER     _IOW('I', 111, uint32_t)

#define REMOTE_IOC_GET_TW_LEADER_ACT         _IOR('I', 112, uint32_t)
#define REMOTE_IOC_GET_TW_BIT0_TIME          _IOR('I', 113, uint32_t)
#define REMOTE_IOC_GET_TW_BIT1_TIME          _IOR('I', 114, uint32_t)
#define REMOTE_IOC_GET_TW_REPEATE_LEADER     _IOR('I', 115, uint32_t)


#define REMOTE_IOC_GET_REG_BASE_GEN          _IOR('I', 121, uint32_t)
#define REMOTE_IOC_GET_REG_CONTROL           _IOR('I', 122, uint32_t)
#define REMOTE_IOC_GET_REG_LEADER_ACT        _IOR('I', 123, uint32_t)
#define REMOTE_IOC_GET_REG_LEADER_IDLE       _IOR('I', 124, uint32_t)
#define REMOTE_IOC_GET_REG_REPEAT_LEADER     _IOR('I', 125, uint32_t)
#define REMOTE_IOC_GET_REG_BIT0_TIME         _IOR('I', 126, uint32_t)
#define REMOTE_IOC_GET_REG_FRAME_DATA        _IOR('I', 127, uint32_t)
#define REMOTE_IOC_GET_REG_FRAME_STATUS      _IOR('I', 128, uint32_t)

#define REMOTE_IOC_SET_FN_KEY_SCANCODE       _IOW('I', 131, uint32_t) 
#define REMOTE_IOC_SET_LEFT_KEY_SCANCODE     _IOW('I', 132, uint32_t)
#define REMOTE_IOC_SET_RIGHT_KEY_SCANCODE    _IOW('I', 133, uint32_t)
#define REMOTE_IOC_SET_UP_KEY_SCANCODE       _IOW('I', 134, uint32_t)
#define REMOTE_IOC_SET_DOWN_KEY_SCANCODE     _IOW('I', 135, uint32_t)
#define REMOTE_IOC_SET_OK_KEY_SCANCODE       _IOW('I', 136, uint32_t)
#define REMOTE_IOC_SET_PAGEUP_KEY_SCANCODE   _IOW('I', 137, uint32_t)
#define REMOTE_IOC_SET_PAGEDOWN_KEY_SCANCODE _IOW('I', 138, uint32_t)

#define REMOTE_IOC_SET_TW_BIT2_TIME          _IOW('I', 129, uint32_t)
#define REMOTE_IOC_SET_TW_BIT3_TIME          _IOW('I', 130, uint32_t)
#define REMOTE_IOC_SET_FACTORY_CUSTOMCODE    _IOW('I', 139, uint32_t)
#define ADC_KP_MAGIC 'P'
#define KEY_IOC_SET_MOVE_MAP                 _IOW_BAD(ADC_KP_MAGIC,0X02,int)
#define KEY_IOC_SET_MOVE_ENABLE              _IOW_BAD(ADC_KP_MAGIC,0X03,int)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef   struct{
       unsigned short *key_map;
       unsigned short *repeat_key_map;
       unsigned short *mouse_map;
	   unsigned int *factory_customercode_map;
       unsigned int factory_infcode;
       unsigned int factory_unfcode;
       unsigned int factory_code;
       unsigned int repeat_delay;
       unsigned int repeat_peroid;
       unsigned int work_mode ;
       unsigned int mouse_speed;
	unsigned int repeat_enable;
	unsigned int release_delay;
	unsigned int release_fdelay;
	unsigned int release_sdelay;
	unsigned int debug_enable;
//sw
	unsigned int 	bit_count;
	unsigned int 	tw_leader_act;
	unsigned int 	tw_bit0;
	unsigned int   tw_bit1;
	unsigned int   tw_bit2;
	unsigned int   tw_bit3;
	unsigned int 	tw_repeat_leader;
//reg
	unsigned int  reg_base_gen;
	unsigned int  reg_control;
	unsigned int  reg_leader_act;
	unsigned int  reg_leader_idle;
	unsigned int  reg_repeat_leader;
	unsigned int  reg_bit0_time;

	unsigned int fn_key_scancode;
        unsigned int left_key_scancode;
	unsigned int right_key_scancode;
	unsigned int up_key_scancode;
	unsigned int down_key_scancode;
	unsigned int ok_key_scancode;
	unsigned int pageup_key_scancode;
	unsigned int pagedown_key_scancode;
}remote_config_t;

//these string must in this order and sync with struct remote_config_t
extern char*  config_item[33];

extern int malloc_new_remote(remote_config_t **remote);
extern int set_config(remote_config_t *remote, int device_fd);
extern int get_config_from_file(FILE *fp, remote_config_t *remotes[]);

#endif
