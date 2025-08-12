
void ft_swap_char(char *c1, char *c2) {
    *c1 ^= *c2;
    *c2 ^= *c1;
    *c1 ^= *c2;
}

