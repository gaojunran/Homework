#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PATH_MAX 1024
#define BUFSIZ 8192

// eprintf and exit wrapper
void fatal(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

// Check if path is a file
int is_file(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) return 0;
    return S_ISREG(st.st_mode);
}

// Check if path is a directory
int is_dir(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) return 0;
    return S_ISDIR(st.st_mode);
}

// Convert to absolute path
// TODO: a better solution
char *to_abs_path(const char *path, char *resolved_path) {
    if (path[0] != '/') {
        // relative path
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            snprintf(resolved_path, 1028, "%s/%s", cwd, path);
        } else {
            perror("getcwd");
            exit(1);
        }
    } else {
        // absolute path
        strncpy(resolved_path, path, 1024);
    }
    return resolved_path;
}

// Get file name from path
const char *get_file_name(const char *path) {
    const char *slash = strrchr(path, '/');
    return slash ? slash + 1 : path;
}

// Copy file from src to dest
void copy_file(const char *src, const char *dest) {
    char abs_src[PATH_MAX], abs_dest[PATH_MAX];
    to_abs_path(src, abs_src);
    to_abs_path(dest, abs_dest);

    if (!is_file(src)) {
        fprintf(stderr, "File %s does not exist\n", src);
        exit(1);
    }

    if (strcmp(abs_src, abs_dest) == 0) {
        fprintf(stderr, "File %s is tried to be copied to itself\n", src);
        exit(1);
    }

    if (is_file(dest)) {
        printf("File %s already exists. Overwrite? [y/n] ", src);
        char ch = getchar();
        if (ch != 'y' && ch != 'Y') {
            printf("Skipping file %s.\n", src);
            return;
        }
        while (getchar() != '\n'); // flush stdin
    }

    int in_fd = open(src, O_RDONLY);
    if (in_fd < 0) {
        perror("open src");
        exit(1);
    }

    int out_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd < 0) {
        perror("open dest");
        close(in_fd);
        exit(1);
    }

    // Buffered copy loop
    char buf[BUFSIZ];
    ssize_t bytes;
    while ((bytes = read(in_fd, buf, BUFSIZ)) > 0) {
        if (write(out_fd, buf, bytes) != bytes) {
            perror("write");
            close(in_fd);
            close(out_fd);
            exit(1);
        }
    }

    if (bytes < 0) {
        perror("read");
    }

    close(in_fd);
    close(out_fd);
}

// Copy multiple files to a destination directory
void copy_files(int file_count, char **files, const char *destination) {
    if (!is_dir(destination)) {
        fatal("Destination is not a directory");
    }

    for (int i = 0; i < file_count; i++) {
        const char *src = files[i];
        const char *filename = get_file_name(src);
        char dest_path[PATH_MAX];
        snprintf(dest_path, sizeof(dest_path), "%s/%s", destination, filename);
        copy_file(src, dest_path);
    }
    printf("Files successfully copied to %s\n", destination);
}

// Move multiple files to a destination directory
void move_files(int file_count, char **files, const char *destination) {
    if (!is_dir(destination)) {
        fatal("Destination is not a directory");
    }

    for (int i = 0; i < file_count; i++) {
        const char *src = files[i];
        const char *filename = get_file_name(src);
        char dest_path[PATH_MAX];
        snprintf(dest_path, sizeof(dest_path), "%s/%s", destination, filename);

        // Try hard link first
        if (link(src, dest_path) != 0) {
            perror("link");
            printf("Copying %s instead.\n", src);
            copy_file(src, dest_path);
        }

        // Remove original
        if (unlink(src) != 0) {
            perror("unlink");
            exit(1);
        }
    }
    printf("Files successfully moved to %s\n", destination);
}

// Entry point
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s source1 [source2 ...] destination\n", argv[0]);
        exit(1);
    }

    const char *progname = get_file_name(argv[0]);

    if (strstr(progname, "copy")) {
        copy_files(argc - 2, &argv[1], argv[argc - 1]);
    } else if (strstr(progname, "move")) {
        move_files(argc - 2, &argv[1], argv[argc - 1]);
    } else {
        fatal("Invalid program name, must contain 'copy' or 'move'");
    }

    return 0;
}
