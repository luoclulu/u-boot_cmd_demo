#include <common.h>
#include <bootm.h>
#include <command.h>
#include <env.h>
#include <errno.h>
#include <image.h>
#include <malloc.h>
#include <nand.h>
#include <asm/byteorder.h>
#include <linux/ctype.h>
#include <linux/err.h>
#include <u-boot/zlib.h>
#include <mapmem.h>

static int do_hello(struct cmd_tbl *cmdtp, int flag, int argc,
		   char *const argv[])
{
	int i;
	printf("hello, world! %d\n", argc);

	for (i = 0; i < argc; i++) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	return 0;
}

U_BOOT_CMD(
	hello,	1,		1,	do_hello,
	"a hello program to test u-boot cmd",
	"\n"
	"    - A test program to test help informaiton of new command.\n"
	"      Here is another line to add content."
);