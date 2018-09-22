#-include /../../../*.mk
include $(BALONG_TOPDIR)/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

   zreladdr-$(CONFIG_ARCH_TEST)	:= 0x35208000
params_phys-$(CONFIG_ARCH_TEST)	:= 0x35200100
initrd_phys-$(CONFIG_ARCH_TEST)	:= 0x35200000

   zreladdr-$(CONFIG_ARCH_P531)	:= 0x54B08000
params_phys-$(CONFIG_ARCH_P531)	:= $(CFG_PRODUCT_KERNEL_PARAMS_PHYS)
initrd_phys-$(CONFIG_ARCH_P531)	:= $(CFG_DDR_ACORE_ADDR)

   zreladdr-$(CONFIG_ARCH_V7R2)	:= 0x54B08000
params_phys-$(CONFIG_ARCH_V7R2)	:= $(CFG_PRODUCT_KERNEL_PARAMS_PHYS)
initrd_phys-$(CONFIG_ARCH_V7R2)	:= $(CFG_DDR_ACORE_ADDR)

   zreladdr-$(CONFIG_ARCH_V711)	:= 0x54B08000
params_phys-$(CONFIG_ARCH_V711)	:= $(CFG_PRODUCT_KERNEL_PARAMS_PHYS)
initrd_phys-$(CONFIG_ARCH_V711)	:= $(CFG_DDR_ACORE_ADDR)
