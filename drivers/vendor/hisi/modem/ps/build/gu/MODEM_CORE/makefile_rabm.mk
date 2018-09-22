#***********************************************************#
# include the define at the top
#***********************************************************#
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

#***********************************************************#
# moudle name & core define
#***********************************************************#
OBC_LOCAL_CORE_NAME		?=mcore

ifeq ($(INSTANCE_ID) ,INSTANCE_0)
OBC_LOCAL_MOUDLE_NAME	?=rabm_ccore
endif

ifeq ($(INSTANCE_ID) ,INSTANCE_1)
OBC_LOCAL_MOUDLE_NAME	?=rabm1_ccore
endif

#***********************************************************#
# compiler flags
#***********************************************************#
#COMM FLAGS
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_flags.mk

#USER FLAGS
CC_USER_FLAGS   ?= 
AS_USER_FLAGS   ?=

CC_USER_FLAGS += -falign-arrays

ifeq ($(CFG_THUMB_COMPILE),YES)
CC_USER_FLAGS += -mlong-calls
endif 

#***********************************************************#
# compiler defines
#***********************************************************#
#COMM DEFINES
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm_defines.mk

#USER DEFINES
CC_USER_DEFINES ?=

ifeq ($(INSTANCE_ID) ,INSTANCE_1)
CC_USER_DEFINES	+=-DINSTANCE_1
endif
				
#ԭ�ű�û�д��Ż�ѡ�Ϊ����һ�£���ʱ�ر�
OBC_C_OPTIM_OPTION :=

#***********************************************************#
# include Directories
#***********************************************************#
#common include directories
include $(BALONG_TOPDIR)/modem/ps/build/gu/MODEM_CORE/ps_comm.inc

#nas include directories
OBC_LOCAL_INC_DIR ?=
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/config/log \
	$(BALONG_TOPDIR)/config/nvim/include/gu \
        $(BALONG_TOPDIR)/include/nv/gu/codec \
	$(BALONG_TOPDIR)/config/osa \
	$(BALONG_TOPDIR)/include/drv \
	$(BALONG_TOPDIR)/include/oam/comm/om \
	$(BALONG_TOPDIR)/include/oam/comm/osa \
	$(BALONG_TOPDIR)/include/oam/comm/scm \
	$(BALONG_TOPDIR)/include/oam/comm/si \
	$(BALONG_TOPDIR)/include/oam/comm/socp \
	$(BALONG_TOPDIR)/include/oam/comm/usimm \
	$(BALONG_TOPDIR)/include/oam/comm/errno \
	$(BALONG_TOPDIR)/include/oam/comm/dms \
	$(BALONG_TOPDIR)/include/oam/comm/nvim \
	$(BALONG_TOPDIR)/include/oam/gu/log \
	$(BALONG_TOPDIR)/include/oam/gu/om \
	$(BALONG_TOPDIR)/include/oam/gu/nvim \
	$(BALONG_TOPDIR)/include/oam/gu/hpa \
	$(BALONG_TOPDIR)/include/oam/lt/msp \
	$(BALONG_TOPDIR)/include/phy/gphy \
	$(BALONG_TOPDIR)/include/phy/wphy \
	$(BALONG_TOPDIR)/include/ps/gups \
	$(BALONG_TOPDIR)/include/ps/tlps \
	$(BALONG_TOPDIR)/include/ps/nas \
	$(BALONG_TOPDIR)/include/taf \
	$(BALONG_TOPDIR)/include/tools \
	$(BALONG_TOPDIR)/include/nv/gu/nas \
	$(BALONG_TOPDIR)/include/nv/gu/gas \
	$(BALONG_TOPDIR)/include/nv/gu/was \
	$(BALONG_TOPDIR)/include/nv/gu/ttf \
	$(BALONG_TOPDIR)/include/nv/gu/oam \
	$(BALONG_TOPDIR)/include/nv/gu/codec \
	$(BALONG_TOPDIR)/include/med

OBC_LOCAL_INC_DIR += \
    $(BALONG_TOPDIR)/modem/ps/inc/gu \
	$(BALONG_TOPDIR)/modem/ps/inc/lt \
	$(BALONG_TOPDIR)/modem/ps/comm/inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/DICC/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/FLOWCTRL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/LINK/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/MEM/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/STL/Inc \
    $(BALONG_TOPDIR)/modem/ps/comm/comm/CDS/Inc \
	$(BALONG_TOPDIR)/modem/ps/comm/gu/zlib/Inc \
	$(BALONG_TOPDIR)/modem/ps/nas/inc \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/mml/INC \
	$(BALONG_TOPDIR)/modem/ps/nas/comm/UTRANCTRL/INC \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/lib \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Fsm/INC \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Cc/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Gmm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmc/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Mmcomm/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Nasapi/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sm/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Sms/inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Ss/Inc \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Tc/Inc \
	$(BALONG_TOPDIR)/modem/taf/inc \
	$(BALONG_TOPDIR)/modem/taf/comm/inc \
	$(BALONG_TOPDIR)/modem/taf/comm/src/mcore/TAF/Lib/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/Lib \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Fsm/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Xml/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Lib/Log \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Call/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Data/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Msg/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Phone/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Sups/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/Mn/Task/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/VC/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafDrvAgent/Inc \
	$(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/CBA/Inc \
    $(BALONG_TOPDIR)/modem/taf/gu/src/ccore/src/TafMta/Inc
	
#***********************************************************#
# source files
#***********************************************************#
OBC_LOCAL_SRC_FILE := \
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/Rabm_ApsTransmodeSet.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/Rabm_Assistant.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/Rabm_DataAndFlux.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/Rabm_DealGmmMsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/Rabm_DealSmMsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/Rabm_DealSnMsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/Rabm_DealTimeoutMsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/Rabm_MsgDispatch.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/rabmcommon.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/rabmmain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/rabmram.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/rabmrcvmsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/rabmsndmsg.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/NasRabmMain.c\
    $(BALONG_TOPDIR)/modem/ps/nas/gu/src/Rabm/src/NasRabmMsgProc.c\
    

ifeq ($(CFG_RAT_MODE),RAT_GU)
OBC_LOCAL_SRC_FILE += \

endif

ifeq ($(CFG_RAT_MODE),RAT_GUL)
OBC_LOCAL_SRC_FILE += \

endif

#***********************************************************
#include rules. must be droped at the bottom, OBB_BUILD_ACTION values: cc tqe lint fortify
#***********************************************************
include $(BALONG_TOPDIR)/build/scripts/rules/$(OBB_BUILD_ACTION)_vxworks6.8_rules.mk
