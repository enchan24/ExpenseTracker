#include <stdio.h>
#include <stdlib.h>

#define FOOD 1
#define TRANSPORT 2
#define ENTERTAINMENT 3

#define BALANCE_FILE "data/balance.txt"
#define RECORD_FILE "data/record.txt"

struct record{
	char type;
	int amount;
	int category;
};
void showMenu(void){
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

int loadMoney(void){
	int sum = 0;
	FILE *fp = fopen(BALANCE_FILE, "r");
	if(fp != NULL){
	    fscanf(fp, "%d", &sum);
	    fclose(fp);
	}else{
		sum = 0;
	}
	return sum;
}

void saveMoney(int sum){
	FILE *fp = fopen(BALANCE_FILE, "w");
	if(fp != NULL){
		fprintf(fp, "%d", sum);
		fclose(fp);
	}else{
		printf("儲存錯誤。"); 
	}
}

void saveRecord(struct record r){
	FILE *fc = fopen(RECORD_FILE,"a");
	if(fc != NULL){
		fprintf(fc,"%c %d %d\n",r.type,r.amount,r.category);
		fclose(fc);
	}
}

void showRecord(void){
	struct record r;
	FILE *fc = fopen(RECORD_FILE,"r");
	FILE *fp = fopen(BALANCE_FILE,"r");
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

void queryExpense(void){
	struct record r;
	FILE *fc = fopen(RECORD_FILE,"r");
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

void queryExpenseSum(void){
	struct record r;
	int sum = 0,foodExpense = 0,transportExpense = 0,entertainmentExpense = 0;
	FILE *fc = fopen(RECORD_FILE,"r");
	if(fc == NULL){
		printf("沒有紀錄。\n");
		return;
	}
	while(fscanf(fc," %c%d%d",&r.type,&r.amount,&r.category) == 3){
		if(r.type == '-'){
			sum += r.amount;
			if(r.category == FOOD){
				foodExpense += r.amount;
			}else if(r.category == TRANSPORT){
				transportExpense += r.amount;
			}else if(r.category == ENTERTAINMENT){
				entertainmentExpense += r.amount;
			} 
		}
	}
	fclose(fc);
	printf("支出總額:%d\n",sum);
	printf("食物支出總額:%d\n",foodExpense);
	printf("交通支出總額:%d\n",transportExpense);
	printf("娛樂支出總額:%d\n",entertainmentExpense);
}

void resetFile(void){

    FILE *fp;

    fp = fopen(RECORD_FILE,"w");
    if(fp != NULL)
        fclose(fp);

    fp = fopen(BALANCE_FILE,"w");
    if(fp != NULL){
        fprintf(fp,"0");
        fclose(fp);
    }
    printf("所有資料已清除\n");
}

int main(){
    int sum=0;
    int running = 1;
    char op;
    sum = loadMoney();
	showMenu();
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
				saveRecord(r);
				sum += r.amount;
				break;
			}
			case '2':{
				struct record r;
				printf("請輸入支出:");
				scanf("%d",&r.amount);
				printf("請選分類:\n1食物\n2交通\n3娛樂\n");
				scanf("%d", &r.category);
				r.type = '-';
				saveRecord(r);
				sum -= r.amount;
				break;
			}
			case '3':{
				printf("目前餘額:%d",sum);
				break;
			}
			case '4':{
				showRecord();
				break;
			}
			case '5':{
				queryExpense();
				break;
			}
			case '6':{
				queryExpenseSum();
				break;
			}
			case '9':{
				resetFile();
				break;
			}
			case '0':{
				printf("程式結束。");
				saveMoney(sum);
				running = 0;
				break;
			}
			default:{
				printf("輸入字元錯誤，請輸入 0~6 或 9。\n");
				break;
			}
		}
	}
    return 0;
}