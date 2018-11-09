int main(int argc, char **argv)

/* Создание программного канала */

/* для команд cat и sed */

{
    /* Проверка количества параметров и получение имени файла */


    if (argc != 2 ) {
        printf("Нужно передать только один параметр - имя входного файла!\n");
        return 1;
    }

    int pid, pid2;

    int fd[2];

    int status, dead;

    switch(pid = fork())

    {

    case -1: /* Cбой при вызове fork() */

        printf("Ошибка при вызове fork() #1 \n");

        return 1;

    case 0: /* ПОТОМОК #1 */

        pipe(fd);

        switch(pid2 = fork())

        {

        case -1: /* Cбой при вызове fork() */

            printf("Ошибка при вызове fork() #2 \n");

            return 2;

        case 0: /* ПОТОМОК #2 */

            close(0); dup(fd[0]); close(fd[0]); close(fd[1]);

            execl("/usr/bin/sed", "sed", "s/^[ \t]*//", 0); // sed делает нужные преобразования с текстов после того как получен результат от cat

            puts("Ошибка при вызове SED \n");

            return 0;

        default: /* */

            close(1); dup(fd[1]);

            close(fd[1]); close(fd[0]);

            execl("/bin/cat", "cat", argv[1] ,0); // сначала вызываем cat с именем как аргументом

            puts("Ошибка при вызове cat\n");

            return 0;
        }

    default: /* ПРЕДОК ГЛАВНЫЙ */

        dead = wait(&status);

        return 0;

    }

}
