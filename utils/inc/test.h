#ifndef TEST_H_
#define TEST_H_

#define NULL ((void*)0)

#define SPECIAL_OUTPUT_PORT (*((volatile char *)0x20))
#define SPECIAL_INPUT_PORT  (*((volatile char *)0x22))

void print_str(const char *str)
{
    const char *c;
    for (c = str; *c != '\0' ; c++)
    {
        SPECIAL_OUTPUT_PORT = *c;
    }
}

void print_num(int num)
{
    char str[15];
    int i = 0;
    if (num == 0)
    {
        SPECIAL_OUTPUT_PORT = '0';
    }
    else
    {
        while (num != 0)
        {
            str[i++] = (num % 10) + '0';
            num /= 10;
        }
        for (int j = i - 1 ; j >= 0 ; j--)
        {
            SPECIAL_OUTPUT_PORT = str[j];
        }
    }

}
void print_num_binary(int num)
{
    int str[sizeof(int)*8];
    int i = 0;
    if (num==0)
    {
    SPECIAL_OUTPUT_PORT ='0';
    }
    else
    {
    for (i=0;num>0;i++)
    {
    str[i]=num%2;
    num=num/2;
    }
    for (i=i-1;i>=0;i--)
    {
    SPECIAL_OUTPUT_PORT = str[i]+'0';
    }
    }
}

void print_char(char C)
{
    SPECIAL_OUTPUT_PORT = C;
}

void new_line()
{
    SPECIAL_OUTPUT_PORT = '\n';
}

#endif /* TEST_H_ */
