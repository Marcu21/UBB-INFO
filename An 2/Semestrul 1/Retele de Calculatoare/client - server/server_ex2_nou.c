#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <arpa/inet.h>

int sem_id;
int *max_ever;
int udp_sock;
struct sockaddr_in udp_addr;

void sem_lock(int sem_id) {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;
    semop(sem_id, &op, 1);
}

void sem_unlock(int sem_id) {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;
    semop(sem_id, &op, 1);
}

int calculate_lcm(int a, int b) {
    int temp_a = a, temp_b = b;
    while (temp_b != 0) {
        int temp = temp_b;
        temp_b = temp_a % temp_b;
        temp_a = temp;
    }
    return a * (b / temp_a);
}

void handle_client(int c) {
    int count, max = 0;
    recv(c, &count, sizeof(count), 0);
    //count = ntohl(count);
    printf("Count este: %d\n", count);
    int numbers[count];
    recv(c, numbers, sizeof(numbers), 0);

    for (int i = 0; i < count; i++) {
	//numbers[i] = ntohl(numbers[i]);
	printf("%d\n", numbers[i]);
        if (numbers[i] > max) max = numbers[i];
    }

    struct sockaddr_in parent_addr;
    socklen_t addr_len = sizeof(parent_addr);
    getpeername(c, (struct sockaddr *)&parent_addr, &addr_len);

    sendto(udp_sock, &max, sizeof(max), 0, (struct sockaddr *)&udp_addr, sizeof(udp_addr));

    int lcm = calculate_lcm(max, *max_ever);
    lcm = htonl(lcm);
    write(c, &lcm, sizeof(lcm));
    close(c);
}


int main() {
    int s, c;
    struct sockaddr_in server, client;
    socklen_t l;

    // Initialize semaphore and shared memory
    sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    semctl(sem_id, 0, SETVAL, 1);
    int shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    max_ever = (int *)shmat(shm_id, NULL, 0);
    *max_ever = 0;

    // Setup UDP socket for receiving max values from children
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(12345);
    udp_addr.sin_addr.s_addr = INADDR_ANY;
    bind(udp_sock, (struct sockaddr *)&udp_addr, sizeof(udp_addr));

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Error creating server TCP socket");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Error binding TCP socket");
        return 1;
    }

    listen(s, 5);
    
    int received_max;
    while (1) {
        l = sizeof(client);
        c = accept(s, (struct sockaddr *) &client, &l);
        if (c < 0) {
            perror("Error accepting connection");
            continue;
        }
        if (fork() == 0) { // child process for TCP connection
            handle_client(c);
            return 0;
        }
        close(c);
        
        // Parent process to handle UDP reception and max ever updating
        if (recv(udp_sock, &received_max, sizeof(received_max), 0) > 0) {
            sem_lock(sem_id);
            if (received_max > *max_ever) {
                *max_ever = received_max;
            }
            sem_unlock(sem_id);
        }
    }

    return 0;
}
