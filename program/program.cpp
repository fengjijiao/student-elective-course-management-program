//题目：假定有n门课程，每门课程有课程编号，课程名称，课程性质，总学时，授课学时，实验学时，学分，开课学期等信息。试设计一选修课程系统。
//维护人员账号abc密码123
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
typedef struct Course {
    int number;
    char Name[50];
    char character[100];
    double sumtime;
    double teachtime;
    double testtime;
    double score;
    char term[50];
    struct Course *next;
} CS;
typedef struct Student {
	char Name[50];
    char Username[16];
    char Password[16];
    int CourseNumber;
    struct Student *next;
} ST;
char *Course_Data_file_location="CourseData.txt";
char *Student_Data_file_location="StudentData.txt";
int AdminFlag=1,MainFlag=1,StudentFlag=1;
CS *Course_Data_head=NULL;//头部声明及初始化
ST *Student_Data_head=NULL,*Current_Student_Ptr=NULL;
//将数据从文件中读取并生成单链表,返回头指针
CS *Course_data_read(){
    FILE *fp;
    CS *Course_Data_head=(CS *)malloc(sizeof(CS));//创建头指针
    if(!Course_Data_head){
        printf("创建头指针失败!\n");
        return NULL;
    }
    Course_Data_head->next=NULL;//将头指针next置为NULL
    CS *Course_Data_last=Course_Data_head;//创建最后的一条数据指针
    if((fp=fopen(Course_Data_file_location,"r"))!=NULL){//判断是否存在数据文件,存在则打开
        while(!feof(fp)){//当文件读完时结束循环
            CS *Course_Data_next=(CS *)malloc(sizeof(CS));
            if(!Course_Data_next){
                printf("创建新结点失败!\n");
                return NULL;
            }
            fscanf(fp,"%d\t%s\t%s\t%lf\t%lf\t%lf\t%lf\t%s\t",&Course_Data_next->number,Course_Data_next->Name,Course_Data_next->character,&Course_Data_next->sumtime,&Course_Data_next->teachtime,&Course_Data_next->testtime,&Course_Data_next->score,Course_Data_next->term);
            Course_Data_next->next=Course_Data_last->next;//在最后记录的next指向新读取的数据
            Course_Data_last->next=Course_Data_next;//将最后记录更新为新添加的结点
            Course_Data_last=Course_Data_last->next;//将last指向最新的节点
        }
        fclose(fp);//读取结束释放内存
    }
    return Course_Data_head;
}
//将数据写入文件
void Course_data_write(CS * Course_Data_head){
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    FILE *fp=fopen(Course_Data_file_location,"w");
    int sum=0;//总数初始化
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        fprintf(fp,"%d\t%s\t%s\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%s\t\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
        sum++;
    }
    fclose(fp);
    printf("保存完成,共%d条！\n",sum);
    if(sum==0){
        printf("未找到任何课程信息！\n");
    }
}
//将数据从文件中读取并生成单链表,返回头指针
ST *Student_data_read(){
    FILE *fp;
    ST *Student_Data_head=(ST *)malloc(sizeof(ST));//创建头指针
    if(!Student_Data_head){
        printf("创建头指针失败!\n");
        return NULL;
    }
    Student_Data_head->next=NULL;//将头指针next置为NULL
    ST *Student_Data_last=Student_Data_head;//创建最后的一条数据指针
    if((fp=fopen(Student_Data_file_location,"r"))!=NULL){//判断是否存在数据文件,存在则打开
        while(!feof(fp)){//当文件读完时结束循环
            ST *Student_Data_next=(ST *)malloc(sizeof(ST));
            if(!Student_Data_next){
                printf("创建新结点失败!\n");
                return NULL;
            }
            fscanf(fp,"%s\t%s\t%s\t%d\t",Student_Data_next->Name,Student_Data_next->Username,Student_Data_next->Password,&Student_Data_next->CourseNumber);
            Student_Data_next->next=Student_Data_last->next;//在最后记录的next指向新读取的数据
            Student_Data_last->next=Student_Data_next;//将最后记录更新为新添加的结点
            Student_Data_last=Student_Data_last->next;//将last指向最新的节点
        }
        fclose(fp);//读取结束释放内存
    }
    return Student_Data_head;
}
//将数据写入文件
void Student_data_write(ST * Student_Data_head){
    ST *Student_Data_last=Student_Data_head;//创建新指针指向头指针
    FILE *fp=fopen(Student_Data_file_location,"w");
    int sum=0;//总数初始化
    while(Student_Data_last->next != NULL){
        Student_Data_last=Student_Data_last->next;
        fprintf(fp,"%s\t%s\t%s\t%d\t\n",Student_Data_last->Name,Student_Data_last->Username,Student_Data_last->Password,Student_Data_last->CourseNumber);
        sum++;
    }
    fclose(fp);
    printf("保存完成,共%d条！\n",sum);
    if(sum==0){
        printf("未找到任何学生信息！\n");
    }
}
//查重函数,通过ID
int RepitationByID(int id){
    int AdminFlag=1;
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        if(Course_Data_last->number ==	id){
            AdminFlag=0;
            break;
        }
    }
    return AdminFlag;
}
//查重函数,通过名称
int RepitationByName(char name[]){
    int AdminFlag=1;
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        if(!strcmp(Course_Data_last->Name,name)){
            AdminFlag=0;
            break;
        }
    }
    return AdminFlag;
}
//统计课程总数
int Course_Length(){
    int sum=0;
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        sum++;
    }
    return sum;
}
//统计学生总数
int Student_Length(){
    int sum=0;
    ST *Student_Data_last=Student_Data_head;//创建新指针指向头指针
    while(Student_Data_last->next != NULL){
        Student_Data_last=Student_Data_last->next;
        sum++;
    }
    return sum;
}
//统计课程被选总数
int Course_selected_Length(int Number){
    int sum=0;
    ST *Student_Data_last=Student_Data_head;//创建新指针指向头指针
    while(Student_Data_last->next != NULL){
        Student_Data_last=Student_Data_last->next;
        if(Student_Data_last->CourseNumber == Number) sum++;
    }
    return sum;
}
//统计课程未选总数
int Course_Unselected_Length(){
    int sum=0;
    ST *Student_Data_last=Student_Data_head;//创建新指针指向头指针
    while(Student_Data_last->next != NULL){
        Student_Data_last=Student_Data_last->next;
        if(Student_Data_last->CourseNumber == 0) sum++;
    }
    return sum;
}
//课程信息查询,返回课程编号
int Search_Course_Name_to_Number(char Name[]){
	CS *Course_Data_last=Course_Data_head;
    while(Course_Data_last->next != NULL){
		Course_Data_last=Course_Data_last->next;
        if(!strcmp((Course_Data_last->Name),Name)){
			return Course_Data_last->number;
            break;
        }
    }
    return 0;
}
//课程信息查询,返回指针
CS *Search_Courese_Info(int number){
	if(number==0) return NULL;
	CS *Course_Data_last=Course_Data_head;
    while(Course_Data_last->next != NULL){
		Course_Data_last=Course_Data_last->next;
        if((Course_Data_last->number) == number){
			return Course_Data_last;
            break;
        }
    }
    return NULL;
}
//课程信息查询,Only Current Student,返回课程名称
void Search_Course_Current_Student_to_Name(char *name){
	CS *Current_Course_Info=NULL;
	if((Current_Course_Info=Search_Courese_Info(Current_Student_Ptr->CourseNumber))==NULL){
	    strcpy(name,"未选择");
	}else{
		strcpy(name,Current_Course_Info->Name);
	}
}
//课程信息查询,返回课程名称
void Search_Course_Student_to_Name(int CourseNumber,char *name){
	CS *Current_Course_Info=NULL;
	if((Current_Course_Info=Search_Courese_Info(CourseNumber))==NULL){
	    strcpy(name,"未选择");
	}else{
		strcpy(name,Current_Course_Info->Name);
	}
}
void Course_Add(){
	system("cls");//清屏
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    CS *another=(CS *)malloc(sizeof(CS));
    printf("请按提示输入要添加的课程信息：\n");
    Course_Addreinputid:printf("课程编号:\n");
    scanf("%d",&another->number);
	if(another->number<=0){
	    printf("课程编号只允许为非负整数！\n");
        goto Course_Addreinputid;
	}
    if(!RepitationByID(another->number)){
        printf("该课程编号已存在！\n");
        goto Course_Addreinputid;
    }
    Course_Addreinputname:printf("课程名称:\n");
    scanf("%s",another->Name);
    if(!RepitationByName(another->Name)){
        printf("该课程名称已存在！\n");
        goto Course_Addreinputname;
    }
    printf("课程性质:\n");
    scanf("%s",another->character);
    printf("总学时:\n");
    scanf("%lf",&another->sumtime);
    printf("授课学时:\n");
    scanf("%lf",&another->teachtime);
    printf("实验学时:\n");
    scanf("%lf",&another->testtime);
    printf("学分:\n");
    scanf("%lf",&another->score);
    printf("开课学期:\n");
    scanf("%s",another->term);
    another->next=NULL;
    while(Course_Data_last->next != NULL){//直到最后一个节点
        Course_Data_last=Course_Data_last->next;
    }
    Course_Data_last->next=another;//将最后一个节点next指向新节点
    Course_data_write(Course_Data_head);
    printf("添加成功！\n");
}
void Course_Find(char key_type){
	system("cls");//清屏
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    if(key_type=='1'){//按课程编号查询
        int number;
        printf("请输入要查找的课程编号：\n");
        scanf("%d",&number);
        int sum=0;//总数初始化
        printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\n");
        while(Course_Data_last->next != NULL){//直到next为空时结束循环
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->number == number){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("未找到包含该课程编号的信息！\n");
        }
    }else if(key_type=='2'){
        char Name[50];
        printf("请输入要查找的课程名称：\n");
        scanf("%s",Name);
        int sum=0;//总数初始化
        printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\n");
        while(Course_Data_last->next != NULL){//直到next为空时结束循环
            Course_Data_last=Course_Data_last->next;
            if(!strcmp(Course_Data_last->Name,Name)){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("未找到包含该课程名称的信息！\n");
        }
    }else if(key_type=='3'){
        char character[100];
        printf("请输入要查找的课程性质：\n");
        scanf("%s",character);
        int sum=0;//总数初始化
        printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\n");
        while(Course_Data_last->next != NULL){//直到next为空时结束循环
            Course_Data_last=Course_Data_last->next;
            if(!strcmp(Course_Data_last->character,character)){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("未找到包含该课程性质的信息！\n");
        }
    }else if(key_type=='4'){
        double sumtime;
        printf("请输入要查找的总学时：\n");
        scanf("%lf",&sumtime);
        int sum=0;//总数初始化
        printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\n");
        while(Course_Data_last->next != NULL){//直到next为空时结束循环
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->sumtime == sumtime){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("未找到包含该总学时的信息！\n");
        }
    }else if(key_type=='5'){
        double teachtime;
        printf("请输入要查找的授课学时：\n");
        scanf("%lf",&teachtime);
        int sum=0;//总数初始化
        printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\n");
        while(Course_Data_last->next != NULL){//直到next为空时结束循环
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->teachtime == teachtime){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("未找到包含该授课学时的信息！\n");
        }
    }else if(key_type=='6'){
        double testtime;
        printf("请输入要查找的实验学时：\n");
        scanf("%lf",&testtime);
        int sum=0;//总数初始化
        printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\n");
        while(Course_Data_last->next != NULL){//直到next为空时结束循环
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->testtime == testtime){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("未找到包含该实验学时的信息！\n");
        }
    }else if(key_type=='7'){
        double score;
        printf("请输入要查找的学分：\n");
        scanf("%lf",&score);
        int sum=0;//总数初始化
        printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\n");
        while(Course_Data_last->next != NULL){//直到next为空时结束循环
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->score == score){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("未找到包含该学分的信息！\n");
        }
    }else if(key_type=='8'){
        char term[50];
        printf("请输入要查找的开课学期：\n");
        scanf("%s",term);
        int sum=0;//总数初始化
        printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\n");
        while(Course_Data_last->next != NULL){//直到next为空时结束循环
            Course_Data_last=Course_Data_last->next;
            if(!strcmp(Course_Data_last->term,term)){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("未找到包含该开课学期的信息！\n");
        }
    }else{
        printf("找不到指令,请重新输入！\n");
    }
}
void Course_Modify(){
	system("cls");//清屏
    char subCourse_Modify,Name[50],character[100],term[50];
    double sumtime,testtime,teachtime,score;
    int number,sum=0;
	ST *Student_Data_last=NULL;
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    printf("请输入要修改的课程名称:\n");
    scanf("%s",Name);
    while(Course_Data_last->next != NULL && strcmp(Course_Data_last->Name,Name)){
        Course_Data_last=Course_Data_last->next;
    }
    if(strcmp(Course_Data_last->Name,Name)){
        printf("该课程不存在!\n");
    }else{
        printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
        printf("＊　　　　　  　修改课程信息  　　　　　＊\n");
        printf("＊--------------------------------------＊\n");
        printf("＊--------------选择修改类型------------＊\n");
        printf("＊--------------------------------------＊\n");
        printf("＊　　　　　　　1.课程编号　　　　　　　＊\n");
        printf("＊　　　　　　　2.课程名称　　　　　　　＊\n");
        printf("＊　　　　　　　3.课程性质　　　　　　　＊\n");
        printf("＊　　　　　　　4.总学时  　　　　　　　＊\n");
        printf("＊　　　　　　　5.授课学时　　　　　　　＊\n");
        printf("＊　　　　　　　6.实验学时　　　      　＊\n");
        printf("＊　　　　　　　7.学分    　　　　　　　＊\n");
        printf("＊　　　　　　　8.开课学期　　　　　　　＊\n");
        printf("＊--------------------------------------＊\n");
        printf("＊　　　　　　　0.返回      　　　　　　＊\n");
        printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
        submd:subCourse_Modify=getch();
        printf("您输入了：%c\n",subCourse_Modify);
        switch(subCourse_Modify){
            case '1':
                printf("原课程编号:%d\n",Course_Data_last->number);
            Course_Addreinputidb:printf("请输入新的课程编号:\n");
                scanf("%d",&number);
				if(number<=0){
				    printf("课程编号只允许为非负整数！\n");
                    goto Course_Addreinputidb;
				}
                if(!RepitationByID(number)){
                    printf("该课程编号已存在！\n");
                    goto Course_Addreinputidb;
                }
                Course_Data_last->number=number;
                Course_data_write(Course_Data_head);//保存数据到文件
                Student_Data_last=Student_Data_head;//创建新指针指向头指针
                while(Student_Data_last->next != NULL){
                    Student_Data_last=Student_Data_last->next;
                    if(Student_Data_last->CourseNumber == number){
						Student_Data_last->CourseNumber=number;
						sum++;
					}
                }
				Student_data_write(Student_Data_head);
                printf("修改成功,已同步%d次!\n",sum);
                break;
            case '2':
                printf("原课程名称:%s\n",Course_Data_last->Name);
            Course_Addreinputnameb:printf("请输入新的课程名称:\n");
                scanf("%s",Name);
                if(!RepitationByName(Name)){
                    printf("该课程名称已存在！\n");
                    goto Course_Addreinputnameb;
                }
                strcpy(Course_Data_last->Name,Name);
                Course_data_write(Course_Data_head);//保存数据到文件
                printf("修改成功!\n");
                break;
            case '3':
                printf("原课程性质:%s\n",Course_Data_last->character);
                printf("请输入新的课程性质:\n");
                scanf("%s",character);
                strcpy(Course_Data_last->character,character);
                Course_data_write(Course_Data_head);//保存数据到文件
                printf("修改成功!\n");
                break;
            case '4':
                printf("原总学时:%lf\n",Course_Data_last->sumtime);
                printf("请输入新的总学时:\n");
                scanf("%lf",&sumtime);
                Course_Data_last->sumtime=sumtime;
                Course_data_write(Course_Data_head);//保存数据到文件
                printf("修改成功!\n");
                break;
            case '5':
                printf("原授课学时:%lf\n",Course_Data_last->teachtime);
                printf("请输入新的授课学时:\n");
                scanf("%lf",&teachtime);
                Course_Data_last->teachtime=teachtime;
                Course_data_write(Course_Data_head);//保存数据到文件
                printf("修改成功!\n");
                break;
            case '6':
                printf("原实验学时:%lf\n",Course_Data_last->testtime);
                printf("请输入新的实验学时:\n");
                scanf("%lf",&testtime);
                Course_Data_last->testtime=testtime;
                Course_data_write(Course_Data_head);//保存数据到文件
                printf("修改成功!\n");
                break;
            case '7':
                printf("原学分:%lf\n",Course_Data_last->score);
                printf("请输入新的学分:\n");
                scanf("%lf",&score);
                Course_Data_last->score=score;
                Course_data_write(Course_Data_head);//保存数据到文件
                printf("修改成功!\n");
                break;
            case '8':
                printf("原开课学期:%s\n",Course_Data_last->term);
                printf("请输入新的开课学期:\n");
                scanf("%s",term);
                strcpy(Course_Data_last->term,term);
                Course_data_write(Course_Data_head);//保存数据到文件
                printf("修改成功!\n");
                break;
            case '0':
                printf("返回操作已完成！\n");
                break;
            default:
                printf("找不到指令,请重新输入！\n");
                goto submd;//指令错误,重新返回提示指令操作
                break;
        };
    }
}
void Course_PrintList(){
	system("cls");//清屏
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    int sum=0;//总数初始化
    printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t学分\t开课学期\t选修人数\n");
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\t%8d\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term,Course_selected_Length(Course_Data_last->number));
        sum++;
    }
    if(sum>0){
        printf("课程总数:%d条,学生总数:%d人,未选人数:%d人\n",Course_Length(),Student_Length(),Course_Unselected_Length());
    }else{
        printf("未找到任何课程信息！\n");
    }
}
void Course_Delete(){
	system("cls");//清屏
    CS *Course_Data_last=Course_Data_head;//创建新指针指向头指针
    char Name[50];
    int sum=0,ssum=0;
    printf("请输入要删除的课程名称:\n");
    scanf("%s",Name);
    while(Course_Data_last->next != NULL){
        if(!strcmp(Course_Data_last -> next -> Name,Name)){
            ST *Student_Data_last=Student_Data_head;//创建新指针指向头指针
            while(Student_Data_last->next != NULL){
                Student_Data_last=Student_Data_last->next;
                if(Student_Data_last->CourseNumber == Course_Data_last -> next -> number){
			        Student_Data_last->CourseNumber=0;
				    ssum++;
			    }
            }
            CS *p=Course_Data_last->next;
            Course_Data_last->next=Course_Data_last->next->next;
            p->next=NULL;
            free(p);
            sum++;
            break;
        }
        Course_Data_last=Course_Data_last->next;
    }
    if(sum>0){
        Course_data_write(Course_Data_head);//保存数据到文件
		Student_data_write(Student_Data_head);
        printf("删除成功,同步将%d名学生选修情况置为未选!\n",ssum);
    }else{
        printf("该课程不存在!\n");
    }
}
//学生选课情况
void Course_Situaction(){
	system("cls");//清屏
	char name[50];
	ST *Student_Data_last = Student_Data_head;
	//int Course_Everyone_Sum[Course_Length()];
	printf("学生姓名\t选修课程\t\n");
	while(Student_Data_last->next!=NULL){
		Student_Data_last=Student_Data_last->next;
		Search_Course_Student_to_Name(Student_Data_last->CourseNumber,name);
		printf("%8s\t%8s\t\n",Student_Data_last->Name,name);
	}
}
//维护人员权限检查
int AdminPermissionCheck(){
	system("cls");//清屏
	char username[16],password[16],ch;
	printf("请输入账号:\n");
	scanf("%s",username);
	printf("请输入密码:\n");
	int i=0;
	while(((ch=getch())!=13)&&i<16){//13为回车ascil
		password[i]=ch;
		putchar('*');
		i++;
	}
	putchar('\n');
	if(!strcmp(username,"abc")&&!strcmp(password,"123")){
		 return 1;
	}else{
		 printf("账号或密码错误!\n");
		 return 0;
	}
}
//学生权限检查核心
int StudentPermissionCheckCore(char username[],char password[]){
	ST *Student_Data_last = Student_Data_head;
	int isfound=0;
	while(Student_Data_last->next!=NULL && !isfound){
		Student_Data_last=Student_Data_last->next;
		if(!strcmp(Student_Data_last->Username,username)&& !strcmp(Student_Data_last->Password,password)){
			Current_Student_Ptr=Student_Data_last;
			isfound++;
		}
	}
	return isfound;
}
//学生权限检查
int StudentPermissionCheck(){
	system("cls");//清屏
	char username[16],password[16],ch;
	printf("请输入账号:\n");
	scanf("%s",username);
	printf("请输入密码:\n");
	int i=0;
	while(((ch=getch())!=13)&&i<16){//13为回车ascil
		password[i]=ch;
		putchar('*');
		i++;
	}
	putchar('\n');
	if(StudentPermissionCheckCore(username,password)){
		 return 1;
	}else{
		 printf("账号或密码错误!\n");
		 return 0;
	}
}
//维护
void Admin(){
	system("cls");//清屏
    while (AdminFlag) {
        char AdminDemand,subAdminDemand;
        printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
        printf("＊　　　　　　选修课程管理系统        　＊\n");
        printf("＊--------------------------------------＊\n");
        printf("＊--------------选择相关操作------------＊\n");
        printf("＊--------------------------------------＊\n");
        printf("＊　　　　　　　1.添加课程　　　　　　　＊\n");
        printf("＊　　　　　　　2.查找课程　　　　　　　＊\n");
        printf("＊　　　　　　　3.修改课程　　　　　　　＊\n");
        printf("＊　　　　　　　4.查看课程　　　　　　　＊\n");
        printf("＊　　　　　　　5.删除课程　　　　　　　＊\n");
		printf("＊　　　　　　　6.学生选修情况　　　　　＊\n");
        printf("＊--------------------------------------＊\n");
        printf("＊　　　　　　　0.退出维护系统　　　　　＊\n");
        printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
        topAD:AdminDemand = getch();
        printf("您输入了：%c\n", AdminDemand);
        switch (AdminDemand) {
            case '1':
                Course_Add();
                break;
            case '2':
                printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
                printf("＊　　　　　　　　查询课程　　　　　　　＊\n");
                printf("＊--------------------------------------＊\n");
                printf("＊--------------选择查询类型------------＊\n");
                printf("＊--------------------------------------＊\n");
                printf("＊　　　　　　　1.课程编号　　　　　　　＊\n");
                printf("＊　　　　　　　2.课程名称　　　　　　　＊\n");
                printf("＊　　　　　　　3.课程性质　　　　　　　＊\n");
                printf("＊　　　　　　　4.总学时  　　　　　　　＊\n");
                printf("＊　　　　　　　5.授课学时　　　　　　　＊\n");
                printf("＊　　　　　　　6.实验学时　　　　      ＊\n");
                printf("＊　　　　　　　7.学分    　　　　　　　＊\n");
                printf("＊　　　　　　　8.开课学期　　　　　　　＊\n");
                printf("＊--------------------------------------＊\n");
                printf("＊　　　　　　　0.返回            　　　＊\n");
                printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
            subAD:subAdminDemand = getch();
                printf("您输入了：%c\n", subAdminDemand);
                switch (subAdminDemand) {
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                        Course_Find(subAdminDemand);
                        break;
                    case '0':
                        printf("返回操作已完成！\n");
                        break;
                    default:
                        printf("找不到指令,请重新输入！\n");
                        goto subAD;//指令错误,重新返回提示指令操作
                        break;
                };
                break;
            case '3':
                Course_Modify();
                break;
            case '4':
                Course_PrintList();
                break;
            case '5':
                Course_Delete();
                break;
			case '6':
				Course_Situaction();
				break;
            case '0':
                AdminFlag = 0;
                free(Course_Data_head);//通用释放内存
                Course_Data_head = NULL;
                printf("退出操作已完成！\n");
                break;
            default:
                printf("找不到指令,请重新输入！\n");
                goto topAD;//指令错误,重新返回提示指令操作
                break;
        };
    }
}
//学生修改选课
void Student_Course_Modify(){
	system("cls");//清屏
	char Name[50];
	int number=0;
	printf("请输入要选择的课程名称:\n");
	scanf("%s",Name);
	if(!(number=Search_Course_Name_to_Number(Name))){
		printf("课程不存在!\n");
	}else{
		Current_Student_Ptr->CourseNumber=number;
		Student_data_write(Student_Data_head);
		printf("修改成功!\n");
	}
}
//选课
void Student(){
	char StudentDemand,Current_Course_Name[50];
	while (StudentFlag) {
	Search_Course_Current_Student_to_Name(Current_Course_Name);//将单前学生课程名称返回
	printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
    printf("＊　　　　　  学生选修课程系统        　＊\n");
    printf("＊--------------------------------------＊\n");
    printf("＊--------------选择相关操作------------＊\n");
    printf("＊--------------------------------------＊\n");
	printf("＊%s%-29s＊\n","当前选课:",Current_Course_Name);
    printf("＊　　　　　　　1.查看可选课程　　　　　＊\n");
	printf("＊　　　　　　　2.修改选修课程　　　　　＊\n");
    printf("＊--------------------------------------＊\n");
    printf("＊　　　　　　　0.退出　　　　　　　　　＊\n");
    printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
	topSD:StudentDemand = getch();
    printf("您输入了：%c\n", StudentDemand);
    switch (StudentDemand){
	case '1':
		Course_PrintList();
		break;
	case '2':
		Student_Course_Modify();
		break;
	case '0':
        StudentFlag = 0;
        printf("退出操作已完成！\n");
        break;
    default:
        printf("找不到指令,请重新输入！\n");
        goto topSD;//指令错误,重新返回提示指令操作
        break;
	};
}
}
void main() {
	char MainDemand;
	Course_Data_head = Course_data_read();
    if (Course_Data_head == NULL) {
        AdminFlag = 0;
        printf("数据读取过程出现错误,无法打开维护界面!\n");
    }
	Student_Data_head = Student_data_read();
    if (Student_Data_head == NULL) {
        StudentFlag = 0;
        printf("数据读取过程出现错误,无法打开学生界面!\n");
    }
	while (MainFlag) {
	printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
    printf("＊　　　　　  　选修课程系统          　＊\n");
    printf("＊--------------------------------------＊\n");
    printf("＊----------------选择类型--------------＊\n");
    printf("＊--------------------------------------＊\n");
    printf("＊　　　　　　　1.学生选课　　　　　　　＊\n");
    printf("＊　　　　　　　2.课程维护　　　　　　　＊\n");
    printf("＊--------------------------------------＊\n");
    printf("＊　　　　　　　0.退出　　　　　　　　　＊\n");
    printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
	topMD:MainDemand = getch();
    printf("您输入了：%c\n", MainDemand);
    switch (MainDemand) {
        case '1':
			if(StudentPermissionCheck()){
				Student();
			}
            break;
        case '2':
			if(AdminPermissionCheck()){
				Admin();
			}
			break;
		case '0':
            MainFlag = 0;
            printf("退出操作已完成！\n");
            break;
        default:
            printf("找不到指令,请重新输入！\n");
            goto topMD;//指令错误,重新返回提示指令操作
            break;
	};
	}
}