#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_LEN 50

//定义结构体
typedef struct {                                 //定义单个学生的结构体类型
	int sno;										      //学号
	char sname[MAX_LEN+1];				 //名字
	char sex[MAX_LEN+1];						                  //性别
	char major[MAX_LEN+1];                //专业
}S_stu;
typedef struct stu_node {                     //定义学生结点类型struct_node这里首字母用小写和它的类型名区分开
	S_stu data;
	struct stu_node *next;
}Stu_node;
typedef struct stu_link {                   //定义链表结构
	Stu_node *head;                                //头指针
	int size;                                        //链表元素个数
}Stu_link;

typedef struct {                                           //单个课程信息结构体
	int cno;                                                  //课程号
	char cname[MAX_LEN+1];                        //课程名称
	int classHours;                                       //课时数
}S_cou;
typedef struct cou_node {
	S_cou data;
	struct cou_node *next;
}Cou_node;
typedef struct cou_link {
	Cou_node *head;
	int size;
}Cou_link;

typedef struct {                                     //课程成绩信息结构体
	int sno;                                                //学号
	int cno;                                                //课程号
	int score;                                             //成绩
}S_cog;
typedef struct cog_node {//课程成绩信息结点
	S_cog data;
	struct cog_node *next;
}Cog_node;
typedef struct cog_link {//课程成绩链表
	Cog_node *head;
	int size;
}Cog_link;


//定义要用的全局链表
Stu_link stus;//学生信息链表
Cou_link cous;//课程信息链表
Cog_link cogs;//课程成绩链表

//函数声明
int read_line(char str[], int n);//按行读取字符并以字符串形式储存
int init(void);//初始化链表（置空，加头结点）
int choose(void);//选择功能
int pri_stu(Stu_link* stus);//打印学生链表
int sor_stu_sno(Stu_link *stus);//将学生链表根据学号排序，输入为链表结构地址
int fun4(void);//选4时


//函数实现
int read_line(char str[], int n) {
	int ch, i = 0;

	while (isspace(ch = getchar()))
		;
	while (ch != '\n' && ch != EOF) {
		if (i < n)
			str[i++] = ch;
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}

int init(void) {
	Stu_node *new_stu = (Stu_node*)malloc(sizeof(Stu_node));
	memset(new_stu, 0, sizeof(Stu_node));
	stus.head = new_stu;
	Cou_node *new_cou = (Cou_node*)malloc(sizeof(Cou_node));
	memset(new_cou, 0, sizeof(Cou_node));
	cous.head = new_cou;
	Cog_node *new_cog = (Cog_node*)malloc(sizeof(Cog_node));
	memset(new_cog, 0, sizeof(Cog_node));
	cogs.head = new_cog;

	return 1;
}

int choose(void) {
	int cho = 0;
	scanf("%d", &cho);
	return cho;
}

int pri_stu(Stu_link* stus) {
	Stu_node *p = stus->head;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	while (p->next != NULL) {
		printf("学号:%d\t姓名%s\t性别%s\t专业%s\n",
			p->data.sno,
			p->data.sname,
			p->data.sex,
			p->data.major);

		p = p->next;
	}

	return 1;
}

int sor_stu_sno(Stu_link *stus) {
	Stu_node *p = stus->head, *q = p->next;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	if ((0 == stus->size) || (1 == stus->size)){//空链表或者只有一个元素
		return 1;
    }
	//检测、交换
		S_stu temp;
		int i = 0, j = 0;
		for (i = 0; i < stus->size - 1; i++) {
			for (j = 0; j < stus->size - i - 1; j++) {
				if (p->data.sno > q->data.sno) {
					temp = q->data;
					q->data = p->data;
					p->data = temp;
				}
				p = q;
				q = q->next;
			}
			p = stus->head;
			q = p->next;
		}
		
	 

	return 1;
}

int fun4(void) {
	//读取文件并建立链表
	FILE *fp = fopen("student.txt", "r");
	if (NULL == fp) {//错误情况处理
		printf("打开学生信息文件失败\n");
		return 0;
	}
	while (!feof(fp)) {
		Stu_node *new_stu = (Stu_node*)malloc(sizeof(Stu_node));//新结点
		memset(new_stu, 0, sizeof(Stu_node));
		fscanf(fp, "%d", &new_stu->data.sno);
		fscanf(fp, " \t%s", new_stu->data.sname);
		fscanf(fp, " \t%s", new_stu->data.sex);
		fscanf(fp, " \t%s\n", new_stu->data.major);
		new_stu->next = stus.head;
		stus.head = new_stu;
		stus.size++;
	}
	printf("学生信息链表已建立，共%d条记录\n", stus.size);
	//排序并输出
	sor_stu_sno(&stus);
	pri_stu(&stus);
	return 1;
}

int menu(void) {
		printf("---------------------------------------------------------------\n");
		printf("                         学生课程成绩查询系统\n");

		printf("4.建立学生链表\n");
		//printf("5.建立课程链表\n");
		//printf("6.建立成绩链表\n");
		//printf("7.查询所有信息\n");
		//printf("8.查询指定成绩\n");
		//printf("9.小于60分学生\n");
		//printf("10.逆序4的链表\n");
		//printf("11.链式队列做7\n");

		printf("0.退出系统并保存修改\n");
		printf("-1.退出系统并不保存任何信息\n");

		printf("---------------------------------------------------------------\n");
		return 1;
}

int main(void)
{
	                                          //变量声明
	int cho = 0;
	                                          //初始化
	init();
	                                            //开始循环
	while (1) {
		                                            //打印菜单
		menu();
		cho = choose();
		//选择语句
		if (-1 == cho) {//不保存退出未完成
			break;
		}
		if (0 == cho) {//保存退出未完成
			break;
		}
		if (4 == cho) {
			fun4();
			break;
		}

	                                                 //不保存退出
	                                                 //保存退出
	                                                 //其他函数实现

	}
	
	//结束循环

	return 0;
}
