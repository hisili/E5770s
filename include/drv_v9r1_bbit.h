

#ifndef __DRV_V9R1_BBIT_H__
#define __DRV_V9R1_BBIT_H__

#include "drv_comm.h"


/************************V9R1BBIT START***********************/
typedef enum
{
    DBLED_DRV1 = 0,        /* DRV���Ե�1 */
    DBLED_DRV2,            /* DRV���Ե�2 */
    DBLED_DSP1 = 2,        /* DSP���Ե�1 */
    DBLED_DSP2,            /* DSP���Ե�2 */
    DBLED_RESERVED1 = 4,   /* �������Ե�1 */
    DBLED_RESERVED2,       /* �������Ե�2 */
    DBLED_MAX
}DBLED_ID_E;


extern int DRV_DBLED_ON(unsigned int ledId);


extern int DRV_DBLED_OFF(unsigned int ledId);

/*V9R1SFT SC����ַ��BBITƽ̨��SC*/
#define SC_BASE    SOC_SCTRL_BASE_ADDR


extern int DRV_COPY_NVUSE_TO_NVBACKUP ( void );



extern int DRV_COPY_NVUPGRADE_TO_NVUSE( void );
/*************************V9R1BBIT END************************/

#endif

