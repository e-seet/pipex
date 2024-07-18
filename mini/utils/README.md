# Test command for redirections

## Create / Rewrite the whole file

echo "Hello, world!" > output.txt

## This appends to the file

echo "Additional text." >> output.txt

## Reads from the file

cat < input.txt

cat << EOF

## To do

1. env variables
2. Edge cases
3. formatting

Check why if i press up key after read doc it will seg fault. Is it due to read line or what.

1. Don't have to handle semicolon
2. Check the following:
$world=./var/env

'"$world"' should return the env: ./var/env

''$world'' does not

3.This returns /usr/eddieseet

echo $HOME
echo "$HOME"
echo "'$HOME'"

returns '$HOME'
echo '$HOME'
echo '"$HOME"'

Have yet to use. To find out

readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork,
signal, sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, execve,
dup, dup2, pipe,getenv,

wait, waitpid, wait3, wait4,
opendir, readdir, closedir,
strerror, perror,

isatty, ttyname, ttyslot, ioctl,
stat, lstat, fstat, unlink,
tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs

 Note:

 1. argv[0] and argv[1] may have issues due to parsing
 2. mini->path may have issues as well due to the nature of parsing

 These needs to be checked

echo << eof > output.txt