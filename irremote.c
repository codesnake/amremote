#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/ioctl.h>
#include "remote_config.h"
#include "keydefine.h"
#define FACTCUSTCODE_MAX 20
#define CUSTOM_REMOTE_MAX 20
#define MAX_KEY_MAPS 256
#define MAX_MOUSE_MAPS 4
#define DEVICE_NAME "/dev/amremote"
#define DEVICE_KP  "/dev/am_adc_kpd"

unsigned short default_key_map[MAX_KEY_MAPS] = {
KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, /*0~7*/
KEY_8, KEY_9, KEY_BACK, KEY_UP, KEY_BACKSPACE, KEY_ENTER, KEY_DOWN, KEY_MENU, /*8~f*/
KEY_LEFT, KEY_RIGHT, KEY_R, KEY_S, KEY_U, KEY_G, KEY_K, KEY_L, /*10~17*/
KEY_M, KEY_N, KEY_D, KEY_T, KEY_H, KEY_B, KEY_I, KEY_J, /*18~1f*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*20~27*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*28~2f*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*30~37*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*38~3f*/

KEY_C, KEY_F, KEY_E, KEY_P, KEY_V, KEY_A, KEY_Q, KEY_O, /*40~47*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*48~4f*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_W, KEY_Z, KEY_RESERVED, KEY_RESERVED, KEY_Y, /*50~57*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_X, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*58~5f*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*60~67*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*68~6f*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*70~77*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*78~7f*/

KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*80~87*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*88~8f*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*90~97*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*98~9f*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*a0~a7*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*a8~af*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*b0~b7*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*b8~bf*/

KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*c0~c7*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*c8~cf*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*d0~d7*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*d8~df*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*e0~e7*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*e8~ef*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, /*f0~f7*/
KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED, KEY_RESERVED /*f8~ff*/
};

unsigned short default_mouse_map[4] = {
 //0x10, 0x11, 0x0b, 0x0e 
 0xffff, 0xffff, 0xffff, 0xffff
};

unsigned short adc_map[2] ={0xffff, 0xffff};//left,right
unsigned int adc_move_enable = 0;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int malloc_new_remote(remote_config_t **remote)
{
    *remote = (remote_config_t *)malloc(sizeof(remote_config_t));
    if (!*remote) {
        printf("Memory allocation for 'remote' failed!\n");
        return -1;
    }

    remote_config_t *new_remote = *remote;

    memset(new_remote, 0xff, sizeof(remote_config_t));

    new_remote->key_map = (unsigned short *)malloc(sizeof(unsigned short) * MAX_KEY_MAPS);
    if (!new_remote->key_map) {
        printf("Memory allocation for 'key_map' failed!\n");
        return -1;
    }

    memset(new_remote->key_map, KEY_RESERVED, sizeof(unsigned short) * MAX_KEY_MAPS);

    new_remote->mouse_map = (unsigned short *)malloc(sizeof(unsigned short) * MAX_MOUSE_MAPS);
    if (!((remote_config_t *)*remote)->mouse_map) {
        printf("Memory allocation for 'mouse_map' failed!\n");
        return -1;
    }

    memset(new_remote->mouse_map, 0xFFFF, sizeof(unsigned short) * MAX_MOUSE_MAPS);

    new_remote->repeat_key_map = (unsigned short *)malloc(sizeof(unsigned short) * MAX_KEY_MAPS);
    if (!new_remote->repeat_key_map) {
        printf("Memory allocation for 'repeat_key_map' failed!\n");
        return -1;
    }

    memset(new_remote->repeat_key_map, KEY_RESERVED, sizeof(unsigned short) * MAX_KEY_MAPS);

    new_remote->factory_customercode_map = (unsigned int *)malloc(sizeof(unsigned int) * FACTCUSTCODE_MAX);
    if (!new_remote->factory_customercode_map) {
        printf("Memory allocation for 'repeat_key_map' failed!\n");
        return -1;
    }

    memset(new_remote->factory_customercode_map, 0xFFFFFFFF, sizeof(unsigned int) * FACTCUSTCODE_MAX);

    return 0;
}

