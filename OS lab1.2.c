#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct User {
    char login[8];
    char password[8];
    char* sanctions;
} User;

int numUsers = 0;
User** users = NULL;


User* createUser(const char* login, const char* password) {
    User* user = (User*)malloc(sizeof(User));
    //user->login = (char*)malloc(sizeof(char));
    //user->password = (char*)malloc(sizeof(char));
    user->sanctions = (char*)malloc(sizeof(char));
    if (user->login == NULL ||
        user->password == NULL||
        user->sanctions == NULL)
        {
            perror("Memory error\n");
        }
    strcpy(user->login, login);
    strcpy(user->password, password);
    strcpy(user->sanctions, "unlim");
    return user;
}

void freeUser(User* user) {
    //free(user->login);
    free(user->sanctions);
    free(user);
}
/*int check_len(char* value){
    int counter = 0;
    for (int i = 0; i < 100; i++)
    {
        if ( value[i] == 'k'){
            counter++;
        }
    }
    printf("%d\n", counter);
}*/
void authorization(){
    

    char login[8];
    char password[8];
    printf("Введите \"exit\", чтобы завершить программу\n");
    printf("Введите логин: ");
    fgets(login, sizeof(login), stdin);
    //check_len(login);
    
    login[strlen(login) - 1] = '\0';  

        /*if (strcmp(login, "exit") == 0) {
            break;
        }*/
    printf("Введите пароль: ");
    fgets(password, sizeof(password), stdin);
    password[strlen(password) - 1] = '\0';  
    User* newUser = createUser(login, password);
    numUsers++;
    users = (User**)realloc(users, sizeof(User*) * numUsers);
    users[numUsers - 1] = newUser;
    


    
}

int main() {
    
    authorization();
    printf("\nВсего пользователей: %d\n", numUsers);
    for (int i = 0; i < numUsers; i++) {
        printf("Пользователь %d\n", i + 1);
        printf("Логин: %s\n", users[i]->login);
        printf("Пароль: %s\n", users[i] -> password);
    }

    for (int i = 0; i < numUsers; i++) {
        freeUser(users[i]);
    }
    free(users);
    

    return 0;
}
