#include <stdio.h>
#include <stdlib.h>

static int compareVersioin(char *v1, char *v2)
{
    int ret = 0;
    while (*v1 != '\0' || *v2 != '\0') {
        while (*v1 != '\0' && *v1 == '0') {
            v1++;
        }
        while (*v2 != '\0' && *v2 == '0') {
            v2++;
        }

        int n1 = 0;
        while (*v1 != '\0' && *v1 != '.') {
            n1 = n1 * 10 + (*v1 - '0');
            v1++;
        }

        int n2 = 0;
        while (*v2 != '\0' && *v2 != '.') {
            n2 = n2 * 10 + (*v2 - '0');
            v2++;
        }

        ret = n1 - n2;
        if (ret != 0) {
            return ret > 0 ? 1 : -1;
        }

        if (*v1 == '.') {
            v1++;
        }
        if (*v2 == '.') {
            v2++;
        }
    }
    return ret;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test versioin1 version2\n");
        exit(-1);
    }
    printf("%d\n", compareVersioin(argv[1], argv[2]));
    return 0;
}
