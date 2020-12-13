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

extern char console_buffer[CONFIG_SYS_CBSIZE + 1];

typedef struct menu_structure menu_s;
struct menu_structure{
	int cflag;
	char *name;
	void (* menu_print)(void);
	void (* menu_function)(void);
	menu_s *prev;
	menu_s *next;
};

void test_menu_print(void)
{
	printf("###test menu line 1\n");
	printf("###test menu line 2\n");
}

void test_menu_func(void)
{
	printf("###L1##\n");
}

int menu_s_test(void)
{
	menu_s menu_test = {
		.cflag = 0,
		.name = "menu_test",
		.menu_print = test_menu_print,
		.menu_function = test_menu_func,
		.prev = NULL,
		.next = NULL,
	};

	menu_test.menu_print();
	menu_test.menu_function();

	return 0;
}

#define MAX_FUNCTIONS 10
int traverse_menu_function(void)
{
	int i;

	for (i = 0; i < MAX_FUNCTIONS; i++){
		
	}
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

void main_menu(void)
{
	printf("\n");
	printf("[1] main menu a\n");
	printf("[2] main menu b\n");
	printf("[3] main menu c\n");
	printf("[4] main menu d\n");
	printf("[5] menu_s test\n");
	printf("[Ctrl-c] exit\n");
}

void menu_loop(void)
{
	int len;
	const char *menu_cmd;
	char choice;

	for (;;) {
		main_menu();

		len = cli_readline(CONFIG_MENU_PROMPT);
		menu_cmd = console_buffer;
		choice = menu_cmd[0];
		printf("len is %d\n", len);

		if (len < 0)
			return;
		else
			do_menu_cmd(choice);
	}
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

