//��Ŀ���ٶ���n�ſγ̣�ÿ�ſγ��пγ̱�ţ��γ����ƣ��γ����ʣ���ѧʱ���ڿ�ѧʱ��ʵ��ѧʱ��ѧ�֣�����ѧ�ڵ���Ϣ�������һѡ�޿γ�ϵͳ��
//ά����Ա�˺�abc����123
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
CS *Course_Data_head=NULL;//ͷ����������ʼ��
ST *Student_Data_head=NULL,*Current_Student_Ptr=NULL;
//�����ݴ��ļ��ж�ȡ�����ɵ�����,����ͷָ��
CS *Course_data_read(){
    FILE *fp;
    CS *Course_Data_head=(CS *)malloc(sizeof(CS));//����ͷָ��
    if(!Course_Data_head){
        printf("����ͷָ��ʧ��!\n");
        return NULL;
    }
    Course_Data_head->next=NULL;//��ͷָ��next��ΪNULL
    CS *Course_Data_last=Course_Data_head;//��������һ������ָ��
    if((fp=fopen(Course_Data_file_location,"r"))!=NULL){//�ж��Ƿ���������ļ�,�������
        while(!feof(fp)){//���ļ�����ʱ����ѭ��
            CS *Course_Data_next=(CS *)malloc(sizeof(CS));
            if(!Course_Data_next){
                printf("�����½��ʧ��!\n");
                return NULL;
            }
            fscanf(fp,"%d\t%s\t%s\t%lf\t%lf\t%lf\t%lf\t%s\t",&Course_Data_next->number,Course_Data_next->Name,Course_Data_next->character,&Course_Data_next->sumtime,&Course_Data_next->teachtime,&Course_Data_next->testtime,&Course_Data_next->score,Course_Data_next->term);
            Course_Data_next->next=Course_Data_last->next;//������¼��nextָ���¶�ȡ������
            Course_Data_last->next=Course_Data_next;//������¼����Ϊ����ӵĽ��
            Course_Data_last=Course_Data_last->next;//��lastָ�����µĽڵ�
        }
        fclose(fp);//��ȡ�����ͷ��ڴ�
    }
    return Course_Data_head;
}
//������д���ļ�
void Course_data_write(CS * Course_Data_head){
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    FILE *fp=fopen(Course_Data_file_location,"w");
    int sum=0;//������ʼ��
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        fprintf(fp,"%d\t%s\t%s\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%s\t\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
        sum++;
    }
    fclose(fp);
    printf("�������,��%d����\n",sum);
    if(sum==0){
        printf("δ�ҵ��κογ���Ϣ��\n");
    }
}
//�����ݴ��ļ��ж�ȡ�����ɵ�����,����ͷָ��
ST *Student_data_read(){
    FILE *fp;
    ST *Student_Data_head=(ST *)malloc(sizeof(ST));//����ͷָ��
    if(!Student_Data_head){
        printf("����ͷָ��ʧ��!\n");
        return NULL;
    }
    Student_Data_head->next=NULL;//��ͷָ��next��ΪNULL
    ST *Student_Data_last=Student_Data_head;//��������һ������ָ��
    if((fp=fopen(Student_Data_file_location,"r"))!=NULL){//�ж��Ƿ���������ļ�,�������
        while(!feof(fp)){//���ļ�����ʱ����ѭ��
            ST *Student_Data_next=(ST *)malloc(sizeof(ST));
            if(!Student_Data_next){
                printf("�����½��ʧ��!\n");
                return NULL;
            }
            fscanf(fp,"%s\t%s\t%s\t%d\t",Student_Data_next->Name,Student_Data_next->Username,Student_Data_next->Password,&Student_Data_next->CourseNumber);
            Student_Data_next->next=Student_Data_last->next;//������¼��nextָ���¶�ȡ������
            Student_Data_last->next=Student_Data_next;//������¼����Ϊ����ӵĽ��
            Student_Data_last=Student_Data_last->next;//��lastָ�����µĽڵ�
        }
        fclose(fp);//��ȡ�����ͷ��ڴ�
    }
    return Student_Data_head;
}
//������д���ļ�
void Student_data_write(ST * Student_Data_head){
    ST *Student_Data_last=Student_Data_head;//������ָ��ָ��ͷָ��
    FILE *fp=fopen(Student_Data_file_location,"w");
    int sum=0;//������ʼ��
    while(Student_Data_last->next != NULL){
        Student_Data_last=Student_Data_last->next;
        fprintf(fp,"%s\t%s\t%s\t%d\t\n",Student_Data_last->Name,Student_Data_last->Username,Student_Data_last->Password,Student_Data_last->CourseNumber);
        sum++;
    }
    fclose(fp);
    printf("�������,��%d����\n",sum);
    if(sum==0){
        printf("δ�ҵ��κ�ѧ����Ϣ��\n");
    }
}
//���غ���,ͨ��ID
int RepitationByID(int id){
    int AdminFlag=1;
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        if(Course_Data_last->number ==	id){
            AdminFlag=0;
            break;
        }
    }
    return AdminFlag;
}
//���غ���,ͨ������
int RepitationByName(char name[]){
    int AdminFlag=1;
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        if(!strcmp(Course_Data_last->Name,name)){
            AdminFlag=0;
            break;
        }
    }
    return AdminFlag;
}
//ͳ�ƿγ�����
int Course_Length(){
    int sum=0;
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        sum++;
    }
    return sum;
}
//ͳ��ѧ������
int Student_Length(){
    int sum=0;
    ST *Student_Data_last=Student_Data_head;//������ָ��ָ��ͷָ��
    while(Student_Data_last->next != NULL){
        Student_Data_last=Student_Data_last->next;
        sum++;
    }
    return sum;
}
//ͳ�ƿγ̱�ѡ����
int Course_selected_Length(int Number){
    int sum=0;
    ST *Student_Data_last=Student_Data_head;//������ָ��ָ��ͷָ��
    while(Student_Data_last->next != NULL){
        Student_Data_last=Student_Data_last->next;
        if(Student_Data_last->CourseNumber == Number) sum++;
    }
    return sum;
}
//ͳ�ƿγ�δѡ����
int Course_Unselected_Length(){
    int sum=0;
    ST *Student_Data_last=Student_Data_head;//������ָ��ָ��ͷָ��
    while(Student_Data_last->next != NULL){
        Student_Data_last=Student_Data_last->next;
        if(Student_Data_last->CourseNumber == 0) sum++;
    }
    return sum;
}
//�γ���Ϣ��ѯ,���ؿγ̱��
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
//�γ���Ϣ��ѯ,����ָ��
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
//�γ���Ϣ��ѯ,Only Current Student,���ؿγ�����
void Search_Course_Current_Student_to_Name(char *name){
	CS *Current_Course_Info=NULL;
	if((Current_Course_Info=Search_Courese_Info(Current_Student_Ptr->CourseNumber))==NULL){
	    strcpy(name,"δѡ��");
	}else{
		strcpy(name,Current_Course_Info->Name);
	}
}
//�γ���Ϣ��ѯ,���ؿγ�����
void Search_Course_Student_to_Name(int CourseNumber,char *name){
	CS *Current_Course_Info=NULL;
	if((Current_Course_Info=Search_Courese_Info(CourseNumber))==NULL){
	    strcpy(name,"δѡ��");
	}else{
		strcpy(name,Current_Course_Info->Name);
	}
}
void Course_Add(){
	system("cls");//����
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    CS *another=(CS *)malloc(sizeof(CS));
    printf("�밴��ʾ����Ҫ��ӵĿγ���Ϣ��\n");
    Course_Addreinputid:printf("�γ̱��:\n");
    scanf("%d",&another->number);
	if(another->number<=0){
	    printf("�γ̱��ֻ����Ϊ�Ǹ�������\n");
        goto Course_Addreinputid;
	}
    if(!RepitationByID(another->number)){
        printf("�ÿγ̱���Ѵ��ڣ�\n");
        goto Course_Addreinputid;
    }
    Course_Addreinputname:printf("�γ�����:\n");
    scanf("%s",another->Name);
    if(!RepitationByName(another->Name)){
        printf("�ÿγ������Ѵ��ڣ�\n");
        goto Course_Addreinputname;
    }
    printf("�γ�����:\n");
    scanf("%s",another->character);
    printf("��ѧʱ:\n");
    scanf("%lf",&another->sumtime);
    printf("�ڿ�ѧʱ:\n");
    scanf("%lf",&another->teachtime);
    printf("ʵ��ѧʱ:\n");
    scanf("%lf",&another->testtime);
    printf("ѧ��:\n");
    scanf("%lf",&another->score);
    printf("����ѧ��:\n");
    scanf("%s",another->term);
    another->next=NULL;
    while(Course_Data_last->next != NULL){//ֱ�����һ���ڵ�
        Course_Data_last=Course_Data_last->next;
    }
    Course_Data_last->next=another;//�����һ���ڵ�nextָ���½ڵ�
    Course_data_write(Course_Data_head);
    printf("��ӳɹ���\n");
}
void Course_Find(char key_type){
	system("cls");//����
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    if(key_type=='1'){//���γ̱�Ų�ѯ
        int number;
        printf("������Ҫ���ҵĿγ̱�ţ�\n");
        scanf("%d",&number);
        int sum=0;//������ʼ��
        printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\n");
        while(Course_Data_last->next != NULL){//ֱ��nextΪ��ʱ����ѭ��
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->number == number){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("δ�ҵ������ÿγ̱�ŵ���Ϣ��\n");
        }
    }else if(key_type=='2'){
        char Name[50];
        printf("������Ҫ���ҵĿγ����ƣ�\n");
        scanf("%s",Name);
        int sum=0;//������ʼ��
        printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\n");
        while(Course_Data_last->next != NULL){//ֱ��nextΪ��ʱ����ѭ��
            Course_Data_last=Course_Data_last->next;
            if(!strcmp(Course_Data_last->Name,Name)){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("δ�ҵ������ÿγ����Ƶ���Ϣ��\n");
        }
    }else if(key_type=='3'){
        char character[100];
        printf("������Ҫ���ҵĿγ����ʣ�\n");
        scanf("%s",character);
        int sum=0;//������ʼ��
        printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\n");
        while(Course_Data_last->next != NULL){//ֱ��nextΪ��ʱ����ѭ��
            Course_Data_last=Course_Data_last->next;
            if(!strcmp(Course_Data_last->character,character)){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("δ�ҵ������ÿγ����ʵ���Ϣ��\n");
        }
    }else if(key_type=='4'){
        double sumtime;
        printf("������Ҫ���ҵ���ѧʱ��\n");
        scanf("%lf",&sumtime);
        int sum=0;//������ʼ��
        printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\n");
        while(Course_Data_last->next != NULL){//ֱ��nextΪ��ʱ����ѭ��
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->sumtime == sumtime){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("δ�ҵ���������ѧʱ����Ϣ��\n");
        }
    }else if(key_type=='5'){
        double teachtime;
        printf("������Ҫ���ҵ��ڿ�ѧʱ��\n");
        scanf("%lf",&teachtime);
        int sum=0;//������ʼ��
        printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\n");
        while(Course_Data_last->next != NULL){//ֱ��nextΪ��ʱ����ѭ��
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->teachtime == teachtime){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("δ�ҵ��������ڿ�ѧʱ����Ϣ��\n");
        }
    }else if(key_type=='6'){
        double testtime;
        printf("������Ҫ���ҵ�ʵ��ѧʱ��\n");
        scanf("%lf",&testtime);
        int sum=0;//������ʼ��
        printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\n");
        while(Course_Data_last->next != NULL){//ֱ��nextΪ��ʱ����ѭ��
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->testtime == testtime){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("δ�ҵ�������ʵ��ѧʱ����Ϣ��\n");
        }
    }else if(key_type=='7'){
        double score;
        printf("������Ҫ���ҵ�ѧ�֣�\n");
        scanf("%lf",&score);
        int sum=0;//������ʼ��
        printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\n");
        while(Course_Data_last->next != NULL){//ֱ��nextΪ��ʱ����ѭ��
            Course_Data_last=Course_Data_last->next;
            if(Course_Data_last->score == score){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("δ�ҵ�������ѧ�ֵ���Ϣ��\n");
        }
    }else if(key_type=='8'){
        char term[50];
        printf("������Ҫ���ҵĿ���ѧ�ڣ�\n");
        scanf("%s",term);
        int sum=0;//������ʼ��
        printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\n");
        while(Course_Data_last->next != NULL){//ֱ��nextΪ��ʱ����ѭ��
            Course_Data_last=Course_Data_last->next;
            if(!strcmp(Course_Data_last->term,term)){
                printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term);
                sum++;
            }
        }
        if(sum==0){
            printf("δ�ҵ������ÿ���ѧ�ڵ���Ϣ��\n");
        }
    }else{
        printf("�Ҳ���ָ��,���������룡\n");
    }
}
void Course_Modify(){
	system("cls");//����
    char subCourse_Modify,Name[50],character[100],term[50];
    double sumtime,testtime,teachtime,score;
    int number,sum=0;
	ST *Student_Data_last=NULL;
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    printf("������Ҫ�޸ĵĿγ�����:\n");
    scanf("%s",Name);
    while(Course_Data_last->next != NULL && strcmp(Course_Data_last->Name,Name)){
        Course_Data_last=Course_Data_last->next;
    }
    if(strcmp(Course_Data_last->Name,Name)){
        printf("�ÿγ̲�����!\n");
    }else{
        printf("������������������������������������������\n");
        printf("������������  ���޸Ŀγ���Ϣ  ������������\n");
        printf("��--------------------------------------��\n");
        printf("��--------------ѡ���޸�����------------��\n");
        printf("��--------------------------------------��\n");
        printf("����������������1.�γ̱�š���������������\n");
        printf("����������������2.�γ����ơ���������������\n");
        printf("����������������3.�γ����ʡ���������������\n");
        printf("����������������4.��ѧʱ  ����������������\n");
        printf("����������������5.�ڿ�ѧʱ����������������\n");
        printf("����������������6.ʵ��ѧʱ������      ����\n");
        printf("����������������7.ѧ��    ����������������\n");
        printf("����������������8.����ѧ�ڡ���������������\n");
        printf("��--------------------------------------��\n");
        printf("����������������0.����      ��������������\n");
        printf("������������������������������������������\n");
        submd:subCourse_Modify=getch();
        printf("�������ˣ�%c\n",subCourse_Modify);
        switch(subCourse_Modify){
            case '1':
                printf("ԭ�γ̱��:%d\n",Course_Data_last->number);
            Course_Addreinputidb:printf("�������µĿγ̱��:\n");
                scanf("%d",&number);
				if(number<=0){
				    printf("�γ̱��ֻ����Ϊ�Ǹ�������\n");
                    goto Course_Addreinputidb;
				}
                if(!RepitationByID(number)){
                    printf("�ÿγ̱���Ѵ��ڣ�\n");
                    goto Course_Addreinputidb;
                }
                Course_Data_last->number=number;
                Course_data_write(Course_Data_head);//�������ݵ��ļ�
                Student_Data_last=Student_Data_head;//������ָ��ָ��ͷָ��
                while(Student_Data_last->next != NULL){
                    Student_Data_last=Student_Data_last->next;
                    if(Student_Data_last->CourseNumber == number){
						Student_Data_last->CourseNumber=number;
						sum++;
					}
                }
				Student_data_write(Student_Data_head);
                printf("�޸ĳɹ�,��ͬ��%d��!\n",sum);
                break;
            case '2':
                printf("ԭ�γ�����:%s\n",Course_Data_last->Name);
            Course_Addreinputnameb:printf("�������µĿγ�����:\n");
                scanf("%s",Name);
                if(!RepitationByName(Name)){
                    printf("�ÿγ������Ѵ��ڣ�\n");
                    goto Course_Addreinputnameb;
                }
                strcpy(Course_Data_last->Name,Name);
                Course_data_write(Course_Data_head);//�������ݵ��ļ�
                printf("�޸ĳɹ�!\n");
                break;
            case '3':
                printf("ԭ�γ�����:%s\n",Course_Data_last->character);
                printf("�������µĿγ�����:\n");
                scanf("%s",character);
                strcpy(Course_Data_last->character,character);
                Course_data_write(Course_Data_head);//�������ݵ��ļ�
                printf("�޸ĳɹ�!\n");
                break;
            case '4':
                printf("ԭ��ѧʱ:%lf\n",Course_Data_last->sumtime);
                printf("�������µ���ѧʱ:\n");
                scanf("%lf",&sumtime);
                Course_Data_last->sumtime=sumtime;
                Course_data_write(Course_Data_head);//�������ݵ��ļ�
                printf("�޸ĳɹ�!\n");
                break;
            case '5':
                printf("ԭ�ڿ�ѧʱ:%lf\n",Course_Data_last->teachtime);
                printf("�������µ��ڿ�ѧʱ:\n");
                scanf("%lf",&teachtime);
                Course_Data_last->teachtime=teachtime;
                Course_data_write(Course_Data_head);//�������ݵ��ļ�
                printf("�޸ĳɹ�!\n");
                break;
            case '6':
                printf("ԭʵ��ѧʱ:%lf\n",Course_Data_last->testtime);
                printf("�������µ�ʵ��ѧʱ:\n");
                scanf("%lf",&testtime);
                Course_Data_last->testtime=testtime;
                Course_data_write(Course_Data_head);//�������ݵ��ļ�
                printf("�޸ĳɹ�!\n");
                break;
            case '7':
                printf("ԭѧ��:%lf\n",Course_Data_last->score);
                printf("�������µ�ѧ��:\n");
                scanf("%lf",&score);
                Course_Data_last->score=score;
                Course_data_write(Course_Data_head);//�������ݵ��ļ�
                printf("�޸ĳɹ�!\n");
                break;
            case '8':
                printf("ԭ����ѧ��:%s\n",Course_Data_last->term);
                printf("�������µĿ���ѧ��:\n");
                scanf("%s",term);
                strcpy(Course_Data_last->term,term);
                Course_data_write(Course_Data_head);//�������ݵ��ļ�
                printf("�޸ĳɹ�!\n");
                break;
            case '0':
                printf("���ز�������ɣ�\n");
                break;
            default:
                printf("�Ҳ���ָ��,���������룡\n");
                goto submd;//ָ�����,���·�����ʾָ�����
                break;
        };
    }
}
void Course_PrintList(){
	system("cls");//����
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    int sum=0;//������ʼ��
    printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\tѧ��\t����ѧ��\tѡ������\n");
    while(Course_Data_last->next != NULL){
        Course_Data_last=Course_Data_last->next;
        printf("%8d\t%8s\t%8s\t%6.1lf\t%8.1lf\t%8.1lf\t%4.1lf\t%8s\t%8d\n",Course_Data_last->number,Course_Data_last->Name,Course_Data_last->character,Course_Data_last->sumtime,Course_Data_last->teachtime,Course_Data_last->testtime,Course_Data_last->score,Course_Data_last->term,Course_selected_Length(Course_Data_last->number));
        sum++;
    }
    if(sum>0){
        printf("�γ�����:%d��,ѧ������:%d��,δѡ����:%d��\n",Course_Length(),Student_Length(),Course_Unselected_Length());
    }else{
        printf("δ�ҵ��κογ���Ϣ��\n");
    }
}
void Course_Delete(){
	system("cls");//����
    CS *Course_Data_last=Course_Data_head;//������ָ��ָ��ͷָ��
    char Name[50];
    int sum=0,ssum=0;
    printf("������Ҫɾ���Ŀγ�����:\n");
    scanf("%s",Name);
    while(Course_Data_last->next != NULL){
        if(!strcmp(Course_Data_last -> next -> Name,Name)){
            ST *Student_Data_last=Student_Data_head;//������ָ��ָ��ͷָ��
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
        Course_data_write(Course_Data_head);//�������ݵ��ļ�
		Student_data_write(Student_Data_head);
        printf("ɾ���ɹ�,ͬ����%d��ѧ��ѡ�������Ϊδѡ!\n",ssum);
    }else{
        printf("�ÿγ̲�����!\n");
    }
}
//ѧ��ѡ�����
void Course_Situaction(){
	system("cls");//����
	char name[50];
	ST *Student_Data_last = Student_Data_head;
	//int Course_Everyone_Sum[Course_Length()];
	printf("ѧ������\tѡ�޿γ�\t\n");
	while(Student_Data_last->next!=NULL){
		Student_Data_last=Student_Data_last->next;
		Search_Course_Student_to_Name(Student_Data_last->CourseNumber,name);
		printf("%8s\t%8s\t\n",Student_Data_last->Name,name);
	}
}
//ά����ԱȨ�޼��
int AdminPermissionCheck(){
	system("cls");//����
	char username[16],password[16],ch;
	printf("�������˺�:\n");
	scanf("%s",username);
	printf("����������:\n");
	int i=0;
	while(((ch=getch())!=13)&&i<16){//13Ϊ�س�ascil
		password[i]=ch;
		putchar('*');
		i++;
	}
	putchar('\n');
	if(!strcmp(username,"abc")&&!strcmp(password,"123")){
		 return 1;
	}else{
		 printf("�˺Ż��������!\n");
		 return 0;
	}
}
//ѧ��Ȩ�޼�����
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
//ѧ��Ȩ�޼��
int StudentPermissionCheck(){
	system("cls");//����
	char username[16],password[16],ch;
	printf("�������˺�:\n");
	scanf("%s",username);
	printf("����������:\n");
	int i=0;
	while(((ch=getch())!=13)&&i<16){//13Ϊ�س�ascil
		password[i]=ch;
		putchar('*');
		i++;
	}
	putchar('\n');
	if(StudentPermissionCheckCore(username,password)){
		 return 1;
	}else{
		 printf("�˺Ż��������!\n");
		 return 0;
	}
}
//ά��
void Admin(){
	system("cls");//����
    while (AdminFlag) {
        char AdminDemand,subAdminDemand;
        printf("������������������������������������������\n");
        printf("��������������ѡ�޿γ̹���ϵͳ        ����\n");
        printf("��--------------------------------------��\n");
        printf("��--------------ѡ����ز���------------��\n");
        printf("��--------------------------------------��\n");
        printf("����������������1.��ӿγ̡���������������\n");
        printf("����������������2.���ҿγ̡���������������\n");
        printf("����������������3.�޸Ŀγ̡���������������\n");
        printf("����������������4.�鿴�γ̡���������������\n");
        printf("����������������5.ɾ���γ̡���������������\n");
		printf("����������������6.ѧ��ѡ�����������������\n");
        printf("��--------------------------------------��\n");
        printf("����������������0.�˳�ά��ϵͳ������������\n");
        printf("������������������������������������������\n");
        topAD:AdminDemand = getch();
        printf("�������ˣ�%c\n", AdminDemand);
        switch (AdminDemand) {
            case '1':
                Course_Add();
                break;
            case '2':
                printf("������������������������������������������\n");
                printf("��������������������ѯ�γ̡���������������\n");
                printf("��--------------------------------------��\n");
                printf("��--------------ѡ���ѯ����------------��\n");
                printf("��--------------------------------------��\n");
                printf("����������������1.�γ̱�š���������������\n");
                printf("����������������2.�γ����ơ���������������\n");
                printf("����������������3.�γ����ʡ���������������\n");
                printf("����������������4.��ѧʱ  ����������������\n");
                printf("����������������5.�ڿ�ѧʱ����������������\n");
                printf("����������������6.ʵ��ѧʱ��������      ��\n");
                printf("����������������7.ѧ��    ����������������\n");
                printf("����������������8.����ѧ�ڡ���������������\n");
                printf("��--------------------------------------��\n");
                printf("����������������0.����            ��������\n");
                printf("������������������������������������������\n");
            subAD:subAdminDemand = getch();
                printf("�������ˣ�%c\n", subAdminDemand);
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
                        printf("���ز�������ɣ�\n");
                        break;
                    default:
                        printf("�Ҳ���ָ��,���������룡\n");
                        goto subAD;//ָ�����,���·�����ʾָ�����
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
                free(Course_Data_head);//ͨ���ͷ��ڴ�
                Course_Data_head = NULL;
                printf("�˳���������ɣ�\n");
                break;
            default:
                printf("�Ҳ���ָ��,���������룡\n");
                goto topAD;//ָ�����,���·�����ʾָ�����
                break;
        };
    }
}
//ѧ���޸�ѡ��
void Student_Course_Modify(){
	system("cls");//����
	char Name[50];
	int number=0;
	printf("������Ҫѡ��Ŀγ�����:\n");
	scanf("%s",Name);
	if(!(number=Search_Course_Name_to_Number(Name))){
		printf("�γ̲�����!\n");
	}else{
		Current_Student_Ptr->CourseNumber=number;
		Student_data_write(Student_Data_head);
		printf("�޸ĳɹ�!\n");
	}
}
//ѡ��
void Student(){
	char StudentDemand,Current_Course_Name[50];
	while (StudentFlag) {
	Search_Course_Current_Student_to_Name(Current_Course_Name);//����ǰѧ���γ����Ʒ���
	printf("������������������������������������������\n");
    printf("������������  ѧ��ѡ�޿γ�ϵͳ        ����\n");
    printf("��--------------------------------------��\n");
    printf("��--------------ѡ����ز���------------��\n");
    printf("��--------------------------------------��\n");
	printf("��%s%-29s��\n","��ǰѡ��:",Current_Course_Name);
    printf("����������������1.�鿴��ѡ�γ̡�����������\n");
	printf("����������������2.�޸�ѡ�޿γ̡�����������\n");
    printf("��--------------------------------------��\n");
    printf("����������������0.�˳���������������������\n");
    printf("������������������������������������������\n");
	topSD:StudentDemand = getch();
    printf("�������ˣ�%c\n", StudentDemand);
    switch (StudentDemand){
	case '1':
		Course_PrintList();
		break;
	case '2':
		Student_Course_Modify();
		break;
	case '0':
        StudentFlag = 0;
        printf("�˳���������ɣ�\n");
        break;
    default:
        printf("�Ҳ���ָ��,���������룡\n");
        goto topSD;//ָ�����,���·�����ʾָ�����
        break;
	};
}
}
void main() {
	char MainDemand;
	Course_Data_head = Course_data_read();
    if (Course_Data_head == NULL) {
        AdminFlag = 0;
        printf("���ݶ�ȡ���̳��ִ���,�޷���ά������!\n");
    }
	Student_Data_head = Student_data_read();
    if (Student_Data_head == NULL) {
        StudentFlag = 0;
        printf("���ݶ�ȡ���̳��ִ���,�޷���ѧ������!\n");
    }
	while (MainFlag) {
	printf("������������������������������������������\n");
    printf("������������  ��ѡ�޿γ�ϵͳ          ����\n");
    printf("��--------------------------------------��\n");
    printf("��----------------ѡ������--------------��\n");
    printf("��--------------------------------------��\n");
    printf("����������������1.ѧ��ѡ�Ρ���������������\n");
    printf("����������������2.�γ�ά������������������\n");
    printf("��--------------------------------------��\n");
    printf("����������������0.�˳���������������������\n");
    printf("������������������������������������������\n");
	topMD:MainDemand = getch();
    printf("�������ˣ�%c\n", MainDemand);
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
            printf("�˳���������ɣ�\n");
            break;
        default:
            printf("�Ҳ���ָ��,���������룡\n");
            goto topMD;//ָ�����,���·�����ʾָ�����
            break;
	};
	}
}