//
// Created by matt on 8/9/26.
//
// connection_2.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define MY_PORT "8080"
#define BACKLOG 10

char* read_file(FILE* file, const long file_size) {
    char *html_buffer = (char *) malloc(file_size + 1);
    if (html_buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(html_buffer, 1, file_size, file);
    html_buffer[bytes_read] = '\0';

    return html_buffer;
}

int create_con() {
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC; // ipv4 or ivp6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE; //

    status = getaddrinfo(NULL, MY_PORT, &hints, &servinfo);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s:\n", gai_strerror(status));
        return -1;
    }

    int sock_fd = -1;
    struct addrinfo *res;
    int yes = 1;

    for (res = servinfo; res != NULL; res = res->ai_next) {
        sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sock_fd == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sock_fd, res->ai_addr, res->ai_addrlen) == -1) {
            close(sock_fd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);

    if (res == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        return -1;
    }

    return sock_fd;
}

int main(void) {
    char* file_name = "index.html";

    FILE* file_ptr = fopen(file_name, "rb");

    if (file_ptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    if (fseek(file_ptr, 0, SEEK_END) == -1) {
        perror("Error seeking to end of file");
        fclose(file_ptr);
        return 1;
    }

    const long file_size = ftell(file_ptr);
    if (file_size < 0) {
        perror("Error getting file size");
        fclose(file_ptr);
        return 1;
    }

    if (fseek(file_ptr, 0, SEEK_SET) == -1) {
        perror("Error seeking to start of file");
        fclose(file_ptr);
        return 1;
    }

    char *file_content = read_file(file_ptr, file_size);
    if (file_content == NULL) {
        fclose(file_ptr);
        return 1;
    }

    char *file_header = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n"
                        "Content-Length: %ld\r\n"
                        "\r\n";

    // calculate new file header size
    int new_header_size = snprintf(NULL, 0, file_header, file_size) + 1;

    char *new_file_header = (char *) malloc(new_header_size);
    if (new_file_header == NULL) {
        perror("Memory allocation failed");
        free(file_content);
        fclose(file_ptr);
        return 1;
    }

    snprintf(new_file_header, new_header_size, file_header, file_size);

    // cocat the new_file_header + file_content
    size_t total_len = (new_header_size - 1) + file_size;
    char *final_str = (char *) malloc(total_len + 1);

    if (final_str == NULL) {
        perror("Error trying to allocate memory to final string");
        free(new_file_header);
        free(file_content);
        return 1;
    }

    snprintf(final_str, total_len, "%s%s", new_file_header, file_content);
    free(new_file_header);
    free(file_content);

    // create connection
    int sock_fd = create_con();
    int is_listening = listen(sock_fd, BACKLOG);

    if (is_listening == -1) {
        perror("Failed to listen on port 8080");
        free(final_str);
        fclose(file_ptr);
        return 1;
    }

    struct sockaddr_storage their_addr;
    int new_sock_fd;
    socklen_t addr_size;

    addr_size = sizeof their_addr;
    new_sock_fd = accept(sock_fd, (struct sockaddr *) &their_addr, &addr_size);

    // read the browser request
    char request_buffer[2048];
    const ssize_t bytes_received = recv(new_sock_fd, request_buffer, sizeof(request_buffer) - 1, 0);
    if (bytes_received > 0) {
        request_buffer[bytes_received] = '\0';
        printf("The browser sent:\n%s\n", request_buffer);
    }

    // send the data
    const ssize_t bytes_sent = send(new_sock_fd, final_str, total_len,0);
    if (bytes_sent == -1) {
        perror("Failed to send data");
    } else {
        printf("Successfully sent %ld bytes to the browser!\n", bytes_sent);
    }

    // free resources
    close(new_sock_fd);
    fclose(file_ptr);
    free(final_str);
    return 0;
}