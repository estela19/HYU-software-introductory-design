#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct _time {
	int minute;
	int second;
}Time;

typedef struct _song {
	char title[100];
	char artist[100];
	Time length;
}Song;

typedef struct _songList {
	Song *songs;
	int size;
	int capacity;
}Songlist;

//����ϴ� �Լ��鿡 ���� ����
Songlist dataload(void);
int datasave(Songlist*);
int printmenu(Songlist*);
int printsong(Song*);
void printsongmenu(Songlist*, Song*);
Song* searchsong(Songlist*, char*, char*);
int editsong(Song*);
int deletesong(Songlist*, Song*);
int addsong(Songlist*);
int printallsongs(Songlist*);
int deleteall(Songlist*);
int searchmenu(Songlist*);

//for�� ��� ����
int i, j, k;
//��ü �޴� �Լ������͹迭 (5�� �޴����)
int(*funcs[])(Songlist*) = { datasave, searchmenu, addsong, printallsongs, deleteall, printmenu };

int main() {
	printf("-----------Mini Music Library-----------\n\n");
	//dataload�ϸ� ������ ����ü�� songlist ��� ����ü�� ����
	Songlist songlist = dataload();
	Songlist* p_songlist = &songlist;
	// �⺻�޴��� 5(�޴����)
	int state = 5; 
	//�Լ��� ���ϰ��� -1�� �ƴҶ����� �� �Լ����� ��ȯ�ϴ� int ���� �ε����� �Լ� ����
	while (state != -1) state = funcs[state](p_songlist);
	//state�� -1�̸� �����Ѵ�. ������ �����Ҵ��� songlist �Ҵ�����
	free(songlist.songs);
	return 0;
}

//���� ã�� ���� songlist�� �����ϸ� �� ����ü�����͸� ��ȯ�ϰ� ������ NULL�� ��ȯ�ϴ� �Լ�
Song* searchsong(Songlist* p_songlist, char* title, char* artist) {
	//songlist�� capacity��ŭ �ݺ��ϸ鼭
	for (i = 0; i < p_songlist -> capacity; i++) {
		//songlist�� ���� �Է��� Ÿ��Ʋ�� ����
		if (!strcmp(p_songlist->songs[i].title, title))
			//��Ƽ��Ʈ�� �����鼭
			if (!strcmp(p_songlist->songs[i].artist, artist))
				//�� ���̵� 0�� �ƴϸ�
				if (p_songlist->songs[i].length.minute != 0 && p_songlist->songs[i].length.second != 0) {
					//�� song ����ü ������ ��ȯ
					Song* p_song = &(p_songlist->songs[i]);
					return p_song;
				}
	}
	return NULL;
}

//printmenu���� search�� �����ϸ� ȣ��Ǵ� �Լ�. �ش� ���� �ִ��� ������ Ȯ���Ѵ�
int searchmenu(Songlist* p_songlist) {
	char title[100];
	char artist[100];
	printf("Input title : ");
	scanf(" %[^\n]s ", title);
	printf("Input artist : ");
	scanf(" %[^\n]s ", artist);

	int result;
	//�ش���� �ִ��� �˻�
	Song* p_song = searchsong(p_songlist, title, artist);
	//�ش� ���� ������
	if (p_song == NULL) {
		printf("<ERROR> Can't find song.\n");
		//5�� �����ؼ� printmenu�� ���ư�
		return 5;
	}
	//�ش� ���� ������
	else {
		//�� ������ ����ϰ� printsongmenuȣ��
		printsong(p_song);
		printsongmenu(p_songlist, p_song);
	}
}

//������ ���� ����� �Լ�
int deletesong(Songlist* p_songlist, Song* p_song) {
	// ����̸� 0���� �ٲٰ�
	p_song->length.minute = 0;
	p_song->length.second = 0;
	//�� ������ 1���δ�
	p_songlist->size--;
	printf("...delete success\n");
}

//p_song�� �ش��ϴ� ������ ����ϴ� �Լ�
int printsong(Song* p_song) {
	printf("\nTitle : %s\n", p_song->title);
	printf("Artist : %s\n", p_song->artist);
	printf("Length : %d min %d sec\n", p_song->length.minute, p_song->length.second);
	printf("\n");
}

