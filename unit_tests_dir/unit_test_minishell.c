/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** unit_test_minishell
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

//Test(my_printf, simple_string, .init = redirect_all_std)
//{
//    my_printf("Hello World");
//    cr_assert_stdout_eq_str("Hello World");
//}
//
//Test(my_printf, str_format, .init = redirect_all_std)
//{
//    my_printf("The string is here: %s","im here");
//    cr_assert_stdout_eq_str("The string is here: im here");
//}
//
//Test(my_printf, c_spec, .init = redirect_all_std)
//{
//    my_printf("%c",'a');
//    cr_assert_stdout_eq_str("a");
//}
//
//Test(my_printf, cap_f_spec, .init = redirect_all_std)
//{
//    my_printf("%f",5.0);
//    cr_assert_stdout_eq_str("5.000000");
//}
//
//Test(my_printf, cap_x_spec, .init = redirect_all_std)
//{
//    my_printf("%X",10);
//    cr_assert_stdout_eq_str("A");
//}
//
//Test(my_printf, x_spec, .init = redirect_all_std)
//{
//    my_printf("%x",10);
//    cr_assert_stdout_eq_str("a");
//}
//
//Test(my_printf, a_spec, .init = redirect_all_std)
//{
//    my_printf("%a",5.0);
//    cr_assert_stdout_eq_str("0x1.4000000000000p+2");
//}
//
//Test(my_printf, d_spec, .init = redirect_all_std)
//{
//    my_printf("%d",500);
//    cr_assert_stdout_eq_str("500");
//}
//
//Test(my_printf, e_spec, .init = redirect_all_std)
//{
//    my_printf("%.2e",123.0);
//    cr_assert_stdout_eq_str("1.23e+02");
//}
//
//Test(my_printf, cap_e_spec, .init = redirect_all_std)
//{
//    my_printf("%E",123.0);
//    cr_assert_stdout_eq_str("1.230000E+02");
//}
//
//Test(my_printf, percent_spec, .init = redirect_all_std)
//{
//    my_printf("%%");
//    cr_assert_stdout_eq_str("%");
//}
//
//Test(my_printf, f_spec, .init = redirect_all_std)
//{
//    my_printf("%f", 5.0);
//    cr_assert_stdout_eq_str("5.000000");
//}
//
//Test(my_printf, cap_g_spec, .init = redirect_all_std)
//{
//    my_printf("%G", 5.0);
//    cr_assert_stdout_eq_str("5");
//}
//
//Test(my_printf, g_spec, .init = redirect_all_std)
//{
//    my_printf("%g",50000000.0);
//    cr_assert_stdout_eq_str("5e+07");
//}
//
//Test(my_printf, o_spec, .init = redirect_all_std)
//{
//    my_printf("%o", 5);
//    cr_assert_stdout_eq_str("5");
//}
//
//Test(my_printf, u_spec, .init = redirect_all_std)
//{
//    my_printf("%u", 5);
//    cr_assert_stdout_eq_str("5");
//}
