/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelelz <aelelz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:52:01 by aelelz            #+#    #+#             */
/*   Updated: 2024/11/22 16:49:34 by aelelz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		ft_checker(const char str, va_list args);
void	ft_point(unsigned long long num);
int		ft_point_count(unsigned long long num);
int		ft_print_point(unsigned long long num);
int		ft_putchar(int c);
int		ft_put_nbr(int nb);
int		ft_putstr(char *s);
int		ft_print_unsigned(unsigned int num);
int		ft_print_hex(unsigned int num, const char format);
void	ft_print_digit(unsigned int num, const char format);
int		ft_hex_count(unsigned int num);

#endif