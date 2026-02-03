#include "cub3d.h"
#include "libft.h"

int main(int argc,char *argv[])
{
    if (argc != 2)
    {
        write(2,"Invalid number of arguments\n",28);
        return 1;
    }
    if(parse_file(argv[1]) != 0)
    {
        write(2,"Error while parsing the file\n",29);
        return 1;
    }
}