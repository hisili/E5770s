

#ifndef __DRV_CLK_H__
#define __DRV_CLK_H__

#ifndef NULL
#define NULL (void *)0
#endif

struct clk {
    char                              *name;               /*clock name*/
    unsigned int	                  refcnt;              /*clock referent count*/
    struct clk	                     *parent;              /*the parent of this clock*/
    unsigned long                     rate;                /*clock rate*/
    struct clk_ops		             *ops;                 /*clock oprate function*/
    struct clksel	                 *sel_parents;         /*clocks can be this clock's parent*/
    unsigned int                     clkid;                /*clock id ,come from clk_id ,referent to struct crg_tag array*/
};

/**
 * struct clk_ops - standard clock operations
 */
struct clk_ops {
    int        (*isenable)(struct clk *clk);
    int        (*enable)(struct clk *clk);
    void      (*disable)(struct clk *clk);
    int	   (*round_rate)(struct clk *clk, unsigned long rate);
    int	   (*set_rate)(struct clk *clk, unsigned long rate);
    int	   (*set_parent)(struct clk *clk, struct clk *parent);
};


/**
 * struct clksel - select clk parent by clock register
 */
struct clksel {
	struct clk	*sel_parent;              /*clocks can be parent*/
	int	             sel_val;                    	/* the value should be set to the registers' enable bit */
	unsigned long	parent_min;              /*parent min rate*/
	unsigned long	parent_max;              /*parent max rate*/
};



#ifdef __VXWORKS__
/***********************************************************************
*����:��ȡʱ��
*���:dev:NULL,  id:��ʱ�Ӿ�̬ע��ʱ������
*����:ʱ�ӽṹ��ָ��
*ʱ�ӱ��뾲̬ע��󣬲���ʹ�ã���Ȼ��ȡʧ��
************************************************************************/
 struct clk *clk_get(char *dev, const char *id);

 /***********************************************************************
*����:ʹ��ʱ��
*���:ʱ�ӽṹ��ָ��
*����:�ɹ�Ϊ0��ʧ�ܷ�0
************************************************************************/
int clk_enable(struct clk *clk);

/***********************************************************************
*����:ȥʹ��ʱ��
*���:ʱ�ӽṹ��ָ��
*����:��
************************************************************************/
void clk_disable(struct clk *clk);

/***********************************************************************
*����:��ȡʱ��Ƶ��
*���:ʱ�ӽṹ��ָ��
*����:ʱ��Ƶ��
************************************************************************/
unsigned long clk_get_rate(struct clk *clk);

long clk_round_rate(struct clk *clk, unsigned long rate);

/***********************************************************************
*����:����ʱ��Ƶ��
*���:ʱ�ӽṹ��ָ�룬Ԥ����Ƶ��ֵ(���Ƿ�Ƶ��)
*����:�ɹ�Ϊ0��ʧ�ܷ�0
************************************************************************/
int clk_set_rate(struct clk *clk, unsigned long rate);

/***********************************************************************
*����:����ʱ�Ӹ���
*���:ʱ�ӽṹ��ָ�룬����ʱ�ӽṹ��ָ��
*����:�ɹ�Ϊ0��ʧ�ܷ�0
************************************************************************/
int clk_set_parent(struct clk *clk, struct clk *parent);

/***********************************************************************
*����:��ȡʱ�Ӹ���
*���:ʱ�ӽṹ��ָ��
*����:����ʱ�ӽṹ��ָ��
************************************************************************/
struct clk *clk_get_parent(struct clk *clk);
#endif

/***********************************************************************
*����:��ѯʱ��״̬
*���:ʱ�ӽṹ��ָ��
*����: 1:enable  0:disable
************************************************************************/
int clk_status(struct clk *c);

#endif

