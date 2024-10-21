#ifndef MINISHELL_H
#define MINISHELL_H

#include "./includes/libft1/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/wait.h>

extern int last_exit_status;


//=-------------------------------------------------------parsing
typedef enum e_num
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	WHITESPACE,
	QUOTES
}						t_tokens;
// typedef struct s_env
// {
//  char   *value;
//  char  	*key;
//  struct s_env *next;
// }    t_env;

typedef struct s_lexer
{
	char				*str;
	t_tokens			tokens;
	struct s_lexer		*next;
}					t_lexer;

typedef struct s_data
{
    char *line;
    struct s_data *next;
	t_lexer		*head;
}   t_data;

typedef struct list
{
	int			content;
	struct list	*next;
}				t_list;


typedef struct s_file
{
	char				*file_name;
	t_tokens			file_type;
	// bool				quotes;
	struct s_file		*next;
}			t_file;


typedef struct s_command
{
	char				**cmd;//[0] command [1] argument
	t_file				*file;
	struct s_command	*next;
}			t_command;




typedef struct s_garbage
{
    void *ptr;
    struct s_garbage *next;

}   t_garbage;

typedef struct s_env
{
 char   *value;
 char      *key;
 struct s_env *next;
}    t_env;

typedef struct  s_shell
{
    t_env *env;
    char **env_array;
    t_garbage *garbage;
}t_shell;




//======================PARSING==================================
//===============================================================
//===============================================================
int				parsing(int ac ,char *av[], char **envr);
int				ft_isalnum_parsing(int c);
char			*ft_strjoin_parsing(char *s1, char *s2);
int				ft_isdigit_parsing(int c);
int				ft_strcmp_parsing(char *s1, char *s2);
size_t 			ft_strlen_parsing(char *str);
void			ft_putstr_fd(char *s, int fd);
void 			add_spaces(t_data *data);
char			**ft_split_parsing(char *s, char c);
t_list			*ft_lstlast_parsing(t_list *lst);
int				ft_lstsize_parsing(t_list *lst);
void			ft_lstadd_front_parsing(t_list **lst, t_list *new);
t_list			*ft_lstnew_parsing(int content);
void 			lexer(t_data *line);
void			ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);
void			ft_lstadd_back_file(t_file **lst, t_file *new);
void			ft_lstadd_back_command(t_command **lst, t_command *new);
t_lexer 		*new_lexer_node(t_tokens type,char *str);
void 			add_node(t_lexer **head, t_tokens type ,char *str);
char			*ft_strdup_parsing(char *s1);
char			*ft_substr_parsing(char *s, unsigned int start, size_t len);
char 			*add_spaces2(t_data *data) ;
int 			syntax_error(t_data *data);
void 			expand(t_lexer *lexer, t_env *env);
void			the_expandables(t_lexer **lexer, t_env *env, char **str_to_expand);
int				check_quotes_in_expand(char *str);
char			*get_key(char *str);
char			*get_value(t_env *env, char *key);
void			expand_in_heredoc(char **str, t_env *env);
void			not_expandables(t_lexer **lexer);
int				cheking_the_expand(char *str, t_env *env, int *i, char **str_to_expand);
char			*add_escape_characters(char *str);
int				after_quote(t_lexer **lexer, char **str_to_expand);
void			special_case(t_lexer *lexer, char **str_to_expand, int *i);
char			**get_key_before_expand(void);
void			special_case_in_heredoc(char *str, char **str_to_expand, int *i);
void			dollar_and_quote(char **str_to_expand, int *i);
t_command 		*parser(t_data *data);
void 			parser_works(char **command, t_lexer **head, t_file **file_name);
int 			is_redirection(t_tokens token);
void 			handle_redirection(t_lexer **head, t_file **file_name ,int redirection_type);
void 			handle_word(char **command, t_lexer **head);
char 			*handle_quotes(char *str);
int 			check_redirection(char *line);





/////////////////still for test mn hna /////////
void 			display_token_command(t_command *command);
void			display_token_lexer(t_lexer *lexer);
char			*get_token(t_tokens token);
/////////////////7tal hna ///////////////


int exec_cmd(char **arr,t_shell *shell);
int exec_built_in(char **arr,t_shell *shell);

int env_(char **args, t_shell *shell);
void free_arr(char **arr);
int echo_(char **args);
int exit_(char **args);
int pwd_(t_shell *shell);

int cd_(char **args, t_shell *shell);
int unset_(char **args, t_shell *shell);
int search_in(char *str, char c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
int	ft_strcmp(char *s1, char *s2);
char    *ft_strncpy(char *dest,  char *src, unsigned int n);


//env
t_env *create_node(char *env);
t_env *get_last_node(t_env *head);
void add_back(t_env **head ,t_env *new_content);
t_env *cp_env_in_liste(char **env, t_shell *shell);
//export
int export_(char **args, t_shell *shell);
int is_valid_identifier(char *str);
char *get_env_value(t_env *env, const char *key);


// garbage collector utiles
void free_env(t_shell *t_shell);

void	ft_grapadd_back(t_garbage **lst, t_garbage *new);
t_garbage	*ft_graplast(t_garbage *lst);
int	ft_lstsize(t_garbage **lst);
void	ft_grapadd_front(t_garbage **lst, t_garbage *new);
t_garbage	*ft_grapnew(void* content);
void ft_garbage_free(t_garbage *garbage);
// void cleanup_readline();
// int	ft_strcmp(const char *s1,const char *s2);

// pipe
void free_array(char **array);
char *find_command(char *cmd, char **env);
void set_dup(int has_pipe, int fd[2], int end);
void make_pipe(char **args, t_shell *shell);
void print_array(char **array);
void execute_command(char **args, t_shell *shell);





//redirections
// int handle_output_redirection(char **args, int *i);
// char **process_redirections(char **args, int *has_redirection);

#endif






