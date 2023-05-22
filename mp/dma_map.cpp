//
//
//


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/uio.h>
#include <poll.h>

#define UIO_DEV "/dev/uio0"
#define BUFFER_SIZE 4096

int main() {
    int uio_fd;
    void *uio_mem;
    int dma_offset = 0;  // DMA offset within the UIO device

    // Open the UIO device file
    uio_fd = open(UIO_DEV, O_RDWR);
    if (uio_fd < 0) {
        perror("Failed to open UIO device");
        return 1;
    }

    // Map UIO device memory to user space
    uio_mem = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, uio_fd, 0);
    if (uio_mem == MAP_FAILED) {
        perror("Failed to map UIO memory");
        close(uio_fd);
        return 1;
    }

    // Configure DMA transfer
    struct uio_dmabuf dma_buf;
    dma_buf.offset = dma_offset;
    dma_buf.size = BUFFER_SIZE;

    if (ioctl(uio_fd, UIO_DMABUF_MAP, &dma_buf) < 0) {
        perror("Failed to map DMA buffer");
        munmap(uio_mem, BUFFER_SIZE);
        close(uio_fd);
        return 1;
    }

    // Start the DMA transfer
    if (ioctl(uio_fd, UIO_DMABUF_START) < 0) {
        perror("Failed to start DMA transfer");
        munmap(uio_mem, BUFFER_SIZE);
        close(uio_fd);
        return 1;
    }

    // Wait for the DMA transfer to complete
    struct pollfd pfd;
    pfd.fd = uio_fd;
    pfd.events = POLLIN;

    int poll_ret;
    do {
        poll_ret = poll(&pfd, 1, -1);
    } while (poll_ret < 0 && errno == EINTR);

    if (poll_ret < 0) {
        perror("Failed to poll for DMA completion");
        munmap(uio_mem, BUFFER_SIZE);
        close(uio_fd);
        return 1;
    }

    // Process the received data
    unsigned char *buffer = (unsigned char *)dma_buf.addr;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%02X ", buffer[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n");

    // Cleanup
    if (ioctl(uio_fd, UIO_DMABUF_UNMAP) < 0) {
        perror("Failed to unmap DMA buffer");
    }
    munmap(uio_mem, BUFFER_SIZE);
    close(uio_fd);

    return 0;
}