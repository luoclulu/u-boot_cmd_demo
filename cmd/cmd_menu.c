#include <common.h>
#include <command.h>
#include <env.h>
#include <errno.h>
#include <malloc.h>
#include <cli.h>
#include <asm/byteorder.h>
#include <linux/ctype.h>
#include <linux/err.h>
#include <u-boot/zlib.h>

#define CONFIG_MENU_PROMPT "Menu->"
#define MAX_MENU_FUNCTIONS 10

extern char console_buffer[CONFIG_SYS_CBSIZE + 1];

typedef struct menu_structure menu_s;
struct menu_structure{
	char *name;
	char *menu_print;
	int lines;
	int cflag;
	void (* func)(void);
	void (* op)(menu_s *);
	void (* back)(char *);
	void *private;
	menu_s *prev;
};

int traverse_menu_function(int lines)
{
	int i;

	if (lines > MAX_MENU_FUNCTIONS)
		printf("Error! Menu lines %d greater than Maximum!\n", lines);
	
	for (i = 0; i < lines; i++){
	}

	return 0;
}

void wait_for_menu_select(void)
{
	int len;
	const char *menu_cmd;

	len = cli_readline(CONFIG_MENU_PROMPT);
	menu_cmd = console_buffer;
	printf("-debug- cmd is %s\n", menu_cmd);

	//if (strncmp())
}

void back_to_premenu(menu_s *cur_menu)
{
	if (cur_menu->prev == NULL) {
		printf("**At the top level**\n");
		printf("**Press <Ctrl-c> to exit menu**\n");
	}

	cur_menu = cur_menu->prev;
	printf("%s", cur_menu->menu_print);
//	cur_menu->func();
	wait_for_menu_select();
}

void test_menu_func(void)
{
	printf("###L1##\n");
}

int menu_s_test(void)
{
	menu_s menu_test = {
		.name = "menu_test",
		.menu_print = "\n"
			"[1]\n"
			"[2]\n"
			"[3]\n"
			"[4]\n",
		.cflag = 0,
		.func = test_menu_func,
		.prev = NULL,
	};

	menu_test.func();

	return 0;
}

menu_s *alloc_menu_struct(void)
{
	menu_s *menu;

	menu = (menu_s *)malloc(sizeof(menu_s));
	if (menu == NULL)
		printf("Malloc failed!\n");

	return menu;
}

void free_menu_struct(menu_s *menu)
{
	free(menu);
}

int do_menu_cmd(const char choice)
{
	switch(choice) {
	case '1':
		printf("*1*\n");
		break;
	case '2':
		printf("*2*\n");
		break;
	case '3':
		printf("*3*\n");
		break;
	case '4':
		printf("*4*\n");
		break;
	case '5':
		menu_s_test();
	default:
		printf("Not a menu command!\n");
		break;
	}

	return 0;
}

int menu_initialize(void)
{
	int i;
	menu_s *menu_second = alloc_menu_struct();

	menu_second->name = "second";
	menu_second->menu_print = "\n"
		"[a] sec menu\n"
		"[b] sec menu\n"
		"[c] sec menu\n"
		"[d] sec menu\n";
	menu_second->lines = 4;
	menu_second->prev = NULL;

	for (i = 0; i < menu_second->lines; i++) {
	}
	return 0;
}

int do_menu_operation(menu_s *menu)
{
	int i,len;
	char *menu_cmd;

	printf("%s", menu->menu_print);

	len = cli_readline(CONFIG_MENU_PROMPT);
	menu_cmd = console_buffer;
	printf("-debug- cmd is %s\n", menu_cmd);
	

	if (len < 0)
		return len;

	for (i = 0; i < menu->lines; i++) {
	}

	return -1;
}

void menu_loop(void)
{
	int ret;
	//char *cmd = "xxx"; /* Initial Command Input */

	menu_s *menu_main = alloc_menu_struct();
	menu_main->name = "main";
	menu_main->menu_print = "\n"
		"[1] main menu\n"
		"[2] main menu\n"
		"[3] main menu\n"
		"[4] main menu\n";
	menu_main->lines = 4;
	menu_main->prev = NULL;

	menu_initialize();
	
	for (;;) {
		ret = do_menu_operation(menu_main);

		if (ret < 0)
			return;
	}

	free_menu_struct(menu_main);
}

static int do_menu(struct cmd_tbl *cmdtp, int flag, int argc,
		   char *const argv[])
{
	printf("*********************************\n");
	printf("**********  Menu Demo  **********\n");	
	printf("*********************************\n");

	menu_loop();

	return 0;
}

U_BOOT_CMD(
	menu,	10,		1,	do_menu,
	"Display a menu to choose which program to execute",
	"\n"
	"    - A program to learn the operation about menu.\n"
	"      Here is another line to add content."
);

