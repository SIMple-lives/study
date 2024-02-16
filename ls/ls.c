#include "test.c"

int main(int argc, char *argv[])
{
    int find = 0;
    int orders[8] = {0};
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            while ((find = getopt(argc, argv, "aIlrstR")) != -1)
            {
                switch (find)
                {
                case 'a':
                    orders[a] = 1;
                    break;
                case 'r':
                    orders[r] = 1;
                    break;
                case 's':
                    orders[s] = 1;
                    break;
                case 't':
                    orders[t] = 1;
                    break;
                case 'l':
                    orders[l] = 1;
                    break;
                case 'R':
                    orders[R] = 1;
                    break;
                case 'I':
                    orders[I] = 1;
                    break;
                default:
                    fprintf(stderr, "Invalid option\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    int countfile = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            countfile++;
        }
    }

    if (countfile == 0)
    {
        char current_path[MAX_PATH];
        if ((getcwd(current_path, MAX_PATH)) != NULL)
        {
            if (orders[R] == 0)
            {
                do_open(current_path, orders);
            }
            else
            {
                do_open_R(current_path, orders);
            }
        }
        else
        {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            if (countfile > 1)
            {
                printf("%s\n", argv[i]);
            }
            if (orders[R] == 0)
            {
                do_open(argv[i], orders);
            }
            else
            {
                do_open_R(argv[i],orders);
            }
        }
    }
}