//���� �߰��ϴ� �Լ� (2.newsong�϶� �����)
int addsong(Songlist* p_songlist) {
	Song* check;
	char new_title[100];
	char new_artist[100];
	int new_minute = 0;
	int new_second = 0;
	printf("Input title : ");
	scanf(" %[^\n]s", new_title);
	printf("Input artist : ");
	scanf( " %[^\n]s", new_artist);

	//�Է¹��� Ÿ��Ʋ�� ��Ƽ��Ʈ�� songlist�� �����ϴ��� Ȯ��
	check = searchsong(p_songlist, new_title, new_artist);

	//Ȯ�ΰ�� ���� ���̸� ���̸� �Է¹޴´�
	if (check == NULL) {
		printf("Input length  \n");
		printf("minute : ");
		scanf(" %d", &new_minute);
		printf("second : ");
		scanf(" %d", &new_second);

		//�ʰ� 60�ʸ� �Ѱų� �����̸� ������ ����ϰ� �ٽ� �Է¹޴´�
		while (new_second < 0 || new_second > 59) {
			printf("<EROOR> Wrong second!\n");
			printf("Input new length\n");
			printf("minute : ");
			scanf("%d", &new_minute);
			printf("second : ");
			scanf("%d", &new_second);
		}

		//���� �߰��ϱ� ���� songs�� ��ĭ �ø���. �߰��� ����� size�� �������� ǥ���Ѵ�.
		p_songlist->songs = realloc(p_songlist->songs, sizeof(Song) * (p_songlist->capacity + 1));
		p_songlist->capacity++;
		p_songlist->size++;
		//���� ���� �ڸ��� ��Ƽ��Ʈ, Ÿ��Ʋ, ���̸� �����Ѵ�.
		Song * p_song = &p_songlist->songs[p_songlist->capacity - 1];
		strcpy(p_song->artist, new_artist);
		strcpy(p_song->title, new_title);
		p_song->length.minute = new_minute;
		p_song->length.second = new_second;
		printf("...add success\n");
	}
	//���� �̹� �����ߴ� ���̸� ������ ����Ѵ�
	else printf("<ERROR> This song already exsit.\n");
	//5�� ������ printmenu�� ���ư���
	return 5;
}

//search ���� ã�� ���� �����ϴ� �Լ�
int editsong(Songlist* p_songlist, Song* p_song) {
	printf("Input new title : ");
	scanf(" %[^\n]s", &p_song->title);
	printf("Input new artist : ");
	scanf(" %[^\n]s", &p_song->artist);
	printf("\nInput new length\n");
	printf("minute : ");
	scanf("%d", &p_song->length.minute);
	printf("second : ");
	int tmp;
	scanf("%d", &tmp);
	//60�ʸ� �Ѱų� �����̸� ������ ����ϰ� �ٽ� �Է¹޴´�
	while (tmp < 0 || tmp > 59) {
		printf("<EROOR> Wrong second!\n");
		printf("Input new length\n");
		printf("minute : ");
		scanf("%d", &p_song->length.minute);
		printf("second : ");
		scanf("%d", &tmp);
	}
	p_song->length.second = tmp;
	printf("...Edit song succes\n");
}

//�����Ҷ� �����͸� �ҷ����� �Լ�
Songlist dataload(void) {
	//�����͸� ���� ����ü�� �����Ѵ�
	Songlist songlist;
	FILE* f = NULL;
	f = fopen("example.txt", "r");
	fscanf(f, "%d", &songlist.size);
	//ó�� ������ ���������� size�� capacity�� ����.
	songlist.capacity = songlist.size;
	//���� ������ŭ �޸𸮸� �Ҵ��Ѵ�
	songlist.songs = (Song*)malloc(sizeof(Song) * songlist.size);
	//�Ҵ��� �޸𸮿� ���� ���� �ִ´�.
	for (i = 0; i < songlist.size; i++) {
		fscanf(f, "%d %d", &songlist.songs[i].length.minute, &songlist.songs[i].length.second);
		fscanf(f, " %[^\n]s", &songlist.songs[i].artist);
		fscanf(f, " %[^\n]s", &songlist.songs[i].title);
	}
	printf("...Data load success\n");
	//�����͸� ���� ����ü�� �����Ѵ�.
	return songlist;
}

//��ü ���� ����� �Լ�
int deleteall(Songlist* p_songlist) {
	char ans[10];
	printf("Are you sure? (y or n) : ");
	scanf("%s", ans);
	//���� �Է��� y ���ٸ�
	if (!strcmp(ans, "y")) {
		//��ü songs�� ���鼭 �� ���̸� 0���� �ʱ�ȭ�Ѵ�
		for (i = 0; i < p_songlist->capacity ; i++) {
			p_songlist->songs[i].length.minute = 0;
			p_songlist->songs[i].length.second = 0;
		}
		//�� ������ 0���� �ٲ۴�
		p_songlist->size = 0;
		printf("...Delete success\n");
	}
	//5�� ������ printmenu�� ���ư���
	return 5;
}

