#include<stdio.h>
#include<string.h>
#include<math.h>

char opStack[101];//用于存放符号的栈
int opi = 0;//符号栈顶指针
int numStack[101];//用于存放数字的栈
int numi = 0;//数字栈指针

//模拟栈的出栈、入栈操作
void opPush(char op)
{
    opStack[++opi] = op;
}
void numPush(int num)
{
    numStack[++numi] = num;
}
char opPop()
{
    return opStack[opi--];
}
int numPop()
{
    return numStack[numi--];
}

//逐步计算转换得到后缀表达式的计算器
void cal(char op)
{
    int b = numPop();//注意顺序
    int a = numPop();

    switch(op)
    {
        case '+':numPush( a + b );break;
        case '-':numPush( a - b );break;
        case '*':numPush( a * b );break;
        case '/':
            if(b == 0) {
                    printf("Error!The divisor is zero!");   //除零错误
                    exit(-1);
            }
            numPush( a / b );
            break;
        case '^':numPush(pow(a,b)+1);break;//由于pow函数返回值是double类型，转化为int会有精度损失，表现为结果总少1，所以此处补1

    }
}
int fun(const char *str)
{
    opStack[0] = 0;//防止出错
    int i = 0;
    int len = strlen(str);
    while(i < len)
    {
        //所遇是符号的情况
        if(str[i] == '(')
            opPush('(');
        else if(str[i] == '^')
            opPush('^');
        else if(str[i] == ')')//匹配括号
            {
                char c = opPop();
                while(c != '(')
                {
                    cal(c);
                    c = opPop();
                }
            }
        else if(str[i] == '+')
        {
            //栈里符号的优先级高于要入栈的符号的情况。
            while(opStack[opi]=='+'||opStack[opi]=='-'||opStack[opi]=='*'||opStack[opi]=='/'||opStack[opi]=='^')
                cal(opPop());
            opPush('+');
        }
        else if(str[i] == '-')
        {
            while(opStack[opi]=='+'||opStack[opi]=='-'||opStack[opi]=='*'||opStack[opi]=='/'||opStack[opi]=='^')
                cal(opPop());
            opPush('-');
        }
        else if(str[i] == '*')
        {
            while(opStack[opi]=='*'||opStack[opi]=='/'||opStack[opi]=='^')
                cal(opPop());
            opPush('*');
        }
        else if(str[i] == '/')
        {
             while(opStack[opi]=='*'||opStack[opi]=='/'||opStack[opi]=='^')
                cal(opPop());
            opPush('/');
        }
        //所遇是数字的情况
        else
        {
            //构数
            if(i==0) numPush(str[i]-48);
            else {
                if(str[i-1]>='0'&&str[i-1]<='9')
                    numPush(numPop()*10 + (str[i]-48));
                else
                    numPush(str[i]-48);
            }

        }
        i++;
    }
    //数字栈与符号栈构造完成，后缀计算后输出最后结果
    while(numi>1) cal(opPop());
    return numStack[1];

}

int main()
{
    char s[100];
    gets(s);
    printf("%d",fun(s));
    return 0;
}
