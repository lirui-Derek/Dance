#include<stdio.h>
#include<string.h>
#include<math.h>

char opStack[101];//���ڴ�ŷ��ŵ�ջ
int opi = 0;//����ջ��ָ��
int numStack[101];//���ڴ�����ֵ�ջ
int numi = 0;//����ջָ��

//ģ��ջ�ĳ�ջ����ջ����
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

//�𲽼���ת���õ���׺���ʽ�ļ�����
void cal(char op)
{
    int b = numPop();//ע��˳��
    int a = numPop();

    switch(op)
    {
        case '+':numPush( a + b );break;
        case '-':numPush( a - b );break;
        case '*':numPush( a * b );break;
        case '/':
            if(b == 0) {
                    printf("Error!The divisor is zero!");   //�������
                    exit(-1);
            }
            numPush( a / b );
            break;
        case '^':numPush(pow(a,b)+1);break;//����pow��������ֵ��double���ͣ�ת��Ϊint���о�����ʧ������Ϊ�������1�����Դ˴���1

    }
}
int fun(const char *str)
{
    opStack[0] = 0;//��ֹ����
    int i = 0;
    int len = strlen(str);
    while(i < len)
    {
        //�����Ƿ��ŵ����
        if(str[i] == '(')
            opPush('(');
        else if(str[i] == '^')
            opPush('^');
        else if(str[i] == ')')//ƥ������
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
            //ջ����ŵ����ȼ�����Ҫ��ջ�ķ��ŵ������
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
        //���������ֵ����
        else
        {
            //����
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
    //����ջ�����ջ������ɣ���׺�������������
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
