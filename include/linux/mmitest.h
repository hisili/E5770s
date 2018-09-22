

#ifndef __MMI_TEST_LINUX_H__
#define __MMI_TEST_LINUX_H__
#include <product_config.h>
#include <linux/types.h>

#define MAX_BYTE                       (0xFF)

enum mmi_test_key_id
{
    MMI_TEST_POWER_KEY,
    MMI_TEST_MENU_KEY,
    MMI_TEST_RESET_KEY,
    /*Add your key definition here.*/
    MMI_TEST_KEY_MAX,
};

enum mmi_test_key_event
{
    MMI_KEY_RELEASE,
    MMI_KEY_PRESS,
};



void mmi_key_event_hook(
    enum mmi_test_key_id key, 
    enum mmi_test_key_event evt
);

enum mmi_lcd_img_id
{
    MMI_LCD_IMG_ALLBLACK,
    MMI_LCD_IMG_ALLWHITE,
    MMI_LCD_IMG_ALLICONS,
    MMI_LCD_IMG_TEST_PASS,
    MMI_LCD_IMG_TEST_FAIL,
    MMI_LCD_IMG_MAX = MAX_BYTE
};

void mmi_lcd_show_image(enum mmi_lcd_img_id img);
#endif /*__MMI_TEST_LINUX_H__*/
