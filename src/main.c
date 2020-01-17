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

#define PROGRAM_NAME "password"

#define DEFAULT_LENGTH (16)
#define DEFAULT_NUMBER (1)

void printProgramVersion() {
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
            fprintf(stderr, "Invalid argument: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    /* Reset errno before calling malloc */
    errno = 0;

    /** This is the buffer that will be used to store the generated passwords */
    char* buffer = malloc(length * sizeof (char));

    /* Make sure the buffer was allocated successfully */
    if (buffer == NULL) {
        if (errno == ENOMEM) {
            /** Calls to malloc can fail with this error code if the
             *  application hits the RLIMIT_AS or RLIMIT_DATA limits.
             * 
             *  See getrlimit(2)
             */
            fprintf(stderr, "[Error] %s\n", strerror(errno));
        } else {
            /** If errno does not equal ENOMEM, the user must have requested a
             *  password of length zero. Malloc will return NULL successfully
             *  after allocating the requested zero bytes. Simply tell the user
             *  what they did and return with a successful exit status.
             */
            fprintf(stderr, "Did you mean to request a password of zero length?\n");
            exit(EXIT_SUCCESS);
        }
    }

    for (size_t i = 0; i < number; ++i) {
        /* Reset the buffer */
        memset(buffer, 0, length);

        /* Reset errno before calling getrandom */
        errno = 0;

        /* Populate the buffer with cryptographically-strong random bytes */
        ssize_t bytes_received = getrandom(buffer, length, 0);

        /* Make sure the call to getrandom succeeded */
        if (bytes_received == -1) {
            switch (errno) {
                /** This is the error code returned by the kernel if the 
                 *  system lacked sufficient entropy to handle the request.
                 *  To prevent this error, the GRND_NONBLOCK flag must not
                 *  be set, or /dev/urandom must be called instead of
                 *  /dev/random. This is the recommended practice anyways,
                 *  as per the kernel documentation.
                 *
                 */
                case EAGAIN: {
                    /** This can be salvaged by simply calling getrandom again
                     *  for the remaining bytes in the buffer.
                     */
                    // TODO: Handle this error properly.
                } break;

                /** This error is essentially a segmentation fault; the 
                 *  address specified in the call to getrandom is outside
                 *  of the accessible address space.
                 *
                 */
                case EFAULT: {
                    /** This error will be triggered if the call to malloc
                     *  to allocate the buffer fails, which can occur if the
                     *  length of the password requested exceeds the heap size
                     *  allowed by the kernel. This error is therefore
                     *  categorically unsalvageable.
                     * 
                     *  Simply display error information and exit.
                     * 
                     */
                    fprintf(stderr, "[Error] %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                } break;

                /* The call was interrupted by a signal handler */
                case EINTR: {
                    // TODO: handle
                } break;

                /** This error is triggered by an invalid flag argument in the
                 *  call to getrandom.
                 */
                case EINVAL: {
                    // TODO: handle
                } break;

                /** This error is triggered if the GNU C library determines
                 *  that the current kernel does not implement the getrandom
                 *  system call, which was introduced in kernel version 3.17
                 *  and glibc version 2.25.
                 *
                 */
                case ENOSYS: {
                    /** There is no good way to recover from this error. While
                     *  intel processors since Ivy Bridge have a built-in
                     *  random number generator via the RDRAND instruction,
                     *  incorporating a hardware dependency like that seems
                     *  like a non-solution because if a user has a processor
                     *  from at least 2012, chances are they wouldn't run into
                     *  the ENOSYS error in the first place.
                     * 
                     *  For now simply display error information and exit.
                     */
                    fprintf(stderr, "[Error] %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                } break;
            }
        }

        /** Since the 'char' data type is signed, we have to iterate over the
         *  character buffer and correct the values, making sure they fit in
         *  the range 33-126. The 32 is a space and 127 is the DEL (delete)
         *  control character in ASCII, so normalizing the output to values
         *  between 32 and 127 makes sure the output is very random, but only
         *  printable characters are used.
         * 
         */
        for (size_t j = 0; j < length; ++j) {
            if (buffer[j] < 0) {
                buffer[j] += 127;
            }

            if (buffer[j] < 33) {
                buffer[j] += 33;
            }
        }

        /* Output the generated password */
        printf("%s\n", buffer);
    }

    return EXIT_SUCCESS;
}
