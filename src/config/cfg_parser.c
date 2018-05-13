
/** input configure file 
 * parse the input and generate cfg.h file use for the project
 * if use static method also generate global.c file
 */

void usage(char *argv)
{
    printf("usage:\n"
            "%s [configure file]\r\n"
            basename(argv));
}

int main(int argc, char *argv[])
{
    FILE *file = NULL;

    if ( 2 != argc ) 
    {
        usage(argv[0]);
        return 0;
    }

    file = fopen(argv[1], "r");
    if ( NULL == file ) 
    {
        printf("%s\n", strerror(errno));
        return -1;
    }
    
    return 0;
}
