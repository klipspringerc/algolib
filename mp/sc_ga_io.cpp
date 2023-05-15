//
// Scatter-gather IO example
//
#include "io.h"

int scgt_write() {
    int fd;
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
    char  buf[3][60] = {
            "The term buccaneer comes from the word boucan.\n",
            "A boucan is a wooden frame used for cooking meat.\n",
            "Buccaneer is the West Indies name for a pirate.\n" };
    if (fd == -1) {
        perror("open failed");
        return 1;
    }
    printf("got fd value %d \n", fd);
    iovec iov[3];
    ssize_t  nr;
    for (int i=0; i < 3; i++) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]) +1;
    }
    nr = writev(fd, iov, 3);
    if (nr == -1) {
        perror("writev failed");
        return 1;
    }
    printf("wrote %lu bytes \n", nr);
    if (close(fd)) {
        perror("close failed");
        return 1;
    }
    return 0;
}

int read() {
    iovec iov[3];
    ssize_t  nr;
    return 0;
}

//int main() {
//    return scgt_write();
//}
