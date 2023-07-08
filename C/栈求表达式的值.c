#include <stdio.h>
#include <stdlib.h>
typedef enum { false = 0, true = 1 }bool;
#define MAXSIZE 50
// �ַ�ջ
typedef struct
{
	char data[MAXSIZE];
	int top;
}Stack;

void InitStack(Stack **s)
{
	*s = (Stack*)malloc(sizeof(Stack));
	(*s)->top = -1;
}

bool Push(Stack *s, char e)
{
	if (s->top == MAXSIZE - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(Stack **s, char *e)
{
	if ((*s)->top == -1)
		return false;
	*e = (*s)->data[(*s)->top];
	(*s)->top--;
	return true;
}

bool GetTop(Stack **s, char *e)
{
	if ((*s)->top == -1)
		return false;
	*e = (*s)->data[(*s)->top];
	return true;
}

bool StackEmpty(Stack **s)
{
	if ((*s)->top == -1)
		return true;
	return false;
}

// ����׺���ʽת���ɺ�׺���ʽ
void trans(char *exp, char postexp[])
{
	int i = 0;
	char e;
	Stack *Optr;
	InitStack(&Optr); //��ʼ��������ջ��Ϊ�洢��׺���ʽ��׼��

	while (*exp != '\0') // ��ÿ���ַ������жϴ���
	{
		switch (*exp)
		{
			//������������
			//����������ţ�ֱ����ջ
			case '(':
				Push(Optr, '(');
				exp++;
				break;
			//���Ϊ�����ţ�һֱ��ջ������ֱ���� ( Ҳ��ջ
			case ')': 
				Pop(&Optr, &e);
				while (e != '(')
				{
					postexp[i++] = e;
					Pop(&Optr, &e);
				}
				exp++;
				break;
			// + - ���ȼ���ͬ������ͬһ���������
			case '+':
			case '-': 
				//���� + - �����ȼ�ֻ�� ( ������ֻҪջ���ַ���Ϊ ( ��һֱ��ջ����֮���� + - ��ջ��
				while (!StackEmpty(&Optr)) 
				{
					GetTop(&Optr, &e);
					if (e == '(')
						break;
					else
					{
						postexp[i++] = e;
						Pop(&Optr, &e);
					}
				}
				//��� + - ��ջ
				Push(Optr, *exp);
				exp++;
				break;
			case '*':
			case '/':
				// * / ���ȼ��� * / ^ ! С���������ջ������������ǣ��ͳ�ջ����֮�ͽ� * / ��ջ
				while (!StackEmpty(&Optr))
				{
					GetTop(&Optr, &e);
					if (e == '/' || e == '*' ||e=='^' || e=='!') // * / �����ȼ�����������ǰ��� * /������ǰ��� + -������Ҫ��ǰ��� * / ����ջ��+ - ��������Ϊ�µ� * / �����ջ�ͣ����ȼ��ߡ�
					{
						postexp[i++] = e;
						Pop(&Optr, &e);
					}
					else
						break; // ��������� + - ������ ���˳���
				}
				//��� / * ��ջ
				Push(Optr, *exp);
				exp++;
				break;
			case '^':
				// ^ ���ȼ����� ^ ! С�����ջ������������ǣ����ջ����֮�� ^ ��ջ
				while (!StackEmpty(&Optr))
				{
					GetTop(&Optr, &e);
					if (e == '^' || e == '!')
					{
						postexp[i++] = e;
						Pop(&Optr, &e);
					}
					else
						break; // ��������� + - * / ( ���˳���
				}
				Push(Optr, *exp); //��� ^ ��ջ
				exp++;
				break;
			case '!':
				// ! ���ȼ����� ! С���������ջ�������Ϊ !,�����ջ����֮���� ! ��ջ
				while (!StackEmpty(&Optr))
				{
					GetTop(&Optr, &e);
					if (e == '!')
					{
						postexp[i++] = e;
						Pop(&Optr, &e);
					}
					else
						break; // ��������� + - * / ^ ( ���˳���
				}
				//��� ! ��ջ
				Push(Optr, *exp);
				exp++;
				break;
			default:
				while (*exp > '0' && *exp < '9') //ѭ���ж��Ƿ�Ϊ�����ַ���������򱣴浽postexp��ѭ���ж�����Ϊ�����Ƕ�λ����
				{
					postexp[i++] = *exp;
					exp++;
				}
				//��#�ָ����������ַ�
				postexp[i++] = '#'; 
		}
	}
	while (!StackEmpty(&Optr)) //ɨ����exp�󣬲�����ջ���ܻ��в�����������浽postexp
	{
		Pop(&Optr, &e);
		postexp[i++] = e;
	}
	postexp[i] = '\0'; //�����ַ���
	free(Optr); //����ջ
}

//���ַ���ʽ�ĺ�׺���ʽ��ת����������ʽ�ı��ʽ�����м���
typedef struct
{
	double data[MAXSIZE];
	int top;
}Stack_num;

void InitStack_num(Stack_num **s)
{
	*s = (Stack_num *)malloc(sizeof(Stack_num));
	(*s)->top = -1;
}

bool Push_num(Stack_num **s, double e)
{
	if ((*s)->top == MAXSIZE - 1)
		return false;
	(*s)->top++;
	(*s)->data[(*s)->top] = e;
	return true;
}

bool Pop_num(Stack_num **s, double *e)
{
	if ((*s)->top == -1)
		return false;
	*e = (*s)->data[(*s)->top];
	(*s)->top--;
	return true;
}

//�����׺���ʽ��ֵ
double compvalue(char *postexp)
{
	Stack_num *num;
	int i = 1;
	double result;
	double a, b;
	double c;
	double d;
	InitStack_num(&num);
	while (*postexp != '\0')
	{
		switch (*postexp)
		{
			case '+':
				Pop_num(&num, &a); 
				Pop_num(&num, &b);
				//���� b+a ��ֵ
				c = b + a;
				Push_num(&num, c);
				break;
			case '-':
				//���� b-a ��ֵ
				Pop_num(&num, &a);
				Pop_num(&num, &b);
				c = b - a;
				Push_num(&num, c);
				break;
			case '*':
				Pop_num(&num, &a);
				Pop_num(&num, &b);
				//���� b*a ��ֵ
				c = b * a;
				Push_num(&num, c);
				break;
			case '/':
				Pop_num(&num, &a); // a�ǳ���
				Pop_num(&num, &b);
				//���� b/a ��ֵ
				if (a != 0)
				{
					c = b / a;
					Push_num(&num, c);
				}
				else
				{
					printf("��0����\n");
					exit(0);
				}
				break;
			case '^':
				Pop_num(&num, &a); // a��ָ��
				Pop_num(&num, &b);
				//���� b^a ��ֵ
				if (a != 0)
				{
					i = 1;
					c = 1;
					while(i <= a) {
						c = c * b;
						i++;
					}
				}
				else if(b != 0)
				{
					c = 1;
				}
				else {
					c = 0;
				}
				Push_num(&num, c);
				break;
			case '!':
				Pop_num(&num, &a);
				//���� a! ��ֵ
				c = 1;
				i = a;
				while (i != 0) {
					c = c * i;
					i--;
				}
				Push_num(&num, c);
				break;
			default:
				//����������������ֻ�����ַ���ʽ�����֣�����ת���ɶ�Ӧ������
				d = 0;
				while (*postexp >= '0' && *postexp <= '9')
				{
					d = 10 * d + (*postexp - '0');
					postexp++;
				}
				Push_num(&num, d);
		}
		postexp++; //������һ���ַ�
	}
	Pop_num(&num, &result);
	return result;
}
//����û�����ı��ʽ������
bool test(char *exp)
{
	int i = 0;
	Stack *s;
	char e;
	//�ж��Ƿ�����Ƿ��ַ�
	for (; exp[i] != '\0'; i++)
	{
		if (!((exp[i] >= '0' && exp[i] <= '9') || exp[i] == '!' || exp[i] == '^' || exp[i] == '+' || exp[i] == '-' || \
			exp[i] == '*' || exp[i] == '/' || exp[i] == '(' || exp[i] == ')'))

			return false;
	}
	//������ʽ�а������ţ���֤���ŵ�������
	InitStack(&s);
	for (i = 0; exp[i] != '\0'; i++)
	{
		switch (exp[i])
		{
		case '(':
			Push(s, exp[i]);
			break;
		case ')':
			if (Pop(&s, &e))
			{
				if (exp[i] == ')' && e == '(')
					return true;
				else
					return false;
			}
			else
				return false;
			break;
		}
	}
	//ջΪ�ձ�ʾ����ƥ��ɹ�
	if (s->top != -1)  
		return false;
	else
		return true;
	return true;
}

int main()
{
	//�洢�û��������׺���ʽ
	char exp[MAXSIZE];
	//���ڴ洢ת����ĺ�׺���ʽ
	char postexp[MAXSIZE];
	while (true)
	{
		printf("������ʽ��");
		scanf("%s", exp);
		if (!test(exp))
		{
			printf("���ڷǷ��ַ��������Ų�ƥ�䣡\n");
			continue;
		}
		trans(exp, postexp);
		printf("��׺���ʽ:%s\n", postexp);
		printf("���:%lf\n", compvalue(postexp));
	}
	return 0;
}