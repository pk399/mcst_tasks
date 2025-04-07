// Parses options from the command line
// Valid options: -m, -c, -s, t,
// --elbrus=[1c+, 2c+, 2c3, 4c, 8c, 16c]

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

const char* OPTSTR = "mcst";

const struct option OPTS[] =
{
    {"elbrus", 1, NULL, 'e'},
    {}
};

const char* VALID_ELBRUS[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c"};

#define ARRSZ(arr) sizeof(arr)/sizeof(arr[0])

int main(int argc, char** argv)
{
    #define GO() getopt_long(argc, argv, OPTSTR, OPTS, NULL)

    int opt = 0;

    // Check options
    while ( -1 != (opt = GO()) )
    {
        bool correct = true;

        if ( opt == ':' || opt == '?' ) correct = false;
        else if ( opt == 'e' )
        {
            correct = false;
            for (int i = 0; i < ARRSZ(VALID_ELBRUS); i++)
            {
                if ( !strcmp(optarg, VALID_ELBRUS[i]) )
                {
                    correct = true;
                }
            }
        }

        if ( !correct )
        {
            printf("Options are incorrect\n");
            return 1;
        }
    }

    // Parse options
    optind = 1;

    printf("Options are correct");    
    char prefix = ':';

    while ( -1 != (opt = GO()) )
    {
        switch (opt)
        {
            case 'm':
            case 'c':
            case 's':
            case 't':
                printf("%c %c", prefix, opt);
                break;
            case 'e':
                printf("%c elbrus=%s", prefix, optarg);
                break;
            default: // ??? should be unreachable
        }

        prefix = ',';
    }
    
    if ( optind != argc )
    {
        printf(", non-options");
        prefix = ':';

        for (int i = optind; i < argc; i++)
        {
            printf("%c %s", prefix, argv[i]);
            prefix = ',';
        }
    }

    printf("\n");
}
