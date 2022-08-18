#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* for time() */
#define FILENAME "menu.txt"
#define BUFSIZE 128
#define MAXLINE 512

int getMenuList(char **list);
void freeMenuList(char **list);

int main(int argc, char **argv)
{
    int days = 1;
    int i, flinescount, specline;
    char *list[MAXLINE];

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [days, default is 1]\n", argv[0]);
        return -1;
    }
    if (argc == 2) {
        days = atoi(argv[1]);
    }
    if ((flinescount = getMenuList((char **)&list)) < 0) {
        return -1;
    }
    srand(time(NULL));
    for (i = 0; i < days; i++) {
        specline = rand() % flinescount;
        printf("[%d] %s", i+1, list[specline]);
    }
    freeMenuList(list);
    return 0;
}

/* getMenuList:  store every line of FILENAME to list, need to free outside */
int getMenuList(char **list)
{
    FILE *fp = NULL;
    char *buf = NULL;
    int i = 0;

    if ((fp = fopen(FILENAME, "r")) == NULL) {
        perror("getMenuList: fopen:");
        return -1;
    }

    while (1) {
        if ((buf = (char *)malloc(BUFSIZE * sizeof(char))) == NULL) {
            perror("getMenuList: malloc:");
            return -1;
        }
        if ((fgets(buf, BUFSIZE, fp)) == NULL)
            break;
        list[i++] = buf;
    }
    list[i] = NULL;
    fclose(fp);
    return i;
}

/* freeMenuList:  free menu list */
void freeMenuList(char **list)
{
    int i;

    for (i = 0; list[i] != NULL; i++)
        free(list[i]);
}
