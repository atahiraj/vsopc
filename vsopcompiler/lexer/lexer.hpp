/* ----------------------------------------------------------------------------
 *
 * Small header for user's procedures
 *
 * --------------------------------------------------------------------------*/

#ifndef LEXER_H
#define LEXER_H

/*!
 * \file lexer.hpp
 * \brief Header containing some useful functions for lexical analysis.
 * \author Tahiraj Arian
 * \author Leroy Antoine
 * \version 0.1
 */

/*!
 * \brief Read a TOKEN.
 *
 * \return TOKEN : An integer representing the token.
 */
int yylex(void);

/*!
 * \brief Initialisation of the lexer.
 *
 * \param filename : The name of the file.
 */
void yylex_init(char *filename);

/*!
 * \brief Read all the TOKENs.
 *
 * \return  TOKEN if lexer correct,
 *          0 Otherwise.
 */
int yylex_dump(void);

#endif
