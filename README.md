# EvIBM

This program is a scientific iniciation project. It simulates an Individual Based Model created by Marcus Aguiar (Aguiar _et al_, 2009). The project is funded by FAPESP - Fundação de apoio a pesquisa do estado de São Paulo.

## Notes by Juan
Comments were added in the syntax of [CriticMarkup][critic]. You can find a
reference for the syntax (it's very minimal) in the [Github page][github]. In
there you'll also find plugins for the Sublime editor, though I'd highly suggest
you use [the Vim plugin][vim] that, in addition, allows you to quickly accept or
reject changes.

[critic]: http://criticmarkup.com/
[github]: https://github.com/CriticMarkup/CriticMarkup-toolkit.git
[vim]: https://github.com/vim-pandoc/vim-criticmarkup.git

## How to compile
```bash
$ gcc main.c -o out
$ ./out
```
### With make
After cloning the folder, go in it and compile with the command
```bash
$ make
```
If you need, here's how to install make
```bash
$ sudo apt install build.essentials
```
## At this point
I cannot make libraries. I have to test and tidy up the code, but I just don't know where to start this.  

## References

DE AGUIAR, Marcus Aloizo Martinez et al. Global patterns of speciation and diversity. **Nature**, v. 460, n. 7253, p. 384-387, 2009.
