#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_LEN 50

//定义结构体
typedef struct {//定义单个学生的结构体类型
	int sno;	//学号
	char sname[MAX_LEN + 1];	//名字
	char sex[MAX_LEN + 1];//性别
	char major[MAX_LEN + 1];//专业
}S_stu;
typedef struct stu_node {//定义学生结点类型struct_node这里首字母用小写和它的类型名区分开
	S_stu data;
	struct stu_node *next;
}Stu_node;
typedef struct stu_link {//定义链表结构
	Stu_node *head;//头指针
	int size;//链表元素个数
}Stu_link;

typedef struct {//单个课程信息结构体
	int cno;//课程号
	char cname[MAX_LEN + 1];//课程名称
	int classHours;//课时数
}S_cou;
typedef struct cou_node {
	S_cou data;
	struct cou_node *next;
}Cou_node;
typedef struct cou_link {
	Cou_node *head;
	int size;
}Cou_link;

typedef struct {//课程成绩信息结构体
	int sno;//学号
	int cno;//课程号
	int score;//成绩
}S_cog;
typedef struct cog_node {//课程成绩信息结点
	S_cog data;
	struct cog_node *next;
}Cog_node;
typedef struct cog_link {//课程成绩链表
	Cog_node *head;
	int size;
}Cog_link;

typedef struct {//所有信息结构
	int sno;
	char sname[MAX_LEN];
	char major[MAX_LEN];
	int cno;
	char cname[MAX_LEN];
	int score;
	
}S_all;
typedef struct all_node{//所有信息的结点
	S_all data;
	struct all_node *next;
}All_node;
typedef struct all_link{//所有信息链表
	All_node *head;
	int size;
}All_link;


//定义要用的全局链表
Stu_link stus;//学生信息链表
Cou_link cous;//课程信息链表
Cog_link cogs;//课程成绩链表
All_link alls;//所有信息链表
All_link apoi_stu_alls;//函数8中存放指定课程号的所有学生的链表
All_link apoi_stu_alls2;//函数9中存放成绩小于60的学生的链表

//函数声明
int read_line(char str[], int n);//按行读取字符并以字符串形式储存
int init(void);//初始化链表（置空，加头结点）
int choose(void);//选择功能
int pri_stu(Stu_link *stus);//打印学生链表
int pri_cou(Cou_link *cous);//打印课程链表
int pri_cog(Cog_link *cogs);//打印课程成绩信息链表
int pri_all(All_link *alls);//打印所有信息链表
int sor_stu_sno(Stu_link *stus);//将学生链表根据学号排序，输入为链表结构地址
int sor_cou_cno(Cou_link *cous);//课程信息排序
int sor_cog_sno_cno(Cog_link *cogs);//课程成绩信息排序
int sor_all_sco(All_link *alls);//所有信息排序
int sor_ap_stu_sco(All_link *ap_alls);//将搜索到的链表按成绩排序
int wri_all(All_link *alls);//将alls信息链表存入文件
int fun4(void);//选4时
int fun5(void);//选5时
int fun6(void);//选6时
int fun7(void);//选7时
int fun8(void);//选8时
int fun9(void);//选9时


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
	memset(&stus, 0, sizeof(Stu_link));
	memset(&cous, 0, sizeof(Cou_link));
	memset(&cogs, 0, sizeof(Cog_link));
	memset(&alls, 0, sizeof(All_link));
	memset(&apoi_stu_alls, 0, sizeof(All_link));
	memset(&apoi_stu_alls2, 0, sizeof(All_link));

	Stu_node *new_stu = (Stu_node*)malloc(sizeof(Stu_node));
	memset(new_stu, 0, sizeof(Stu_node));
	stus.head = new_stu;
	Cou_node *new_cou = (Cou_node*)malloc(sizeof(Cou_node));
	memset(new_cou, 0, sizeof(Cou_node));
	cous.head = new_cou;
	Cog_node *new_cog = (Cog_node*)malloc(sizeof(Cog_node));
	memset(new_cog, 0, sizeof(Cog_node));
	cogs.head = new_cog;

	All_node *new_all = (All_node*)malloc(sizeof(All_node));
	memset(new_all, 0, sizeof(All_node));
	alls.head = new_all;

	new_all = (All_node*)malloc(sizeof(All_node));
	memset(new_all, 0, sizeof(All_node));
	apoi_stu_alls.head = new_all;

	new_all = (All_node*)malloc(sizeof(All_node));
	memset(new_all, 0, sizeof(All_node));
	apoi_stu_alls2.head = new_all;

	return 1;
}

