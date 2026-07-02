#include <stdio.h>
#include <stdlib.h>

struct record{
	char type;
	int amount;
	char category;
};
void showmenu(void){
	printf("\n=====記帳程式=====\n");
    printf("1.新增收入\n");
    printf("2.新增支出\n");
    printf("3.查看餘額\n");
    printf("4.查看紀錄\n");
    printf("5.查看支出紀錄\n");
    printf("6.分類支出統計\n");
    printf("9.清除紀錄\n");
    printf("0.離開\n");
}

int loadmoney(void){
	int sum = 0;
	FILE *fp = fopen("money.txt", "r");
	if(fp != NULL){
	    fscanf(fp, "%d", &sum);
	    fclose(fp);
	}else{
		sum = 0;
	}
	return sum;
}

void savemoney(int sum){
	FILE *fp = fopen("money.txt", "w");
	if(fp != NULL){
		fprintf(fp, "%d", sum);
		fclose(fp);
	}else{
		printf("儲存錯誤。"); 
	}
}

void saverecord(struct record r){
	FILE *fc = fopen("money1.txt","a");
	if(fc != NULL){
		fprintf(fc,"%c %d %d\n",r.type,r.amount,r.category);
		fclose(fc);
	}
}

void showrecord(void){
	struct record r;
	FILE *fc = fopen("money1.txt","r");
	FILE *fp = fopen("money.txt","r");
	if(fc == NULL && fp == NULL){
		printf("沒有紀錄。\n");
		return;
	}
	printf("\n=====交易紀錄=====\n");
	while(fscanf(fc," %c%d%d",&r.type,&r.amount,&r.category) == 3){
		printf("%c%d\n",r.type,r.amount);
	}
	fclose(fc);
	fclose(fp);
}

void query_expence(void){
	struct record r;
	FILE *fc = fopen("money1.txt","r");
	if(fc == NULL){
		printf("沒有紀錄。\n");
		return;
	}
	printf("\n=====支出紀錄=====\n");
	while(fscanf(fc," %c%d%d",&r.type,&r.amount,&r.category) == 3){
		if(r.type == '-'){
			printf("%c%d\n",r.type,r.amount);
		}
	}
	fclose(fc);
}

void query_expence_sum(void){
	struct record r;
	int sum = 0,food = 0,trn = 0,ent = 0;
	FILE *fc = fopen("money1.txt","r");
	if(fc == NULL){
		printf("沒有紀錄。\n");
		return;
	}
	while(fscanf(fc," %c%d%d",&r.type,&r.amount,&r.category) == 3){
		if(r.type == '-'){
			sum += r.amount;
			if(r.category == 1){
				food += r.amount;
			}else if(r.category == 2){
				trn += r.amount;
			}else if(r.category == 3){
				ent += r.amount;
			} 
		}
	}
	fclose(fc);
	printf("支出總額:%d\n",sum);
	printf("食物支出總額:%d\n",food);
	printf("交通支出總額:%d\n",trn);
	printf("娛樂支出總額:%d\n",ent);
}

void reset_file(void){

    FILE *fp;

    fp = fopen("money1.txt","w");
    if(fp != NULL)
        fclose(fp);

    fp = fopen("money.txt","w");
    if(fp != NULL){
        fprintf(fp,"0");
        fclose(fp);
    }

    printf("所有資料已清除\n");
}

int main(){
    int mon,sum=0;
    int running = 1;
    char op;
    sum = loadmoney();
	showmenu();
	while(running){
		printf("\n請輸入:");
		scanf(" %c",&op);
		switch(op){
			case '1':{
				struct record r;
				printf("請輸入收入:");
				scanf("%d",&r.amount);
				r.type = '+';
				r.category = 0;
				saverecord(r);
				sum += r.amount;
				break;
			}
			case '2':{
				struct record r;
				printf("請輸入支出:");
				scanf("%d",&r.amount);
				printf("請選分類\n1食物\n2交通\n3娛樂:\n");
				scanf("%d", &r.category);
				r.type = '-';
				saverecord(r);
				sum -= r.amount;
				break;
			}
			case '3':{
				printf("目前餘額:%d",sum);
				break;
			}
			case '4':{
				showrecord();
				break;
			}
			case '5':{
				query_expence();
				break;
			}
			case '6':{
				query_expence_sum();
				break;
			}
			case '9':{
				reset_file();
				break;
			}
			case '0':{
				printf("程式結束。");
				savemoney(sum);
				running = 0;
				break;
			}
			default:{
				printf("輸入字元錯誤，請輸入 0~3。\n");
				break;
			}
		}
	}
    return 0;
}