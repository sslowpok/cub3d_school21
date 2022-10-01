//
// Created by Sheryl Slowpoke on 10/1/22.
//

int	ft_strcmp(const char *s1, const char *s2)
{
    int	i;

    i = 0;
    while (s1[i] != '\0' || s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return (0);
}