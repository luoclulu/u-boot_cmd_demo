#include <common.h>
#include <command.h>
#include <env.h>
#include <errno.h>
#include <image.h>
#include <malloc.h>
#include <asm/byteorder.h>
#include <linux/ctype.h>
#include <linux/err.h>
#include <linux/list.h>
#include <u-boot/zlib.h>

typedef struct menu_list {
	int val;
	char *name;
	struct list_head list;
} ml_s;

LIST_HEAD(menu_header);

static ml_s *alloc_menu_list(int id)
{
	ml_s *menu;

	menu = (ml_s *)malloc(sizeof(ml_s));
	menu->val = id;
	if (menu == NULL)
		printf("Malloc failed!\n");

	return menu;
}

static void free_menu_list(int id)
{
	
}

void deallob_menu_list(void)
{
	//del

	//free
}

void menu_list_init(void)
{
	struct menu_list *menu;
	struct menu_list *menu2;
	menu = (ml_s *)malloc(sizeof(ml_s));

	menu->val = 1;
	
	list_add(menu, &menu_header);

	menu2 = (ml_s *)malloc(sizeof(ml_s));

	menu2->val = 2;

	list_add(menu2, &menu_header);
}

void list_head_test(void)
{
	ml_s led, gpio, beep, *tmp;

	led.name = "led";
	gpio.name = "gpio";
	beep.name = "beep";

	list_add(&led.list, &menu_header);
	list_add(&gpio.list, &menu_header);
	list_add(&beep.list, &menu_header);
	//list_add(NULL, &menu_header);

	list_for_each_entry(tmp, &menu_header, list) {
		printf("devname is %s\n", tmp->name);
	}
	
	printf("0\n");
	list_del(&beep.list);
	list_del(&gpio.list);
	list_del(&led.list);
}

static int do_list(struct cmd_tbl *cmdtp, int flag, int argc,
		   char *const argv[])
{
	printf("**********list test***********\n");

	list_head_test();
	//menu_list_init();

	return 0;
}

U_BOOT_CMD(
	list,	1,		1,	do_list,
	"a demo program to test list",
	"\n"
	"    - A demo program to learn the usage of list.\n"
	"      Here is another line to add content."
);

