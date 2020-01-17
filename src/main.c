/** 
 *  password v1.0.0 Cryptographically-secure password utility
 *  Copyright (C) 2020 Jose Fernando Lopez Fernandez
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "password.h"

static void printProgramVersion() {
    printf("%s version %d.%d.%d\n", PROGRAM_NAME, 1, 0, 1);
}

int main(int argc, char *argv[])
{
    /* Length of the passwords to be generated */
    size_t length = DEFAULT_LENGTH;

    /* Number of passwords to generate */
    size_t number = DEFAULT_NUMBER;

    /* Process command-line arguments */
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            printProgramVersion();
            printf("Generate cryptographically secure passwords\n");
            printf("Usage:\n\t%s [--length N] [--number N]\n", PROGRAM_NAME);
            printf("\t%s [-L N] [-N N]\n", PROGRAM_NAME);
            exit(EXIT_SUCCESS);
        } else if (!strcmp(argv[i], "--version")) {
            printProgramVersion();
            exit(EXIT_SUCCESS);
        } else if (!strcmp(argv[i], "--length") || !strcmp(argv[i], "-L")) {
            /** Make sure there is another argument after this one still,
             *  otherwise the user did not actually provide an actual length
             *  parameter.
             *
             */
            if (i == (argc - 1)) {
                fprintf(stderr, "Error: length parameter expected\n");
                exit(EXIT_FAILURE);
            }
            
            /* The pointer to the first non-numeric digit character */
            char** endptr = &(argv[++i]);

            /* Set the length to the user-specific setting */
            length = strtoul(argv[i], endptr, 10);

            /** Validate the result of the strtoul function call by checking
             *  whether the endptr variable equals '\0', meaning that the
             *  entire string in argv[i] was a valid numeric digit except for
             *  the null-terminator, to which the endptr now points.
             */
            if (**endptr != '\0') {
                fprintf(stderr, "Error: Invalid argument\n");
                exit(EXIT_FAILURE);
            }
        } else if (!strcmp(argv[i], "--number") || !strcmp(argv[i], "-N")) {
            /** Make sure there is another argument after this one still,
             *  otherwise the user did not actually provide an actual number
             *  parameter.
             *
             */
            if (i == (argc - 1)) {
                fprintf(stderr, "Error: number parameter expected\n");
                exit(EXIT_FAILURE);
            }
            
            /* The pointer to the first non-numeric digit character */
            char** endptr = &(argv[++i]);

            /* Set the number of strings to generate to the user-specific setting */
            number = strtoul(argv[i], endptr, 10);

            /** Validate the result of the strtoul function call by checking
             *  whether the endptr variable equals '\0', meaning that the
             *  entire string in argv[i] was a valid numeric digit except for
             *  the null-terminator, to which the endptr now points.
             */
            if (**endptr != '\0') {
                fprintf(stderr, "Error: Invalid argument\n");
                exit(EXIT_FAILURE);
            }
        } else {
            /** If we detect an invalid command-line argument, exit with an
             *  error status and print the offending argument.
             */
            fprintf(stderr, "Invalid argument: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    /* Generate the random strings */
    char** random_strings = generateRandomStrings(length, number);

    /** Iterate over the random string array and print each string. As we pass
     *  through each string, free the string after printing it.
     */
    for (size_t i = 0; i < number; ++i) {
        printf("%s\n", random_strings[i]);
        free(random_strings[i]);
    }

    /* Free the random strings array container */
    free(random_strings);

    return EXIT_SUCCESS;
}
