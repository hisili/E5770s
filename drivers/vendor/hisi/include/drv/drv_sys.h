

#ifndef __DRV_SYS_H__
#define __DRV_SYS_H__

#include "drv_comm.h"


extern long bsp_sys_creat(const char  *pathname, int mode);
#define DRV_SYS_CREAT(pathname,mode) bsp_sys_creat(pathname,mode)

extern long bsp_sys_open(const char  *filename,int flags, int mode);
#define DRV_SYS_OPEN(filename,flags,mode) bsp_sys_open(filename,flags,mode)

extern long bsp_sys_close(unsigned int fd);
#define DRV_SYS_CLOSE(fd) bsp_sys_close(fd)

extern long bsp_sys_lseek(unsigned int fd, unsigned int offset,unsigned int origin);
#define DRV_SYS_LSEEK(fd,offset,origin) bsp_sys_lseek(fd,offset,origin)

extern long bsp_sys_read(unsigned int fd, char  *buf, unsigned int count);
#define DRV_SYS_READ(fd, buf, count) bsp_sys_read(fd, buf, count)

extern long bsp_sys_write(unsigned int fd, const char  *buf,unsigned int count);
#define DRV_SYS_WRITE(fd, buf, count) bsp_sys_write(fd, buf, count)

extern long bsp_sys_mkdir(const char  *pathname, int mode);
#define DRV_SYS_MKDIR(pathname, mode) bsp_sys_mkdir(pathname, mode)

extern long bsp_sys_rmdir(const char  *pathname);
#define DRV_SYS_RMDIR(pathname) bsp_sys_rmdir(pathname)

extern long bsp_sys_unlink(const char  *pathname);
#define DRV_SYS_UNLINK(pathname) bsp_sys_unlink(pathname)

extern long bsp_sys_getdents(unsigned int fd,
          void  *dirent,
          unsigned int count);
#define DRV_SYS_GETDENTS(fd,dirent,count) bsp_sys_getdents(fd,dirent,count)

extern long bsp_sys_sync(void);
#define DRV_SYS_SYNC() bsp_sys_sync()

extern long bsp_sys_sync_file(unsigned int fd);
#define DRV_SYS_SYNC_FILE(fd) bsp_sys_sync_file(fd)

/*****************************************************************************
* �� �� ��  : BSP_GetSysFrame
*
* ��������  : get system frame num 
*
* �������  : ��
* �������  :
*
* �� �� ֵ  : frame num/0xffff
*
* �޸ļ�¼  : 2012��4��18��  wangjing  creat
*****************************************************************************/
extern BSP_U16 BSP_GetSysFrame(BSP_VOID);

/*****************************************************************************
* �� �� ��  : BSP_GetSysSubFrame
*
* ��������  : get sub system frame num 
*
* �������  : ��
* �������  :
*
* �� �� ֵ  : frame num/0xffff
*
* �޸ļ�¼  : 2012��4��18��  wangjing  creat
*****************************************************************************/
extern BSP_U16 BSP_GetSysSubFrame(BSP_VOID);

#endif

