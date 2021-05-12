#include "includes/libft.h"
#include "includes/minishell.h"

// int main(void)
// {
// 	char str[] = "truc";
// 	char buff[100];
// 	int	tab[2];
// 	int stdin_copy = dup(0);
// 	int stdout_copy = dup(1);
// 	close(0);
// 	close(1);
	
// 	pipe(tab);
// 	write(1, str, strlen(str));
// 	buff[read(0, buff, 99)] = 0;
// 	dprintf(stdout_copy, "%s\n", buff);
// 	dup2(stdin_copy, 0);
// 	dup2(stdout_copy, 1);
// 	close(stdin_copy);
// 	close(stdout_copy);
// 	dprintf(1, "%d %d\n", tab[0], tab[1]);
// }

int main (int argc, char ** argv) {
    int i;

    for( i=1; i<argc-1; i++)
    {
        int pd[2];
        pipe(pd);

        if (!fork()) {
            dup2(pd[1], 1); // remap output back to parent
            execlp(argv[i], argv[i], NULL);
            perror("exec");
            abort();
        }

        // remap output from previous child to input
        dup2(pd[0], 0);
        close(pd[1]);
        close(pd[0]);
    }

    execlp(argv[i], argv[i], NULL);
    perror("exec");
    abort();
}