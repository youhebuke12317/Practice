/************************************************************************
 * 描述：接收网络数据时，以十六进制和字符形式打印出来
 *      用于调试
 ************************************************************************/
#include <stdio.h>
#include <strng.h>

void Hexdump(void *data, int len);
void OX(unsigned char *data, int len);


void network_debug(unsigned char *data, int len)
{   
    printf("----------------debug--------------\n");
    Hexdump(data, len);
    //OX(data, len);
    printf("\n");
}

/* 十六进制 */
static char dec2hex[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

/*
 * 打印形式类似于wireshark,这个更好.....
 * */
void Hexdump(void *data, int len)
{
    // 每行显示的字符个数
    int showlen = 0;
    char str[16] = {' '};
    int line = ((uint32_t)len >> 4);

    if ((len & 15) != 0)
        line++;

    int i;
    for (i = 0; i < len; i++) {
        uint8_t byte = ((char*)data)[i];

        // 第二个符号
        printf("%c", dec2hex[(byte & 0xf0) >> 4]);
        // 第一个符号
        printf("%c", dec2hex[(byte & 0xf)]);
        // 空格
        printf(" ");
        // 填充
        if ((i == (len - 1)) && (showlen < 15)) {
            printf(" ");
            int i;
            for (i = 0; i < (15 - showlen); i++)
                printf("   ");
        }
        // 输出值 
        // ZL: isprint()检查包含空格的任何可打印字符, 返回0表示不可打印
        str[showlen] = (isprint(byte)) ? byte : '.';
        showlen++;
        // 换行
        if (((i + 1) & 15) == 0) {
            printf(" %.*s", 8, str);
            printf(" %.*s", 8, str + 8);
            printf("\n");
            showlen = 0;
            if (i == (len - 1)) return;
        }
    }

    // 对于不足16的进行换行
    for (i = showlen; i <= 15; i++)
        str[i] = ' ';
    printf("%.*s", 8, str);
    printf("%.*s", 8, str + 8);
    printf("\n");
}

/*
 * 将收到的数据以16进制形式打印出来
 * 自己的写法 
 * */
void OX(unsigned char *data, int len)
{
    printf("data_len-> %d -------- tada_type-> %d\n", len, data[0]);
    int i = 0, index = 0;
    for(; i < len; i++)
    {
        if(index < 16)
        {
            printf("%02X ", data[i]);
            index++;
            if(index == 8)
            {
                printf(" ");
            } 
        } else {
            printf("\n");
            index = 0;
        }
    }
    printf("\n");
}


