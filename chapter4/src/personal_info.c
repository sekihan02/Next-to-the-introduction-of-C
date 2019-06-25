#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING 256

// 個人情報用構造体
struct persol_info
{
	int no;						// 保険証番号
	char name[MAX_STRING];		// 名前
	char addr[MAX_STRING];		// 住所
	int birthday;				// 生年月日
	int age;					// 年齢
	int tel_num;				// 電話番号
	char maddr[MAX_STRING];		// メールアドレス
	char diagnosis[MAX_STRING];	// 診断結果
	struct persol_info *next;	// 次のデータへのポインタ
};

// リストの先頭を記憶するポインタ
struct personal_info *address = NULL;

// データを登録する関数
int enter(int, const char*, const char*);

// 保険証番号から名前を検索する関数
struct personal_info *find(int);

// 指定した保険証番号の個人名を削除する関数
int delete(int);
// 全データの表示
void show_all(void);
// 全データの削除
void delete_all(void);

int main(int argc, char const *argv[])
{
	struct personal_info *address_data;
	char in_buf[8];
	char in_no[MAX_STRING];
	char in_name[MAX_STRING];
	char in_addr[MAX_STRING];
	char in_birthday[MAX_STRING];
	char in_age[MAX_STRING];
	char in_tel_num[MAX_STRING];
	char in_maddr[MAX_STRING];
	char in_diagnosis[MAX_STRING];
	char *c;
	int no, menu_no;

	do
	{
		printf("Input :\n 1 to enter,\n 2 to search,\n 3 to delete,\n 4 to all\n 9 to quit\n");
		printf("Input menu number -> ");
		
		fgets(in_buf, sizeof(in_buf), stdin);
		// 入力値を10進数に変換する
		menu_no = strtol(in_buf, NULL, 10);
		switch (menu_no)
		{
		case 1:
			printf("Input number -> ");
			fgets(in_no, sizeof(in_no), stdin);
			
			break;
		
		default:
			break;
		}
	} while (/* condition */);
	


	return 0;
}

