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

int do_menu_cmd(const char choice)
{
	//printf("The input choice is %c\n", choice);

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
	default:
		printf("Not a menu command!\n");
		break;
	}

	return 0;
}

void main_menu(void)
{
	printf("[1] main menu a\n");
	printf("[2] main menu b\n");
	printf("[3] main menu c\n");
	printf("[4] main menu d\n");
	printf("[q] exit\n");
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
		//printf("choice is %c\n", choice);

		if (len == -1)
			return;
		else
			do_menu_cmd(choice);
	}
}

static int do_menu(struct cmd_tbl *cmdtp, int flag, int argc,
		   char *const argv[])
{
	printf("*******************\n");
	printf("***  Menu Demo  ***\n");	
	printf("*******************\n");

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

