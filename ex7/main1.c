
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SETS 5
#define PICKS_PER_SET 7
#define MIN_NUM 1
#define MAX_NUM 69

static void sort_asc(int *arr, int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

static void generate_set(int out[PICKS_PER_SET]) {
    int used[MAX_NUM + 1] = {0};
    int count = 0;
    while (count < PICKS_PER_SET) {
        int r = rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM;
        if (!used[r]) {
            used[r] = 1;
            out[count++] = r;
        }
    }
    /* 前 6 個號碼排序，第 7 個保留抽出順序 */
    sort_asc(out, PICKS_PER_SET - 1);
}

int main(void) {
    int n = 0;
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SETS) {
        printf("輸入無效，請輸入 1 到 %d 之間的整數。\n", MAX_SETS);
        return 1;
    }

    srand((unsigned int)time(NULL));

    int sets[MAX_SETS][PICKS_PER_SET];
    for (int i = 0; i < n; i++) {
        generate_set(sets[i]);
    }

    FILE *fp = fopen("lotto.txt", "w");
    if (!fp) {
        perror("無法開啟 lotto.txt");
        return 1;
    }

    time_t now = time(NULL);
    char time_buf[64];
    strcpy(time_buf, ctime(&now));
    size_t len = strlen(time_buf);
    if (len > 0 && time_buf[len - 1] == '\n') {
        time_buf[len - 1] = '\0';
    }

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s =\n", time_buf);

    for (int i = 0; i < MAX_SETS; i++) {
        fprintf(fp, "[%d]: ", i + 1);
        if (i < n) {
            for (int j = 0; j < PICKS_PER_SET; j++) {
                fprintf(fp, "%02d%s", sets[i][j], (j < PICKS_PER_SET - 1) ? " " : "");
            }
            fprintf(fp, "\n");
        } else {
            for (int j = 0; j < PICKS_PER_SET; j++) {
                fprintf(fp, "--%s", (j < PICKS_PER_SET - 1) ? " " : "");
            }
            fprintf(fp, "\n");
        }
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