//�޴��� ����ϴ� �Լ�
int printmenu(Songlist* p_songlist) {
	char input[10] = { 0, };
	int menu = 0;
	printf("------------------------------------------\n"
		"1. Search\n"
		"2. New song\n"
		"3. Print all\n"
		"4. Delete all\n"
		"0. Exit\n"
		"-------------------------------------------\n"
		">>>");
	scanf("%s", input);
	// ���ڿ��� �޾Ƽ� int�������� ��ȯ�Ѵ�
	menu = atoi(input);
	//menu������ ����ų� ���ڿ�����(��ȯ���� 0�̰� ���ڿ��� ù��°�� 0�̾ƴϸ�) ������ ����Ѵ�
	if (menu < 0 || menu > 4 ||(menu == 0 && input[0] != '0')) {
		printf("<ERROR> You can select 0~4\n");
		//5�� ������ printmenu�� �ٽ� �θ���
		return 5;
	}
	//�Է¹��� menu�� ������ �ش� ������ �Լ��� ȣ���Ѵ�
	return menu;
}

//search�޴����� �ش���� ã������ �޴��� ����ϴ� �Լ�
void printsongmenu(Songlist* p_songlist, Song* p_song) {
	//search�޴����� �� ���ÿ� �ش��ϴ� �Լ������͹迭
	int(*searchfuncs[])(Songlist * p_songlist, Song * p_song) = { printmenu, editsong, deletesong, printsongmenu };
	char input[10] = { 0, };
	int menu = 0;
	printf("----------------------------------------\n"
		"1. Edit\n"
		"2. Delete\n"
		"0. Previous\n"
		"----------------------------------------\n"
		">>>");
	//���ڿ��� �Է¹��� �� int�� ��ȯ
	scanf("%s", input);
	menu = atoi(input);
	//���� ���� ���̰ų� ���ڿ��ٸ� ���� ����� �ڱ� �ڽ� ȣ��
	if (menu < 0 || menu > 2 ||(menu == 0 && input[0] != '0')) {
		printf("<ERROR> You can select 0~2\n");
		searchfuncs[3](p_songlist, p_song);
	}
	//�Է��� �������̾����� �ش� menu�� ȣ���� �� ��ü �޴�(printmenu)ȣ��
	searchfuncs[menu](p_songlist, p_song);
	searchfuncs[0](p_songlist, p_song);
}

//songlist�� �����ϴ� ��� ����� ����ϴ� �Լ�
int printallsongs(Songlist* p_songlist) {
	//��ü songlistũ�⸸ŭ ���鼭
	for (i = 0; i < p_songlist->capacity; i++) {
		//�ش� ���� ���̰� 0�� �ƴϸ� ���
		if(p_songlist->songs[i].length.minute != 0 || p_songlist->songs[i].length.second != 0)
			printf("%s - %s (%d : %d)\n", p_songlist->songs[i].title, p_songlist->songs[i].artist, p_songlist->songs[i].length.minute, p_songlist->songs[i].length.second);
	}
	//���� ���� ���ٸ� nothing���
	if (p_songlist->size == 0) printf("<Nothing>\n");
	//5�� �����ؼ� printmenu�� ���ư�
	return 5;
}

//������ ���� songlist�� �ִ� ����� �����ϴ� �Լ�
int datasave(Songlist* p_songlist) {
	FILE* f = NULL;
	f = fopen("example.txt", "w");
	//�� ������ ���� �����ϰ�
	fprintf(f, "%d\n", p_songlist->size);
	//�� ũ�⸸ŭ ���鼭
	for (i = 0; i < p_songlist->capacity; i++) {
		// �� ���̰� 0�� �ƴϸ� ����
		if (p_songlist->songs[i].length.minute != 0 && p_songlist->songs[i].length.second != 0) {
			fprintf(f, "%d %d\n", p_songlist->songs[i].length.minute, p_songlist->songs[i].length.second);
			fprintf(f, "%s\n", p_songlist->songs[i].artist);
			fprintf(f, "%s\n", p_songlist->songs[i].title);
		}
	}
	printf("...Data save success\n");
	//-1�� �����ؼ� ���α׷��� ���� ������ �˸�.
	return -1;
}