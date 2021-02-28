#include"key.h"
#include"stc8.h"

void Key_Init(void)
{
	KEY_UP=1;         //定义按键输入端口
	KEY_DOWN=1;
	KEY_OK=1;
	KEY_CANCEL=1;
}
