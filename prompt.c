#include "shell.h"

/**
 * ignore_space - return string without spaces in front
 * @str: string
 * Return: new string
 */
char *ignore_space(char *str)
{
        while (*str == ' ')
                str++;
        return (str);
}

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read via get_line
 * @command: user's typed in command
 * @env: environmental variable linked list
 */
void ctrl_D(int i)
{
        if (i == 0) /* handles Ctrl+D */
        {
                if (isatty(STDIN_FILENO))/* ctrl+d prints newline */
                        write(STDOUT_FILENO, "\n", 1);
                exit(0);
        }
}

/**
 * prompt - repeatedly prompts user and executes user's cmds if applicable
 * @en: envrionmental variables
 * Return: 0 on success
 */
int prompt(char **en)
{
        list_t *env;
        size_t i = 0, n = 0;
        int command_line_no = 0, exit_stat = 0;
        char *command;

        env = env_linked_list(en);
        do {
                command_line_no++;
                if (isatty(STDIN_FILENO)) /* reprompt if in interactive shell */
                        write(STDOUT_FILENO, "$ ", 2);
                else
                        non_interactive(env);
                command = NULL; i = 0; /* reset vars each time loop runs */
                i = get_line(&command); /* read user's cmd in stdin */
                ctrl_D(i); /* exits shell if ctrl-D */
                command = ignore_space(command);
                n = 0;
                while (command[n] != '\n') /* replace get_line's \n with \0 */
                        n++;
                command[n] = '\0';
                if (command[0] == '\0') /* reprompt if user hits enter only */
                {
                        continue;
                }
        } while (1); /* keep on repeating till user exits shell */
        return (exit_stat);
}
