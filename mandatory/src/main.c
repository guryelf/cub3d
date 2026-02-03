#include "cub3d.h"
#include "libft.h"

int main(int argc,char *argv[])
{
    if (argc != 2)
    {
        write(2,"Invalid number of arguments\n",28);
        return 1;
    }
    if(!ft_strchr(argv[1],'.'))
    {
        write(2,"Invalid file\n",13);
        return 1;
    }
    if(ft_strncmp(ft_strrchr(argv[1],'.'),".cub",4) != 0)
    {
        write(2,"Invalid file\n",13);
        return 1;
    }
}