int choose(void) {
	int cho = 0;
	scanf("%d", &cho);
	return cho;
}

int pri_stu(Stu_link *stus) {
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

int pri_cou(Cou_link *cous) {
	Cou_node *p = cous->head;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	while (p->next != NULL) {
		printf("课程号:%d\t课程名%s\t课时%d\n",
			p->data.cno,
			p->data.cname,
			p->data.classHours);

		p = p->next;
	}

	return 1;
}

int pri_cog(Cog_link *cogs) {
	Cog_node *p = cogs->head;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	while (p->next != NULL) {
		printf("学号:%d\t课程号%d\t成绩%d\n",
			p->data.sno,
			p->data.cno,
			p->data.score);

		p = p->next;
	}

	return 1;
}

int pri_all(All_link *alls) {
	All_node *p = alls->head;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	while (p->next != NULL) {
		printf("学号:%d\t姓名:%s\t专业:%s\t课程号:%d\t课程名称%s\t成绩%d\n",
			p->data.sno,
			p->data.sname,
			p->data.major,
			p->data.cno,
			p->data.cname,
			p->data.score
			);

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
	if ((0 == stus->size) || (1 == stus->size)) {//空链表或者只有一个元素
		if (0 == stus->size)
			printf("链表为空\n");
		if (1 == stus->size)
			printf("链表只有一个结点，无需排序\n");
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

int sor_cou_cno(Cou_link *cous) {
	Cou_node *p = cous->head, *q = p->next;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	if ((0 == cous->size) || (1 == cous->size)) {//空链表或者只有一个元素
		if (0 == cous->size)
			printf("链表为空\n");
		if (1 == cous->size)
			printf("链表只有一个结点，无需排序\n");
		return 1;
	}
	//检测、交换
	S_cou temp;
	int i = 0, j = 0;
	for (i = 0; i < cous->size - 1; i++) {
		for (j = 0; j < cous->size - i - 1; j++) {
			if (p->data.cno > q->data.cno) {
				temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
			p = q;
			q = q->next;
		}
		p = cous->head;
		q = p->next;
	}



	return 1;
}

int sor_cog_sno_cno(Cog_link *cogs) {
	Cog_node *p = cogs->head, *q = p->next;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	if ((0 == cogs->size) || (1 == cogs->size)) {//空链表或者只有一个元素
		if (0 == cogs->size)
			printf("链表为空\n");
		if (1 == cogs->size)
			printf("链表只有一个结点，无需排序\n");
		return 1;
	}
	//检测、交换
	S_cog temp;
	int i = 0, j = 0;
	for (i = 0; i < cogs->size - 1; i++) {//课程号排序
		for (j = 0; j < cogs->size - i - 1; j++) {
			if (p->data.sno > q->data.sno) {
				temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
			p = q;
			q = q->next;
		}
		p = cogs->head;
		q = p->next;
	}

	for (i = 0; i < cogs->size - 1; i++) {//课程号排序
		for (j = 0; j < cogs->size - i - 1; j++) {
			if (p->data.sno == q->data.sno) {//学号相同则比较课程号大小
				if (p->data.cno > q->data.cno) {
					temp = q->data;
					q->data = p->data;
					p->data = temp;
				}
			}
			p = q;
			q = q->next;
		}
		p = cogs->head;
		q = p->next;
	}

	return 1;
}

int sor_all_sco(All_link *alls) {//降序排序
	All_node *p = alls->head, *q = p->next;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	if ((0 == alls->size) || (1 == alls->size)) {//空链表或者只有一个元素
		if (0 == alls->size)
			printf("链表为空\n");
		if (1 == alls->size)
			printf("链表只有一个结点，无需排序\n");
		return 1;
	}
	//检测、交换
	S_all temp;
	int i = 0, j = 0;
	for (i = 0; i < alls->size - 1; i++) {
		for (j = 0; j < alls->size - i - 1; j++) {
			if (p->data.score < q->data.score) {
				temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
			p = q;
			q = q->next;
		}
		p = alls->head;
		q = p->next;
	}

	printf("学生成绩链表建立完毕，共%d条信息\n\n", alls->size);

	return 1;
}

int sor_ap_stu_sco(All_link *ap_alls) {
	All_node *p = ap_alls->head, *q = p->next;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}
	if ((0 == ap_alls->size) || (1 == ap_alls->size)) {//空链表或者只有一个元素
		if (0 == ap_alls->size)
			printf("链表为空\n");
		if (1 == ap_alls->size)
			printf("链表只有一个结点，无需排序\n");
		return 1;
	}
	//检测、交换
	S_all temp;
	int i = 0, j = 0;
	for (i = 0; i < ap_alls->size - 1; i++) {
		for (j = 0; j < ap_alls->size - i - 1; j++) {
			if (p->data.score < q->data.score) {
				temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
			p = q;
			q = q->next;
		}
		p = ap_alls->head;
		q = p->next;
	}

	printf("降序排序已完成\n\n");

	return 1;
}

int wri_all(All_link *alls) {
	//写入文件
	FILE *fp = fopen("studentGrade.txt", "r");//确保文件存在，不存在则创建一个
	if (NULL == fp)
		printf("studentGrade.txt文件不存在，为您新建一个\n");
	fclose(fp);

	fp = fopen("studentGrade.txt", "w");

	All_node *p = alls->head;
	int written = 0;
	if (NULL == p) {
		printf("链表故障\n");
		return 0;
	}

	while (NULL != p->next) {
		fprintf(fp, "%d\t%s\t%s\t%d\t%s\t%d\n",
			p->data.sno,
			p->data.sname,
			p->data.major,
			p->data.cno,
			p->data.cname,
			p->data.score
		);

		written++;

		p = p->next;
	}
	printf("写入文件成功，写入%d条信息\n\n", written);

	fclose(fp);
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
	printf("学生信息链表已建立，共%d条记录\n\n", stus.size);
	//排序并输出
	sor_stu_sno(&stus);
	pri_stu(&stus);
	return 1;
}

int fun5(void) {
	//读取文件并建立链表
	FILE *fp = fopen("course.txt", "r");
	if (NULL == fp) {//错误情况处理
		printf("打开课程信息文件失败\n");
		return 0;
	}
	while (!feof(fp)) {
		Cou_node *new_cou = (Cou_node*)malloc(sizeof(Cou_node));//新结点
		memset(new_cou, 0, sizeof(Cou_node));
		fscanf(fp, "%d", &new_cou->data.cno);
		fscanf(fp, " \t%s", new_cou->data.cname);
		fscanf(fp, " \t%d\n", &new_cou->data.classHours);
		new_cou->next = cous.head;
		cous.head = new_cou;
		cous.size++;
	}
	printf("课程信息链表已建立，共%d条记录\n\n", cous.size);
	//排序并输出
	sor_cou_cno(&cous);
	pri_cou(&cous);
	return 1;
}

int fun6(void) {
	//读取文件并建立链表
	FILE *fp = fopen("courseGrade.txt", "r");
	if (NULL == fp) {//错误情况处理
		printf("打开课程成绩信息文件失败\n");
		return 0;
	}
	while (!feof(fp)) {
		Cog_node *new_cog = (Cog_node*)malloc(sizeof(Cog_node));//新结点
		memset(new_cog, 0, sizeof(Cog_node));
		fscanf(fp, "%d", &new_cog->data.sno);
		fscanf(fp, " \t%d", &new_cog->data.cno);
		fscanf(fp, " \t%d\n", &new_cog->data.score);
		new_cog->next = cogs.head;
		cogs.head = new_cog;
		cogs.size++;
	}
	printf("课程成绩信息链表已建立，共%d条记录\n\n", cogs.size);
	//排序并输出
	sor_cog_sno_cno(&cogs);
	pri_cog(&cogs);

	return 1;
}

int fun7(void) {
	fun4();//建立三个链表
	fun5();
	fun6();

	Stu_node *p = stus.head;//定义操作四个链表的指针
	Cou_node *q = cous.head;
	Cog_node *r = cogs.head;
	All_node *s = alls.head;

	while (NULL != p->next) {//遍历学生信息链表
		while (1) {
			//进行到一个学生的所有课程信息都录入完成
			All_node *new_all = (All_node*)malloc(sizeof(All_node));//分配结点空间
			if (NULL == new_all) {
				printf("分配空间失败\n");
				return 0;
			}
			memset(new_all, 0, sizeof(All_node));

			new_all->data.sno = p->data.sno;//从学生信息链表读入三个信息(该循环中学生信息不变）
			strcpy(new_all->data.sname, p->data.sname);
			strcpy(new_all->data.major, p->data.major);

			//搜索并读入一行信息（课程名称和成绩）
			while ((r->data.sno != p->data.sno) && (NULL != r->next))//根据当前学号找到对应的成绩和课程号
				r = r->next;
			if (NULL == r->next)
				break;
			new_all->data.score = r->data.score;
			int cur_cno;
			cur_cno = r->data.cno;

			new_all->data.cno = cur_cno;

			while ((q->data.cno != cur_cno) && (NULL != q->next))//根据当前课程号找到对应的课程名称
				q = q->next;
			if (NULL == q->next)
				break;
			strcpy(new_all->data.cname, q->data.cname);

			new_all->next = alls.head;//插入结点
			alls.head = new_all;

			alls.size++;//4.19.9:32增加

			q = q->next;
			r = r->next;
			
		}
		p = p->next;//下一个学生
		q = cous.head;
		r = cogs.head;
	}
	sor_all_sco(&alls);


	pri_all(&alls);


	return 1;
}

int fun8(void) {
	fun7();

	printf("\n");

	int key;
	printf("输入要搜索的课程号:");
	scanf("%d", &key);
	printf("\n正在搜索中......请稍后~\n\n");

	All_node *p = alls.head;
	while (NULL != p->next) {
		if (p->data.cno == key) {
			All_node *new_all = (All_node*)malloc(sizeof(All_node));
			memset(new_all, 0, sizeof(All_node));

			new_all->data = p->data;

			new_all->next = apoi_stu_alls.head;//插入结点
			apoi_stu_alls.head = new_all;

			apoi_stu_alls.size++;
		}

		p = p->next;
	}
	printf("课程号为%d的学生成绩信息链表已经建立，共%d条信息\n\n", key, apoi_stu_alls.size);

	sor_ap_stu_sco(&apoi_stu_alls);

	pri_all(&apoi_stu_alls);

	return 1;
}

int fun9(void) {
	fun7();

	printf("\n");

	int key = 60;

	All_node *p = alls.head;
	while (NULL != p->next) {
		if (p->data.score < key) {
			All_node *new_all = (All_node*)malloc(sizeof(All_node));
			memset(new_all, 0, sizeof(All_node));

			new_all->data = p->data;

			new_all->next = apoi_stu_alls2.head;//插入结点
			apoi_stu_alls2.head = new_all;

			apoi_stu_alls2.size++;
		}

		p = p->next;
	}
	printf("成绩低于%d的学生成绩信息链表已经建立，共%d条信息\n\n", key, apoi_stu_alls2.size);

	sor_ap_stu_sco(&apoi_stu_alls2);

	pri_all(&apoi_stu_alls2);

	return 1;
}



int menu(void) {
	printf("---------------------------------------------------------------\n");
	printf("                         学生课程成绩查询系统\n");

	printf("4.建立学生链表\n");
	printf("5.建立课程链表\n");
	printf("6.建立成绩链表\n");
	printf("7.查询所有信息\n");
	printf("8.查询指定成绩\n");
	printf("9.小于60分学生\n");
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
		if (5 == cho) {
			fun5();
			break;
		}
		if (6 == cho) {
			fun6();
			break;
		}
		if (7 == cho) {
			fun7();
			wri_all(&alls);
			break;
		}
		if (8 == cho) {
			fun8();
			break;
		}
		if (9 == cho) {
			fun9();
			break;
		}

		//不保存退出
		//保存退出
		//其他函数实现

	}

	//结束循环

	return 0;
}

