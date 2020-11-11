#ccflags-y += -Wall

# zhaopengfei@wind-mobi.com 20180711 begin >>> [1/5] add the mastar device info
ccflags-y += -I$(srctree)/drivers/misc/wind_device_info/
# zhaopengfei@wind-mobi.com 20180711 end   <<< [1/5] add the mastar device info
	
#ccflags-y += -I$(srctree)/drivers/input/touchscreen/mediatek/msg2xxx/
#ccflags-y += -I$(srctree)/drivers/input/touchscreen/mediatek/
#ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/
#ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include/

obj-$(CONFIG_TOUCHSCREEN_MSG2836) += ilitek_drv_qcom.o \
	ilitek_drv_update.o \
	ilitek_drv_main.o \
	ilitek_drv_mp_test.o \
	new_mp_test/mp_misc.o \
	new_mp_test/mp_result.o \
	new_mp_test/mp_parse.o \
	new_mp_test/mp_test.o \
	new_mp_test/mp_main.o \


