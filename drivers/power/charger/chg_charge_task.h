
#ifndef CHG_CHARGE_TASK_H
#define CHG_CHARGE_TASK_H
/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/
/**********************************************************************
函 数 名: chg_main_task
功能描述: 归一化充电任务
输入参数: None
输出参数: None
返 回 值: None
注意事项: 涵盖了Linux和Vxworks的实现
          因为有系统调用,因此注意包含相应的库文件
***********************************************************************/
int32_t  chg_main_task( void  *task_para );

/**********************************************************************
函 数 名      : chg_task_init
功能描述  :  开机初始化,开机后进行的charger的基本配置
                            启动充电任务及定时器
输入参数  : 无。
输出参数  : 无。
返 回 值      : 无。
注意事项  : 无。
***********************************************************************/
extern void chg_task_init(void);
#endif/*CHG_CHARGE_TASK_H*/