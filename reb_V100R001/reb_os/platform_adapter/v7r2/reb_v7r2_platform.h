#ifndef REB_TASK_H
#define REB_TASK_H


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

void hard_timer_creat(unsigned int time_in_ms, unsigned int input_para );
void hard_timer_reset( unsigned int time_in_ms );
void hard_timer_delete(void);
int reb_nv_kernel_read(void);
void reb_for_power_off(void);
int reb_is_factory_mode(void);
unsigned long  reb_get_current_systime(void);
#endif