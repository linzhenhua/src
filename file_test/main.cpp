#include <cstdio>
#include <cstring>

int main()
{
    FILE *fp = fopen("111.txt", "w");
    if (!fp)
    {
        printf("Save failed.");
        return 0;
    }

    int val = 1306;
    //int val = 1400;
    unsigned char buf[6] = { 0 };
    memcpy(&buf[1], &val, sizeof(int));

    //printf("buf: %s\n", buf);

    fwrite(buf, sizeof(char), 6, fp);
    fclose(fp);

    fp = fopen("111.txt", "rb");
    if (!fp)
    {
        printf("Open failed.");
        return 0;
    }

    char c = 0;
    int rval = 0;
    int ret1 = fread(&c, 1, 1, fp);
    int ret2 = fread(&rval, 4, 1, fp);

    printf("%d %d %d %d\n", ret1, ret2, feof(fp) ? 1 : 0, ferror(fp) ? 1 : 0);
    printf("%d %d\n", c, rval);

    fclose(fp);

    return 0;
}
