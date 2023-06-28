# pipex

This project aims to deepen understanding of the two concepts of UNIX mechanism: Redirections and Pipes.

---
### Mandatory part
The program  should repeat the behaviour of the shell command

```
$> < file1 cmd1 | cmd2 > file2 
```
and looks like this:
```
$> ./pipex file1 cmd1 cmd2 file2
```


All errors like: wrong commands, permission to files and etc, need be handle.

#### Examples
``
$> ./pipex infile "ls -l" "wc -l" outfile
``
Should behave like: `< infile ls -l | wc -l > outfile`

``
$> ./pipex infile "grep a1" "wc -w" outfile
``
Should behave like: `< infile grep a1 | wc -w > outfile`

# 

### Bonus part
Program should:
#### - handle multiple pipes.

  Shell command ` $> < file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2 `

  will look like this: `$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`

#### - support << and >>, when instead of file1 ishere_doc.

  Shell command `$> cmd1 << LIMITER | cmd2 >> file2`

   will look like this: `$> ./pipex here_doc LIMITER cmd1 cmd2 file2`


---


## Launch the program

```
# Clone the project and access the folder
git clone https://github.com/maryana-la/pipex && cd pipex/

# Build project
make

# Create a file to use in program input
echo "aaaaaaaaaaaaaaaaaaaaaaa" > in_file

# Run the program like the example
./pipex "in_file" "tr a b" "tr b c" "out_file"

# Check the output file
cat output_file

---

# Run bonus part
make bonus

# Run the program like the example
./pipex "here_doc" "END" "tr a b" "tr b c" "tr c d" "output_file"

# Check the output file
cat output_file

# Clean output files with
make fclean
```
