/*
    File:    fsize.h
    Author:  Гаврилов Владимир Сергеевич
    Created: 06 August 2015, 10:06
    e-mails: vladimir.s.gavrilov@gmail.com,
             gavrilov.vladimir.s@mail.ru,
             gavvs1977@yandex.ru
*/

#ifndef FSIZE_H
#define FSIZE_H
#include <cstdio>
/**
 * \param [in] fptr  the file pointer
 * \return           a) (-1), if fptr == NULL
 *                   b) the size of the file in bytes, otherwise
 */
long fsize(FILE* fptr);
#endif