void free_remote(remote_config_t **remote)
{
    remote_config_t *free_remote = *remote;

    if (free_remote)
    {
        if (free_remote->factory_customercode_map)
        {
            free(free_remote->factory_customercode_map);
            free_remote->factory_customercode_map = NULL;
        }

        if (free_remote->repeat_key_map)
        {
            free(free_remote->repeat_key_map);
            free_remote->repeat_key_map = NULL;
        }

        if (free_remote->mouse_map)
        {
            free(free_remote->mouse_map);
            free_remote->mouse_map = NULL;
        }

        if (free_remote->key_map)
        {
            free(free_remote->key_map);
            free_remote->key_map = NULL;
        }

        free(free_remote);
        free_remote = NULL;
    }
}

int main(int argc, char* argv[])
{
    remote_config_t *remotes[CUSTOM_REMOTE_MAX] = { NULL };
    FILE *fp;
    int i, j;
    int device_fd;
    unsigned int val;

    device_fd = open(DEVICE_NAME, O_RDWR);

    if(device_fd < 0){
        printf("Can't open %s .\n", DEVICE_NAME);
        return -2;
        }
    if(argc < 2){
            remote_config_t *remote = NULL;
            if (!malloc_new_remote(&remote))
            {
                remote->factory_code = 0x40400001;
                remote->work_mode = 1;
                remote->repeat_enable = 1;
                remote->release_delay = 150;
                remote->debug_enable = 1;
                remote->reg_control = 0xfbe40;
                remote->repeat_delay = 250;
                remote->repeat_peroid = 33;
                memcpy(remote->key_map, default_key_map, sizeof(unsigned short) * MAX_KEY_MAPS);
                memcpy(remote->mouse_map, default_mouse_map, sizeof(unsigned short) * MAX_MOUSE_MAPS);
                remotes[0] = remote;
            }
        }
    else if(argv[1][0]=='-'){
        printf("Usage : %s configfile\n", argv[0]);
        return -3;
        }
    else{
        fp=fopen(argv[1], "r");
        if(!fp){
            printf("Open file %s is failed!!!\n", argv[1]);
            return -4;
            }
        get_config_from_file(fp, remotes);
        fclose(fp);
        }

    ioctl(device_fd, REMOTE_IOC_RESET_KEY_MAPPING, NULL);

    for (j = 0; j < CUSTOM_REMOTE_MAX; j++)
    {
        remote_config_t *custom_remote = remotes[j];
        if (!custom_remote)
            continue;

        custom_remote->factory_code >>= 16;
        set_config(custom_remote, device_fd);

        for (i = 0; i < 256; i++)
            if (custom_remote->key_map[i] != KEY_RESERVED) {
                val = (i << 16) | custom_remote->key_map[i];
                ioctl(device_fd, REMOTE_IOC_SET_KEY_MAPPING, &val);
            }

        for (i = 0; i < 256; i++)
            if (custom_remote->repeat_key_map[i] != KEY_RESERVED) {
                val = (i << 16) | custom_remote->repeat_key_map[i];
                ioctl(device_fd, REMOTE_IOC_SET_REPEAT_KEY_MAPPING, &val);
            }

        for (i = 0; i < 4; i++)
            if (custom_remote->mouse_map[i] != 0xffff) {
                val = (i << 16) | custom_remote->mouse_map[i];
                ioctl(device_fd, REMOTE_IOC_SET_MOUSE_MAPPING, &val);
            }

        for (i = 0; i < FACTCUSTCODE_MAX; i++)
            if (custom_remote->factory_customercode_map[i] != 0xffffffff) {
                val = (i << 16) | custom_remote->factory_customercode_map[i];
                ioctl(device_fd, REMOTE_IOC_SET_FACTORY_CUSTOMCODE, &val);
            }
    }

    close(device_fd);

    for (i = 0; i < CUSTOM_REMOTE_MAX; i++)
        free_remote(&remotes[i]);

    device_fd = open(DEVICE_KP, O_RDWR);
    if (device_fd >= 0) {
        if (adc_move_enable != 0) {
            for (i = 0; i < ARRAY_SIZE(adc_map); i++) {
                if (adc_map[i] != 0xffff) {
                    val = (i << 16) | adc_map[i];
                    ioctl(device_fd, KEY_IOC_SET_MOVE_MAP, &val);
                    printf("adc_map[%d] = %d ,val = %d \n", i, adc_map[i], val);
                }
            }
        }

        ioctl(device_fd, KEY_IOC_SET_MOVE_ENABLE, &adc_move_enable);
        printf("adc_move_enable = %d \n", adc_move_enable);

        close(device_fd);
    }

    return 0;
}
